#pragma once
#include <string>
#include <vector>
#include <iostream>

class ArchivoManagerUtil {
public:

    static bool guardar(const std::string &nombreArchivo, const void *registro, int tamanioRegistro);
    static bool guardar(const std::string &nombreArchivo, int pos, const void *registro, int tamanioRegistro);
    static bool leer(const std::string &nombreArchivo, int pos, void *destino, int tamanioRegistro);
    static int leerTodos(const std::string &nombreArchivo, void *destino, int tamanioRegistro, int cantidadMaxima);
    static int cantidadRegistros(const std::string &nombreArchivo, int tamanioRegistro);


    static bool agregar(const std::string &nombreArchivo, const void *registro, int tamanioRegistro);
    static void listarTodos(const std::string &nombreArchivo, int tamanioRegistro, void (*mostrar)(const void *));

};
