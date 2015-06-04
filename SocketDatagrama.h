//
// Created by Daniel Franco on 5/18/15.
//

#ifndef DATAGRAM_SOCKETDATAGRAMA_H
#define DATAGRAM_SOCKETDATAGRAMA_H
#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <chrono>
#include <mutex>


class SocketDatagrama{
public:
    SocketDatagrama(char*, int);
    SocketDatagrama();
    ~SocketDatagrama();
//Recibe un paquete tipo datagrama proveniente de este socket int recibe(PaqueteDatagrama & p);
//Envía un paquete tipo datagrama desde este socket
    int envia(PaqueteDatagrama & p);
    int recibe(PaqueteDatagrama & p);
    int enviaEnteros(PaqueteDatagrama & p);
    int recibeEnteros(PaqueteDatagrama & p);
    int bindLocalSocket(char *);
    void cambiaDirIp(char *, int);
    int obtieneID();
    int setBroadcast();

    //Funciones estáticas
    static void enviaBroadcast(char* hostname, int port, PaqueteDatagrama &p);
    static void imprimeTabla(char* hostname, int port, PaqueteDatagrama &buffer);
    //Getters
    sockaddr_storage * getSourceAddress();

private:
    struct addrinfo * remoteAddress;
    struct sockaddr_storage sourceAddress;

    int s; //ID socket
};


#endif //DATAGRAM_SOCKETDATAGRAMA_H
