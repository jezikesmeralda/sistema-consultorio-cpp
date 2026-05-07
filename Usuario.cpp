#include "Usuario.h"
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

static string toUpper(const string &s)
{
    string r = s;
    for (char &c : r) c = toupper(c);
    return r;
}


Usuario::Usuario()
{
    strcpy(_usuario, "");
    strcpy(_contrasenia, "");
    strcpy(_rol, "");
    strcpy(_dniPersona, "");
    _estado = true;
}

void Usuario::setUsuario(string u)
{
    if (!u.empty())
    {
        strncpy(_usuario, u.c_str(), sizeof(_usuario)-1);
        _usuario[sizeof(_usuario)-1] = '\0';
    }
}
void Usuario::setContrasenia(string c)
{
    if (!c.empty())
    {
        strncpy(_contrasenia, c.c_str(), sizeof(_contrasenia)-1);
        _contrasenia[sizeof(_contrasenia)-1] = '\0';
    }
}

void Usuario::setRol(string r)
{
    string R = toUpper(r);
    strncpy(_rol, R.c_str(), sizeof(_rol)-1);
    _rol[sizeof(_rol)-1] = '\0';
}

void Usuario::setDniPersona(string dni)
{
    // válido solo si tiene exactamente 8 dígitos
    if (dni.length() == 8 &&
            all_of(dni.begin(), dni.end(), ::isdigit))
    {
        strncpy(_dniPersona, dni.c_str(), sizeof(_dniPersona)-1);
        _dniPersona[sizeof(_dniPersona)-1] = '\0';
    }
}

void Usuario::setEstado(bool e)
{
    _estado = e;
}

string Usuario::getUsuario()
{
    return _usuario;
}
string Usuario::getContrasenia()
{
    return _contrasenia;
}
string Usuario::getRol()
{
    return _rol;
}
string Usuario::getDniPersona()
{
    return _dniPersona;
}
bool Usuario::getEstado()
{
    return _estado;
}

void Usuario::cargar()
{
    string aux;

    cout << "\n=== CREAR USUARIO DEL SISTEMA ===\n";

    cout << "Usuario (nombre de login): ";
    cin >> aux;
    setUsuario(aux);

    cout << "Contrasenia: ";
    cin >> aux;
    setContrasenia(aux);

    cout << "Rol (administrador / secretario / medico): ";
    cin >> aux;

    string auxUpper = toUpper(aux);

    while (!(auxUpper == "ADMINISTRADOR" || auxUpper == "SECRETARIO" || auxUpper == "MEDICO"))
    {
        cout << "Rol invalido. Ingrese administrador / secretario / medico: ";
        cin >> aux;
        auxUpper = toUpper(aux);
    }

    setRol(auxUpper);

    if (auxUpper == "MEDICO")
    {
        cout << "DNI del medico asociado: ";
        cin >> aux;
        setDniPersona(aux);
    }
    else
    {
        setDniPersona("");
    }

    setEstado(true);
}


string Usuario::toString()
{
    return "Usuario: " + string(_usuario) +
           " | Rol: " + string(_rol) +
           " | DNI Persona: " + string(_dniPersona);
}
