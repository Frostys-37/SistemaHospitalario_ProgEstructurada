#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// Constantes generales
const int MAX_PACIENTES = 200;
const int MAX_MEDICOS = 20;
const int MAX_ESPECIALIDADES = 3;
const int MAX_CITAS = 50;
const int MAX_CONSULTAS = 50;
const int MAX_FACTURAS = 50;

// Tutor legal (solo aplica si el paciente es menor de 18)
struct Tutor {
    char nombre[60];
    char identidad[14];   // 13 digitos + '\0'
    int  edad;
    char parentesco[20];
    char celular[15];
    bool tieneTutor;      // false si el paciente es mayor de edad
};

//Paciente
struct Paciente {
    char  codigo[10];     // Ej: "P-0001"
    char  nombre[60];
    char  identidad[14];  // 13 digitos + '\0'
    int   edad;
    char  genero;         // 'M' o 'F'
    float altura;         // metros
    float peso;           // kg
    char  celular[15];
    char  correo[50];
    char  notas[100];
    Tutor tutor;
    bool  activo;         // eliminacion logica
    char  razonBaja[100]; // motivo si activo == false
};

// Especialidad
struct Especialidad {
    char codigo[5]; //ej: "E-01"
    char nombre[40];
};

// ---- Medico ----
struct Medico {
    char codigo[12];          // codigo de trabajador, ej "M-0001"
    char nombre[60];
    char identidad[14];
    int  edad;
    char genero;
    char celular[15];
    char correo[50];
    char codEspecialidad[5];  // FK -> Especialidad.codigo
    char notas[100];
    bool activo;
};
 
// ---- Cita ----
struct Cita {
    char codigo[10];          // "C-0001"
    char codigoPaciente[10];  // FK -> Paciente.codigo
    char codigoMedico[12];    // FK -> Medico.codigo
    char fecha[11];           // "dd/mm/aaaa"
    char hora[6];              // "hh:mm"
    char estado[15];           // "activa" | "cancelada" | "reprogramada"
    char motivo[100];          // razon si fue cancelada
};
 
// ---- Consulta ----
struct Consulta {
    char codigo[10];          // "CO-0001"
    char codigoCita[10];      // FK -> Cita.codigo
    char diagnostico[150];
    char tratamiento[150];
};
 
// ---- Factura ----
struct Factura {
    char codigo[12];          // "F-C0001"
    char codigoCita[10];      // FK -> Cita.codigo
    float total;
};
 
#endif