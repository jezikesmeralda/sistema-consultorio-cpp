#include "FacturaArchivo.h"
#include "ArchivoManagerUtil.h"

FacturaArchivo::FacturaArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo), _tamanioRegistro(sizeof(Factura)) {}

bool FacturaArchivo::guardar(const Factura &reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, &reg, _tamanioRegistro);
}

bool FacturaArchivo::guardar(int pos, const Factura &reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, _tamanioRegistro);
}

bool FacturaArchivo::leer(int pos, Factura &dest) {
    return ArchivoManagerUtil::leer(_nombreArchivo, pos, &dest, _tamanioRegistro);
}

int FacturaArchivo::leerTodos(Factura *vec, int cantidadMax) {
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, _tamanioRegistro, cantidadMax);
}

int FacturaArchivo::cantidadRegistros() {
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, _tamanioRegistro);
}

int FacturaArchivo::buscarPorId(int idFactura) {
    int cant = cantidadRegistros();
    Factura reg;
    for (int i = 0; i < cant; ++i) {
        if (!leer(i, reg)) continue;
        if (reg.getIdFactura() == idFactura ) return i;
    }
    return -1;
}

int FacturaArchivo::getNuevoId() {
  int cant = cantidadRegistros();
    if (cant == 0) return 1;

    Factura reg;
    int maxId = 0;

    for (int i = 0; i < cant; i++) {
        leer(i, reg);


        if (!reg.getEstado()) continue;

        if (reg.getIdFactura() > maxId) {
            maxId = reg.getIdFactura();
        }
    }

    return maxId + 1;
}
