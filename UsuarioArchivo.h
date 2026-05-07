#pragma once
#include "Usuario.h"
#include <string>

class UsuarioArchivo {
private:
    std::string _nombreArchivo;
    int _tamanioRegistro;

public:
    UsuarioArchivo(std::string nombreArchivo = "usuarios.dat");

    bool guardar(const Usuario &reg);
    bool guardar(int pos, const Usuario &reg);
    bool leer(int pos, Usuario &reg);
    int leerTodos(Usuario *vec, int cantMax);
    int cantidadRegistros();

    int buscarPorNombre(const std::string &nombre);

    bool bajaLogica(int pos);   // <<--- AGREGADO
};
