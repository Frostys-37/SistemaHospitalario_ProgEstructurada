#ifndef MEDICO_H
#define MEDICO_H

#include <string>
#include "estructuras.h"
using namespace std;

// Cargar datos de txt a arreglos
void cargarMedicos(Medico lista[], int &total);
void guardarMedicos(Medico lista[], int total);
void cargarEspecialidades(Especialidad lista[], int &total);
void guardarEspecialidades(Especialidad lista[], int total);

// Busquedas
int buscarMedicoXCodigo(Medico lista[], int total, string codigo);
int buscarEspecialidadXCodigo(Especialidad lista[], int total, string codigo);

// Funciones principales
void registrarEspecialidad(Especialidad lista[], int &total);
void registrarMedico(Medico lista[], int &total, Especialidad especialidades[], int totalEspecialidades);
void mostrarMedico(Medico m);
void listarMedicos(Medico lista[], int total);
void listarEspecialidades(Especialidad lista[], int total);
void verHorarioDisponible(Medico lista[], int total);

// SubMenu
void menuMedicos(Medico lista[], int &total, Especialidad especialidades[], int &totalEspecialidades);
#endif // MEDICO_H