#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "pila.h"
#include "stom.h"


///Main
int main()
{
//*********************************************
    //guardarJuegosEnArchivo(JUEGOSTIENDA, "a+b");//Simulamos los juegos que existen en la aplicacion,
//*********************************************
//    guardarJuegosEnArchivo(JUEGOSTIENDA, "ab");
//    leerJuegosDeTienda(JUEGOSTIENDA);
    leerJuegosOrdenadosNombreTienda(JUEGOSTIENDA);
    return 0;
}
