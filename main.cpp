#include <iostream>
#include <string>
#include <sys/time.h>
#include <thread>
#include <list>
#include <mutex>

#include "SocketDatagrama.h"
using namespace std;


std::mutex mutex1;

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
    
    /*
        Se envía la referencia de la función estática,
     */
    
    
    std::thread t1(SocketDatagrama::enviaBroadcast, std::ref(datagrama),std::ref(mutex1),std::ref(socketDatagrama));
    std::thread t2(SocketDatagrama::imprimeTabla,std::ref(buffer),std::ref(mutex1),&(socketDatagrama));
    t1.join();
    t2.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
       
    return 0;
}