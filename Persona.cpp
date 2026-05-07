#include "Persona.h"
#include <cstring>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;

Persona::Persona()
{
    _nombre[0] = '\0';
    _apellido[0] = '\0';
    _dni[0] = '\0';
    _email[0] = '\0';
    _telefono[0] = '\0';
    _genero[0] = '\0';
}

Persona::Persona(string nombre, string apellido, string dni,
                 string email, string telefono,
                 Fecha fechaNacimiento, string genero)
{
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
    setEmail(email);
    setTelefono(telefono);
    setFechaNacimiento(fechaNacimiento);
    setGenero(genero);
}

/// ===== SETTERS =====
void Persona::setNombre(string nombre)
{
    // Verificar que el nombre no esté vacío
    if (nombre.empty())
    {
        std::cout << "Error: El nombre no puede estar vacio." << std::endl;
        return;
    }
    for (size_t i = 0; i < nombre.length(); i++)
    {
        char c = nombre[i]; // Obtener el carácter actual
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' '))
        {
            std::cout << "Error: El nombre solo puede contener letras y espacios." << std::endl;
            return;
        }
    }
    // Asignar el nombre válido
    strcpy(this -> _nombre,nombre.c_str());
}

void Persona::setApellido(string apellido)
{

    if(apellido.empty())
    {
        std::cout << "Error: El Apellido no puede estar vacio." << std::endl;
    }
    for(char v : apellido)
    {
        if(!((v >= 'A' && v <= 'Z')|| (v >= 'a' && v <= 'z')||  v == ' '))
        {
            std::cout << "Error: El Apellido solo puede contener letras y espacios." << std::endl;
            return;
        }
    }
    strcpy ( this -> _apellido,apellido.c_str()) ;
}


void Persona::setDni(string dni)
{
    if(dni.empty())
    {
        cout << "Error: El numero de Dni no puede estar vacio " << endl;
        return;
    }
    strcpy ( this -> _dni,dni.c_str()) ;
}

void Persona::setEmail(string email)
{
    if (email.empty())
    {
        std::cout << "Error: El email no puede estar vacío." << std::endl;
        return;
    }
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    // Verificar que haya un '@' y un '.' después del '@'
    if (atPos == std::string::npos || dotPos == std::string::npos)
    {
        std::cout << "Error: El email debe contener un '@' y un '.' despues del '@'." << std::endl;
        return;
    }
    // Verificar que no haya espacios
    if (email.find(' ') != std::string::npos)
    {
        std::cout << "Error: El email no puede contener espacios." << std::endl;
        return;
    }
    strcpy ( this -> _email,email.c_str()) ;
}


void Persona::setTelefono(string telefono)
{
    if (telefono.empty())
    {
        std::cout << "Error: El numero de teléfono no puede estar vacio." << std::endl;
        return;
    }

    // Validar que solo contenga números
    for (char c : telefono)
    {
        if (c < '0' || c > '9')
        {
            std::cout << "Error: El numero de telefono solo debe contener digitos." << std::endl;
            return;
        }
    }

    // Validar longitud mínima (puedes ajustarla según necesidad)
    if (telefono.length() < 7 || telefono.length() > 15)
    {
        std::cout << "Error: El numero de telefono debe tener entre 7 y 15 digitos." << std::endl;
        return;
    }

    strcpy ( this -> _telefono,telefono.c_str()) ;
}
void Persona::setFechaNacimiento(Fecha fecha)
{
    _fechaNacimiento = fecha;
}

void Persona::setGenero(string genero)
{
   if (!genero.empty())
    genero[0] = toupper(genero[0]);

while (genero != "M" && genero != "F" && genero != "O") {
    cout << "Genero invalido (M/F/O)\n";
    cout << "Reingrese un genero valido (M/F/O): ";
    cin >> genero;
    if (!genero.empty())
        genero[0] = toupper(genero[0]);
}
}
string Persona::getNombre()
{
    return _nombre;
}
::string Persona::getApellido()
{
    return _apellido;
}
string Persona::getDni()
{
    return _dni;
}
string Persona::getEmail()
{
    return _email;
}
string Persona::getTelefono()
{
    return _telefono;
}
Fecha Persona::getFechaNacimiento()
{
    return _fechaNacimiento;
}
string Persona::getGenero()
{
    return _genero;
}


void Persona::cargar()
{
    cout << "--- Carga de datos Personales ---\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string aux;

    // ===== NOMBRE =====
    while (true)
    {
        cout << "Nombre: ";
        getline(cin, aux);

        string antes = getNombre();
        setNombre(aux);

        if (getNombre() != antes) break; // se actualizó
        cout << "Reingrese el nombre.\n";
    }

    // ===== APELLIDO =====
    while (true)
    {
        cout << "Apellido: ";
        getline(cin, aux);

        string antes = getApellido();
        setApellido(aux);

        if (getApellido() != antes) break;
        cout << "Reingrese el apellido.\n";
    }

    // ===== DNI =====
    while (true)
    {
        cout << "DNI (8 digitos): ";
        getline(cin, aux);

        string antes = getDni();
        setDni(aux);

        // tu setter NO valida nada → agregamos validación externa mínima:
        if (aux.length() == 8 && all_of(aux.begin(), aux.end(), ::isdigit)) break;

        cout << "DNI invalido.\n";
    }

    // ===== EMAIL =====
    while (true)
    {
        cout << "Email: ";
        getline(cin, aux);

        string antes = getEmail();
        setEmail(aux);

        if (getEmail() != antes) break;
        cout << "Reingrese un email valido.\n";
    }

    // ===== TELEFONO =====
    while (true)
    {
        cout << "Telefono: ";
        getline(cin, aux);

        string antes = getTelefono();
        setTelefono(aux);

        if (getTelefono() != antes) break;
        cout << "Reingrese el número de teléfono.\n";
    }

    // ===== FECHA DE NACIMIENTO =====
    cout << "Fecha de nacimiento:\n";
    Fecha f;
    f.cargarFecha();
    setFechaNacimiento(f);
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    // ===== GENERO =====
     cout << "Genero (M/F/O): ";
        getline(cin, aux);
        setGenero(aux);


}

string Persona::toString()
{
    string s;
    s += _apellido;
    s += ", ";
    s += _nombre;
    s += "  DNI: ";
    s += _dni;
    return s;
}
