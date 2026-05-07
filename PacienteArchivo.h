#pragma once
#include "Paciente.h"
#include "ArchivoManagerUtil.h"
#include <string>

class PacienteArchivo {
private:
    std::string _nombreArchivo;

public:
    PacienteArchivo(std::string nombreArchivo = "pacientes.dat");

    bool guardar(Paciente reg);
    bool guardar(int pos, Paciente reg);
    Paciente leer(int pos);
    int leerTodos(Paciente* vec, int cantidad);
    int cantidadRegistros();
    int buscarPorDNI(std::string dni);
    bool eliminarLogico(int pos);
};
