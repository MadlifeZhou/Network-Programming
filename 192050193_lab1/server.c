#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_COUNT_CLIENTS 100


int main(int argc, char *argv[])
{
    /**
     * 1. 知道从哪个主机来
     * 2. 发送给所有主机
     * 3. 所有的主机接受
     * 4. 打印主机名字+时间
     */
    int clients[MAX_COUNT_CLIENTS];
    char is_active[MAX_COUNT_CLIENTS];


    int sockfd, newsockfd;
    uint16_t portno;
    unsigned int clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *)&serv_addr, sizeof(serv_addr));

    // define the port of server
    portno = 5001;

    // initial server addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // 任何地址可以访问
    serv_addr.sin_port = htons(portno); // port is 5001

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {

        perror("ERROR on binding");

        exit(1);
    }

    while(1) {
        /* Now start listening for the clients, here process will
         * *  go in sleep mode and will wait for the incoming connection
         * */

        listen(sockfd, 5);
        clilen = sizeof(cli_addr);

        /* Accept actual connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        printf("IP is %s\n", inet_ntoa(cli_addr.sin_addr));

        printf("Port is %d\n", htons(cli_addr.sin_port));

        /* If connection is established then start communicating */
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255); // recv on Windows

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("newsockfd:%d\n", newsockfd);

        printf("Here is the message: %s\n", buffer);

        /* Write a response to the client */
        n = write(newsockfd, "I got your message", 18); // send on Windows


        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }
    return 0;
}