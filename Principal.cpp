#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include "Parqueo.h"
#include "BuscarVehiculo.h"
#include "ColaEspera.h"
#include "Metricas.h"
using namespace std;

//Debe de retornar true si la plca es valida y false si no 
bool placaValida(string placa) 
{
    regex formato("^[A-Za-z]{3}[0-9]{3}$"); //Le da el formato a la placa, debe de ser 3 letras con 3 numeros
    return regex_match(placa, formato);
}

//
int leerOpcion() 
{
    int opcion;
    //repite hasta que este valido 
    while (true) 
    {
        cin >> opcion;
        //retorna true si el usuario escribio algo que no es un numero y verifica que sea un positivo
        if (cin.fail() || opcion < 0) 
        {
            cin.clear();//Limpia si hubo un error 
            cin.ignore(1000, '\n');//Limpia lo que quedó hasta el enter
            cout << "Opcion invalida. Ingrese un numero: ";
        }
        else 
        {
            cin.ignore(1000, '\n');
            return opcion;
        }
    }
}


int leerEnteroPositivo(string mensaje) 
{
    int valor;
    while (true) 
    {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor <= 0) 
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Valor invalido. Intente de nuevo.\n";
        }
        else 
        {
            cin.ignore(1000, '\n');
            return valor;
        }
    }
}

int main()
{
    cout << "-.-.-.-.SISTEMA DE PARQUEO INTELIGENTE-.-.-.-.\n";

    //Ingresa los espacios de cada categoria 
    int normales = leerEnteroPositivo("Espacios normales: ");
    int motos = leerEnteroPositivo("Espacios para motos: ");
    int preferenciales = leerEnteroPositivo("Espacios preferenciales: ");


    Parqueo parqueo(normales, motos, preferenciales);
    BuscarVehiculo hash;
    ColaEspera cola;
    Metricas metricas;
    int tick = 1; //Empieza en 1 y sube solo cuando entra o sale un vehiculo

    //Elegir estrategia
    int estrategia;
    cout << "\nSeleccione estrategia de asignacion:\n";
    cout << "1. Estrategia A - primer espacio libre\n";
    cout << "2. Estrategia B - por tipo de espacio\n";
    cout << "Opcion: ";

    estrategia = leerOpcion();
    while (estrategia != 1 && estrategia != 2)
    {
        cout << "Solo estrategia 1 o 2: ";
        estrategia = leerOpcion();
    }

    if (estrategia == 1) {
        cout << "Usando Estrategia A\n";
    }
    else 
    {
        cout << "Usando Estrategia B\n";
    }

    int opcion;
    do 
    {
        cout << "\n-.-.-.-.MENU-.-.-.-.\n";
        cout << "1. Registrar entrada\n";
        cout << "2. Registrar salida\n";
        cout << "3. Buscar vehiculo por placa\n";
        cout << "4. Ver estado del parqueo\n";
        cout << "5. Ver lista de espera\n";
        cout << "6. Ver reporte de metricas\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        if (opcion == 1) 
        {
            
            string placa, tipo;
            char preferencial;
            bool pref = false;

            cout << "Placa: ";
            cin >> placa;

            cin.ignore(1000, '\n');
            //Convierte todas las letras de la placa a mayusculas
            transform(placa.begin(), placa.end(), placa.begin(), ::toupper);

            if (!placaValida(placa)) 
            {
                cout << "Formato invalido. Ejemplo: ABC123\n";
                continue;
            }

            //Valida tipo
            do 
            {
                cout << "Tipo (carro/moto): ";
                cin >> tipo;
                cin.ignore(1000, '\n');
                transform(tipo.begin(), tipo.end(), tipo.begin(), ::tolower);
                if (tipo != "carro" && tipo != "moto") 
                {
                    cout << "Solo se permite carro o moto.\n";
                }     
            } while (tipo != "carro" && tipo != "moto");

            // Validar preferencial
            if (tipo == "carro") 
            {
                do 
                {
                    cout << "Es preferencial? (s/n): ";
                    cin >> preferencial;
                    cin.ignore(1000, '\n');
                    //convierte letras a minuscula
                    preferencial = tolower(preferencial);
                    if (preferencial != 's' && preferencial != 'n') {
                        cout << "Solo s o n.\n";
                    }
                } while (preferencial != 's' && preferencial != 'n');
                pref = (preferencial == 's');
            }

            // Validar duplicado
            if (hash.existe(placa) || cola.existe(placa)) 
            {
                cout << "Esa placa ya esta en el sistema.\n";
                continue;
            }

            //crea el vehiculi con los datos ingresados
            Vehiculo v(placa, tipo, pref);
            //Se guarda el momento en la que entró el vehiculo 
            v.tiempoEntrada = tick;

            //Asignar según estrategia
            int idEspacio = -1;
            if (estrategia == 1) 
            {
                idEspacio = parqueo.asignarEspacioA(v);
            }
            else 
            {
                idEspacio = parqueo.asignarEspacioB(v);
            }
                
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
                cout << placa << " asignado a espacio #" << idEspacio << "\n";
            }
            else 
            {
                cola.agregar(v);
                cout << "Parqueo lleno. " << placa
                    << " enviado a lista de espera.\n";
            }
            tick++;

        }
        else if (opcion == 2) 
        {
            //registra salida
            string placa;
            cout << "Placa a retirar: ";
            cin >> placa;
            cin.ignore(1000, '\n');
            transform(placa.begin(), placa.end(), placa.begin(), ::toupper);

            if (!hash.existe(placa)) {
                cout << "La placa no fue encontrada en el parqueo.\n";
                continue;
            }

            //obtener tipo ANTES de liberar
            string tipoEspacio = parqueo.getTipoEspacioLiberado(placa);

            parqueo.liberarEspacio(placa);
            hash.eliminarPlaca(placa);
            cout << placa << " retirado correctamente.\n";

            //Atender lista de espera según estrategia
            if (!cola.estaVacia()) 
            {

                if (estrategia == 1) 
                {
                    //Estrategia A: 
                    //primero en cola sin importar tipo
                    Vehiculo siguiente = cola.siguiente();
                    //Calcula cuánto tiempo esperó el vehículo en la cola
                    double tiempoEspera = tick - siguiente.tiempoEntrada;
                    metricas.registrarEspera(tiempoEspera);

                    int idEspacio = parqueo.asignarEspacioA(siguiente);
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
                        cout << siguiente.placa
                            << " salio de espera - espacio #"
                            << idEspacio << "\n";
                    }

                }
                else 
                {
                    //Estrategia B: 
                    //busca el primero compatible con el tipo
                    Vehiculo siguiente = cola.siguienteCompatible(tipoEspacio);

                    if (siguiente.placa == "") 
                    {
                        cout << "No hay vehiculos compatibles en espera.\n";
                    }
                    else 
                    {
                        double tiempoEspera = tick - siguiente.tiempoEntrada;
                        metricas.registrarEspera(tiempoEspera);

                        int idEspacio = parqueo.asignarEspacioB(siguiente);
                        if (idEspacio != -1) 
                        {
                            cola.eliminarPorPlaca(siguiente.placa);
                            hash.registrarUbicacion(siguiente.placa, idEspacio);
                            metricas.registrarOcupacion(
                                parqueo.getVehiculosActuales(),
                                parqueo.getCapacidad()
                            );
                            metricas.registrarUso(idEspacio,
                                parqueo.getUsosEspacio(idEspacio)
                            );
                            cout << siguiente.placa
                                << " salio de espera - espacio #"
                                << idEspacio << "\n";
                        }
                    }
                }
            }

            metricas.registrarOcupacion(
                parqueo.getVehiculosActuales(),
                parqueo.getCapacidad()
            );
            tick++;

        }
        else if (opcion == 3) 
        {
            //Buscar placa
            string placa;
            cout << "Placa a buscar: ";
            cin >> placa;
            cin.ignore(1000, '\n');
            transform(placa.begin(), placa.end(), placa.begin(), ::toupper);

            int espacio = hash.buscarEspacio(placa);
            if (espacio != -1) 
            {
                cout << "Vehiculo " << placa
                    << " esta en espacio #" << espacio << "\n";
            }
            else if (cola.existe(placa)) 
            {
                cout << "Vehiculo " << placa
                    << " esta en lista de espera.\n";
            }
            else 
            {
                cout << "Vehiculo no encontrado.\n";
            }

        }
        else if (opcion == 4) 
        {
            parqueo.mostrarEstado();

        }
        else if (opcion == 5) 
        {
            cola.mostrar();

        }
        else if (opcion == 6) 
        {
            metricas.mostrarReporte();

        }
        else if (opcion != 0) {
            cout << "Opcion no valida. Elija entre 0 y 6.\n";
        }

    } while (opcion != 0);

    cout << "\n-.-.-.-.RESUMEN FINAL-.-.-.-.\n";
    metricas.mostrarReporte();
    return 0;
}