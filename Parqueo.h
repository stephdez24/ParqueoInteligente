#ifndef PARQUEO_H
#define PARQUEO_H
#include <vector>
#include <iostream>
#include "Espacio.h"
#include "Vehiculo.h"

using namespace std;

class Parqueo {
private:
    vector<Espacio> espacios;
    int capacidad;
    int vehiculosActuales;

public:
    Parqueo(int normales, int motos, int preferenciales) 
    {
        capacidad = normales + motos + preferenciales;
        vehiculosActuales = 0;
        int id = 1;
        for (int i = 0; i < normales; i++) 
        {
            espacios.push_back(Espacio(id++, "normal"));
        }
        for (int i = 0; i < motos; i++) 
        {
            espacios.push_back(Espacio(id++, "moto"));
        }
        for (int i = 0; i < preferenciales; i++) 
        {
            espacios.push_back(Espacio(id++, "preferencial"));
        }       
    }

    //Retorna id del espacio asignado, retorna -1 si no hay
    int asignarEspacio(Vehiculo& v) 
    {
        for (auto& e : espacios) 
        {
            if (!e.ocupado && e.aceptaVehiculo(v.tipo, v.preferencial)) 
            {
                e.ocupar(v.placa);
                vehiculosActuales++;
                return e.id;
            }
        }
        return -1;
    }

    //Retorna true si libero espacio, false si la placa no estaba
    bool liberarEspacio(string placa) 
    {
        //Busca el primer espacio libre en orden
        for (auto& e : espacios) 
        {
            if (e.ocupado && e.placaActual == placa) 
            {
                e.liberar();
                vehiculosActuales--;
                return true;
            }
        }
        return false;
    }

    bool estaLleno() 
    {
        return vehiculosActuales >= capacidad;
    }

    int getVehiculosActuales() { return vehiculosActuales; }
    int getCapacidad() { return capacidad; }

    //Retorna usos de un espacio por id
    int getUsosEspacio(int id) 
    {
        for (auto& e : espacios) 
        {
            if (e.id == id) return e.totalUsos;
        }
        return 0;
    }

    void mostrarEstado() 
    {
        cout << "\nESTADO DEL PARQUEO\n";
        cout << "Ocupados: " << vehiculosActuales << "/" << capacidad << "\n";

        //Recorre todos los elementos del vector (: - significa en o dentro de)
        for (auto& e : espacios) 
        {
            cout << "Espacio #" << e.id << " [" << e.tipoEspacio << "] -> ";
            if (e.ocupado) 
            {
                cout << e.placaActual << "\n";
            }
            else 
            {
                cout << "LIBRE\n";
            }
        }
    }
};
#endif