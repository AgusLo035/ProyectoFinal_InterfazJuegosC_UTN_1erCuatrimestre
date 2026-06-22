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

    int posicionEnArray = menuInicio(&arrUsuarios, &validos); //leer lo que devuelve en general.c


    if (posicionEnArray == -3 || posicionEnArray == -2) //se eligió cerrar el programa o se registró un usuario
    {
        return 0; //se cierra el programa.
    }else if (posicionEnArray == -1)
    {
        printf("\nHa ocurrido un error crítico en alguna parte del programa. Se ha finalizado el programa.\n");
        return 0;
    }


//    Usuario *arr = NULL; //arreglo que contiene a todos los usuarios

    ///Temporal para probar carrito
//
//    Juego test = cargarNuevoJuego();
//    Juego test2 = cargarNuevoJuego();
//
//    Usuario *arrUsuarios = malloc(sizeof(Usuario)*2); //creo un array de 1 usuario
//
//    Usuario admin = crearUsuarioAdmin();
//
//    arrUsuarios[0] = admin;
//
//    cargarACarritoUsuario(&arrUsuarios[0].carritoDeJuegos, &arrUsuarios[0].validosCarrito, test);
//    cargarACarritoUsuario(&arrUsuarios[0].carritoDeJuegos, &arrUsuarios[0].validosCarrito, test2);
//
//    mostrarDatosUsuario(arrUsuarios[0]);
//
//    mostrarCarritoDeUsuario(arrUsuarios[0]);


    ///FIN Temporal

    //Recordatorio de crear admin y al menos 10 juegos
    //Que admin sea el primer usuario
    //Recordatorio que usuarios es todo trabajado con array

    printf("Bienvenido a STOM! El mejor programa para comprar juegos.\n\n\n");

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
