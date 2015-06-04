#include <iostream>
#include <string>
#include <sys/time.h>
#include <thread>
#include <list>
#include "SocketDatagrama.h"
using namespace std;





int main() {

    unsigned int data_size = 2;
    string data;
    string ip;
    int port = 0;

    cout<<"Introduce la IP"<<endl;
    cin>>ip;
    cout<<"Introduce el puerto"<<endl;
    cin>>port;
    cout<<"Introduce los datos"<<endl;
    cin>>data;
 
 
    PaqueteDatagrama datagrama(data_size);
    datagrama.inicializaIp(const_cast<char*>( ip.c_str()));
    datagrama.inicializaPuerto(port);
    SocketDatagrama socketDatagrama;
    
    socketDatagrama.cambiaDirIp(const_cast<char*>( ip.c_str()), port);

    PaqueteDatagrama buffer(data_size);

    datagrama.inicializaEnteros(data);

    
    
    std::thread t1(SocketDatagrama::enviaBroadcast,const_cast<char*>( ip.c_str()), port, std::ref(datagrama));
    std::thread t2(SocketDatagrama::imprimeTabla,const_cast<char*>( ip.c_str()), port, std::ref(buffer));
    t1.join();
    t2.join();
    
    
    
    
    return 0;
}