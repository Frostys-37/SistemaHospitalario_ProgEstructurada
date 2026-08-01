#ifndef CONSULTA_H
#define CONSULTA_H

#include <string>
#include "estructuras.h"
#include "config.h"
#include "cita.h"
#include "paciente.h"
#include "medico.h"

using namespace std;

bool cargarConsultas(Consulta consultas[], int &totalConsultas);
bool guardarConsultas(Consulta consultas[], int totalConsultas);
int buscarConsultaPorCodigo(Consulta consultas[], int totalConsultas, string codigo);
string generarCodigoConsulta(Consulta consultas[], int totalConsultas);

bool cargarFacturas(Factura facturas[], int &totalFacturas);
bool guardarFacturas(Factura facturas[], int totalFacturas);
string generarCodigoFactura(Factura facturas[], int totalFacturas);

bool validarCodigoCita(Cita citas[], int totalCitas, string codigoCita, int &indice);
void registrarConsulta(Cita citas[], int totalCitas, Consulta consultas[], int &totalConsultas,
                       Paciente listaPacientes[], int totalPacientes,
                       Medico listaMedicos[], int totalMedicos);
void registrarFactura(Cita citas[], int totalCitas, Consulta consultas[], int totalConsultas,
                      Factura facturas[], int &totalFacturas,
                      Paciente listaPacientes[], int totalPacientes,
                      Medico listaMedicos[], int totalMedicos);
void menuConsultas(Cita citas[], int totalCitas, Consulta consultas[], int &totalConsultas,
                   Factura facturas[], int &totalFacturas,
                   Paciente listaPacientes[], int totalPacientes,
                   Medico listaMedicos[], int totalMedicos);

#endif
