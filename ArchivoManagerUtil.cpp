#include "ArchivoManagerUtil.h"
#include <cstdio>

bool ArchivoManagerUtil::guardar(const std::string &nombreArchivo, const void *registro, int tamanioRegistro) {
    FILE *p = fopen(nombreArchivo.c_str(), "ab");
    if (!p) return false;
    bool ok = fwrite(registro, tamanioRegistro, 1, p);
    fclose(p);
    return ok;
}

bool ArchivoManagerUtil::guardar(const std::string &nombreArchivo, int pos, const void *registro, int tamanioRegistro) {
    FILE *p = fopen(nombreArchivo.c_str(), "rb+");
    if (!p) return false;
    fseek(p, pos * tamanioRegistro, SEEK_SET);
    bool ok = fwrite(registro, tamanioRegistro, 1, p);
    fclose(p);
    return ok;
}

bool ArchivoManagerUtil::leer(const std::string &nombreArchivo, int pos, void *destino, int tamanioRegistro) {
    FILE *p = fopen(nombreArchivo.c_str(), "rb");
    if (!p) return false;
    fseek(p, pos * tamanioRegistro, SEEK_SET);
    bool ok = fread(destino, tamanioRegistro, 1, p);
    fclose(p);
    return ok;
}

int ArchivoManagerUtil::leerTodos(const std::string &nombreArchivo, void *destino, int tamanioRegistro, int cantidadMaxima) {
    FILE *p = fopen(nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;
    int leidos = fread(destino, tamanioRegistro, cantidadMaxima, p);
    fclose(p);
    return leidos;
}

int ArchivoManagerUtil::cantidadRegistros(const std::string &nombreArchivo, int tamanioRegistro) {
    FILE *p = fopen(nombreArchivo.c_str(), "rb");
    if (!p) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / tamanioRegistro;
    fclose(p);
    return cant;
}



// === Funciones de gestión de registros ===

bool ArchivoManagerUtil::agregar(const std::string &nombreArchivo, const void *registro, int tamanioRegistro) {
    if (guardar(nombreArchivo, registro, tamanioRegistro)) {

        return true;
    }
    std::cout << "Error al guardar el registro.\n";
    return false;
}

void ArchivoManagerUtil::listarTodos(const std::string &nombreArchivo, int tamanioRegistro, void (*mostrar)(const void *)) {
    int cantidad = cantidadRegistros(nombreArchivo, tamanioRegistro);
    if (cantidad == 0) {
        std::cout << "No hay registros cargados.\n";
        return;
    }

    std::vector<char> buffer(cantidad * tamanioRegistro);
    leerTodos(nombreArchivo, buffer.data(), tamanioRegistro, cantidad);

    for (int i = 0; i < cantidad; i++) {
        mostrar(buffer.data() + i * tamanioRegistro);
    }
}

