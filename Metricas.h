#ifndef METRICAS_H
#define METRICAS_H
#include <iostream>
#include <queue> 
#include "Vehiculo.h"
using namespace std;

class Metricas
{
public:
    //Variables para cálculos directos
    double sumaOcupacion = 0;
    int muestraOcupacion = 0;

    double sumaEspera = 0;
    double esperaMaxima = 0;
    int vehiculosEnEspera = 0;

    //Para el espacio más usado
    int idEspacioMasUsado = -1;
    int maxUsos = 0;

    //Registrar ocupación
    void registrarOcupacion(int vehiculosActuales, int capacidad)
    {
        //(double)capacidad) - esto para división entera 
        sumaOcupacion += (vehiculosActuales / (double)capacidad) * 100;
        muestraOcupacion++;
    }

    //Registrar espera
    void registrarEspera(double tiempo)
    {
        sumaEspera += tiempo;
        vehiculosEnEspera++;
        if (tiempo > esperaMaxima)
        {
            esperaMaxima = tiempo;
        }
    }

    //Registrar uso de espacio
    void registrarUso(int id, int usos)
    {
        if (usos > maxUsos)
        {
            maxUsos = usos;
            idEspacioMasUsado = id;
        }
    }

    void mostrarReporte(queue<Vehiculo> colaFinal, int tickActual)
    {
        //Crear copia para no modificar la original
        queue<Vehiculo> copia = colaFinal;

        //Registrar espera de vehiculos que quedaron en cola
        while (!copia.empty())
        {
            double espera = tickActual - copia.front().tiempoEntrada;
            registrarEspera(espera);
            copia.pop();
        }
        cout << "\nReporte" << endl;

        //Ocupación promedio
        double ocupacionPromedio;

        if (muestraOcupacion > 0)
        {
            ocupacionPromedio = sumaOcupacion / muestraOcupacion;
        }
        else
        {
            ocupacionPromedio = 0;
        }
        cout << "Ocupacion promedio: " << ocupacionPromedio << "%" << endl;

        //Tiempo de espera
        if (vehiculosEnEspera > 0) {
            cout << "Tiempo promedio de espera: " << sumaEspera / vehiculosEnEspera << endl;
            cout << "Tiempo maximo de espera: " << esperaMaxima << " ticks" << endl;
        }
        else
        {
            cout << "Tiempo promedio de espera: N/A (ningun vehiculo espero)" << endl;
            cout << "Tiempo maximo de espera: N/A" << endl;
        }

        //Espacio más usado
        if (idEspacioMasUsado != -1) {
            cout << "Espacio mas usado: #" << idEspacioMasUsado << " con " << maxUsos << " usos." << endl;
        }
        else
        {
            cout << "Espacio mas usado: N/A (ningún vehiculo ingreso)" << endl;
        }
    }
};

#endif