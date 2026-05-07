#pragma once
#include "Factura.h"
#include <string>

class FacturaArchivo {
private:
    std::string _nombreArchivo;
    int _tamanioRegistro;
public:
    FacturaArchivo(std::string nombreArchivo = "facturas.dat");

    bool guardar(const Factura &reg);
    bool guardar(int pos, const Factura &reg);
    bool leer(int pos, Factura &dest);
    int leerTodos(Factura *vec, int cantidadMax);
    int cantidadRegistros();
    int buscarPorId(int idFactura);
    int getNuevoId();

};
