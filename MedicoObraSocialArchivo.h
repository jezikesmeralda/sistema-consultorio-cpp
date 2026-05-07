#pragma once
#include <string>
#include "MedicoObraSocial.h"
#include "ArchivoManagerUtil.h"

class MedicoObraSocialArchivo {
private:
    std::string _nombreArchivo;

public:
    MedicoObraSocialArchivo(std::string nombreArchivo = "medico_obrasocial.dat");

    bool guardar(MedicoObraSocial registro);
    bool guardar(int pos, MedicoObraSocial registro);
    MedicoObraSocial leer(int pos);
    int leerTodos(MedicoObraSocial* vec, int cantidad);
    int cantidadRegistros();
    int getNuevoId();

    int buscarRelacion(std::string dniMedico, int idObraSocial);
    bool eliminar(int pos);
};
