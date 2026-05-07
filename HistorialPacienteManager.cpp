#include "HistorialPacienteManager.h"
#include "PacienteArchivo.h"
#include "MedicoArchivo.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

HistorialPacienteManager::HistorialPacienteManager() :
    _archivo("historiales_pacientes.dat") {}

void HistorialPacienteManager::agregarHistorial()
{
    string dniPaciente;
    cout << "Ingrese DNI del paciente: ";
    cin >> dniPaciente;

    PacienteArchivo pacArch("pacientes.dat");
    int posPac = pacArch.buscarPorDNI(dniPaciente);
    if (posPac == -1)
    {
        cout << "El paciente no existe. No se puede cargar el historial.\n";
        return;
    }

    string dniMedico;
    MedicoArchivo medArch("medicos.dat");
    int posMedico;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpiar buffer

    do
    {
        cout << "Ingrese DNI del medico que atendio: ";
        getline(cin, dniMedico);
        posMedico = medArch.buscarPorDNI(dniMedico);
        if (posMedico == -1)
            cout << "El medico no existe. Intente nuevamente.\n";
    }
    while (posMedico == -1);

    HistorialPaciente nuevo;
    nuevo.cargar(dniPaciente, dniMedico);  // ahora recibe ambos DNIs

    if (_archivo.guardar(nuevo))
        cout << "Historial guardado correctamente.\n";
    else
        cout << "Error al guardar el historial.\n";
}
void HistorialPacienteManager::listarPorPaciente(std::string dni)
{
    _archivo.listarPorPaciente(dni);
}

void HistorialPacienteManager::listarPorFecha(Fecha fecha)
{
    _archivo.listarPorFecha(fecha);
}



void HistorialPacienteManager::listarPorNombreApellido(std::string nombre, std::string apellido)
{
    PacienteArchivo archivoPac;
    int cantidadPac = archivoPac.cantidadRegistros();
    if (cantidadPac == 0)
    {
        cout << "No hay pacientes registrados.\n";
        return;
    }
    vector<Paciente> pacientes(cantidadPac);
    archivoPac.leerTodos(pacientes.data(), cantidadPac);
    bool encontrado = false;
    for (auto &p : pacientes)
    {
        if (p.getNombre() == nombre && p.getApellido() == apellido)
        {
            cout << "\nHistoriales del paciente: " << p.getNombre() << " " << p.getApellido() << "\n";
            _archivo.listarPorPaciente(p.getDni());
            encontrado = true;
        }
    }
    if (!encontrado)
        cout << "No se encontro ningun paciente con ese nombre y apellido.\n";
}
void HistorialPacienteManager::modificarHistorial(std::string dni)
{
    int pos = _archivo.buscarPorDNI(dni);
    if (pos == -1)
    {
        cout << "No se encontro historial para ese paciente.\n";
        return;
    }
    HistorialPaciente reg = _archivo.leer(pos);
    cout << "Historial actual:\n" << reg.toString() << endl;
    cout << "\n¿Que desea modificar?\n";
    cout << "1. Texto del historial\n";
    cout << "2. Fecha de atencion\n";
    cout << "Opción: ";
    int opc;
    cin >> opc;
    cin.ignore();
    if (opc == 1)
    {
        string nuevoTexto;
        cout << "Ingrese nuevo texto del historial:\n";
        getline(cin, nuevoTexto);
        reg.setHistorial(nuevoTexto);
    }
    else if (opc == 2)
    {
        cout << "Ingrese nueva fecha:\n";
        Fecha nueva;
        nueva.cargarFecha();
        reg.setFechaAtencion(nueva);
    }
    else
    {
        cout << "Opcion no valida.\n";
        return;
    }
    if (_archivo.guardar(pos, reg))
        cout << "Historial actualizado correctamente.\n";
    else cout << "Error al guardar los cambios.\n";
}

void HistorialPacienteManager::mostrarTodos()
{
    int cantidad = _archivo.cantidadRegistros();
    if (cantidad == 0)
    {
        cout << "No hay historiales cargados.\n";
        return;
    }
    vector<HistorialPaciente> historiales(cantidad);
    _archivo.leerTodos(historiales.data(), cantidad);
    for (auto &h : historiales) if (h.getEstado()) cout << h.toString() << endl;
}
