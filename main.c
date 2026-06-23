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
    int flagGuardado = -1;

    printf("Bienvenido a STOM! El mejor programa para comprar juegos.\n\n\n");

    int posicionEnArray = menuInicio(&arrUsuarios, &validos); //leer lo que devuelve en general.c

    if (posicionEnArray < -1) //se eligió cerrar el programa o se registró un usuario o se colocaron mal los datos de logeo
    {
        return 0; //se cierra el programa.
    }else if (posicionEnArray == -1) //esto ocurre si en algún punto hubo error de fopen, realloc o malloc
    {
        printf("\nHa ocurrido un error crítico en alguna parte del programa. Se ha finalizado el programa.\n");
        return 0;
    }else
    {
        menuPrincipalUsuario(&arrUsuarios, validos, posicionEnArray);
    }

    char decisionGuardado[3] = "si";

    while(flagGuardado == -1 && strcmpi(decisionGuardado, "si") == 0)
    {
        flagGuardado = guardarArrUsuariosEnArchivo(LISTAUSUARIOS, arrUsuarios, validos);
        if (flagGuardado == -1)
        {
            printf("\nHa ocurrido un error en el fopen. No se han guardado ninguno de los cambios. Quiere intentar de nuevo? (Escriba si para intentar de nuevo, cualquier otra cosa para desisitr): ");
            limpiarStdin();
            scanf(" %2[^\n]", decisionGuardado);
            printf("\n");
        }
    }

    if (flagGuardado == -1)
    {
        printf("\nNo se han guardado los cambios. Algo debio salir muy mal.\n");
    }else
    {
        printf("\nSe han guardado los cambios exitosamente. Gracias por usar STOM.\n");
    }

    return 0;




//*********************************************
    //guardarJuegosEnArchivo(JUEGOSTIENDA);//Simulamos los juegos que existen en la aplicacion,
//*********************************************
//    guardarJuegosEnArchivo(JUEGOSTIENDA);
//    leerJuegosDeTienda(JUEGOSTIENDA);

//    leerJuegosOrdenadosNombreTienda(JUEGOSTIENDA);

    return 0;
}
