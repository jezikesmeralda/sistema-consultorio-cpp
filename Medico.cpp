#include "Medico.h"
#include <iostream>
#include <cstring>
#include <limits>
#include <cctype>
#include <sstream>
#include <iomanip>
using namespace std;

Medico::Medico() : Persona(), _idEspecialidad(0), _sueldo(0), _estado(true)
{
    strcpy(_matriculaProfesional, "");
}

Medico::Medico(string nombre, string apellido, string dni,
               string email, string telefono, Fecha fechaNacimiento,
               string genero, int idEspecialidad, string matricula,
               double sueldo, Fecha fechaIngreso, bool estado)
    : Persona(nombre, apellido, dni, email, telefono, fechaNacimiento, genero),
      _idEspecialidad(idEspecialidad), _sueldo(sueldo),
      _fechaIngreso(fechaIngreso), _estado(estado)
{
    strncpy(_matriculaProfesional, matricula.c_str(), sizeof(_matriculaProfesional) - 1);
    _matriculaProfesional[sizeof(_matriculaProfesional) - 1] = '\0';
}

void Medico::setIdEspecialidad(int id)
{
    while (id <= 0)
    {
        cout << "ID de especialidad invalido. Ingrese un numero mayor a 0: ";
        cin >> id;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            id = 0;
        }
    }
    _idEspecialidad = id;
}

void Medico::setMatriculaProfesional(std::string matricula)
{
    while (true)
    {
        if (matricula.length() != 12)
        {
            cout << "La matricula debe tener EXACTAMENTE 12 caracteres. Ingrese nuevamente: ";
            getline(cin, matricula);
            continue;
        }

        bool valida = true;
        for (char c : matricula)
        {
            if (!isalnum(static_cast<unsigned char>(c)))
            {
                valida = false;
                break;
            }
        }

        if (!valida)
        {
            cout << "La matricula solo puede contener letras y numeros. Intente nuevamente: ";
            getline(cin, matricula);
            continue;
        }

        break; // matrícula válida
    }

    strncpy(_matriculaProfesional, matricula.c_str(), sizeof(_matriculaProfesional) - 1);
    _matriculaProfesional[sizeof(_matriculaProfesional) - 1] = '\0';
}



void Medico::setSueldo(double sueldo)
{
    while (sueldo <= 0)
    {
        cout << "Sueldo invalido. Ingrese un valor positivo: ";
        cin >> sueldo;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sueldo = -1;
        }
    }
    _sueldo = sueldo;
}

void Medico::setFechaIngreso(Fecha fecha)
{
    _fechaIngreso = fecha;
}

void Medico::setEstado(bool estado)
{
    _estado = estado;
}

int Medico::getIdEspecialidad()
{
    return _idEspecialidad;
}
string Medico::getMatriculaProfesional()
{
    return _matriculaProfesional;
}
double Medico::getSueldo()
{
    return _sueldo;
}
Fecha Medico::getFechaIngreso()
{
    return _fechaIngreso;
}
bool Medico::getEstado()
{
    return _estado;
}

void Medico::cargar()
{
    cout << "\n=== CARGA DE DATOS DEL MEDICO ===\n";


    Persona::cargar();


    string matricula;
    cout << "Matricula profesional (12 caracteres alfanumericos): ";
    getline(cin, matricula);

    while (true)
    {
        if (matricula.length() != 12)
        {
            cout << "Debe tener EXACTAMENTE 12 caracteres. Intente nuevamente: ";
            getline(cin, matricula);
            continue;
        }
        bool valida = true;
        for (char c : matricula)
        {
            if (!isalnum((unsigned char)c))
            {
                valida = false;
                break;
            }
        }
        if (!valida)
        {
            cout << "Solo puede contener letras y numeros. Intente nuevamente: ";
            getline(cin, matricula);
            continue;
        }
        break;
    }
    setMatriculaProfesional(matricula);


    double sueldo;
    cout << "Sueldo: ";
    cin >> sueldo;

    while (cin.fail() || sueldo <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Sueldo invalido. Ingrese un valor positivo: ";
        cin >> sueldo;
    }
    setSueldo(sueldo);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');



    cout << "Fecha de ingreso:\n";
    Fecha f;
    f.cargarFecha();
    setFechaIngreso(f);



    char op;
    cout << "Estado del medico (A = activo, I = inactivo): ";
    cin >> op;

    while (op != 'A' && op != 'a' && op != 'I' && op != 'i')
    {
        cout << "Opcion invalida. Ingrese A o I: ";
        cin >> op;
    }

    setEstado(op == 'A' || op == 'a');
}

string Medico::toString()
{
     ostringstream os;

    os << Persona::toString()
       << " | Especialidad ID: " << _idEspecialidad
       << " | Matricula: " << _matriculaProfesional
       << " | Sueldo: $" << fixed << setprecision(2) << _sueldo
       << " | Ingreso: " << _fechaIngreso.toString()
       << " | Estado: " << (_estado ? "Activo" : "Inactivo");

    return os.str();
}
