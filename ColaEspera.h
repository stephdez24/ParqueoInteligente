#ifndef COLAESPERA_H
#define COLAESPERA_H
#include <queue>
#include <string>
#include <iostream>
#include "BuscarVehiculo.h"
#include "Vehiculo.h"
using namespace std;

class ColaEspera 
{
private:
    queue<Vehiculo> cola;
    int totalIngreso = 0;

public:
    void agregar(Vehiculo v) 
    {
        cola.push(v);
        totalIngreso++;
    }

    int getTotalIngresos() 
    {
        return totalIngreso;
    }

    bool estaVacia() 
    {
        return cola.empty();
    }

    int tamano() 
    {
        return cola.size();
    }

    //Devuelve el siguiente vehículo en la cola y lo elimina de la cola
    Vehiculo siguiente() 
    {
        if (!cola.empty()) 
        {
            //devuelve el primer vehículo
            Vehiculo v = cola.front();
            //quita ese vahículo de la cola
            cola.pop();
            return v;
        }
        
        return Vehiculo("", "");
    }

    bool existe(string placa) {
        queue<Vehiculo> copia = cola;

        while (!copia.empty()) {
            if (copia.front().placa == placa) {
                return true;
            }
            copia.pop();
        }
        return false;
    }

    void mostrar() 
    {
        if (cola.empty()) 
        {
            cout << "La lista de espera esta vacía" << endl;
            return;
        }

        queue<Vehiculo> copia = cola;
        cout << "--- Lista de Espera ---" << endl;
        while (!copia.empty()) {
            cout << "Placa: " << copia.front().placa << " [" << copia.front().tipo << "]" << endl;
            copia.pop();
        }
    }
};
#endif
