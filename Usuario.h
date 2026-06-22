#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include "Juego.h"
#include <errno.h> //errno es una variable global. Al ocurrir cualquier error al ejecutar algo, codeblocks guarda el error en esta variable. Me sirve para saber si un fopen falló porque el archivo no existe, o porque hubo cualquier otro problema con el fopen

#define VERIFICARLIMITE 51 //estaba en juegos, te lo traje acá pq en juegos no se usa
#define LISTAUSUARIOS "usuarios.bin"

extern char matAdmin[2][LIMITE]; //Se declara que existe en un lugar externo fuera de este archivo, usa el contenido que esta en el main
                                // admin, admin

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
///A HACER:
///Requisito fundamental no guardar usuarios repetidos (según consigna)
///Ver si puedo re-utilizar y modificar la que tengo en juego.c para esto
Usuario registrarUsuario(); //crea un usuario
Usuario crearUsuarioAdmin(); //crea un usuario "admin"
void agregarUsuarioAArr (Usuario **arr, int *cantUsuarios); //recibe el array dinámico de usuarios, aumenta validos por 1, ingresa al usuario en el array. Es básicamente una opción de registro.
int cargarArrDeUsuariosDinamico (Usuario **arr);
///^ esta función ya no existe
///[A HACER] Hasta te diría que eliminemos todos los headers y los pongamos de nuevo, hay muchas funciónes que fueron borradas o modificadas


// Baja / eliminar
void eliminarUsuarioComoAdmin(char nombreDeUsuarioAEliminar[], Usuario arr[], int validos); //verifica si existe el usuario que se quiere eliminar. Llama a la función de abajo si lo encuentra, caso contrario no hace nada.
void eliminarUsuario(Usuario *usuarioAEliminar); //elimina de manera lógica al usuario que se recibe (cambia su flag de eliminado a 1)

//Funciones con Pilas
int contarDimPila(Pila pila);
void reajustarDimPilaTope(Pila *pila, int datoAIngresar);

/// Funciones con Archivos
int pasarUsuariosArchivoAArrDin (char nombreArchivo[], Usuario **arr);
void pasarUsuarioArchiAArrDinArchi (FILE *archi, Usuario **arr, int usuariosRegistradosEnSistema);
int creacionArchivoDeUsuarios (Usuario **arr); //si no existe el archivo usuario, lo crea y añade al primer usuario admin
Usuario leerUsuarioCompletoDeArchi(FILE *archi); //NOTA: antes de llamar a esta función, sí o si hay que mover el indicador de posición 1 posición delante de los validos al inicio del archivo
// Pasar arreglo dinamico de usuarios a Archivo
void guardarArrUsuariosEnArchivo(char nombreArchivo[], Usuario *arr, int validosUsuarios); //Guarda todos los usuarios en archivo. Nota: utiliza "wb", se elimina el archivo ya existente
void guardarUnUsuarioEnArchi(FILE *archi, Usuario usuario);

// Funciones para el usuario Admin
int verificarAdmin(char mat[][LIMITE], char usuarioAdmin[], char passwordAdmin[]);
void eliminarUsuarioComoAdmin(char nombreDeUsuarioAEliminar[], Usuario arr[], int validos);
///[A HACER]:
///hay que hacer un ordenamiento de usuarios con selección e inserción (parte de consigna). Tal vez crear una copia del array usuarios y que el admin pueda ordenar y mostrar ese array para ver a todos los usuarios

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
///^ Revisé la consigna, se refiere a filtrar por eleccion (buscar por parametro X usuario por ejemplo)
///[A HACER] -> un filtro de usuarios (busqueda de usuarios que tengan mas de X juego?). Creo que se puede hacer un copy paste del que está en juegos


// Billetera / Precio / Modificacion
void cargarDineroAlUsuario(Usuario *usuarioACargarDinero);
void debitarDineroAlUsuario (Usuario *usuarioADebitar, float montoADebitar);
float sumarPrecioJuegos (Juego arr[], int validos, int i);

// Carrito / Modificacion
float cargarACarritoUsuario(Juego **carrito, int *validosCarrito, Juego juegoAComprar); //Carga un juego al carrito de un usuario. Devuelve lo que se debe de debitar al usuario
void mostrarCarritoDeUsuario (Usuario usuario); //Muestra el carrito de un usuario
void comprarJuegosDelCarrito(Usuario *usuarioAComprarJuegos);

// Biblioteca personal / Modificacion
void cargarABibliotecaUsuario(Usuario *usuarioACargar, Juego juegoACargar); //

// Quitar de biblioteca
void quitarJuegoDeBibliotecaUsuario(Juego **arr, int *validosBiblioteca, Juego juegoAQuitar);
void deshacerUltimaCompra(Pila *historialId, Usuario *usuarioAReembolsarJuego); //Y reembolsa el dinero al usuario

// Consulta?
int verificarUsuarioRegistrado(Usuario arr[], int validos, char username[], char password[]);
int verificarNombreUsuarioRegistrado(Usuario *arr, int validos, char username[]);


#endif // USUARIO_H_INCLUDED
