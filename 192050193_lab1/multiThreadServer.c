#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define MAX_COUNT_CLIENTS 100

int clients[MAX_COUNT_CLIENTS];
int count = 0;

void *client_handler(void *indexp) {

    int index = *(int *) indexp;
    char buf_rcv[255] = {};
    char buf_snd[255] = {};

    //read the name of client
    char name[20] = {};
    int ret = read(clients[index], name, sizeof(name));

    // localtime

    // current time
    int hour;
    int min;

    if (0 > ret) {
        perror("recv error");
        close(clients[index]);
        exit(1);
    }

    while (1) {
        bzero(buf_rcv, sizeof(buf_rcv));
        read(clients[index], buf_rcv, sizeof(buf_rcv));
        if (strlen(buf_rcv)>0) {
            time_t t = time(NULL);
            struct tm *lt = localtime(&t);
            hour = lt->tm_hour;
            min = lt->tm_min;
            sprintf(buf_snd, "{%d:%d}[%s]:%s", hour, min, name, buf_rcv);
            printf("%s\n", buf_snd);
            for (int i = 0; i <= count; i++) {
                if (i == index || 0 == clients[i]) {
                    continue;
                }
                send(clients[i], buf_snd, sizeof(buf_snd), 0);
            }
        }
    }
}


int main(int argc, char *argv[]) {
    /**
     * 1. 知道从哪个主机来
     * 2. 发送给所有主机
     * 3. 所有的主机接受
     * 4. 打印主机名字+时间
     */

    char is_active[MAX_COUNT_CLIENTS];


    int sockfd, newsockfd;
    uint16_t portno;
    unsigned int clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t n;
    // control the count

    clilen = sizeof(cli_addr);
    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    // define the port of server
    portno = 5001;

    // initial server addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // 任何地址可以访问
    serv_addr.sin_port = htons(portno); // port is 5001

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {

        perror("ERROR on binding");

        exit(1);
    }


    /* Now start listening for the clients, here process will
     * *  go in sleep mode and will wait for the incoming connection
     * */

    listen(sockfd, 5);

    int index = 0;

    while (1) {
        /* Accept actual connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        clients[count] = newsockfd;
        // 获得其存储地址
        index = count;
        count++;

        pthread_t thread_id;
        int ret = pthread_create(&thread_id, NULL, client_handler, &index);
        if (ret < 0) {
            perror("pthread_create");
            return -1;
        }
//        pthread_detach(thread_id);
    }

}