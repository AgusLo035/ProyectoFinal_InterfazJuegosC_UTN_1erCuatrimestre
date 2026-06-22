#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED
#include "Juego.h"
#include "Usuario.h"
#include "pila.h"


///Prototipado

void pausarLimpiarInt();
int menuInicio(Usuario **arrUsuarios, int *validos); //devuelve la posición del usuario a trabajar. Otros resultados/errores posibles: "-3" -> se decidió errar programa. "-2" -> se registró un usuario, se cierra el programa. Antes se pide que reabra el programa e inicie sesión.  "-1" -> error en fopen o malloc/realloc. Se termina el programa.
int menuOpcionesValidasVerificadas (int decision, Usuario **arrUsuarios, int *validos); //solamente es llamado cuando se verifica el usuario introduce una decisión válida. Devuelve la posición del usuario que se termine loggeando en el array dinámico.
int menuOpcionesLoggeoRegistro(int decision, Usuario **arrUsuarios, int *cantUsuarios); //tiene solo las funciones de registro y loggeo (se hace después de muchas verificaciones). Devuelve la posición del usuario a trabajar en array
int sistemaLoggeo(Usuario **arrUsuarios, int *cantUsuarios); //Se escribe usuario y contraseña. Si son correctos, devuelve la posición en el array que tiene el usuario, y se continúa con eso. Si no



#endif // GENERAL_H_INCLUDED
