#pragma once
#include "PacienteArchivo.h"
#include <string>

class PacienteManager {
public:

    void cargarNuevo();
    void listarPorApellido();
    void listarPorObraSocial(int idObra);
    void listarPorFechaNacimiento(Fecha fecha);
    void eliminarPaciente();

private:
    PacienteArchivo _archivo;

};
