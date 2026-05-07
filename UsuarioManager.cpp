#include "UsuarioManager.h"
#include <iostream>
using namespace std;

UsuarioManager::UsuarioManager()
    : _arch("usuarios.dat") {}

void UsuarioManager::crearUsuario() {
    Usuario u;
    u.cargar();

    // Evitar duplicados
    if (_arch.buscarPorNombre(u.getUsuario()) != -1) {
        cout << "Ese nombre de usuario ya existe.\n";
        return;
    }

    if (_arch.guardar(u))
        cout << " Usuario creado correctamente.\n";
    else
        cout << " Error al guardar usuario.\n";
}

void UsuarioManager::listarUsuarios() {
    int cant = _arch.cantidadRegistros();
    if (cant == 0) { cout << "No hay usuarios.\n"; return; }

    Usuario u;
    for (int i = 0; i < cant; i++) {
        _arch.leer(i, u);
        if (u.getEstado()) {
            cout << u.toString() << endl;
        }
    }
}

void UsuarioManager::eliminarUsuario() {
    string nombre;
    cout << "Usuario a eliminar: ";
    cin >> nombre;

    int pos = _arch.buscarPorNombre(nombre);
    if (pos == -1) {
        cout << " No existe ese usuario.\n";
        return;
    }

    if (_arch.bajaLogica(pos))
        cout << " Usuario dado de baja.\n";
    else
        cout << " Error al eliminar usuario.\n";
}

bool UsuarioManager::login(string nombre, string pass, Usuario &resultado) {
    int pos = _arch.buscarPorNombre(nombre);
    if (pos == -1) return false;

    Usuario u;
    _arch.leer(pos, u);

    if (!u.getEstado()) return false;
    if (u.getContrasenia() != pass) return false;

    resultado = u;
    return true;
}
