#pragma once
#include "ObraSocialArchivo.h"
#include "ArchivoManagerUtil.h"
#include <string>

class ObraSocialManager {
private:
    ObraSocialArchivo _archivo;

public:
    ObraSocialManager();

    void agregar();
    void eliminar();
    void modificar();
    void listarTodos();
    void listarPorNombre();
    void listarPorTipoCobertura();
};
