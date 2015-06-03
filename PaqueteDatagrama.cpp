//
// Created by Daniel Franco on 5/18/15.
//


#include <stdlib.h>
#include "PaqueteDatagrama.h"

PaqueteDatagrama::PaqueteDatagrama(char *data, unsigned int size, char *ip, int port) {
    longitud = size;
    this->inicializaIp(ip);
    this->inicializaPuerto(port);
    this->inicializaDatos(data);
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int length) {
    longitud = length;
    datos = new char[length];
}

PaqueteDatagrama::~PaqueteDatagrama() {
    delete datos;
}

char *PaqueteDatagrama::obtieneDireccion() {
    return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud() {
    return longitud;
}

int PaqueteDatagrama::obtienePuerto() {
    return puerto;
}

char *PaqueteDatagrama::obtieneDatos() {
    return datos;
}

void PaqueteDatagrama::inicializaPuerto(int port) {
    puerto = port;
}

void PaqueteDatagrama::inicializaIp(char *address) {
    memcpy(ip,address, sizeof(address));

}

void PaqueteDatagrama::inicializaDatos(char *string) {
    datos = new char[longitud];
    memcpy(datos,string, longitud);
}

void PaqueteDatagrama::inicializaEnteros(char *string) {
    datosEnteros[0]=0;
    datosEnteros[1]=0;
    for(int i=0;i<strlen(string);i++)
    {
        this->datosEnteros[i]= string[i]-48;
    }
}

int *PaqueteDatagrama::obtieneDatosEnteros() {
    return datosEnteros;
}
