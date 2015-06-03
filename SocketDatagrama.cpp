//
// Created by Daniel Franco on 5/18/15.
//

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>
#include "SocketDatagrama.h"

SocketDatagrama::SocketDatagrama(char * hostname ,int portname) {

    //Inicializamos los apuntadores estructuras addrinfo con cero

    remoteAddress = 0;

    //Creamos una estructura que nos ayude a encontrar la información y la llenamos con ceros
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    //Ponemos la dirección como IPV4
    hints.ai_family=AF_INET;
    //Especificamos el tipo de socket como datagrama, para que se descarte TCP
    hints.ai_socktype=SOCK_DGRAM;
    //Podemos dejarlo como 0 o como IPPROTO_TCP
    hints.ai_protocol=0;
    //Se deja para que se regresen resultados solo si el servidor tiene una dirección IPV6 o similarmente si hay
    //dirección IPV4
    hints.ai_flags=AI_ADDRCONFIG;
    //Se regresan una serie de listas enlazadas a remoteAddress, en nuestro caso solo habrá una dirección
    int err=getaddrinfo(hostname,std::to_string(portname).c_str(),&hints,&remoteAddress);
    if (err!=0) {
        exit(0);
    }
    //Creamos el socket a partir de la estructura remoteAddress
    this->s=socket(remoteAddress->ai_family,remoteAddress->ai_socktype,remoteAddress->ai_protocol);
    if (this->s==-1) {
        exit(0);
    }

}

SocketDatagrama::SocketDatagrama() {
}

SocketDatagrama::~SocketDatagrama() {
}


int SocketDatagrama::bindLocalSocket(char * portname) {
    const char* hostname=0; /* wildcard */
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_DGRAM;
    hints.ai_protocol=0;
    hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
    struct addrinfo* res=0;
    int err=getaddrinfo(hostname,portname,&hints,&res);
    if (err!=0) {
        exit(0);
    }

    //Podemos poner el bind a 0 para que utilice el puerto disponible
    if (bind(s,res->ai_addr,res->ai_addrlen)==-1) {
       exit(0);
    }
}


int SocketDatagrama::envia(PaqueteDatagrama &p) {
    sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, remoteAddress->ai_addr, remoteAddress->ai_addrlen);
    return 0;
}

int SocketDatagrama::recibe(PaqueteDatagrama &p) {
    socklen_t clilen = sizeof(sourceAddress);
    ssize_t count= recvfrom(s, (char *) p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&sourceAddress,&clilen);
    return count;
}
int SocketDatagrama::enviaEnteros(PaqueteDatagrama &p) {
    sendto(s, (char *) p.obtieneDatosEnteros(), 2* sizeof(int), 0, remoteAddress->ai_addr, remoteAddress->ai_addrlen);
    return 0;
}

int SocketDatagrama::recibeEnteros (PaqueteDatagrama &p) {
    socklen_t clilen = sizeof(sourceAddress);
    ssize_t count= recvfrom(s, (char *) p.obtieneDatosEnteros(), 2*sizeof(int), 0, (struct sockaddr *)&sourceAddress,&clilen);
    return count;
}

void SocketDatagrama::enviaBroadcast(char* hostname, int port, PaqueteDatagrama &p){

    SocketDatagrama socketDatagrama(hostname,port);
    socketDatagrama.setBroadCast();
    while(1)
    {
        socketDatagrama.enviaEnteros(p);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void SocketDatagrama::cambiaDirIp(char *hostname, int portname) {
    //Inicializamos los apuntadores estructuras addrinfo con cero

    remoteAddress = 0;
    close(this->s);
    //Creamos una estructura que nos ayude a encontrar la información y la llenamos con ceros
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    //Ponemos la dirección como IPV4
    hints.ai_family=AF_INET;
    //Especificamos el tipo de socket como datagrama, para que se descarte TCP
    hints.ai_socktype=SOCK_DGRAM;
    //Podemos dejarlo como 0 o como IPPROTO_TCP
    hints.ai_protocol=0;
    //Se deja para que se regresen resultados solo si el servidor tiene una dirección IPV6 o similarmente si hay
    //dirección IPV4
    hints.ai_flags=AI_ADDRCONFIG;
    //Se regresan una serie de listas enlazadas a remoteAddress, en nuestro caso solo habrá una dirección
    int err=getaddrinfo(hostname,std::to_string(portname).c_str(),&hints,&remoteAddress);
    if (err!=0) {
        exit(0);
    }
    //Creamos el socket a partir de la estructura remoteAddress
    this->s=socket(remoteAddress->ai_family,remoteAddress->ai_socktype,remoteAddress->ai_protocol);
    if (this->s==-1) {
        exit(0);
    }


}

int SocketDatagrama::setBroadCast() {
    int yes=1;
    setsockopt(obtieneID(), SOL_SOCKET,SO_BROADCAST,&yes, sizeof(int));
    return 0;
}

int SocketDatagrama::obtieneID()
{
    return s;
}

sockaddr_storage * SocketDatagrama::getSourceAddress() {
    return &sourceAddress;
}

void SocketDatagrama::imprimeTabla(char* hostname, int port, PaqueteDatagrama buffer) {
    SocketDatagrama socketDatagrama(hostname,port);
    while(1) {
        int received_size;
        int *aux;
        struct sockaddr_in *structRemitente;
        unsigned char addr_from[4];
        received_size = socketDatagrama.recibeEnteros(buffer);
        if (received_size > 0) {
            aux = buffer.obtieneDatosEnteros();
            printf("\nRecibi: %d\n", aux[0]);
            printf("De la ip: ");
            structRemitente = (struct sockaddr_in *) socketDatagrama.getSourceAddress();
            memcpy(addr_from, &structRemitente->sin_addr.s_addr, sizeof(&structRemitente->sin_addr.s_addr));
            //(struct sockaddr *)&sourceAddress
            bzero(socketDatagrama.getSourceAddress(), sizeof(struct sockaddr_storage));
            for (int i = 0; i < 4; i++) {
                printf("%d.", addr_from[i]);
            }
            received_size = 0;
        }
    }
}
