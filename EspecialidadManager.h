#pragma once
#include "EspecialidadArchivo.h"
#include "MedicoArchivo.h"
#include <vector>

class EspecialidadManager {
private:
    EspecialidadArchivo _archivo;

public:
    EspecialidadManager();

    void agregar();
    void listarAlfabeticamente();
    void modificarDescripcion(int id);
    void eliminarEspecialidad(int id);
    void mostrarMedicosPorEspecialidad();
    void buscarPorNombre();
};
