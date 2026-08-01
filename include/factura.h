#ifndef FACTURA_H
#define FACTURA_H

#include <string>
#include "estructuras.h"
#include "config.h"
#include "cita.h"
#include "paciente.h"
#include "medico.h"
#include "consulta.h"

using namespace std;

// Carga y guarda el archivo de facturas
bool cargarFacturas(Factura facturas[], int &totalFacturas);
bool guardarFacturas(Factura facturas[], int totalFacturas);

// Generacion y registro de facturas
string generarCodigoFactura(Factura facturas[], int totalFacturas);
void registrarFactura(Cita citas[], int totalCitas, Consulta consultas[], int totalConsultas,
                      Factura facturas[], int &totalFacturas,
                      Paciente listaPacientes[], int totalPacientes,
                      Medico listaMedicos[], int totalMedicos);

#endif
