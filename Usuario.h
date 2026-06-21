#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include "Juego.h"
#include <errno.h> //errno es una variable global. Al ocurrir cualquier error al ejecutar algo, codeblocks guarda el error en esta variable. Me sirve para saber si un fopen falló porque el archivo no existe, o porque hubo cualquier otro problema con el fopen

#define VERIFICARLIMITE 51 //estaba en juegos, te lo traje acá pq en juegos no se usa
#define LISTAUSUARIOS "usuarios.bin"

typedef struct
{
    char userName[LIMITE];
    char password[LIMITE];
    int eliminado; //acordarse cuando se busca un usuario verificar si esta eliminado
    float billetera;
    Pila historialDeJuego; //ultimos 50 juegos comprados del usuario

    int validosCarrito;
    Juego *carritoDeJuegos; //vuelve a ser array dinámico, por tanto hay que modificar el fwrite también

    int validosBiblioteca;
    Juego *bibliotecaUsuario; //Dolor de cabeza significativo: hice mal (aunque excelente enterarnos ahora) y le pregunté a chatGPT por esto, resulta que en el archivo no se guardan la biblioteca ni el carrito como array, sino como una dirección de memoria/puntero. No incluye a los datos. Para guardar los datos hay que hacer muchos fwrite para cada una de las variables de la estructura, lo mismo para leer cada usuario, es un fread por cada variable. Es medio engorroso por lo que estuve viendo y funciones como la de contar la cantidad de usuarios dejan de funcionar. Si es lo suficientemente engorroso, voy a dejar estos arrays como fijos o separo al menos la bilbioteca de todos los usuarios en otro archivo. Ya estamos usando arrays dinámicos para trabajar con los usuarios en el main así que seguiríamos cumpliendo el requisito del TP.

} Usuario;

///No te quiero tocar esto por si acaso, lo podes ordenar en Alta, Baja, Modificación, Consulta, Listados?
///Igual veo faltan los últimos 2 de consul. y listados que hay que pensar cómo hacerlos
///Tal vez que el admin puede acceder a consulta y listados (en alguno de estos dos va la idea de la pila de la profe de los usuarios más activos también)
///(hoy/mañana te ayudo pq algunos creo sería literal copiar y pegar (con mini modificaciones) las funciones que ya tenemos en juegos.h/c)

// Registro / creación / Alta
Usuario registrarUsuario();
Usuario crearUsuarioAdmin();
void agregarUsuarioAArr (Usuario **arr, int *cantUsuarios) ;
int cargarArrDeUsuariosDinamico (Usuario **arr);

//Funciones con Pilas
int contarDimPila(Pila pila);
void reajustarDimPilaTope(Pila *pila, int datoAIngresar);

// Funciones con Archivos
int pasarUsuariosArchivoAArrDin (char nombreArchivo[], Usuario **arr);
void pasarUsuarioArchiAArrDinArchi (FILE *archi, Usuario **arr, int usuariosRegistradosEnSistema);
int creacionArchivoDeUsuarios (Usuario **arr); //si no existe el archivo usuario, lo crea y añade al primer usuario admin
Usuario leerUsuarioCompletoDeArchi(FILE *archi); //NOTA: antes de llamar a esta función, sí o si hay que mover el indicador de posición 1 posición delante de los validos al inicio del archivo
// Pasar arreglo dinamico de usuarios a Archivo
void guardarArrUsuariosEnArchivo(char nombreArchivo[], Usuario arr[], int validosUsuarios);
void guardarUnUsuarioEnArchi(FILE *archi, Usuario usuario);

// Funciones para el usuario Admin
int verificarAdmin(char mat[][LIMITE], char usuarioAdmin[], char passwordAdmin[]);
void eliminarUsuarioComoAdmin(char nombreDeUsuarioAEliminar[], Usuario arr[], int validos);
///hay que hacer un ordenamiento de usuarios con selección e inserción (parte de consigna). Tal vez crear una copia del array usuarios y que el admin pueda ordenar y mostrar ese array para ver a todos los usuarios

// Borrado Logico / Baja
void eliminarUsuario(Usuario *usuarioAEliminar);

// Mostrar Datos / Listado
void mostrarDatosUsuario(Usuario usuarioCargado);
void mostrarArrUsuarios(Usuario arr[], int validos);

//Buscar y mostrar Por Nombre de Usuario / Consulta
int buscarUsuarioPorNombreUsuario (char nombreDeUsuario[], Usuario arr[], int validos);
void mostrarUsuarioPorNombreUsuario (char nombreDeUsuario[], Usuario arr[], int validos);

//Buscar y mostrar usuario con mayor cantidad de juegos
int buscarUsuarioMayorCantDeJuegosComprados (Usuario arr[], int validos);
void mostrarUsuarioConMayorCantDeJuegos (Usuario arr[], int validos);
//Nota: no voy a usar estos (a menos que objetes)
//pq sino como admin tendría 3 opciones de consulta
///Igual esto es lo que pedia la consigna de buscar una struct por un campo en especifico de ella

// Billetera / Precio / Modificacion
void cargarDineroAlUsuario(Usuario *usuarioACargarDinero);
void debitarDineroAlUsuario (Usuario *usuarioADebitar, float montoADebitar);
float sumarPrecioJuegos (Juego arr[], int validos, int i);

// Carrito / Modificacion
float cargarACarritoUsuario(Juego **arr, int *validosCarrito, Juego juegoAComprar);

// Biblioteca personal / Modificacion
void cargarABibliotecaUsuario(Usuario *usuarioACargar, Juego juegoACargar); //

// Quitar de biblioteca
void quitarJuegoDeBibliotecaUsuario(Juego **arr, int *validosBiblioteca, Juego juegoAQuitar);
void deshacerUltimaCompra(Pila *historialId, Usuario *usuarioAReembolsarJuego); //Y reembolsa el dinero al usuario

#endif // USUARIO_H_INCLUDED
