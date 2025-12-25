/* main.c */
#include "br.h"

bool scontiunation;
bool ccontinuation;

void zero(int8* buf, int16, int16 size) {
    int8 *p;
    int16 n;
    
    for (n=0, p=buf; n<size; n++, p++ )
        *p = 0;
    
    return;
    
}

void child_loop(Client *cli) {
    int8 buf[256];
    int8 n;
    int8 *p, *f;
    int8 cmd[256], folder[256], args[256];

    //write(cli->s, "hey\n", 4);
    //exit(0);

    zero(buf, 256, 0);
    read(cli->s, (char *)buf, 255);    
    n = (int16)strlen((char *)buf);
    if (n > 256)
        n = 254;

    for (p = buf;
        (*p)
            && (n--)
            && (*p != ' ')
            && (*p != '\n')
            && (*p != '\r');

        p++
    );

    zero(cmd, 256,0); zero(folder, 256, 0); zero(args, 256, 0);
    
    if (!(*p) || (!n)) {
        strncpy((char *)cmd, (char *)buf, 255);
        goto done;
        
    } else if (*p == ' ' || *p == '\n' || *p == '\r') {
        *p = 0;
        strncpy((char *)cmd, (char *)buf, 255);
    }  
/////////////////////////////////
    for (p++, f = p;
        (*p)
            && (n--)
            && (*p != ' ')
            && (*p != '\n')
            && (*p != '\r');
    
        p++
    );

    
    if (!(*p) || (!n)) {
        strncpy((char *)folder, (char *)f, 255);
        goto done;
        
    } else if (*p == ' ' || *p == '\n' || *p == '\r') {
        *p = 0;
        strncpy((char *)folder, (char *)f, 255);
    }

    p++;
    if (*p) {
        strncpy((char *)args, (char *)p, 255);
       for (p = args; (
           (*p)
           && (*p != '\n')
           && (*p != '\r')); p++)

          * p = 0;
    }

    done:
        dprintf(cli->s, "cmd:\t%s\n", cmd);
        dprintf(cli->s, "folder:\t%s\n", folder);
        dprintf(cli->s, "args:\t%s\n", args);
    
    return;
}

void mainloop(int s) {
    struct sockaddr_in cli;
    int32 len;    
    int s2;
    char *ip;
    int16 port;
    Client *client;
    pid_t pid;
    
    s2 = accept(s,(struct sockaddr *)&cli, (unsigned int *)&len);
    if (s2 < 0) 
        return;

    port = (int16)htons((int)cli.sin_port);
    ip = inet_ntoa(cli.sin_addr);
    
    printf("connection  form %s:%d\n", ip, port);


    client = (Client *)malloc(sizeof(struct s_client));
    assert(client);

    zero((int8 *)client, sizeof(struct s_client), 0);
    client->s = s2; 
    client->port = port;
    strncpy(client->ip, ip, 15);

    pid = fork();
    if (pid) {
        free(client);
        
        return;
    } else {
        dprintf(s2, "1000 connected to server\n");
        ccontinuation = true;
        while (ccontinuation)
            child_loop(client);

        close(s2);
        free(client);

        return;      
    }
    
    
    return;
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
