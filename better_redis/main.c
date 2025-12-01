/* main.c */
#include "br.h"

bool scontiunation;

void mainloop(int16 port) {
    struct sockaddr_in sock;
    int s;

    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = INADDR_ANY;

    s = socket(AF_INET, SOCK_STREAM, 0);
    assert(s > 0);

    errno = 0;
    if (bind(s, (struct sockaddr*)&sock, sizeof(sock)))
        assert_perror(errno);
    errno = 0;
    if (listen(s, 20))
        assert_perror(errno);
}

int main(int argc, char *argv[]){
    char *sport;
    int16 port;

    if (argc < 2)
        sport = PORT;
    else
        sport = argv[1];

    port = (int16)atoi(sport);
    
    scontiunation = true;
    while(scontiunation)
        mainloop(port);

    return 0;
}
