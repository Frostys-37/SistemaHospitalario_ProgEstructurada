#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "cita.h"

bool existePaciente(const char* codigo);
bool existeMedico(const char* codigo);

using namespace std;

// Lee citas.txt y llena el arreglo en memoria
bool cargarCitas(Cita citas[], int &totalCitas) {
    ifstream archivo(ARCHIVO_CITAS);
    totalCitas = 0;

    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    while (getline(archivo, linea) && totalCitas < MAX_CITAS) {
        if (linea.empty()) continue;

        char buffer[200];
        strcpy(buffer, linea.c_str());

        char* token = strtok(buffer, "|");
        if (token) strcpy(citas[totalCitas].codigo, token);

        token = strtok(NULL, "|");
        if (token) strcpy(citas[totalCitas].codPaciente, token);

        token = strtok(NULL, "|");
        if (token) strcpy(citas[totalCitas].codMedico, token);

        token = strtok(NULL, "|");
        if (token) strcpy(citas[totalCitas].fechaHora, token);

        token = strtok(NULL, "|");
        if (token) strcpy(citas[totalCitas].estado, token);

        totalCitas++;
    }

    archivo.close();
    return true;
}

// Reescribe citas.txt completo con lo que hay en memoria
bool guardarCitas(Cita citas[], int totalCitas) {
    ofstream archivo(ARCHIVO_CITAS);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir " << ARCHIVO_CITAS << " para escribir.\n";
        return false;
    }

    for (int i = 0; i < totalCitas; i++) {
        archivo << citas[i].codigo << "|"
                << citas[i].codPaciente << "|"
                << citas[i].codMedico << "|"
                << citas[i].fechaHora << "|"
                << citas[i].estado << "\n";
    }

    archivo.close();
    return true;
}

// Devuelve el indice de la cita con ese codigo, o -1 si no existe
int buscarCitaPorCodigo(Cita citas[], int totalCitas, const char* codigo) {
    for (int i = 0; i < totalCitas; i++) {
        if (strcmp(citas[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

// Genera el siguiente codigo consecutivo tipo C-001, C-002...
void generarCodigoCita(Cita citas[], int totalCitas, char* codigoNuevo) {
    int maxNumero = 0;

    for (int i = 0; i < totalCitas; i++) {
        int numero = atoi(citas[i].codigo + 2);
        if (numero > maxNumero) {
            maxNumero = numero;
        }
    }

    sprintf(codigoNuevo, "C-%03d", maxNumero + 1);
}

// Imprime los datos de una cita
void mostrarCita(const Cita &c) {
    cout << "----------------------------------------\n";
    cout << "Codigo cita   : " << c.codigo << "\n";
    cout << "Paciente      : " << c.codPaciente << "\n";
    cout << "Medico        : " << c.codMedico << "\n";
    cout << "Fecha/Hora    : " << c.fechaHora << "\n";
    cout << "Estado        : " << c.estado << "\n";
    cout << "----------------------------------------\n";
}

// Muestra todas las citas de un paciente
void listarCitasPorPaciente(Cita citas[], int totalCitas, const char* codPaciente) {
    bool encontro = false;
    for (int i = 0; i < totalCitas; i++) {
        if (strcmp(citas[i].codPaciente, codPaciente) == 0) {
            mostrarCita(citas[i]);
            encontro = true;
        }
    }
    if (!encontro) {
        cout << "Ese paciente no tiene citas registradas.\n";
    }
}

// Muestra todas las citas de un medico
void listarCitasPorMedico(Cita citas[], int totalCitas, const char* codMedico) {
    bool encontro = false;
    for (int i = 0; i < totalCitas; i++) {
        if (strcmp(citas[i].codMedico, codMedico) == 0) {
            mostrarCita(citas[i]);
            encontro = true;
        }
    }
    if (!encontro) {
        cout << "Ese medico no tiene citas registradas.\n";
    }
}

// Revisa si el medico ya tiene otra cita activa en esa misma fecha/hora
bool validarChoqueHorario(Cita citas[], int totalCitas,
                           const char* codMedico, const char* fechaHora,
                           const char* codigoAExcluir) {
    for (int i = 0; i < totalCitas; i++) {
        if (strcmp(citas[i].codigo, codigoAExcluir) == 0) {
            continue; // no comparar la cita contra si misma
        }
        if (strcmp(citas[i].estado, "activa") != 0) {
            continue; // canceladas no generan choque
        }
        if (strcmp(citas[i].codMedico, codMedico) == 0 &&
            strcmp(citas[i].fechaHora, fechaHora) == 0) {
            return true;
        }
    }
    return false;
}

// Pide paciente, medico y fecha/hora validos, y registra la cita
void agendarCita(Cita citas[], int &totalCitas) {
    if (totalCitas >= MAX_CITAS) {
        cout << "No se pueden agendar mas citas, arreglo lleno.\n";
        return;
    }

    char codPaciente[10];
    char codMedico[10];
    char fechaHora[20];

    cout << "\n--- AGENDAR CITA ---\n";

    // Validar que el paciente exista
    do {
        cout << "Codigo de paciente: ";
        cin >> codPaciente;
        if (!existePaciente(codPaciente)) {
            cout << "Ese paciente no existe. Intente de nuevo.\n";
        }
    } while (!existePaciente(codPaciente));

    // Validar que el medico exista
    do {
        cout << "Codigo de medico: ";
        cin >> codMedico;
        if (!existeMedico(codMedico)) {
            cout << "Ese medico no existe. Intente de nuevo.\n";
        }
    } while (!existeMedico(codMedico));

    // Pedir fecha/hora hasta que no choque con otra cita
    bool hayChoque;
    cin.ignore();
    do {
        cout << "Fecha y hora (dd/mm/aaaa hh:mm): ";
        cin.getline(fechaHora, 20);

        hayChoque = validarChoqueHorario(citas, totalCitas, codMedico, fechaHora);
        if (hayChoque) {
            cout << "Ese medico ya tiene una cita en ese horario. Elija otro.\n";
        }
    } while (hayChoque);

    // Registrar la cita nueva
    char nuevoCodigo[10];
    generarCodigoCita(citas, totalCitas, nuevoCodigo);

    strcpy(citas[totalCitas].codigo, nuevoCodigo);
    strcpy(citas[totalCitas].codPaciente, codPaciente);
    strcpy(citas[totalCitas].codMedico, codMedico);
    strcpy(citas[totalCitas].fechaHora, fechaHora);
    strcpy(citas[totalCitas].estado, "activa");

    totalCitas++;
    guardarCitas(citas, totalCitas);

    cout << "Cita agendada con exito. Codigo asignado: " << nuevoCodigo << "\n";
}

// Marca una cita como cancelada (eliminacion logica)
void cancelarCita(Cita citas[], int totalCitas) {
    char codigo[10];
    cout << "\n--- CANCELAR CITA ---\n";
    cout << "Codigo de cita: ";
    cin >> codigo;

    int indice = buscarCitaPorCodigo(citas, totalCitas, codigo);
    if (indice == -1) {
        cout << "No existe una cita con ese codigo.\n";
        return;
    }

    if (strcmp(citas[indice].estado, "cancelada") == 0) {
        cout << "Esa cita ya estaba cancelada.\n";
        return;
    }

    strcpy(citas[indice].estado, "cancelada");
    guardarCitas(citas, totalCitas);
    cout << "Cita cancelada correctamente.\n";
}

// Cambia fecha/hora de una cita existente, validando choque
void reprogramarCita(Cita citas[], int totalCitas) {
    char codigo[10];
    cout << "\n--- REPROGRAMAR CITA ---\n";
    cout << "Codigo de cita: ";
    cin >> codigo;

    int indice = buscarCitaPorCodigo(citas, totalCitas, codigo);
    if (indice == -1) {
        cout << "No existe una cita con ese codigo.\n";
        return;
    }

    if (strcmp(citas[indice].estado, "cancelada") == 0) {
        cout << "No se puede reprogramar una cita cancelada.\n";
        return;
    }

    char nuevaFechaHora[20];
    bool valida;
    cin.ignore();
    do {
        cout << "Nueva fecha y hora (dd/mm/aaaa hh:mm): ";
        cin.getline(nuevaFechaHora, 20);

        if (strcmp(nuevaFechaHora, citas[indice].fechaHora) == 0) {
            cout << "Debe ser distinta a la fecha/hora actual.\n";
            valida = false;
            continue;
        }

        // Excluye la propia cita al validar choque
        bool choque = validarChoqueHorario(citas, totalCitas,
                                            citas[indice].codMedico,
                                            nuevaFechaHora,
                                            citas[indice].codigo);
        if (choque) {
            cout << "El medico ya tiene otra cita en ese horario.\n";
            valida = false;
        } else {
            valida = true;
        }
    } while (!valida);

    strcpy(citas[indice].fechaHora, nuevaFechaHora);
    strcpy(citas[indice].estado, "reprogramada");
    guardarCitas(citas, totalCitas);

    cout << "Cita reprogramada correctamente.\n";
}

// Menu del submodulo de citas
void submenuCitas(Cita citas[], int &totalCitas) {
    int opcion;

    do {
        cout << "\n===== SUB-MENU CITAS =====\n";
        cout << "1. Agendar cita\n";
        cout << "2. Cancelar cita\n";
        cout << "3. Reprogramar cita\n";
        cout << "0. Volver al menu de Gestion\n";
        cout << "Elija opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agendarCita(citas, totalCitas);
                break;
            case 2:
                cancelarCita(citas, totalCitas);
                break;
            case 3:
                reprogramarCita(citas, totalCitas);
                break;
            case 0:
                cout << "Volviendo al menu de Gestion...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}
