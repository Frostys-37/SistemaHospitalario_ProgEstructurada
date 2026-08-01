#ifndef REPORTES_H
#define REPORTES_H

#include "estructuras.h"

// Reportes es de SOLO LECTURA: no modifica ningun arreglo

void reportePacientesAtendidos(Paciente pacientes[], int totalPacientes,
                                Cita citas[], int totalCitas,
                                Consulta consultas[], int totalConsultas);

void reporteMedicoConMasConsultas(Medico medicos[], int totalMedicos,
                                   Cita citas[], int totalCitas,
                                   Consulta consultas[], int totalConsultas);

void reporteTotalFacturado(Factura facturas[], int totalFacturas);

void reporteHistorialPaciente(Paciente pacientes[], int totalPacientes,
                               Cita citas[], int totalCitas,
                               Consulta consultas[], int totalConsultas,
                               Medico medicos[], int totalMedicos);

void reporteConsultasPorRangoFechas(Cita citas[], int totalCitas,
                                     Consulta consultas[], int totalConsultas);

// Sub-menu 
void menuReportes(Paciente pacientes[], int totalPacientes,
                  Medico medicos[], int totalMedicos,
                  Cita citas[], int totalCitas,
                  Consulta consultas[], int totalConsultas,
                  Factura facturas[], int totalFacturas);

#endif // REPORTES_H
