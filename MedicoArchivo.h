#pragma once
#include "Medico.h"
#include "ArchivoManagerUtil.h"
#include <string>

class MedicoArchivo {
private:
    std::string _nombreArchivo;

public:
    MedicoArchivo(std::string nombreArchivo = "medicos.dat");

    bool guardar(Medico reg);
    bool guardar(int pos, Medico reg);
    Medico leer(int pos);
    int leerTodos(Medico *vec, int cantidad);
    int cantidadRegistros();
    int buscarPorDNI(std::string dni);
    bool eliminar(int pos);
};
