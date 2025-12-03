/* main.c */
#include "br.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

bool scontiunation;

void mainloop(int s) {
    struct sockaddr_in cli;
    int len;
    int s2;
    char *ip;
    int16 port;

    s2 = accept(s,(struct sockaddr *)&cli,&len);
    if (s2 < 0) 
        return;

    port = (int16)htons((int)cli->sin_port);
    
    printf("");
}

int initserver(int16 port) {
    struct sockaddr_in sock;
    int s;

    sock.sin_family = AF_INET;
    sock.sin_port = htons((int)port);
    sock.sin_addr.s_addr = inet_addr(HOST);

    s = socket(AF_INET, SOCK_STREAM, 0);
    assert(s > 0);

    errno = 0;
    if (bind(s, (struct sockaddr*)&sock, sizeof(sock)))
        assert_perror(errno);
    errno = 0;
    if (listen(s, 20))
        assert_perror(errno);
    
    printf("server listening on %s:%d\n", HOST, port);

    return s;
}

int main(int argc, char *argv[]){
    char *sport;
    int16 port;
    int s;

    if (argc < 2)
        sport = PORT;
    else
        sport = argv[1];

    port = (int16)atoi(sport);

    s = initserver(port);

    scontiunation = true;
    while(scontiunation)
        mainloop(s);
    
    printf("shutting down..\n");
    close(s);
    
    return 0;
}
