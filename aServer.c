#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SA struct sockaddr
#define max sizeof(int)

void func(int conid)
{
    int dividend, divisor, quotient, remainder;
    read(conid, &dividend, max);
    read(conid, &divisor, max);

    quotient = dividend / divisor;
    remainder = dividend % divisor;

    printf("\nDividend: %d", dividend);
    printf("\nDivisor: %d", divisor);
    printf("\nQuotient: %d", quotient);
    printf("\nRemainder: %d", remainder);

    write(conid, &quotient, max);
    write(conid, &remainder, max);
}

int main()
{
    int sockid, conid, len;
    struct sockaddr_in server, client;
    sockid = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t serAdd;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    bind(sockid, (SA *)&server, sizeof(server));
    listen(sockid, 5);
    conid = accept(sockid, (SA *)&client, &serAdd);
    func(conid);
    return 0;
}
