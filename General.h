#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED
#include "Juego.h"
#include "Usuario.h"
#include "pila.h"


///Prototipado

void pausarLimpiarInt(); //Pausa y despues limpia la terminal
int menuInicio(Usuario **arrUsuarios, int *validos); //Contiene el menu con opciones de registrado y loggeo. Devuelve la posición del usuario que se loggea. Tiene capacidad de devolver códigos de error:
//Errores posibles: "-4" -> datos erroneos de logeo, se cierra el programa. "-3" -> se decidió cerrar programa. "-2" -> se registró un usuario, significa se debe terminar el programa. "-1" -> error en fopen o malloc/realloc, significa se debe terminar el programa.
int menuOpcionesValidasVerificadas (int decision, Usuario **arrUsuarios, int *validos); //Contiene las funciones resultantes de la decisión tomada en menuinicio(). Se carga el archivo de usuarios al array dinámico. Devuelve la posición del usuario que se termine loggeando en el array dinámico. Puede devolver identificador de error.
int menuOpcionesLoggeoRegistro(int decision, Usuario **arrUsuarios, int *cantUsuarios); //Contiene las funciones de registro y loggeo. Devuelve la posición del usuario a trabajar en array. Puede devolver identificador de error.
int sistemaLoggeo(Usuario **arrUsuarios, int *cantUsuarios); //Se escribe usuario y contraseña. Si son correctos, devuelve la posición en el array que tiene el usuario, y se continúa el resto del programa con esa posición. Caso contrario, devuelve error.

///Menu de usuario normal
void menuPrincipalUsuario (Usuario **arrUsuarios, int validos, int posUsuarioActual); //Contiene el menu principal una vez logeado. Llama funciones y a otros menús de ser necesario.
float logicaDeCompraCarrito (Usuario **arrUsuarios, int validos, int posUsuarioActual, float dineroAPagar); //Agrega un juego al carrito. Se verifica no esté ya en carrito o biblioteca. Devuelve el valor total de todos los juegos del carrito sumados.

///Menu específico para la tienda
void menuTienda (); //como solo muestra datos relacionados a qué hay en la tienda, no recibe datos cargados de usuarios. Llama a funciones de juego.h

///Menu de admin
void funcionesAdicionalesParaAdmin(Usuario *arrUsuarios, int validos); //Contiene un menú con acciones solo permitidas para el admin. La mayoría relacionada con modificar juegos y/o usuarios.
void ejecutarFuncionesAdicionalesParaAdmin(int decision, Usuario usuariosEnSistema[], int validos); //Ejecuta las funciones según la decisión tomada en funcionesAdicionalesParaAdmin()




#endif // GENERAL_H_INCLUDED
