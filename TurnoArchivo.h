#pragma once
#include "Turno.h"
#include "ArchivoManagerUtil.h"
#include <string>

class TurnoArchivo {

private:
    std::string _nombreArchivo;
    int _tamanioRegistro;

public:
    TurnoArchivo(std::string nombre = "turnos.dat");

    bool guardar(Turno reg);
    bool guardar(int pos, Turno reg);
    bool leer(int pos, Turno &reg);
    int leerTodos(Turno *vec, int cantidad);
    int cantidadRegistros();
    int generarNuevoId();

    int buscarPorId(int idTurno);
};
