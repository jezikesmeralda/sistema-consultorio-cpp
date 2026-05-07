#include "AgendaMedManager.h"
#include "Turno.h"
#include "TurnoArchivo.h"
#include "TurnoManager.h"
#include <iostream>
#include <algorithm>
using namespace std;

AgendaMedManager::AgendaMedManager()
    : _archivo("agendas_medicos.dat") {}


void AgendaMedManager::agregarAgenda()
{
    AgendaMed reg;

    int nuevoId = _archivo.getNuevoId();
    reg.cargar(nuevoId);

      MedicoArchivo medArch("medicos.dat");
    int posMed = medArch.buscarPorDNI(reg.getDniMedico());
    if (posMed == -1) {
        cout << "El medico NO existe. No se puede crear la agenda.\n";
        return;
    }

    // Verificar duplicados
    if (_archivo.buscarPorDniYFechaHora(
            reg.getDniMedico(),
            reg.getFecha(),
            reg.getHoraInicio(),
            reg.getHoraFin()) != -1)
    {
        cout << "Ese medico ya tiene una agenda en esa fecha y hora.\n";
        return;
    }


    if (_archivo.guardar(reg))
        cout << "Agenda guardada correctamente.\n";
    else
    {
        cout << "Error al guardar la agenda.\n";
        return;
    }

    // Crear y generar turnos
    TurnoManager tm;
    tm.generarTurnosParaAgenda(nuevoId);

    cout << "Turnos generados.\n";
}



void AgendaMedManager::listarPorDniMedico(std::string dni)
{
    int cantidad = ArchivoManagerUtil::cantidadRegistros("agendas_medicos.dat", sizeof(AgendaMed));
    if (cantidad == 0)
    {
        cout << "No hay agendas cargadas.\n";
        return;
    }

    vector<AgendaMed> vec(cantidad);
    ArchivoManagerUtil::leerTodos("agendas_medicos.dat", vec.data(), sizeof(AgendaMed), cantidad);

    bool encontrado = false;
    for (auto &a : vec)
    {
        if (a.getDniMedico() == dni && a.getEstado())
        {
            cout << a.toString() << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron agendas para ese medico.\n";
}
void AgendaMedManager::listarPorFecha(Fecha fecha)
{
    int cantidad = ArchivoManagerUtil::cantidadRegistros("agendas_medicos.dat", sizeof(AgendaMed));
    if (cantidad == 0)
    {
        cout << "No hay agendas cargadas.\n";
        return;
    }

    vector<AgendaMed> vec(cantidad);
    ArchivoManagerUtil::leerTodos("agendas_medicos.dat", vec.data(), sizeof(AgendaMed), cantidad);

    bool encontrado = false;
    for (auto &a : vec)
    {
        Fecha f = a.getFecha();
        if (f.getDia() == fecha.getDia() &&
                f.getMes() == fecha.getMes() &&
                f.getAnio() == fecha.getAnio() &&
                a.getEstado())
        {
            cout << a.toString() << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No hay agendas para esa fecha.\n";
}

void AgendaMedManager::mostrarTodas()
{
    AgendaMedArchivo archivo("agendas_medicos.dat");

    int cantidad = ArchivoManagerUtil::cantidadRegistros("agendas_medicos.dat", sizeof(AgendaMed));
    if (cantidad <= 0)
    {
        cout << "No hay agendas cargadas.\n";
        return;
    }

    cout << "\n=== LISTADO DE AGENDAS ===\n";

    for (int i = 0; i < cantidad; i++)
    {
        AgendaMed ag = archivo.leer(i);

        // Si el registro no se pudo leer o está inactivo, lo salto
        if (!ag.getEstado() || ag.getIdAgenda() == -1)
            continue;

        cout << ag.toString() << endl;
    }
}

void AgendaMedManager::modificarAgenda()
{
    MedicoArchivo medArch("medicos.dat");

    cout << "\n=== MODIFICAR AGENDA DE MÉDICO ===\n";
    cout << "Buscar médico por:\n";
    cout << "1) DNI\n";
    cout << "2) Nombre y apellido\n";
    cout << "Opción: ";
    int opc;
    cin >> opc;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string dniBuscado;

    // ------------------------------------------------------------
    // BUSCAR POR DNI
    // ------------------------------------------------------------
    if (opc == 1)
    {
        cout << "Ingrese DNI del médico: ";
        getline(cin, dniBuscado);
    }
    // ------------------------------------------------------------
    // BUSCAR POR NOMBRE Y APELLIDO
    // ------------------------------------------------------------
    else if (opc == 2)
    {
        string nombre, apellido;

        cout << "Nombre: ";
        getline(cin, nombre);

        cout << "Apellido: ";
        getline(cin, apellido);

        int cant = medArch.cantidadRegistros();
        vector<Medico> lista(cant);
        medArch.leerTodos(lista.data(), cant);

        bool encontrado = false;

        for (auto &m : lista)
        {
            if (m.getNombre() == nombre &&
                    m.getApellido() == apellido &&
                    m.getEstado())
            {
                dniBuscado = m.getDni();
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
        {
            cout << "No se encontró médico con ese nombre y apellido.\n";
            return;
        }
    }
    else
    {
        cout << "Opción inválida.\n";
        return;
    }

    // ------------------------------------------------------------
    // BUSCAR TODAS LAS AGENDAS DEL MÉDICO
    // ------------------------------------------------------------
    vector<int> posiciones;
    int cantAg = _archivo.cantidadRegistros();

    for (int i = 0; i < cantAg; i++)
    {
        AgendaMed reg = _archivo.leer(i);
        if (reg.getEstado() && reg.getDniMedico() == dniBuscado)
        {
            posiciones.push_back(i);
        }
    }

    if (posiciones.empty())
    {
        cout << "El médico no tiene agendas cargadas.\n";
        return;
    }

    // ------------------------------------------------------------
    // MOSTRAR TODAS LAS AGENDAS
    // ------------------------------------------------------------
    cout << "\n=== AGENDAS REGISTRADAS ===\n";
    for (int i = 0; i < (int)posiciones.size(); i++)
    {
        AgendaMed aux = _archivo.leer(posiciones[i]);
        cout << i+1 << ") " << aux.toString() << "\n";
    }

    // ------------------------------------------------------------
    // SELECCIONAR AGENDA A MODIFICAR
    // ------------------------------------------------------------
    cout << "Seleccione número de agenda a modificar: ";
    int seleccion;
    cin >> seleccion;

    if (seleccion < 1 || seleccion > (int)posiciones.size())
    {
        cout << "Selección inválida.\n";
        return;
    }

    int pos = posiciones[seleccion - 1];
    AgendaMed reg = _archivo.leer(pos);

    // ------------------------------------------------------------
    // MENU DE MODIFICACIÓN
    // ------------------------------------------------------------
    int opcion = -1;

    do
    {
        cout << "\n=== AGENDA SELECCIONADA ===\n";
        cout << reg.toString() << "\n";

        cout << "\n¿Qué desea modificar?\n";
        cout << "1) Días de atención\n";
        cout << "2) Fecha de inicio\n";
        cout << "3) Hora\n";
        cout << "4) Consultorio asignado\n";
        cout << "0) Guardar y salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion)
        {
        case 1:
        {
            string dias;
            cout << "Nuevos días (Ej: Lunes, Miércoles): ";
            getline(cin, dias);
            reg.setDiasAtencion(dias);
            break;
        }
        case 2:
        {
            Fecha f;
            cout << "Nueva fecha de inicio:\n";
            f.cargarFecha();
            reg.setFecha(f);
            break;
        }
        case 3:
        {
            cout << "Nueva hora Inicio:\n";
            Hora hI;
            Hora hF;
            hI.cargarHora();
            reg.setHoraInicio(hI);
            cout << "Nueva hora Fin:\n";
            hF.cargarHora();
            reg.setHoraFin(hF);
            break;
        }
        case 4:
        {
            int consult;
            cout << "Nuevo consultorio: ";
            cin >> consult;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            reg.setConsultorioAsignado(consult);
            break;
        }
        case 0:
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    }
    while (opcion != 0);

    // ------------------------------------------------------------
    // GUARDAR CAMBIOS
    // ------------------------------------------------------------
    if (_archivo.guardar(pos, reg))
        cout << " Agenda modificada correctamente.\n";
    else
        cout << " Error al guardar los cambios.\n";
}




void AgendaMedManager::eliminarAgenda(int idAgenda)
{
    int pos = _archivo.buscarPorId(idAgenda);
    if (pos == -1)
    {
        cout << "No se encontrola agenda.\n";
        return;
    }

    AgendaMed reg = _archivo.leer(pos);
    reg.setEstado(false);

    if (ArchivoManagerUtil::guardar("agendas_medicos.dat", pos, &reg, sizeof(AgendaMed)))
        cout << "Agenda eliminada correctamente (baja logica).\n";
    else
        cout << "Error al eliminar la agenda.\n";
}


