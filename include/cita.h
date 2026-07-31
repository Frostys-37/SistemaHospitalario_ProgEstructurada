#ifndef CITA_H
#define CITA_H

#include <string>
#include "estructuras.h"
#include "config.h"
using namespace std;

// Carga y guarda el archivo de citas (ruta en config.h)
bool cargarCitas(Cita citas[], int &totalCitas);
bool guardarCitas(Cita citas[], int totalCitas);

// Menu principal del submodulo. Recibe tambien Paciente y Medico
// porque agendarCita necesita validar contra esos arreglos.
void menuCitas(Cita citas[], int &totalCitas,
               Paciente listaPacientes[], int totalPacientes,
               Medico listaMedicos[], int totalMedicos);

// Las 4 operaciones principales del modulo
void agendarCita(Cita citas[], int &totalCitas,
                  Paciente listaPacientes[], int totalPacientes,
                  Medico listaMedicos[], int totalMedicos);
void cancelarCita(Cita citas[], int totalCitas);
void reprogramarCita(Cita citas[], int totalCitas);
bool validarChoqueHorario(Cita citas[], int totalCitas,
                           string codigoMedico, string fecha, string hora,
                           string codigoAExcluir = "");

// Funciones de apoyo
int buscarCitaPorCodigo(Cita citas[], int totalCitas, string codigo);
string generarCodigoCita(Cita citas[], int totalCitas);
void mostrarCita(const Cita &c);
void listarCitasPorPaciente(Cita citas[], int totalCitas, string codigoPaciente);
void listarCitasPorMedico(Cita citas[], int totalCitas, string codigoMedico);

#endif
