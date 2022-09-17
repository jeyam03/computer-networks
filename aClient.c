#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SA struct sockaddr
#define max sizeof(int)

void func(int sockid)
{
    int dividend, divisor, quotient, remainder;
    printf("Enter the dividend: ");
    scanf("%d", &dividend);
    write(sockid, &dividend, max);

    printf("Enter the divisor: ");
    scanf("%d", &divisor);
    write(sockid, &divisor, max);

    read(sockid, &quotient, max);
    printf("\nThe Quotient is: %d", quotient);

    read(sockid, &remainder, max);
    printf("\nThe Remainder is: %d", remainder);
}
int main()
{
    int sockid, len;
    struct sockaddr_in server;
    sockid = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    connect(sockid, (SA *)&server, sizeof(server));
    func(sockid);
    return 0;
}