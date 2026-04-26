#ifndef BUSCARVEHICULO_H
#define BUSCARVEHICULO_H
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

class BuscarVehiculo
{
private:
    //sirve para guardar pares de clave-valor. Permite buscar elementos por cada clave única sin tener que recorrer toda la estructura 
    unordered_map<string, int> mapaBusqueda;

public:
    
    //Retorna true si se registró, false si la placa ya existe 
    bool registrarUbicacion(string placa, int idEspacio) 
    {
        if (existe(placa)) 
        {
            return false;
        }
        mapaBusqueda[placa] = idEspacio; //Obtiene el elemento, si no existe lo crea y lo guarda en idEspacio que lo asocia a la placa
                                         
        return true;
    }

    bool existe(string placa) 
    {
        //Busca la clave placa dentro del mapa
        //Si lo encuntra devuelve un iterador a ese elemento
        //Si no lo encuentra devuelve mapaBusqueda.end()
        //.end() - indica el final del contenedor - saber cuando algo no se encontró 
        return mapaBusqueda.find(placa) != mapaBusqueda.end();
    }

    //Retorna el espacio donde esta el vehículo
    int buscarEspacio(string placa)
    {
        auto it = mapaBusqueda.find(placa);
        if (it != mapaBusqueda.end())
        {
            return it->second;
        }
        return -1;
    }

    void eliminarPlaca(string placa) 
    {
        mapaBusqueda.erase(placa);
    }

    int totalRegistro() 
    {
        return (int)mapaBusqueda.size();
    }
};
#endif


 