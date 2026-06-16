#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include "Juego.h"

typedef struct
{
    char userName[LIMITE];
    char password[LIMITE];
    float billetera;
    Juego *bibliotecaUsuario;
    Juego *carritoDeJuegos;
    int validosBiblioteca;
    int validosCarrito;
    int eliminado;

} Usuario;


///No te quiero tocar esto por si acaso, lo podes ordenar en Alta, Baja, Modificación, Consulta, Listados?
///Igual veo faltan los últimos 2 de consul. y listados que hay que pensar cómo hacerlos
///Tal vez que el admin puede acceder a consulta y listados (en alguno de estos dos va la idea de la pila de la profe de los usuarios más activos también)
///(hoy/mañana te ayudo pq algunos creo sería literal copiar y pegar (con mini modificaciones) las funciones que ya tenemos* (vamos a tener) en juegos.h/c)

///Son dos funciones de busqueda por campo de struct por CADA struct? O sea, 4 funciones en total?
///o ya con 2 estamos? Si es asi, tenemos la de buscar por usuario y la de buscar por nombre de juego

// Borrado Logico / Baja
void eliminarUsuario(Usuario *usuarioAEliminar);

// Mostrar Datos / Listado
void mostrarDatosUsuario(Usuario usuarioCargado);
void mostrarArrUsuarios(Usuario arr[], int validos);

//Buscar y mostrar Por Nombre de Usuario / Consulta
int buscarUsuarioPorNombreUsuario (char nombreDeUsuario[], Usuario arr[], int validos);
void mostrarUsuarioPorNombreUsuario (char nombreDeUsuario[], Usuario arr[], int validos);

//Buscar y mostrar usuario con mayor cantidad de juegos / Consulta?? no se
int buscarUsuarioMayorCantDeJuegosComprados (Usuario arr[], int validos);
void mostrarUsuarioConMayorCantDeJuegos (Usuario arr[], int validos);


// Registro / creación / Alta
Usuario registrarUsuario();
int cargarArrDeUsuariosDinamico (Usuario **arr);

// Billetera / Modificacion
void cargarDineroAlUsuario(Usuario *usuarioACargarDinero);

// Carrito / Modificacion
void cargarACarritoUsuario(Juego **arr, int *validosCarrito, Juego juegoAComprar);

// Biblioteca personal / Modificacion
void cargarABibliotecaUsuario(Juego **arr, int *validosBiblioteca, Juego juegoACargar);

#endif // USUARIO_H_INCLUDED
