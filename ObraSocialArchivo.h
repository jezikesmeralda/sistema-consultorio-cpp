#pragma once
#include "ObraSocial.h"
#include "ArchivoManagerUtil.h"
#include <string>

class ObraSocialArchivo
{
private:
    std::string _nombreArchivo;

public:
    ObraSocialArchivo(std::string nombreArchivo = "obrasocial.dat");

    bool guardar(ObraSocial registro);
    bool guardar(int pos, ObraSocial obraSocial);
    int leerTodos(ObraSocial registros[], int cantidad);
    ObraSocial leer(int pos);
    int cantidadRegistros();
    int buscarPorId(int id);
    int generarNuevoId();
    bool eliminar(int pos);
};

