#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

int sockfd;

void *recv_other(void *arg) {
    char buf[255] = {};
    while (1) {
        int ret = read(sockfd, buf, sizeof(buf));
        if (0 > ret) {
            perror("error occurs while receiving messages from server");
            exit(1);
        }
        if (strlen(buf) > 0) {
            printf("%s\n", buf);
        }
        bzero(buf,255);
    }
}

int main(int argc, char *argv[]) {
    int n;
    uint16_t portno;
    // define server address
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char *clientName;
    char buffer[256];
    char mode;


    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    // command line:  ./client2 127.0.0.1 5001 client1
    // get the address of server
    server = gethostbyname(argv[1]);
    // get the port of server
    portno = (uint16_t) atoi(argv[2]);
    // define the name of client
    clientName = argv[3];

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* if doesn`t create successfully*/
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // initial the server
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *) &serv_addr.sin_addr.s_addr, (size_t) server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    int ret = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        perror("ERROR connecting");
        return -1;
    }

    /* send clientName to server*/
    ret = write(sockfd, clientName, strlen(clientName));
    if (0 > ret) {
        perror("connect");
        return -1;
    }

    pthread_t tid;
    ret = pthread_create(&tid, NULL, recv_other, NULL);
    if (0 > ret) {
        perror("pthread_create");
        return -1;
    }
//    pthread_detach(tid);

    while (1) {
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        char *a = "m";
        bool enter = strcmp(buffer, a);

        if (enter) {
            printf("Please enter the message: \n");
            bzero(buffer, 256);
            fgets(buffer, 255, stdin);

            /* Send message to the server */
            n = write(sockfd, buffer, strlen(buffer));

            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }

    }


    return 0;
}