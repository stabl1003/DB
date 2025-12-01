/* main.c */
#include "br.h"

bool scontiunation;

void mainloop() {
    struct sockaddr_in sock;
    int s;

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PORT);
    sock.sin_addr.s_addr = inet_addr(HOST);

    s = socket(AF_INET, SOCK_STREAM, 0);
}

int main(int argc, char *argv[]){
    scontiunation = true;
    while(scontiunation)
        mainloop();

    return 0;
}
