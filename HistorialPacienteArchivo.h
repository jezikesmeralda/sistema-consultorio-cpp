#pragma once
#include "HistorialPaciente.h"
#include "ArchivoManagerUtil.h"
#include <string>

class HistorialPacienteArchivo
{
private:
    std::string _nombreArchivo;

public:
    HistorialPacienteArchivo(std::string nombreArchivo = "historiales_pacientes.dat");

    bool guardar(HistorialPaciente registro);
    bool guardar(int pos, HistorialPaciente registro);
    HistorialPaciente leer(int pos);
    int leerTodos(HistorialPaciente *vec, int cantidad);
    int cantidadRegistros();
    int buscarPorDNI(std::string dniPaciente);
    bool eliminar(int pos);


    void listarPorPaciente(std::string dniPaciente);
    void listarPorFecha(Fecha fecha);
};
