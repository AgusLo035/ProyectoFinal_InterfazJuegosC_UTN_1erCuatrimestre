#include "Usuario.h"

char matAdmin[2][LIMITE] = {"admin", "admin"}; //un usuario y una contraseña en la mat del admin
//matAdmin[0] = username
//matAdmin[1] = password

///Main
int main()
{
//*********************************************
    //guardarJuegosEnArchivo(JUEGOSTIENDA, "a+b");//Simulamos los juegos que existen en la aplicacion,
//*********************************************
//    guardarJuegosEnArchivo(JUEGOSTIENDA, "ab");
//    leerJuegosDeTienda(JUEGOSTIENDA);

    leerJuegosOrdenadosNombreTienda(JUEGOSTIENDA);

    //Yo creo que ya estariamos maso, despues en clase hacemos el main
    return 0;
}
