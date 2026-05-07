

#pragma once
#include "HistorialPacienteArchivo.h"
#include "PacienteArchivo.h"
#include <string>
#include <vector>
class HistorialPacienteManager
{
private:
    HistorialPacienteArchivo _archivo;

public:

    HistorialPacienteManager();

    void agregarHistorial();
    void listarPorPaciente(std::string dni);
    void listarPorFecha(Fecha fecha);
    void listarPorNombreApellido(std::string nombre, std::string apellido);
    void modificarHistorial(std::string dni);
    void mostrarTodos();
};
