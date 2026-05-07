#pragma once
#include "DetalleFactura.h"
#include <string>

class DetalleFacturaArchivo {
private:
    std::string _nombreArchivo;
    int _tamanioRegistro;
public:
    DetalleFacturaArchivo(std::string nombreArchivo = "detalles_factura.dat");

    bool guardar(const DetalleFactura &reg);
    bool guardar(int pos, const DetalleFactura &reg);
    bool leer(int pos, DetalleFactura &dest);
    int leerTodos(DetalleFactura *vec, int cantidadMax);
    int cantidadRegistros();
    int getNuevoId();
    int contarDetallesPorFactura(int idFactura);
    int buscarPorIdFactura(int idFactura, DetalleFactura *outVec, int maximo); // devuelve cantidad leida
};
