#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include "estructuras.h"
using namespace std;

const string RUTA_PACIENTES = "data/pacientes.txt";

// Guardado de pacientes en archivo
void cargarPacientes(Paciente lista[], int &total);
void guardarPacientes(Paciente lista[], int total);

// Busqueda de pacientes
int buscarPacienteID(Paciente lista[], int total, string identidad);
int buscarPacienteXCodigo(Paciente lista[], int total, string codigo);

// Funciones principales
void registrarPaciente(Paciente lista[], int &total);
void mostrarPaciente(Paciente p);
void listarActivos(Paciente lista[], int total);
void modificarPaciente(Paciente lista[], int total);
void eliminarLogico(Paciente lista[], int total);
void darAlta(Paciente lista[], int total);

// Manda a menu
void menuPacientes(Paciente lista[], int &total);

#endif // PACIENTE_H