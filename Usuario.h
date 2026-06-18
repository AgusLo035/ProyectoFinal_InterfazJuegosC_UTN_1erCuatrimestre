#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include "Juego.h"

#define VERIFICARLIMITE 51 //estaba en juegos, te lo traje acá pq en juegos no se usa

typedef struct
{
    char userName[LIMITE];
    char password[LIMITE];
    float billetera;
    Juego *bibliotecaUsuario;
    Juego *carritoDeJuegos;
    int validosBiblioteca;
    int validosCarrito;
<<<<<<< HEAD
    int eliminado; //acordarse cuando se busca
=======
    int eliminado;
>>>>>>> 0201745f9a053a126282d0804e018ee1e80708ca
    Pila historialDeJuego; //ultimos juegos comprados del usuario, adios a la idea de usuarios activos

} Usuario;

///No te quiero tocar esto por si acaso, lo podes ordenar en Alta, Baja, Modificación, Consulta, Listados?
///Igual veo faltan los últimos 2 de consul. y listados que hay que pensar cómo hacerlos
///Tal vez que el admin puede acceder a consulta y listados (en alguno de estos dos va la idea de la pila de la profe de los usuarios más activos también)
///(hoy/mañana te ayudo pq algunos creo sería literal copiar y pegar (con mini modificaciones) las funciones que ya tenemos en juegos.h/c)

//Funciones con Pilas
int contarDimPila(Pila pila);
void reajustarDimPilaTope(Pila *pila, int datoAIngresar);

// Funciones con Archivos
int contarCantDeUsuariosEnArchi(FILE *archi);
int pasarUsuariosAArr(FILE *archi, Usuario **arr);
int pasarUsuariosDeArchivoAArr (char nombreArchivo[], Usuario **arr);

// Funciones para el usuario Admin
int verificarAdmin(char mat[][LIMITE], char usuarioAdmin[], char passwordAdmin[]);
void eliminarUsuarioComoAdmin(char nombreDeUsuarioAEliminar[], Usuario arr[], int validos);

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

// Billetera / Precio / Modificacion
void cargarDineroAlUsuario(Usuario *usuarioACargarDinero);
void debitarDineroAlUsuario (Usuario *usuarioADebitar, float montoADebitar);
float sumarPrecioJuegos (Juego arr[], int validos, int i);

// Carrito / Modificacion
float cargarACarritoUsuario(Juego **arr, int *validosCarrito, Juego juegoAComprar);

// Biblioteca personal / Modificacion
void cargarABibliotecaUsuario(Usuario *usuarioACargar, Juego juegoACargar); //la funcion mas chota en mi opinion

// Quitar de biblioteca
void quitarJuegoDeBibliotecaUsuario(Juego **arr, int *validosBiblioteca, Juego juegoAQuitar);
void deshacerUltimaCompra(Pila *historialId, Usuario *usuarioAReembolsarJuego); //Y reembolsa el dinero al usuario

#endif // USUARIO_H_INCLUDED
