#include "General.h"

void limpiarStdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
            printf("\nPor favor ingrese el numero de una de las opciones.\n\n");
            limpiarStdin(); //lo que se ingresó que no es número sigue en stdin porque no se pudo leer, con esto lo limpio
            printf("Su decision: ");
        }

        if (decision > 3 || decision < 1)
        {
            printf("\nPor favor ingrese una opcion valida.\n");
            limpiarStdin();
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
    }else if(decision == 1 && posUsuario == -1) // diferencio login fallido también -> cierro el programa
    {
        posUsuario = -4;
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

int sistemaLoggeo(Usuario **arrUsuarios, int *cantUsuarios) //Se escribe usuario y contraseña. Si son correctos, devuelve la posición en el array que tiene el usuario, y se continúa el resto del programa con esa posición. Caso contrario, devuelve error.
{
    int posicionUsuarioEnArray = -1;

    char nombreUsuarioIngresado[VERIFICARLIMITE]; //51 para verificacion de caracteres org
    char contraseniaUsuarioIngresado[VERIFICARLIMITE]; //^

    do
    {
        printf("\nIngrese el nombre de usuario: ");
        limpiarStdin();
        scanf(" %50[^\n]", nombreUsuarioIngresado);
        if(strlen(nombreUsuarioIngresado) >= LIMITE)
            printf("\nPor favor evite intentar romper el programa.\n");

    }while(strlen(nombreUsuarioIngresado) >= LIMITE);

    do
    {

        printf("\nIngrese su contrasenia: ");
        limpiarStdin();
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



///Funciones de Usuario ya logeado

    //2 a) Opciones disponibles (usuario comun):
    //2 a) Ver tienda (juegos) -> opción de búsqueda, filtrado y ordenamientos,
    // ver carrito (+ lógica de compra, incluye pila)
    // ver biblioteca
    // deshacer última compra y otra opción de devolver cualquier otro juego (solo disponible si el usuario tiene al menos 1 juego),
    // consultar saldo, cargar saldo
    // eliminar usuario -> he decidido que solo el admin puede eliminar usuarios. Digo para no escribir de más cosas que no se piden.

    //Dentro del menú de arriba, pongo un if mostrando más opciones si el usuario es admin, y pasa lo de abajo


    ///FUNCIONAMIENTO DE CARRITO
    //por no describirlo antes ahora hay dolor
    //usuario elige opción de agregar juego a carrito -> busca por nombre. Si existe Y no está ya en el carrito Y el usuario no lo tiene ya en su biblioteca, se agrega (función "cargarACarritoUsuario") y se avisa. Si no existe o no se cumple uno de los otros dos requisitos, se avisa que no se agregó.
    //usuario vuelve al menú principal (puede decidir agregar otro juego)
    //ahora al elegir "comprar juegos de mi carrito" -> llamo a "sumarPrecioJuegos" para que me calcule la cant a pagar y se compara con el sueldo actual
    //si la cant a pagar es mayor al saldo actual, no pasa nada. Si lo es, se llama a "cargarABibliotecaUsuario" -> pero parece necesito la lógica para agregar todos los juegos del carrito, pq la función solo acepta 1

void menuPrincipalUsuario (Usuario **arrUsuarios, int validos, int posUsuarioActual) //Contiene el menu principal. Llama funciones y a otros menús de ser necesario.
{
    char continuo[3] = "si";
    int decisionMenu;
    float dineroAPagar = sumarPrecioJuegos((*arrUsuarios)[posUsuarioActual].carritoDeJuegos, (*arrUsuarios)[posUsuarioActual].validosCarrito, 0); //al entrar al menu, si el usuario tiene juegos en su carrito, se calcula cuanto debe pagar
    //^ después ver si reemplazar con sumarJuegosEnCarrito no genera problemas
    char nombreAIngresarCaseDos[LIMITE];
    Juego juegoAAniadirCaseDos;
    float totalEnCarritoCaseDos;

    do
    {
        printf("\n--MENU PRINCIPAL--\n\n");
        printf("1. Ver tienda.\n"); //DONE
        printf("2. Agregar juego a carrito.\n"); ///Agrega UN juego al carrito. ///MODULARIZAR EN FUNCIÓN, PERO 99% DONE
        printf("3. Ver mi carrito.\n"); //DONE
        printf("4. Vaciar mi carrito.\n"); ///FALTA MODULARIZAR
        printf("5. Comprar juegos de mi carrito.\n");
        printf("6. Deshacer ultima compra.\n");
        printf("7. Consultar saldo.\n"); //DONE
        printf("8. Cargar saldo.\n"); //DONE
        printf("9. Salir del programa.\n"); //DONE
        printf("10. OPCIONES ADMIN.\n"); //DONE
        printf("-------\n\n");

        printf("Eliga la opcion a la que desea ingresar: ");

        while (scanf(" %i", &decisionMenu) != 1)
        {
            printf("\nPor favor ingrese el numero de una de las opciones.\n\n");
            limpiarStdin();
            printf("Eliga la opcion a la que desea ingresar: ");
        }

        switch (decisionMenu)
        {
            case 1:
                menuTienda();
                break;
            case 2:
                printf("\nIngrese el nombre del juego a aniadir al carrito: ");
                fflush(stdin);
                scanf(" %49[^\n]", nombreAIngresarCaseDos);

                juegoAAniadirCaseDos = buscarJuegoPorNombre(nombreAIngresarCaseDos);

                if(juegoAAniadirCaseDos.id == -1) // suponiendo que el archivo existe porque -1 puede ser si el archivo no existe o no se encontro el juego
                {
                    printf("\nEl juego no existe\n");
                    break;
                }
                else // Se carga el juego que se quiere añadir al carrito al carrito del usuario si no ocurre un error o advertencia
                {
                    totalEnCarritoCaseDos = cargarACarritoUsuario(arrUsuarios[posUsuarioActual], juegoAAniadirCaseDos); // Se pasa el juego al carrito y se devuelve el total, solo para mostrar, el case 2 solo es para agregar un juego, no para debitar
                    if(totalEnCarritoCaseDos == -1)
                        printf("\nOcurrio un ERROR. . . El carrito no fue modificado. . .\n");
                    else if (totalEnCarritoCaseDos == -2)
                        printf("\nADVERTENCIA: YA tienes este juego en el carrito. . .\n");
                    else
                        printf("\nLa suma de todos los juegos en tu carrito es de: $%.2f\n", totalEnCarritoCaseDos); // El carrito es modificado agregando el juego
                }
                // No es necesario hacer mas que esto porque para eso estan las demas opciones
                break;
                //funcion que agrega juego de tienda a carrito
                //^ quiero que el usuario busque juego por nombre -> si existe, se pasa el juego como parametro a "cargarACarritoUsuario" -> se continua preguntando con do while si quiere agregarse más al carrito.
                //antes de agregar el juego al carrito, debo de verificar que no exista ya en el carrito o en la bilbioteca del usuario
                //puede que tenga que modificar la función de arriba
                //tengo que hacer una función que vacíe todo el carrito (pq parece lo más fácil de escribir, no quiero hacer otro sistema de quitar un juego específico dsps de verificar exista en carrito)
                /// Te dejo aca abajo tu comentario
                //esto va a estar en función int que devuelve el "dinero a pagar" actual (con flags de error incluídas)
            case 3:
                mostrarCarritoDeUsuario((*arrUsuarios)[posUsuarioActual]);
                break;
            case 4: //para esto hacer una funcion llamada "confirmarIntencionEliminarCarrito" donde pregunto si de verdad quiere eliminar todo
                if((*arrUsuarios)[posUsuarioActual].validosCarrito == 0)
                {
                    printf("\nNo hay juegos en su carrito.\n\n");
                }else
                {
                    free((*arrUsuarios)[posUsuarioActual].carritoDeJuegos);
                    (*arrUsuarios)[posUsuarioActual].carritoDeJuegos = NULL;
                    (*arrUsuarios)[posUsuarioActual].validosCarrito = 0;
                    printf("\nSe han eliminado todos los juegos de su carrito.\n\n");
                }
                break;
            case 5: //modularizar -> confirmar usuario tiene dinero (retornar flag)
                if((*arrUsuarios)[posUsuarioActual].billetera >= dineroAPagar) //al usuario le alcanza
                {
                    comprarJuegosDelCarrito(&(*arrUsuarios)[posUsuarioActual]);
                }else
                {
                    printf("\nSus $%f no alcanzan para comprar su carrito, cuyo total es $%f. Agregue dinero o vacie el carrito.", (*arrUsuarios)[posUsuarioActual].billetera, dineroAPagar);
                }
                break;
            case 6:
                deshacerUltimaCompra(&(*arrUsuarios)[posUsuarioActual].historialDeJuego, &(*arrUsuarios)[posUsuarioActual]);
                break;
            case 7:
                printf("\nSueldo actual: $%f", (*arrUsuarios)[posUsuarioActual].billetera);
                printf("\n");
                break;
            case 8:
                cargarDineroAlUsuario(&(*arrUsuarios)[posUsuarioActual]);
                break;
            case 9:
                printf("\nMuchas por visitar STOM. Esperamos vuelva pronto.\n\n");
                break;
            case 10:
                if (strcmp((*arrUsuarios)[posUsuarioActual].userName, "admin") == 0)
                {
                    funcionesAdicionalesParaAdmin(*arrUsuarios, validos); //llamo a tu función, creo que también hay que darle el array dinámico y validos
                }else
                {
                    printf("\nUsted no es admin. No puede acceder a las funciones admin.\n\n");
                }
        }//fin del switch
    }while(strcmpi(continuo,"si") == 0 && decisionMenu != 9); //puede que desestime la opción de "si", no me acuerdo por qué la puse, pero la idea es que el usuario esté en este menú infinitamente hasta que decida escribir "9"
}


float logicaDeCompraCarrito (Usuario **arrUsuarios, int validos, int posUsuarioActual, float dineroAPagar) //Agrega un juego al carrito. Se verifica no esté ya en carrito o biblioteca. Devuelve el valor total de todos los juegos del carrito sumados.
{
    float saldoRestar = 0; //va a modificarse como flag de error (-1) o como el saldo que hay que quitarle al usuario

    int flagExistenciaJuegoEnBiblioteca;
    int flagExistenciaJuegoEnCarrito;
    char juegoBuscado[LIMITE];
    Juego juegoAIngresar;
    printf("\nEscriba el juego que quiere agregar a su carrito: ");
    scanf(" %49[^\n]", juegoBuscado);
    juegoAIngresar = buscarJuegoPorNombre(juegoBuscado);
    flagExistenciaJuegoEnBiblioteca = verificarSiJuegoEnBibliotecaUsuario(&(*arrUsuarios)[posUsuarioActual], juegoAIngresar);
    flagExistenciaJuegoEnCarrito = verificarSiJuegoEnCarritoUsuario(&(*arrUsuarios)[posUsuarioActual], juegoAIngresar);

    if (flagExistenciaJuegoEnBiblioteca == 0 && flagExistenciaJuegoEnCarrito == 0)
    {
        if (juegoAIngresar.id == -1) //si falla la busqueda/fopen
        {
            printf("\nNo se ha podido abrir el archivo de juegos para agregar al carrito.\n\n");
            saldoRestar = -1; //flag de error
        }else
        {
            int auxDineroAPagar = cargarACarritoUsuario(&(*arrUsuarios)[posUsuarioActual], juegoAIngresar); //si devuelve -1 -> error realloc
            printf("\nEl monto a pagar por el total de juegos en su carrito es $%f. Revise su saldo antes de ir a pagar.\n", dineroAPagar);
            if (auxDineroAPagar != -1 && auxDineroAPagar != -2)
            {
                saldoRestar = auxDineroAPagar; //voy a devolver este valor a pagar
                printf("\nSe ha cargado el juego al carrito exitosamente.\n\n");
            }else if(auxDineroAPagar == -2)
            {
                printf("\nEste juego ya esta en su carrito.\n");
                saldoRestar = -1;
            }else
            {
                printf("\nOcurrio un error al aumentar la cantidad de espacio en el carrito. Intente de nuevo.\n");
                saldoRestar = -1;
            }
        }
    }else
    {
        printf("\nEl juego ya se encuentra en su carrito o biblioteca. Elija otro juego.\n");
        saldoRestar = -1;
    }

    return saldoRestar;
}


// opción de búsqueda, filtrado y ordenamientos,
void menuTienda () //como solo muestra datos relacionados a qué hay en la tienda, no recibe datos cargados de usuarios
{
    int decision;

    do
    {
        printf("\n--Menu de Tienda--\n\n");
        printf("1. Ver todos los juegos.\n");
        printf("2. Filtrar juegos por categoria.\n");
        printf("3. Ver juegos por orden de precio.\n");
        printf("4. Ver juegos por orden alfabetico.\n");
        printf("5. Volver al menu principal.\n");
        printf("----------\n\n");

        printf("Su decision: ");

        while (scanf(" %i", &decision) != 1)
        {
            printf("\nPor favor ingrese un numero.\n\n");
            limpiarStdin();
            printf("Su decision: ");
        }

        switch(decision)
        {
            case 1:
                leerJuegosDeTienda(JUEGOSTIENDA);
                break;
            case 2:
                {
                char categoriaIngresada[LIMITE];
                printf("\nIngrese la categoria que desea filtrar: ");
                limpiarStdin();
                scanf(" %49[^\n]", categoriaIngresada);
                leerJuegosFiltradosTienda(JUEGOSTIENDA, categoriaIngresada);
                break;
                }
            case 3:
                leerJuegosOrdenadosPrecioTienda(JUEGOSTIENDA);
                break;
            case 4:
                leerJuegosOrdenadosNombreTienda(JUEGOSTIENDA);
                break;
            case 5:
                break;
            default:
                printf("\nEsa no es una opcion valida. Intente de nuevo.\n");
                break;
        }

    }while (decision != 5); //solamente se sale del menu si efectivamente quiere salirse (opcion 5)
}








///Funciones admin

///[A HACER] <- puse muchas de estas tags por el código para no perderme en lo que falta hacer
/// necesito que agregues más opciones de switch:
/// hacé que admin también tenga la opción de añadir y otra de eliminar juegos <- todo eso está ya en funciones por suerte (juego.h), es solo llamarlas dependiendo el switch
/// y una ultima opción en el switch para volver al menú normal (y dejá esa opción vacía, después le agrego lo que necesito)

///HECHO ^^^^^^^^^^^^^^^^ FALTA esa ultima opcion

void funcionesAdicionalesParaAdmin(Usuario *arrUsuarios, int validos)
{
    int decision;

    printf("\n--MENU DEL ADMIN--\n\n");
    printf("1. Eliminar Usuario.\n");
    printf("2. Modificar un Juego.\n");
    printf("3. Cargar un nuevo Juego a la Tienda\n");
    printf("4. Quitar un Juego de la Tienda\n");
    printf("5. Buscar usuario.\n");
    printf("6. Ver usuarios por nombre alfabetico.\n");
    printf("7. Ver usuarios por cantidad de juegos.\n");
    printf("8. Identificar usuario que mas juegos tiene.\n");
    printf("9. Volver al Menu Usuario\n\n");

    do
    {
        printf("\nSu decision: ");
        while(scanf("%i", &decision) != 1) //solo en respuesta a lo que estaba acá: no me acuerdo por qué, pero me había salido un error al hacer testeos en main si no había espacios antes del parantesis (al usar strings específicamente) -> estuve agregando espacios antes de los % en todos los scanf de strigns pero puede me falte alguno
        {
            printf("\nPor favor ingrese el numero de una de las opciones.\n");
            limpiarStdin();
            printf("\nSu decision: ");
        }

        if(decision < 1 || decision > 9)
        {
            printf("\nPor favor ingrese una opcion valida.\n");
            limpiarStdin();
        }

    }while(decision < 1 || decision > 9);

    ejecutarFuncionesAdicionalesParaAdmin(decision, arrUsuarios, validos);
}



void ejecutarFuncionesAdicionalesParaAdmin(int decision, Usuario usuariosEnSistema[], int validos)
{
    char nombreDeUsuarioIngresado[LIMITE];

    int idJuegoAmodificar;

    int posCaseCuatro;

    switch(decision)
    {
        case 1:

            printf("\nIngrese el nombre de usuario a eliminar del sistema: ");
            limpiarStdin();
            scanf(" %49[^\n]", nombreDeUsuarioIngresado);
            eliminarUsuarioComoAdmin(nombreDeUsuarioIngresado,usuariosEnSistema, validos);
            break;

        case 2:
            modificarJuego(JUEGOSTIENDA);
            break;

        case 3:
            guardarJuegosEnArchivo(JUEGOSTIENDA);
            break;

        case 4:
            eliminarJuegoDeTienda(JUEGOSTIENDA);
            break;

        case 5:
            printf("\nIngrese el usuario que usted busca: ");
            limpiarStdin();
            scanf(" %49[^\n]", nombreDeUsuarioIngresado);
            posCaseCuatro = buscarUsuarioPorNombreUsuario(nombreDeUsuarioIngresado, usuariosEnSistema, validos);
            if(posCaseCuatro != -1)
                mostrarDatosUsuario(usuariosEnSistema[posCaseCuatro]);
            else
                printf("\nUSUARIO %s NO encontrado.\n", nombreDeUsuarioIngresado);
            break;

        case 6:
            mostrarUsuariosOrdenadosNombre(usuariosEnSistema, validos);
            break;

        case 7:
            mostrarUsuariosOrdenadosCantJuegos(usuariosEnSistema, validos);
            break;

        case 8:
            mostrarUsuarioConMayorCantDeJuegos(usuariosEnSistema, validos);
            break;

        case 9:
            return; //vuelve al menu principal
            break;
    }
}

