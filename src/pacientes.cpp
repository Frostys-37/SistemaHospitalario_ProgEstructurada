#include <iostream>
#include <fstream>
#include <string>
#include "paciente.h"
#include "validaciones.h"
#include "config.h"

using namespace std;

// Funcion que lee los campos con '|' de los txt
string obtenerCampo(string &linea, int &posicion) {
    int fin = (int)linea.find('|', posicion);
    string campo;
    if(fin == (int)string::npos) {
        campo = linea.substr(posicion);
        posicion = (int)linea.size();
    } else {
        campo = linea.substr(posicion, fin - posicion);
        posicion = fin + 1;
    }
    return campo;
}

// =========================================================
//  CARGAR PACIENTES 
// =========================================================
void cargarPacientes(Paciente lista[], int &total) {
    total = 0;
    ifstream archivo(RUTA_PACIENTES);
    if(!archivo.is_open()) {
        return;
    }

    string linea; 

    while(getline(archivo, linea) && total < MAX_PACIENTES) {
        if(linea.empty()) continue; // Ignorar lineas vacias

        int pos = 0;
        Paciente p;
        p.codigo = obtenerCampo(linea, pos);
        p.nombre = obtenerCampo(linea, pos);
        p.identidad = obtenerCampo(linea, pos);
        p.edad = stoi(obtenerCampo(linea, pos));
        p.genero = obtenerCampo(linea, pos)[0];
        p.altura = stof(obtenerCampo(linea, pos));
        p.peso = stof(obtenerCampo(linea, pos));
        p.celular = obtenerCampo(linea, pos);
        p.correo = obtenerCampo(linea, pos);
        p.notas = obtenerCampo(linea, pos);
        p.activo = (obtenerCampo(linea, pos) == "1");
        p.razonBaja = obtenerCampo(linea, pos);
        p.tutor.tieneTutor = (obtenerCampo(linea, pos) == "1");
        p.tutor.identidad = obtenerCampo(linea, pos);
        p.tutor.nombre = obtenerCampo(linea, pos);
        p.tutor.edad = stoi(obtenerCampo(linea, pos));
        p.tutor.parentesco = obtenerCampo(linea, pos);
        p.tutor.celular = obtenerCampo(linea, pos);

        lista[total] = p;
        total++;
    }
    archivo.close();
}

// =========================================================
//  GUARDAR PACIENTES EN ARCHIVO
// =========================================================
void guardarPacientes(Paciente lista[], int total) {
    ofstream archivo(RUTA_PACIENTES);
    if(!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar pacientes." << endl;
        return;
    }

    for(int i = 0; i < total; i++) {
        Paciente &p = lista[i];
        archivo << p.codigo << '|'
                << p.nombre << '|'
                << p.identidad << '|'
                << p.edad << '|'
                << p.genero << '|'
                << p.altura << '|'
                << p.peso << '|'
                << p.celular << '|'
                << p.correo << '|'
                << p.notas << '|'
                << (p.activo ? "1" : "0") << '|'
                << p.razonBaja << '|'
                << (p.tutor.tieneTutor ? "1" : "0") << '|'
                << p.tutor.identidad << '|'
                << p.tutor.nombre << '|'
                << p.tutor.edad << '|'
                << p.tutor.parentesco << '|'
                << p.tutor.celular
                << endl;
    }
    archivo.close();
}

// =========================================================
//  BUSCAR PACIENTE
// =========================================================
int buscarPacienteID(Paciente lista[], int total, string identidad) {
    for(int i = 0; i < total; i++) {
        if(lista[i].identidad == identidad) {
            return i;
        }
    }
    return -1; // Paciente no encontrado
}

// =========================================================
//  MOSTRAR PACIENTE
// =========================================================
void mostrarPaciente(Paciente p) {
    cout << "\n------------------------------" << endl;
    cout << "Código: " << p.codigo << endl;
    cout << "Nombre: " << p.nombre << endl;
    cout << "Identidad: " << p.identidad << endl;
    cout << "Edad: " << p.edad << endl;
    cout << "Género: " << p.genero << endl;
    cout << "Altura: " << p.altura << endl;
    cout << "Peso: " << p.peso << endl;
    cout << "Celular: " << p.celular << endl;
    cout << "Correo: " << p.correo << endl;
    cout << "Notas: " << p.notas << endl;
    cout << "Activo: " << (p.activo ? "Sí" : "No") << endl;
    cout << "Razón de Baja: " << p.razonBaja << endl;
    cout << "Tutor: " << (p.tutor.tieneTutor ? "Sí" : "No") << endl;
    if(p.tutor.tieneTutor) {
        cout << "Identidad del Tutor: " << p.tutor.identidad << endl;
        cout << "Nombre del Tutor: " << p.tutor.nombre << endl;
        cout << "Edad del Tutor: " << p.tutor.edad << endl;
        cout << "Parentesco: " << p.tutor.parentesco << endl;
        cout << "Celular del Tutor: "<< p.tutor.celular<<endl;
    }
    cout << "\n------------------------------" << endl;
}

void listarActivos(Paciente lista[], int total) {
    int encontrados = 0;
    cout << "\nLista de Pacientes Activos:\n";
    for(int i = 0; i < total; i++) {
        if(lista[i].activo) {
            cout << lista[i].codigo << " | " << lista[i].nombre
                 << " | ID: " << lista[i].identidad
                 << " | Edad: " << lista[i].edad << "\n";
            encontrados++;
        }
    }
    if (encontrados == 0) cout << "(No hay pacientes activos registrados)\n";
}

// =========================================================
//  REGISTRAR PACIENTE
// =========================================================
void registrarPaciente(Paciente lista[], int &total) {
    if (total >= MAX_PACIENTES) {
        cout << "No se pueden registrar más pacientes. Límite alcanzado." << endl;
        return;
    }

    Paciente p;
    p.identidad = leerIdentidad("Ingrese la identidad del paciente (13 dígitos): ");
    //Validar si ya existe el paciente
    if(buscarPacienteID(lista, total, p.identidad) != -1) {
        cout << "Ya existe un paciente con esa identidad." << endl;
        return;
    }

    p.nombre = leerTexto("Ingrese el nombre del paciente: ", true);
    p.edad = leerEntero("Ingrese la edad del paciente: ", 0, 120);
    p.genero = leerGenero("Ingrese el género del paciente (M/F): ");
    p.altura = leerPositivo("Ingrese la altura del paciente (en metros ej 1.70): ");
    p.peso = leerPositivo("Ingrese el peso del paciente (en kg): ");
    p.celular = leerTexto("Ingrese el número de celular del paciente: ", false);
    p.correo = leerCorreo("Ingrese el correo electrónico del paciente: ");   
    p.notas   = leerTexto("Notas (o '-' si no aplica): ", false);

    if (p.edad < 18) {

        p.tutor.tieneTutor = true;
        cout << "El paciente es menor de edad. Ingrese los datos del tutor:\n";
        p.tutor.identidad = leerIdentidad(" Identidad del tutor (13 dígitos): ");
        p.tutor.nombre = leerTexto(" Nombre del tutor: ", true);
        p.tutor.edad = leerEntero(" Edad del tutor: ", 18, 110);
        p.tutor.parentesco = leerTexto(" Parentesco con el paciente: ", true);
        p.tutor.celular = leerTexto(" Número de celular del tutor: ", false);

    } else {

        p.tutor.tieneTutor = false;
        p.tutor.nombre = p.tutor.identidad = p.tutor.parentesco = p.tutor.celular = "";
        p.tutor.edad = 0;

    }

    // Asignacion de Codigo de Paciente de forma secuencial
    int numero = total + 1;
    string numeroTexto = to_string(numero);
    while (numeroTexto.length() < 4) {
        numeroTexto = "0" + numeroTexto;
    }
    p.codigo = "P-" + numeroTexto;

    p.activo = true;
    p.razonBaja = "";

    lista[total] = p;
    total++;

    cout << "Paciente registrado exitosamente con código: " << p.codigo << endl;
}

// =========================================================
//  MODIFICAR PACIENTE
// =========================================================
void modificarPaciente(Paciente lista[], int total) {
    string identidad = leerIdentidad("Ingrese la identidad del paciente a modificar:");
    int idx = buscarPacienteID(lista, total, identidad);

    if (idx == -1) {
        cout << "Paciente no encontrado." << endl;
        return;
    }

    if (!lista[idx].activo) {
        cout << "El paciente está dado de baja. No se puede modificar o debe darlo de alta." << endl;
        return;
    }

    Paciente &p = lista[idx];
    mostrarPaciente(p);

    cout << "Ingrese los nuevos datos (deje vacío para mantener el valor actual):\n";
    cout << "1. Edad\n2. Altura\n3. Peso\n4. Celular\n5. Correo\n6. Notas\n0. Cancelar\n";
    int opcion = leerEntero("Opcion: ", 0, 6);

    switch (opcion) {
        case 1: 
            p.edad = leerEntero("Ingrese la nueva edad del paciente: ", 0, 120);
            if(p.edad < 18) {
                p.tutor.tieneTutor = true;
                cout << "El paciente es menor de edad. Ingrese los datos del tutor:\n";
                p.tutor.identidad = leerIdentidad(" Identidad del tutor (13 dígitos): ");
                p.tutor.nombre = leerTexto(" Nombre del tutor: ", true);
                p.tutor.edad = leerEntero(" Edad del tutor: ", 18, 110);
                p.tutor.parentesco = leerTexto(" Parentesco con el paciente: ", true);
                p.tutor.celular = leerTexto(" Número de celular del tutor: ", false);
            }
            break;
        case 2:
            p.altura = leerPositivo("Ingrese la nueva altura del paciente (en metros): ");
            break;
        case 3:
            p.peso = leerPositivo("Ingrese el nuevo peso del paciente (en kg): ");
            break;
        case 4:
            p.celular = leerTexto("Ingrese el nuevo número de celular del paciente: ", false);
            break;
        case 5:
            p.correo = leerCorreo("Ingrese el nuevo correo electrónico del paciente: ");
            break;
        case 6:
            p.notas = leerTexto("Ingrese las nuevas notas del paciente: ", false);
            break;
        case 0:
            cout << "Modificación cancelada." << endl;
            return;
    }

    cout << "Paciente modificado exitosamente." << endl;
}

// =========================================================
//  ELIMINADDOR - DAR DE BAJA A PACIENTE
// =========================================================
void eliminarLogico(Paciente lista[], int total) {
    string identidad = leerIdentidad("Ingrese la identidad del paciente a dar de baja:");
    int idx = buscarPacienteID(lista, total, identidad);
    if (idx == -1) {    
        cout << "Paciente no encontrado." << endl;
        return;
    }

    if (!lista[idx].activo) {
        cout << "El paciente ya está dado de baja." << endl;
        return;
    }

    mostrarPaciente(lista[idx]);
    cout << "\nMotivo de baja:\n1. Alta medica\n2. Defuncion\n";
    int motivo = leerEntero("Opcion: ", 1, 2);

    if(motivo == 1) {
        lista[idx].razonBaja = "Alta medica";
    } else {
        string familiar = leerTexto("Ingrese el nombre del familiar que reporta la defuncion: ", true);
        lista[idx].razonBaja = "Defuncion reportada por: " + familiar;
    }

    lista[idx].activo = false;
    cout << "Paciente dado de baja exitosamente." << endl;
}

// =========================================================
//  DAR DE ALTA A PACIENTE
// =========================================================
void darAlta(Paciente lista[], int total) {
    string identidad = leerIdentidad("Ingrese la identidad del paciente a dar de alta:");
    int idx = buscarPacienteID(lista, total, identidad);
    if (idx == -1) {    
        cout << "Paciente no encontrado." << endl;
        return;
    }

    if (lista[idx].activo) {
        cout << "El paciente ya está activo." << endl;
        return;
    }

    lista[idx].activo = true;
    lista[idx].razonBaja = "";
    cout << "Paciente dado de alta exitosamente." << endl;
}

// =========================================================
//  SUB-MENU
// =========================================================
void menuPacientes(Paciente lista[], int &total) {
    int opcion;
    do {
        cout << "\n================ Menu de Pacientes ================\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Buscar paciente\n";
        cout << "3. Modificar paciente\n";
        cout << "4. Eliminar (baja logica)\n";
        cout << "5. Dar de alta paciente\n";
        cout << "6. Listar pacientes activos\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Seleccione una opcion: ", 0, 6);

        switch(opcion) {
            case 1:
                registrarPaciente(lista, total);
                break;
            case 2:
                {
                    string identidad = leerIdentidad("Ingrese la identidad del paciente a buscar:");
                    int idx = buscarPacienteID(lista, total, identidad);
                    if (idx == -1) {
                        cout << "Paciente no encontrado." << endl;
                    } else {
                        mostrarPaciente(lista[idx]);
                    }
                } 
                break;
            case 3:
                modificarPaciente(lista, total);
                break;
            case 4:
                eliminarLogico(lista, total);
                break;
            case 5:
                darAlta(lista, total);
                break;
            case 6:
                listarActivos(lista, total);
                break;
            case 0:
                guardarPacientes(lista, total);
                cout << "Saliendo del menu de pacientes." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while(opcion != 0);
} 