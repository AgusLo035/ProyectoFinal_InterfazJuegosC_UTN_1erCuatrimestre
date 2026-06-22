#include "Juego.h"
#include "Usuario.h"
#include "General.h"

char matAdmin[2][LIMITE] = {"admin", "admin"}; //un usuario y una contraseña en la mat del admin
//matAdmin[0] = username
//matAdmin[1] = password
///si después podés editar la función que crea al admin usando esta matriz sería feliz (si no lo haces dsps lo hago :'^) )

///RECORDATORIO: hay que explicar lo que hace cada una de las funciones en comentarios, según lo que dice la consigna.

///Agregar en algún lado método para que no se creen usuarios con nombre igual. Hice una función para eso al final de usuario.c, dsps ver donde ponerla

///Main
int main()
{
    Usuario *arrUsuarios = NULL; //futuro array de usuarios
    int validos = 0; //futuro validos de usuarios

    printf("Bienvenido a STOM! El mejor programa para comprar juegos.\n\n\n");

    int posicionEnArray = menuInicio(&arrUsuarios, &validos); //leer lo que devuelve en general.c

    if (posicionEnArray == -3 || posicionEnArray == -2) //se eligió cerrar el programa o se registró un usuario
    {//Hay diferencia por un printf que ocurre dentro de menuInicio
        return 0; //se cierra el programa.
    }else if (posicionEnArray == -1) //esto ocurre si en algún punto hubo error de fopen, realloc o malloc
    {
        printf("\nHa ocurrido un error critico en alguna parte del programa. Se ha finalizado el programa.\n");
        return 0;
    }

    /// Después de las funciones de menú (ver qué parametros necesitan),
    /// Hay que guardar validos y toda el arrUsuarios en un archivo (hay una función para esto)
    /// No sé si nos puedan recriminar no hacerlo cada vez que se modifica algo relacionado a los usuarios, pero sería poner esta misma función en otros lados
    /// Pero falta terminar mi menú de usuarios, me faltan 2 puntos

    //Y ahora que tengo la posición del usuario puedo comenzar a modificarlo

    //función de menu de usuario
    //dentro hay un if que habilita una última opción de funciones de admin

    //potencialmente acá se pone guardar en el archivo usuarios todo lo de usuarios

    //^ y aunque no parezca eso sería todo el main
    //a menos que se me ocurra hacer algun printf de error

    //-----------------------------------------------------------------

    //Recordatorio de crear al menos 10 juegos
    //Recordatorio que usuarios es todo trabajado con array


    //Para ordernarme pongo lo que necesito
    //0) Intro de STOM (msg de bienvenida)
    //1) Registro/Iniciar sesión
    //1a) Setuppeo de registro (pasar a array el usuario creado, y después a archivo)
    //1b) Setuppeo del sistema de loggeo (verificar si usuario existe, si contra correcta, etc) -> estos datos están en el archivo

    //2) "Interfaz" de lo que vé el usuario (junto a opciones)

    //2 a) Opciones disponibles (usuario comun):
    //2 a) Ver tienda (juegos) -> opción de búsqueda, filtrado y ordenamientos,
    // ver carrito (+ lógica de compra, incluye pila)
    // ver biblioteca
    // deshacer última compra y otra opción de devolver cualquier otro juego (solo disponible si el usuario tiene al menos 1 juego),
    // consultar saldo, cargar saldo
    // eliminar usuario -> he decidido que solo el admin puede eliminar usuarios. Digo para no escribir de más cosas que no se piden.

    //Dentro del menú de arriba, pongo un if mostrando más opciones si el usuario es admin, y pasa lo de abajo

    //2 B) Opciones ADMIN (disponibles únicamente si el usuario es el admin):
    //2 B) Eliminar usuario,
    // agregar/quitar/modificar juegos de tienda,
    // busqueda de usuarios, ver listado de usuarios (y sus datos),



//*********************************************
    //guardarJuegosEnArchivo(JUEGOSTIENDA);//Simulamos los juegos que existen en la aplicacion,
//*********************************************
//    guardarJuegosEnArchivo(JUEGOSTIENDA);
//    leerJuegosDeTienda(JUEGOSTIENDA);

//    leerJuegosOrdenadosNombreTienda(JUEGOSTIENDA);

    return 0;
}
