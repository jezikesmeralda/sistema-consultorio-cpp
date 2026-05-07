#pragma once
#include "MedicoObraSocialArchivo.h"
#include "MedicoArchivo.h"
#include "ObraSocialArchivo.h"
#include <vector>
#include <string>

class MedicoObraSocialManager {
private:
    MedicoObraSocialArchivo _archivo;

public:
    MedicoObraSocialManager();

    void agregarRelacion();
    void listarRelaciones();
    void listarObrasSocialesPorMedico(std::string dniMedico);
    void eliminarRelacion(std::string dniMedico, int idObraSocial);
};
