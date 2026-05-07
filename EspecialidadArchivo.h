#pragma once
#include "Especialidad.h"
#include "ArchivoManagerUtil.h"
#include <string>

class EspecialidadArchivo {
private:
    std::string _nombreArchivo;

public:
    EspecialidadArchivo(std::string nombreArchivo = "especialidades.dat");

    bool guardar(Especialidad reg);
    bool guardar(int pos, Especialidad reg);
    Especialidad leer(int pos);
    int leerTodos(Especialidad *vec, int cantidad);
    int cantidadRegistros();
    int buscarPorDescripcion(std::string desc);
    int buscarPorId(int id);
    int generarNuevoId();
    bool eliminar(int pos);
};
