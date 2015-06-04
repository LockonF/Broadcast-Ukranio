//
// Created by Daniel Franco on 5/18/15.
//

#ifndef DATAGRAM_PAQUETEDATAGRAMA_H
#define DATAGRAM_PAQUETEDATAGRAMA_H
#include <stddef.h>
#include <string.h>
#include <string>

class PaqueteDatagrama {
public:
    PaqueteDatagrama(char *, unsigned int, char *, int);
    PaqueteDatagrama(unsigned int );


    ~PaqueteDatagrama();
    char *obtieneDireccion();
    unsigned int obtieneLongitud(); int obtienePuerto();
    char *obtieneDatos();
    void inicializaPuerto(int);
    void inicializaIp(char *);
    void inicializaDatos(char *);
    void inicializaEnteros(std::string);
    int  *obtieneDatosEnteros();


private:
    char *datos;
    int  datosEnteros[2]{0,0};
    char ip[16];
    unsigned int longitud;
    int puerto;
};

#endif //DATAGRAM_PAQUETEDATAGRAMA_H
