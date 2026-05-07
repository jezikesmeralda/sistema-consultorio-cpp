#include "MedicoObraSocialManager.h"
#include <iostream>
using namespace std;

MedicoObraSocialManager::MedicoObraSocialManager()
    : _archivo("medico_obrasocial.dat") {}


void MedicoObraSocialManager::agregarRelacion() {
    auto &relArch = _archivo;
    MedicoArchivo medicoArch;
    ObraSocialArchivo obraArch;

    string dniMedico;
    int idObraSocial;

    cout << "=== ASOCIAR MEDICO A OBRA SOCIAL ===\n";
    cout << "DNI del medico: ";
    cin >> dniMedico;

    int posMed = medicoArch.buscarPorDNI(dniMedico);
    if (posMed == -1) {
        cout << "No se encontro un medico con ese DNI.\n";
        return;
    }

    cout << "ID de la obra social: ";
    cin >> idObraSocial;

    int posObra = obraArch.buscarPorId(idObraSocial);
    if (posObra == -1) {
        cout << "No se encontro una obra social con ese ID.\n";
        return;
    }

    if (relArch.buscarRelacion(dniMedico, idObraSocial) != -1) {
        cout << "El medico ya esta asociado a esa obra social.\n";
        return;
    }

    MedicoObraSocial nuevaRelacion;
    nuevaRelacion.setIdRelacion(relArch.getNuevoId());
    nuevaRelacion.cargar(dniMedico, idObraSocial);
    nuevaRelacion.setDniMedico(dniMedico);
    nuevaRelacion.setIdObraSocial(idObraSocial);

    if (relArch.guardar(nuevaRelacion))
        cout << "Relacion medico obra social registrada correctamente.\n";
    else
        cout << "Error al guardar la relacion.\n";
}



void MedicoObraSocialManager::listarRelaciones() {
    int cantidad = _archivo.cantidadRegistros();
    if (cantidad == 0) {
        cout << "No hay relaciones cargadas.\n";
        return;
    }

    vector<MedicoObraSocial> lista(cantidad);
    _archivo.leerTodos(lista.data(), cantidad);

    cout << "\n=== LISTADO DE RELACIONES MEDICO OBRA SOCIAL ===\n";
    for (auto &r : lista) {
        if (r.getEstado())
            cout << r.toString() << endl;
    }
}


void MedicoObraSocialManager::listarObrasSocialesPorMedico(string dniMedico) {
    int cantidad = _archivo.cantidadRegistros();
    vector<MedicoObraSocial> lista(cantidad);
    _archivo.leerTodos(lista.data(), cantidad);

    bool encontrado = false;
    cout << "\nObras sociales del medico con DNI " << dniMedico << ":\n";
    for (auto &r : lista) {
        if (r.getDniMedico() == dniMedico && r.getEstado()) {
            cout << r.toString() << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "El medico no tiene obras sociales asociadas.\n";
}


void MedicoObraSocialManager::eliminarRelacion(string dniMedico, int idObraSocial) {
    int pos = _archivo.buscarRelacion(dniMedico, idObraSocial);
    if (pos == -1) {
        cout << "No se encontro esa relacion.\n";
        return;
    }

    if (_archivo.eliminar(pos))
        cout << "Relacion eliminada correctamente (baja logica).\n";
    else
        cout << "Error al eliminar la relacion.\n";
}
