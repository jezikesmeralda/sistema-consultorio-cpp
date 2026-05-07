#include "UsuarioArchivo.h"
#include "ArchivoManagerUtil.h"

UsuarioArchivo::UsuarioArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo), _tamanioRegistro(sizeof(Usuario)) {}

bool UsuarioArchivo::guardar(const Usuario &reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, &reg, _tamanioRegistro);
}

bool UsuarioArchivo::guardar(int pos, const Usuario &reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, _tamanioRegistro);
}

bool UsuarioArchivo::leer(int pos, Usuario &reg) {
    return ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, _tamanioRegistro);
}

int UsuarioArchivo::leerTodos(Usuario *vec, int max) {
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, _tamanioRegistro, max);
}

int UsuarioArchivo::cantidadRegistros() {
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, _tamanioRegistro);
}

int UsuarioArchivo::buscarPorNombre(const std::string &nombre) {
    int cant = cantidadRegistros();
    Usuario u;

    for (int i = 0; i < cant; i++) {
        leer(i, u);
        if (u.getEstado() && u.getUsuario() == nombre)
            return i;
    }
    return -1;
}

bool UsuarioArchivo::bajaLogica(int pos) {
    Usuario u;
    if (!leer(pos, u)) return false;

    u.setEstado(false);
    return guardar(pos, u);
}
