#ifndef VEHICULO_H
#define VEHICULO_H
#include <string>
using namespace std;

class Vehiculo 
{
public:
    string placa;
    string tipo;         //carro o moto
    bool preferencial;   //discapacidad/embarazada
    int tiempoEntrada;   // para calcular permanencia

    //Constructor vacío
    Vehiculo() 
    {
        preferencial = false;
        tiempoEntrada = 0;
    }

    //Constructor con datos
    Vehiculo(string p, string t, bool pref = false) 
    {
        placa = p;
        tipo = t;
        preferencial = pref;
        tiempoEntrada = 0;
    }
};

#endif