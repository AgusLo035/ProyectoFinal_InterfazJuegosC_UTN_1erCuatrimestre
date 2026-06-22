#include "General.h"

// sys cls y sys pause
void pausarLimpiarInt() //Pausa y despues limpia la terminal
{
    system("pause");
    system("cls");
}

int menuInicio(Usuario **arrUsuarios, int *validos) //devuelve la posición del usuario a trabajar. Otros resultados/errores posibles: "-3" -> se decidió errar programa. "-2" -> se registró un usuario, se cierra el programa. Antes se pide que reabra el programa e inicie sesión.  "-1" -> error en fopen o malloc/realloc. Se termina el programa.
{
    int posUsuario;
    int decision;

    printf("--MENU--\n\n");
    printf("1. Iniciar sesion.\n");
    printf("2. Registrarse.\n");
    printf("3. Cerrar el programa.\n");

    do
    {
        printf("\nSu decision: ");
        while (scanf("%i", &decision) != 1)
        {
            printf("\nPor favor ingrese el numero de una de las opciones.\n");
            fflush(stdin); //lo que se ingresó que no es número sigue en stdin porque no se pudo leer, con esto lo limpio
            printf("Su decision: ");
        }

        if (decision > 3 || decision < 1)
        {
            printf("\nPor favor ingrese una opcion valida.\n");
        }
    }while(decision > 3 || decision < 1);

    posUsuario = menuOpcionesValidasVerificadas(decision, arrUsuarios, validos);

    if (decision == 3) //opcion 3 es salir del programa
    {
        posUsuario = -3; //para el main significa "cerrar programa"
    }else if(decision == 2)
    {
        posUsuario = -2;
        printf("\nCierre y abra el programa para logearse al usuario creado.\n");
    }

    return posUsuario;
}

int menuOpcionesValidasVerificadas (int decision, Usuario **arrUsuarios, int *validos) //solamente es llamado cuando se verifica el usuario introduce una decisión válida. Devuelve la posición del usuario que se termine loggeando en el array dinámico.
{
    int posUsuario;

    if (decision != 3) //no se continua con el resto del programa si se eligió salirse (que es la opcion 3)
    {
        (*validos) = pasarUsuariosArchivoAArrDin(LISTAUSUARIOS, arrUsuarios); //se llena el arreglo de usuarios (si existen) y se devuelven validos

        if ((*validos) == 0) //si no existe el archivo, se crea ahora
        {
            (*validos) = creacionArchivoDeUsuarios(arrUsuarios); //cant usuarios es igual a -1 si hay error en malloc/abrir el archivo
        }

        if ((*validos) != -1)
        {
            posUsuario = menuOpcionesLoggeoRegistro(decision, arrUsuarios, validos);
        }else //El else ocurre si aparece algún error al abrir el archivo/error en malloc
        {
            printf("\nHa ocurrido un error en la carga de usuarios. Cierre y abra el programa nuevamente.\n");
            posUsuario = -1;
        }
    }else
    {
        printf("\nMuchas gracias por haber utilizado STOM. Vuelva pronto.\n"); //TERMINA EL PROGRAMA
        posUsuario = -3;
    }

    return posUsuario;
}

int menuOpcionesLoggeoRegistro(int decision, Usuario **arrUsuarios, int *cantUsuarios) //tiene solo las funciones de registro y loggeo (se hace después de muchas verificaciones). Devuelve la posición del usuario a trabajar en array
{
    int flag;

    switch (decision)
    {
        case 1:
            flag = sistemaLoggeo (arrUsuarios, cantUsuarios);
            break;
        case 2: ///IMPORTANTE: Hay que verificar que NO puedan existir usuarios del mismo nombre.
            agregarUsuarioAArr (arrUsuarios, cantUsuarios); //Función crea y agrega mediante scanfs a un nuevo usuario al array dinámico.
            guardarArrUsuariosEnArchivo(LISTAUSUARIOS, *arrUsuarios, *cantUsuarios); //Guarda el nuevo usuario en archivo
            flag = -2; //indiciador de que solo se creó usuario
            break;
    }

    return flag;
}

int sistemaLoggeo(Usuario **arrUsuarios, int *cantUsuarios) //Se escribe usuario y contraseña. Si son correctos, devuelve la posición en el array que tiene el usuario, y se continúa con eso. Si no
{
    int posicionUsuarioEnArray = -1;

    char nombreUsuarioIngresado[VERIFICARLIMITE]; //51 para verificacion de caracteres org
    char contraseniaUsuarioIngresado[VERIFICARLIMITE]; //^

    do
    {
        printf("\nIngrese el nombre de usuario: ");
        fflush(stdin);
        scanf(" %50[^\n]", nombreUsuarioIngresado);
        if(strlen(nombreUsuarioIngresado) >= LIMITE)
            printf("\nPor favor evite intentar romper el programa.\n");

    }while(strlen(nombreUsuarioIngresado) >= LIMITE);

    do
    {

        printf("\nIngrese su contrasenia: ");
        fflush(stdin);
        scanf(" %50[^\n]", contraseniaUsuarioIngresado);
        if(strlen(contraseniaUsuarioIngresado) >= LIMITE)
            printf("\nPor favor evite intentar romper el programa.\n");

    }while(strlen(contraseniaUsuarioIngresado) >= LIMITE);

    posicionUsuarioEnArray = verificarUsuarioRegistrado(*arrUsuarios, *cantUsuarios, nombreUsuarioIngresado, contraseniaUsuarioIngresado);

    if (posicionUsuarioEnArray == -1)
    {
        printf("\nEl usuario o contrasenia ingresados son incorrectos. Reinicie el programa e intente nuevamente.\n");
    }

    return posicionUsuarioEnArray;
}
