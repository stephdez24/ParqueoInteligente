#include <iostream>
#include <string>
#include "Parqueo.h"
#include "BuscarVehiculo.h"
#include "ColaEspera.h"
#include "Metricas.h"
#include <algorithm>
#include <regex>
using namespace std;

bool placaValida(string placa) {
    regex formato("^[A-Za-z]{3}[0-9]{3}$");
    return regex_match(placa, formato);
}

int main() {
    // Configurar parqueo
    int normales, motos, preferenciales;
    cout << "SISTEMA DE PARQUEO INTELIGENTE\n";
    cout << "Espacios normales: ";    cin >> normales;
    cout << "Espacios para motos: ";  cin >> motos;
    cout << "Espacios preferenciales: "; cin >> preferenciales;

    Parqueo parqueo(normales, motos, preferenciales);
    BuscarVehiculo hash;
    ColaEspera cola;
    Metricas metricas;
    int tick = 0; // tiempo simulado

    int opcion;
    do {
        tick++;
        cout << "\n--- MENU (tick " << tick << ") ---\n";
        cout << "1. Registrar entrada\n";
        cout << "2. Registrar salida\n";
        cout << "3. Buscar vehiculo por placa\n";
        cout << "4. Ver estado del parqueo\n";
        cout << "5. Ver lista de espera\n";
        cout << "6. Ver reporte de metricas\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            //Registra la entrada 
            string placa, tipo;
            char preferencial;
            bool pref = false;

            cout << "Placa: ";       cin >> placa;
            transform(placa.begin(), placa.end(), placa.begin(), ::toupper);

            if (!placaValida(placa)) 
            {
                cout << "Formato invalido. Ejemplon de placa: ABC123).\n";
                continue;
            }
            cout << "Tipo (carro/moto): "; cin >> tipo;

            //convertir de mayusculas a minuscula 
            transform(tipo.begin(), tipo.end(), tipo.begin(), ::tolower);

            if (tipo == "carro") 
            {
                cout << "¿Es preferencial? (s/n): ";
                cin >> preferencial;
                pref = (preferencial == 's' || preferencial == 'S');
            }

            // Validar duplicado
            if (hash.existe(placa) || cola.existe(placa)) 
            {
                cout << "Esa placa ya está en el sistema.\n";
                continue;
            }

            Vehiculo v(placa, tipo, pref);
            v.tiempoEntrada = tick;

            if (!parqueo.estaLleno()) 
            {
                int idEspacio = parqueo.asignarEspacio(v);

                if (idEspacio != -1) 
                {
                    hash.registrarUbicacion(placa, idEspacio);
                    metricas.registrarOcupacion(
                        parqueo.getVehiculosActuales(),
                        parqueo.getCapacidad()
                    );
                    metricas.registrarUso(idEspacio,
                        parqueo.getUsosEspacio(idEspacio)
                    );
                    cout << placa << " asignado a espacio #"
                        << idEspacio << "\n";
                }
                else 
                {
                    cola.agregar(v);
                    cout << "No hay espacio. Enviado a lista de espera.\n";
                }
            }
            else 
            {
                cola.agregar(v);
                cout << "Parqueo lleno. " << placa
                    << " agregado a lista de espera.\n";
            }
        }

        else if (opcion == 2) 
        {
            //Registrar salida 
            string placa;
            cout << "Placa a retirar: "; cin >> placa;

            if (!hash.existe(placa)) 
            {
                cout << "La placa no fue encontrada en el parqueo.\n";
                continue;
            }

            parqueo.liberarEspacio(placa);
            hash.eliminarPlaca(placa);
            cout << "OK " << placa << " retirado.\n";

            // Atender lista de espera si hay alguien
            if (!cola.estaVacia()) 
            {
                Vehiculo siguiente = cola.siguiente();
                double tiempoEspera = tick - siguiente.tiempoEntrada;
                metricas.registrarEspera(tiempoEspera);

                int idEspacio = parqueo.asignarEspacio(siguiente);
                if (idEspacio != -1) 
                {
                    hash.registrarUbicacion(siguiente.placa, idEspacio);
                    metricas.registrarOcupacion(
                        parqueo.getVehiculosActuales(),
                        parqueo.getCapacidad()
                    );
                    metricas.registrarUso(idEspacio,
                        parqueo.getUsosEspacio(idEspacio)
                    );
                    cout << "OK " << siguiente.placa
                        << " salió de espera - espacio #" << idEspacio << "\n";
                }
            }

            metricas.registrarOcupacion(
                parqueo.getVehiculosActuales(),
                parqueo.getCapacidad()
            );
        }

        else if (opcion == 3)
        {
            //Buscar placa 
            string placa;
            cout << "Placa a buscar: "; cin >> placa;

            int espacio = hash.buscarEspacio(placa);
            if (espacio != -1)
            {
                cout << "Vehiculo " << placa
                    << " está en espacio #" << espacio << "\n";
            }
            else if (cola.existe(placa))
            {
                cout << "Vehiculo " << placa
                    << " está en lista de espera.\n";
            } 
            else
            {
                cout << "Vehiculo no encontrado.\n";
            }
        }

        else if (opcion == 4) parqueo.mostrarEstado();
        else if (opcion == 5) cola.mostrar();
        else if (opcion == 6) metricas.mostrarReporte();
       

    } while (opcion != 0);

    // Reporte final
    cout << "\n RESUMEN FINAL \n";
    metricas.mostrarReporte();
    return 0;
};