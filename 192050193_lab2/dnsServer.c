#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include "dns_protocol.h"

char dns_servers[1][16]; //存放DNS服务器的IP


#define A 1 // Search for IPv4 address

char *ngethostbyname(unsigned char *, int);

void ChangetoDnsNameFormat(unsigned char *, unsigned char *);


int main(int argc, char *argv[]) {
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
    serv_addr.sin_addr.s_addr = INADDR_ANY;
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
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    while(1) {
        /* If connection is established then start communicating */
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255); // recv on Windows

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        /**
         *   ===============================================================================
         *   request the public dns server
         */

        char hostname[100];
        char dns_servername[100] = "223.5.5.5";

        // delete '\n' from the input string
        for (int i = 0; i < strlen(buffer); ++i) {
            if (buffer[i] == '\n') {
                strncpy(hostname, buffer, i);
            }
        }
        strcpy(dns_servers[0], dns_servername);
        // *hostname = 'www.google.com';

        // 由域名获得IPv4地址，A是查询类型
        char *ipAddr = ngethostbyname(hostname, A);
        printf("the IPv4 Address is : %s \n", ipAddr);

        // send the ipv4 address to client
        n = write(newsockfd, ipAddr, strlen(ipAddr));
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }
    return 0;
}

/*
**  User DNS Server to parse URL
*/
char *ngethostbyname(unsigned char *host, int query_type) {
    char buf[65536], *qname, *reader;
    int i, j, s;

    struct sockaddr_in a; //Address

    struct RES_RECORD answers[20]; //  Answer Area 回答区域、授权区域、附加区域中的资源数据字段
    struct sockaddr_in dest; //Address

    struct DNS_HEADER *dns = NULL;
    struct QUESTION *qinfo = NULL;

    printf("\n the url you need to parse：%s", host);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //建立分配UDP套结字

    dest.sin_family = AF_INET; //IPv4
    dest.sin_port = htons(53); //53号端口
    dest.sin_addr.s_addr = inet_addr(dns_servers[0]); //DNS服务器IP

    dns = (struct DNS_HEADER *) &buf;
    /*设置DNS报文首部*/
    dns->id = (unsigned short) htons(getpid()); //id设为进程标识符
    dns->qr = 0; //查询
    dns->opcode = 0; //标准查询
    dns->aa = 0; //不授权回答
    dns->tc = 0; //不可截断
    dns->rd = 1; //期望递归
    dns->ra = 0; //不可用递归
    dns->z = 0; //必须为0
    dns->ad = 0;
    dns->cd = 0;
    dns->rcode = 0;//没有差错
    dns->q_count = htons(1); //1个问题
    dns->ans_count = htons(1);
    dns->auth_count = 0;
    dns->add_count = 0;

    //qname指向查询问题区域的查询名字段
    qname = (unsigned char *) &buf[sizeof(struct DNS_HEADER)];

    ChangetoDnsNameFormat(qname, host);//修改域名格式
    qinfo = (struct QUESTION *) &buf[sizeof(struct DNS_HEADER)
                                     + (strlen((const char *) qname) + 1)]; //qinfo指向问题查询区域的查询类型字段

    qinfo->qtype = htons(query_type); //查询类型为A
    qinfo->qclass = htons(1); //查询类为1

    //向DNS服务器发送DNS请求报文
    printf("\n\n Send Data to Public DNS Server...");
    if (sendto(s, (char *) buf,
               sizeof(struct DNS_HEADER) + (strlen((const char *) qname) + 1) + sizeof(struct QUESTION), 0,
               (struct sockaddr *) &dest, sizeof(dest)) < 0) {
        perror("Send error！");
    }
    printf("Send successfully ！");

    //从DNS服务器接受DNS响应报文
    i = sizeof dest;
    printf("\n Receiving Message...");
    if (recvfrom(s, (char *) buf, 65536, 0, (struct sockaddr *) &dest, (socklen_t *) &i) < 0) {
        perror("Receive error !");
    }
    printf("Receive Successfully !");

    dns = (struct DNS_HEADER *) buf;

    //将reader指向接收报文的回答区域
    reader = &buf[sizeof(struct DNS_HEADER) + (strlen((const char *) qname) + 1)
                  + sizeof(struct QUESTION)];

    printf("\n\n Message include: ");
    printf("\n %d questions", ntohs(dns->q_count));
    printf("\n %d answers \n", ntohs(dns->ans_count));


    /*
    ** Parse the message
    */
    reader = reader + sizeof(short); //short类型长度为32为，相当于域名字段长度，这时reader指向回答区域的查询类型字段
    answers[i].resource = (struct R_DATA *) (reader);
    reader = reader + sizeof(struct R_DATA); //指向回答问题区域的资源数据字段
    answers[i].resource->type = 256;
    if (ntohs(answers[i].resource->type) == A) //判断资源类型是否为IPv4地址
    {
        answers[i].rdata = (unsigned char *) malloc(ntohs(answers[i].resource->data_len));//资源数据
        for (j = 0; j < ntohs(answers[i].resource->data_len); j++) {
            answers[i].rdata[j] = reader[j];
        }
        answers[i].rdata[ntohs(answers[i].resource->data_len)] = '\0';
//        reader = reader + ntohs(answers[i].resource->data_len);
    }

    // Show Data
    if (ntohs(answers[i].resource->type) == A) //判断查询类型IPv4地址
    {
        long *p;
        p = (long *) answers[i].rdata;
        a.sin_addr.s_addr = *p;
        printf("IPv4 address:%s\n", inet_ntoa(a.sin_addr));
    }

    return inet_ntoa(a.sin_addr);
}

/*
** change www.google.com to 3www6google3com
*/
void ChangetoDnsNameFormat(unsigned char *dns, unsigned char *host) {
    int lock = 0, i;
    strcat((char *) host, ".");

    for (i = 0; i < strlen((char *) host); i++) {
        if (host[i] == '.') {
            *dns++ = i - lock;
            for (; lock < i; lock++) {
                *dns++ = host[lock];
            }
            lock++;
        }
    }
    *dns++ = '\0';
}