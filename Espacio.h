#ifndef ESPACIO_H
#define ESPACIO_H
#include <string>
#include "Vehiculo.h"
using namespace std;

class Espacio {
public:
    int id;
    string tipoEspacio;  // "normal", "moto", "preferencial"
    bool ocupado;
    string placaActual;
    int totalUsos;

    // Constructor vacío
    Espacio() {
        id = 0;
        ocupado = false;
        totalUsos = 0;
        placaActual = "";
    }

    // Constructor con datos
    Espacio(int i, string tipo) {
        id = i;
        tipoEspacio = tipo;
        ocupado = false;
        totalUsos = 0;
        placaActual = "";
    }

    // Verifica si el espacio acepta ese tipo de vehículo
    bool aceptaVehiculo(string tipoVehiculo, bool esPreferencial) {
        if (tipoEspacio == "preferencial") {
            return esPreferencial;
        }
        if (tipoEspacio == "moto") {
            return tipoVehiculo == "moto";
        }
        // espacio normal: solo carros no preferenciales
        return tipoVehiculo == "carro" && !esPreferencial;
    }

    // Marca el espacio como ocupado
    void ocupar(string placa) {
        ocupado = true;
        placaActual = placa;
        totalUsos++;
    }

    // Marca el espacio como libre
    void liberar() {
        ocupado = false;
        placaActual = "";
    }
};
#endif