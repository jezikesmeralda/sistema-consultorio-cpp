#include "DetalleFacturaArchivo.h"
#include "ArchivoManagerUtil.h"

DetalleFacturaArchivo::DetalleFacturaArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo), _tamanioRegistro(sizeof(DetalleFactura)) {}

bool DetalleFacturaArchivo::guardar(const DetalleFactura &reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, &reg, _tamanioRegistro);
}
bool DetalleFacturaArchivo::guardar(int pos, const DetalleFactura &reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, _tamanioRegistro);
}
bool DetalleFacturaArchivo::leer(int pos, DetalleFactura &dest) {
    return ArchivoManagerUtil::leer(_nombreArchivo, pos, &dest, _tamanioRegistro);
}
int DetalleFacturaArchivo::leerTodos(DetalleFactura *vec, int cantidadMax) {
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, _tamanioRegistro, cantidadMax);
}
int DetalleFacturaArchivo::cantidadRegistros() {
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, _tamanioRegistro);
}
int DetalleFacturaArchivo::getNuevoId() {
 int cant = cantidadRegistros();
    if (cant == 0) return 1;

    DetalleFactura reg;
    int maxId = 0;

    for (int i = 0; i < cant; i++) {
        leer(i, reg);


        if (!reg.getEstado()) continue;

        if (reg.getIdDetalle() > maxId) {
            maxId = reg.getIdDetalle();
        }
    }

    return maxId + 1;
}

int DetalleFacturaArchivo::contarDetallesPorFactura(int idFactura) {
    int cant = cantidadRegistros();
    DetalleFactura reg;
    int cuenta = 0;
    for (int i = 0; i < cant; ++i) {
        if (!leer(i, reg)) continue;
        if (reg.getIdFactura() == idFactura && reg.getEstado()) ++cuenta;
    }
    return cuenta;
}

int DetalleFacturaArchivo::buscarPorIdFactura(int idFactura, DetalleFactura *outVec, int maximo) {
    int cant = cantidadRegistros();
    DetalleFactura reg;
    int idx = 0;
    for (int i = 0; i < cant && idx < maximo; ++i) {
        if (!leer(i, reg)) continue;
        if (reg.getIdFactura() == idFactura && reg.getEstado()) {
            outVec[idx++] = reg;
        }
    }
    return idx;
}
