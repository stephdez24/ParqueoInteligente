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

    Vehiculo siguiente() {
        if (!cola.empty()) {
            Vehiculo v = cola.front();
            cola.pop();
            return v;
        }
        return Vehiculo("", "");
    }

    //busca el primer vehiculo compatible con el tipo de espacio
    Vehiculo siguienteCompatible(string tipoEspacio) 
    {
        queue<Vehiculo> copia = cola;
        while (!copia.empty()) 
        {
            Vehiculo v = copia.front();
            copia.pop();

            if (tipoEspacio == "normal" && v.tipo == "carro" && !v.preferencial)
            {
                return v;
            }
            if (tipoEspacio == "moto" && v.tipo == "moto")
            {
                return v;
            }
            if (tipoEspacio == "preferencial" && v.preferencial)
            {
                return v;
            }
        }
        //no hay vehiculo compatible
        return Vehiculo("", "");
    }

    //elimina un vehiculo específico por placa
    void eliminarPorPlaca(string placa)
    {
        queue<Vehiculo> nueva;
        while (!cola.empty())
        {
            if (cola.front().placa != placa)
            {
                nueva.push(cola.front());
            }
            cola.pop();
        }
        cola = nueva;
    }

    bool existe(string placa)
    {
        queue<Vehiculo> copia = cola;
        while (!copia.empty())
        {
            if (copia.front().placa == placa)
            {
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
            cout << "La lista de espera esta vacia\n";
            return;
        }
        queue<Vehiculo> copia = cola;
        cout << "--- Lista de Espera ---\n";
        while (!copia.empty()) 
        {
            cout << "Placa: " << copia.front().placa
                << " [" << copia.front().tipo << "]"
                << (copia.front().preferencial ? " [preferencial]" : "")
                << "\n";
            copia.pop();
        }
    }
};
#endif
