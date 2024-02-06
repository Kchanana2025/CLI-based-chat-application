#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char buff[80];
    int sockfd, len, n;
    struct sockaddr_in serveraddr;
    // char sendline[100], recvline[100];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfull created..\n");
    bzero(&serveraddr, sizeof(len));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(43454);
    len = sizeof(serveraddr);

    printf("\nEnter string :");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')

        sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&serveraddr, len);
    bzero(buff, sizeof(buff));
    // fgets(sendline, 100, stdin);
    // bzero(recvline,100);
    // send(sockfd, sendline, strlen(sendline), 0);
    // recv(sockfd, recvline, 100, 0);
    recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&serveraddr, len);
    printf("\nFrom server: %s", buff);
    close(sockfd);
    return 0;
}
