#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "cita.h"
#include "paciente.h"
#include "medico.h"

using namespace std;

// Lee el archivo de citas y llena el arreglo en memoria
bool cargarCitas(Cita citas[], int &totalCitas) {
    ifstream archivo(RUTA_CITAS);
    totalCitas = 0;

    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    while (getline(archivo, linea) && totalCitas < MAX_CITAS) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campo;

        getline(ss, campo, '|'); citas[totalCitas].codigo = campo;
        getline(ss, campo, '|'); citas[totalCitas].codigoPaciente = campo;
        getline(ss, campo, '|'); citas[totalCitas].identidadPaciente = campo;
        getline(ss, campo, '|'); citas[totalCitas].codigoMedico = campo;
        getline(ss, campo, '|'); citas[totalCitas].fecha = campo;
        getline(ss, campo, '|'); citas[totalCitas].hora = campo;
        getline(ss, campo, '|'); citas[totalCitas].estado = campo;
        getline(ss, campo, '|'); citas[totalCitas].motivo = campo;

        totalCitas++;
    }

    archivo.close();
    return true;
}

// Reescribe el archivo de citas completo con lo que hay en memoria
bool guardarCitas(Cita citas[], int totalCitas) {
    ofstream archivo(RUTA_CITAS);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir " << RUTA_CITAS << " para escribir.\n";
        return false;
    }

    for (int i = 0; i < totalCitas; i++) {
        archivo << citas[i].codigo << "|"
                << citas[i].codigoPaciente << "|"
                << citas[i].identidadPaciente << "|"
                << citas[i].codigoMedico << "|"
                << citas[i].fecha << "|"
                << citas[i].hora << "|"
                << citas[i].estado << "|"
                << citas[i].motivo << "\n";
    }

    archivo.close();
    return true;
}

// Devuelve el indice de la cita con ese codigo, o -1 si no existe
int buscarCitaPorCodigo(Cita citas[], int totalCitas, string codigo) {
    for (int i = 0; i < totalCitas; i++) {
        if (citas[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Genera el siguiente codigo consecutivo tipo C-0001, C-0002...
string generarCodigoCita(Cita citas[], int totalCitas) {
    int maxNumero = 0;

    for (int i = 0; i < totalCitas; i++) {
        int numero = stoi(citas[i].codigo.substr(2));
        if (numero > maxNumero) {
            maxNumero = numero;
        }
    }

    ostringstream oss;
    oss << "C-" << setfill('0') << setw(4) << (maxNumero + 1);
    return oss.str();
}

// Imprime los datos de una cita
void mostrarCita(const Cita &c) {
    cout << "----------------------------------------\n";
    cout << "Codigo cita   : " << c.codigo << "\n";
    cout << "Paciente      : " << c.codigoPaciente << " (ID: " << c.identidadPaciente << ")\n";
    cout << "Medico        : " << c.codigoMedico << "\n";
    cout << "Fecha         : " << c.fecha << "\n";
    cout << "Hora          : " << c.hora << "\n";
    cout << "Estado        : " << c.estado << "\n";
    if (!c.motivo.empty()) {
        cout << "Motivo        : " << c.motivo << "\n";
    }
    cout << "----------------------------------------\n";
}

// Muestra todas las citas de un paciente (por codigo)
void listarCitasPorPaciente(Cita citas[], int totalCitas, string codigoPaciente) {
    bool encontro = false;
    for (int i = 0; i < totalCitas; i++) {
        if (citas[i].codigoPaciente == codigoPaciente) {
            mostrarCita(citas[i]);
            encontro = true;
        }
    }
    if (!encontro) {
        cout << "Ese paciente no tiene citas registradas.\n";
    }
}

// Muestra todas las citas de un medico
void listarCitasPorMedico(Cita citas[], int totalCitas, string codigoMedico) {
    bool encontro = false;
    for (int i = 0; i < totalCitas; i++) {
        if (citas[i].codigoMedico == codigoMedico) {
            mostrarCita(citas[i]);
            encontro = true;
        }
    }
    if (!encontro) {
        cout << "Ese medico no tiene citas registradas.\n";
    }
}

// Revisa si el medico ya tiene otra cita activa en esa misma fecha y hora
bool validarChoqueHorario(Cita citas[], int totalCitas,
                           string codigoMedico, string fecha, string hora,
                           string codigoAExcluir) {
    for (int i = 0; i < totalCitas; i++) {
        if (citas[i].codigo == codigoAExcluir) {
            continue; // no comparar la cita contra si misma
        }
        if (citas[i].estado != "activa") {
            continue; // canceladas no generan choque
        }
        if (citas[i].codigoMedico == codigoMedico &&
            citas[i].fecha == fecha && citas[i].hora == hora) {
            return true;
        }
    }
    return false;
}

// Pide identidad de paciente (valida contra el arreglo real de Paciente),
// codigo de medico (valida contra el arreglo real de Medico), fecha y hora,
// y registra la cita guardando tanto codigo como identidad del paciente.
void agendarCita(Cita citas[], int &totalCitas,
                  Paciente listaPacientes[], int totalPacientes,
                  Medico listaMedicos[], int totalMedicos) {
    if (totalCitas >= MAX_CITAS) {
        cout << "No se pueden agendar mas citas, arreglo lleno.\n";
        return;
    }

    string identidadPaciente, codigoMedico, fecha, hora;
    int idxPaciente, idxMedico;

    cout << "\n--- AGENDAR CITA ---\n";

    // Validar paciente por identidad (unica busqueda que expone Paciente)
    do {
        cout << "Identidad del paciente (13 digitos): ";
        cin >> identidadPaciente;
        idxPaciente = buscarPacienteID(listaPacientes, totalPacientes, identidadPaciente);
        if (idxPaciente == -1) {
            cout << "Ese paciente no existe. Intente de nuevo.\n";
        }
    } while (idxPaciente == -1);

    // Validar medico por codigo
    do {
        cout << "Codigo de medico: ";
        cin >> codigoMedico;
        idxMedico = buscarMedicoPorCodigo(listaMedicos, totalMedicos, codigoMedico);
        if (idxMedico == -1) {
            cout << "Ese medico no existe. Intente de nuevo.\n";
        }
    } while (idxMedico == -1);

    // Pedir fecha y hora hasta que no choque con otra cita
    bool hayChoque;
    do {
        cout << "Fecha (dd/mm/aaaa): ";
        cin >> fecha;
        cout << "Hora (hh:mm): ";
        cin >> hora;

        hayChoque = validarChoqueHorario(citas, totalCitas, codigoMedico, fecha, hora);
        if (hayChoque) {
            cout << "Ese medico ya tiene una cita en ese horario. Elija otro.\n";
        }
    } while (hayChoque);

    // Registrar la cita nueva, guardando codigo E identidad del paciente
    string nuevoCodigo = generarCodigoCita(citas, totalCitas);

    citas[totalCitas].codigo = nuevoCodigo;
    citas[totalCitas].codigoPaciente = listaPacientes[idxPaciente].codigo;
    citas[totalCitas].identidadPaciente = listaPacientes[idxPaciente].identidad;
    citas[totalCitas].codigoMedico = codigoMedico;
    citas[totalCitas].fecha = fecha;
    citas[totalCitas].hora = hora;
    citas[totalCitas].estado = "activa";
    citas[totalCitas].motivo = "";

    totalCitas++;
    guardarCitas(citas, totalCitas);

    cout << "Cita agendada con exito. Codigo asignado: " << nuevoCodigo << "\n";
}

// Marca una cita como cancelada (eliminacion logica) y guarda el motivo
void cancelarCita(Cita citas[], int totalCitas) {
    string codigo;
    cout << "\n--- CANCELAR CITA ---\n";
    cout << "Codigo de cita: ";
    cin >> codigo;

    int indice = buscarCitaPorCodigo(citas, totalCitas, codigo);
    if (indice == -1) {
        cout << "No existe una cita con ese codigo.\n";
        return;
    }

    if (citas[indice].estado == "cancelada") {
        cout << "Esa cita ya estaba cancelada.\n";
        return;
    }

    string razon;
    cout << "Razon de la cancelacion: ";
    cin.ignore();
    getline(cin, razon);

    citas[indice].estado = "cancelada";
    citas[indice].motivo = razon;
    guardarCitas(citas, totalCitas);
    cout << "Cita cancelada correctamente.\n";
}

// Cambia fecha/hora de una cita existente, validando choque
void reprogramarCita(Cita citas[], int totalCitas) {
    string codigo;
    cout << "\n--- REPROGRAMAR CITA ---\n";
    cout << "Codigo de cita: ";
    cin >> codigo;

    int indice = buscarCitaPorCodigo(citas, totalCitas, codigo);
    if (indice == -1) {
        cout << "No existe una cita con ese codigo.\n";
        return;
    }

    if (citas[indice].estado == "cancelada") {
        cout << "No se puede reprogramar una cita cancelada.\n";
        return;
    }

    string nuevaFecha, nuevaHora;
    bool valida;
    do {
        cout << "Nueva fecha (dd/mm/aaaa): ";
        cin >> nuevaFecha;
        cout << "Nueva hora (hh:mm): ";
        cin >> nuevaHora;

        if (nuevaFecha == citas[indice].fecha && nuevaHora == citas[indice].hora) {
            cout << "Debe ser distinta a la fecha/hora actual.\n";
            valida = false;
            continue;
        }

        bool choque = validarChoqueHorario(citas, totalCitas,
                                            citas[indice].codigoMedico,
                                            nuevaFecha, nuevaHora,
                                            citas[indice].codigo);
        if (choque) {
            cout << "El medico ya tiene otra cita en ese horario.\n";
            valida = false;
        } else {
            valida = true;
        }
    } while (!valida);

    citas[indice].fecha = nuevaFecha;
    citas[indice].hora = nuevaHora;
    citas[indice].estado = "reprogramada";
    guardarCitas(citas, totalCitas);

    cout << "Cita reprogramada correctamente.\n";
}

// Menu del submodulo de citas
void menuCitas(Cita citas[], int &totalCitas,
               Paciente listaPacientes[], int totalPacientes,
               Medico listaMedicos[], int totalMedicos) {
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
                agendarCita(citas, totalCitas, listaPacientes, totalPacientes, listaMedicos, totalMedicos);
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
