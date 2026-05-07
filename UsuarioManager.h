#pragma once
#include "UsuarioArchivo.h"
#include <string>

class UsuarioManager {
private:
    UsuarioArchivo _arch;

public:
    UsuarioManager();

    void crearUsuario();
    void listarUsuarios();
    void eliminarUsuario();   // <<--- AGREGADO

    bool login(std::string nombre, std::string pass, Usuario &resultado);
};
