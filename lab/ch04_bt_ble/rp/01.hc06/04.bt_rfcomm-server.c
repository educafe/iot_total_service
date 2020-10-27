#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define USE_DYNAMIC_BIND    0   

int dynamic_bind_rc(int sock, struct sockaddr_rc *sockaddr, uint8_t *port);

int main(int argc, char **argv)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    uint8_t ch;
    socklen_t opt = sizeof(rem_addr);

    if (argc != 2) {
        printf("Usage:\n");
        printf("\nrfcomm-server Channel\n");
        exit(1);
    }

    ch = (uint8_t)strtol(argv[1], NULL, 10);

#if(USE_DYNAMIC_BIND == 1)
    uint8_t port;
#endif

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;

#if(USE_DYNAMIC_BIND == 1)    
    dynamic_bind_rc(s, &loc_addr, &port);
    printf("Available Ch : %d\n", port);

    // put socket into listening mode
    listen(s, 1);
#else
    loc_addr.rc_channel = (uint8_t) ch;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);
#endif

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        printf("received [%s]\n", buf);
    }

    // close connection
    close(client);
    close(s);
    return 0;
}



int dynamic_bind_rc(int sock, struct sockaddr_rc *sockaddr, uint8_t *port)
{
    int err;
    for( *port = 1; *port <= 31; *port++ ) {
        sockaddr->rc_channel = *port;
        err = bind(sock, (struct sockaddr *)sockaddr, sizeof(sockaddr));
        if( ! err ) break;
    }
    if( *port == 31 ) {
        err = -1;
    }
    return err;
}



// source : Bluetooth Essentials for Programmers.pdf