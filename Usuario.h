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
///Igual veo faltan los últimos 3 de modif. consul. y listados que hay que pensar cómo hacerlos
///Tal vez cada usuario puede modificar su nombre y el admin puede acceder a consulta y listados (en alguno de estos dos va la idea de la pila de la profe de los usuarios más activos también) y listados
///(^ esto porque el "ABMCL" la consigna dice hacerlo en relación a CADA UNA de las DOS structs que se piden como mínimo)
///(hoy/mañana te ayudo pq algunos creo sería literal copiar y pegar (con mini modificaciones) las funciones que ya tenemos en juegos)

// Borrado Logico
void eliminarUsuario(Usuario *usuarioAEliminar);

// Mostrar Datos
void mostrarDatosUsuario(Usuario usuarioCargado);
void mostrarArrUsuarios(Usuario arr[], int validos);

// Registro / creación
Usuario registrarUsuario();
int cargarArrDeUsuariosDinamico (Usuario **arr);

// Billetera
void cargarDineroAlUsuario(Usuario *usuarioACargarDinero);

// Carrito
void cargarACarritoUsuario(Juego **arr, int *validosCarrito, Juego juegoAComprar);

// Biblioteca personal
void cargarABibliotecaUsuario(Juego **arr, int *validosBiblioteca, Juego juegoACargar);

#endif // USUARIO_H_INCLUDED
