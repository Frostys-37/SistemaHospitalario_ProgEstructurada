#ifndef CONFIG_H
#define CONFIG_H

// DEFINIR RUTAS DE ARCHIVOS AQUI
// El programa correrá con el comando "make run" para que no haya problemas de rutas relativas
// Si alguien agrega un archivo o se crea un txt nuevo añadir la ruta aquí para que el programa pueda acceder a él

const char RUTA_PACIENTES[] = "data/pacientes.txt";
const char RUTA_MEDICOS[] = "data/medicos.txt"; 
const char RUTA_ESPECIALIDADES[] = "data/especialidades.txt";
const char RUTA_CITAS[] = "data/citas.txt";
const char RUTA_CONSULTAS[] = "data/consultas.txt";
const char RUTA_FACTURAS[] = "data/facturas.txt";
const char RUTA_CONTADORES[] = "data/contadores.txt";
const char RUTA_USUARIOS[] = "data/usuarios.txt";
const char RUTA_LOG[] = "data/log.txt";

#endif // CONFIG_H