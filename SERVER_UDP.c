#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char buff[100];
    int sockfd, clen;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed");
        exit(0);
    }
    else
        printf("socket creation successful");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(43454);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Server bind fail");
        exit(0);
    }
    // yaha listen nai hota because this is not connection oriented
    else
        printf("socket successfully binded");
    clen = sizeof(cli);
    while (1)
    {
        // bzero(buff,80);
        // recv from mein client ka saman aa jata hai aur usko sendto mein bhj dete hain ,beacsue we need client ka saman
        recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&cli, &clen); // recv jo hota hai wo revfrom se alag hota hai,rev is used in TCP
        // 3rd parameter ko hm sockaddr stucture mein convert kr rhe hai .cli mein client ka ip address port  ajaega (client ka info)
        // tcp mein accept use hota hai
        // upar address bhj rhe hain clen ka kyunki length nai pta
        // neeche pta hai
        printf("\n UDP Echo back:%s", buff);
        sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&cli, clen); // client ko data bhjenge

        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Client Exit\n");
            break;
        }
    }
}
