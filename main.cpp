#include <iostream>
#include <string>
#include <sys/time.h>
#include <thread>
#include <list>
#include "SocketDatagrama.h"
using namespace std;


SocketDatagrama socketDatagrama;
list<char*> ips;



int main() {

    unsigned int data_size = 2;
    char * data = new char[2];
    char * ip = new char[16];
    int * aux;
    int port = 0;
    ssize_t received_size;
    unsigned char addr_from[4]; //Almacena ip del remitente de un mensaje
    struct sockaddr_in *structRemitente;
    cout<<"Introduce la IP"<<endl;
    cin>>ip;
    cout<<"Introduce el puerto"<<endl;
    cin>>port;
    int count = 0;

    PaqueteDatagrama datagrama(data,data_size,ip,port);

    socketDatagrama.cambiaDirIp(ip, port);

    PaqueteDatagrama buffer(data_size);

    socketDatagrama.setBroadCast();

    cout<<"Introduce los datos"<<endl;
    cin>>data;
    datagrama.inicializaEnteros(data);


    std::thread h1(SocketDatagrama::enviaBroadcast,ip, port,datagrama);
    std::thread h2(SocketDatagrama::imprimeTabla,ip, port,buffer);

    h1.join();
    h2.join();
    return 0;
}