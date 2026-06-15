#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include "Juego.h"

typedef struct
{
    char   userName[LIMITE];
    char   password[LIMITE];
    float  billetera;
    Juego *bibliotecaUsuario;
    Juego *carritoDeJuegos;
    int    validosBiblioteca;
    int    validosCarrito;
    int    eliminado;
} Usuario;

// Registro / creación
Usuario registrarUsuario();

// Billetera
void cargarDineroAlUsuario(Usuario *usuarioACargarDinero);

// Carrito
void cargarACarritoUsuario(Juego **arr, int *validosCarrito, Juego juegoAComprar);

// Biblioteca personal
void cargarABibliotecaUsuario(Juego **arr, int *validos, Juego juegoACargar);

#endif // USUARIO_H_INCLUDED
