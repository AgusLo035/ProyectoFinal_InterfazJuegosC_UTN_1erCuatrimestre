#include "usuario.h"

/// Registro =======================================================================================

Usuario registrarUsuario() //los validos de esto se establecen en función madre
{
    Usuario usuarioCargado;

    char inputTeclado[VERIFICARLIMITE]; //51 para verificacion de caracteres org

    printf("\n=============CREACION DEL USUARIO================\n");

    do
    {
        printf("Ingrese el nombre de usuario: ");
        fflush(stdin);
        scanf("%50[^\n]", inputTeclado);
        if(strlen(inputTeclado) >= LIMITE)
            printf("\nVuelva a ingresar un nombre dentro del rango!\n");

    }while(strlen(inputTeclado) >= LIMITE);

    strcpy(usuarioCargado.userName, inputTeclado);

    do
    {

        printf("\nPASSWORD: ");
        fflush(stdin);
        scanf("%50[^\n]", inputTeclado);
        if(strlen(inputTeclado) >= LIMITE)
            printf("\nVuelva a ingresar un password dentro del rango!\n");

    }while(strlen(inputTeclado) >= LIMITE);

    strcpy(usuarioCargado.password, inputTeclado);

    usuarioCargado.billetera         = 0;
    usuarioCargado.bibliotecaUsuario = NULL;
    usuarioCargado.validosBiblioteca = 0;

    usuarioCargado.carritoDeJuegos = NULL;
    usuarioCargado.validosCarrito = 0;

    usuarioCargado.eliminado = 0;

    inicpila(&usuarioCargado.historialDeJuego);

    printf("\n=============FIN DE LA CREACION DEL USUARIO================\n");

    return usuarioCargado;
}

Usuario crearUsuarioAdmin()
{
    Usuario admin;

    strcpy(admin.userName, "admin");
    strcpy(admin.password, "admin");
    admin.eliminado = 0;
    admin.billetera = 1000;

    admin.carritoDeJuegos = NULL;
    admin.validosCarrito = 0;

    inicpila(&admin.historialDeJuego);

    admin.bibliotecaUsuario = NULL;
    admin.validosBiblioteca = 0;

    return admin;
}

//int cargarArrDeUsuariosDinamico (Usuario **arr, int *cantUsuariosEnElPrograma) //Carga de arreglo din, no es lo mismo que la funcion de pasar de archi a arreglo
//{ //Nota: esto no tiene uso dijiste?
///// SOY MUY TONTO, esto es lo principal que vamos a usar mientras se ejecuta el programa
///// despues, cuando el usuario quiera cerrarlo, lo ultimo que hace es pasar todo ese arreglo de usuarios que se cargaron (o no) al archivo
///// Por ejemplo. Ejecuto, creo un usuario, vuelvo y registro otro usuario, ya tengo 2 usuarios distintos
///// creo :3cc
//    int i = 0;
//    int continuar = 1;
//
//    (*arr) = (Usuario*) malloc(sizeof(Usuario));
//    if(!(*arr))
//    {
//        printf("\nERROR EN MALLOC.\n");
//        return -1;
//    }
//
//    do
//    {
//        (*arr)[i] = registrarUsuario(cantUsuariosEnElPrograma);
//        i++;
//
//        printf("\nDesea registrar otro usuario? 1. SI 0.NO: ");
//
//        while(scanf("%i", &continuar) != 1)
//        {
//            printf("\nIngrese 1 o 0. . .\nDesea registrar otro usuario? 1. SI 0.NO: ");
//            fflush(stdin);
//        }
//
//        if(continuar == 1)
//        {
//            (*arr) = (Usuario*) realloc((*arr), sizeof(Usuario) * (i+1));
//            if(!(*arr))
//            {
//                printf("\nERROR EN REALLOC\n");
//                return -1;
//            }
//        }
//    }while(continuar == 1);
//
//    return i;
//}

void agregarUsuarioAArr (Usuario **arr, int *cantUsuarios) //recibe el array, aumenta validos por 1, ingresa al usuario en el array. Es básicamente una opción de registro,
                                                            //la había empezado en general pero es mejor ponerla acá.
{
    (*cantUsuarios) += 1;

    Usuario *aux = (Usuario*) realloc((*arr), sizeof(Usuario) * (*cantUsuarios)); //hago un espacio para el nuevo usuario

    if (aux != NULL)
    {
        aux[((*cantUsuarios)-1)] = registrarUsuario(); //agrego al usuario en la posición que acabo de crear
        printf("\nUsuario creado exitosamente.\n");
        (*arr) = aux;
    }else
    {
        (*cantUsuarios) -= 1;
        printf("\nHa ocurrido un error en la ampliacion del array para guardar al usuario. Intente de nuevo.\n");
    }
}

/// Pasar usuarios de archivo a ARREGLO =======================================================

///Borrar maybe
//int pasarUsuariosDeArchivoAArr (char nombreArchivo[], Usuario **arr, int validosUsuarios)
//{
//    FILE *archi = fopen(nombreArchivo, "rb");
//    int validos = 0;
//
//    if(archi)
//    {
//        validos = pasarUsuariosAArr(archi, arr, validosUsuarios); //devuelve -1 en caso de error
//        fclose(archi);
//    }
//    else
//    {
//        printf("\n\nADVERTENCIA: El archivo de usuarios ''%s'' aún NO existe o NO se pudo abrir. . .\n\n", nombreArchivo);
//        //estoy 67% seguro que para intentar romper el programa van a sacar uno/ambos de los archivos
//        (*arr) = NULL; // para que quede inicializado aunque sea en null si no existe todavía el archivo
//    }
//
//    return validos;
//}
//
//int pasarUsuariosAArr(FILE *archi, Usuario **arr, int cantDeUsuarios)
//{
////    int cantDeUsuarios = contarCantDeUsuariosEnArchi(archi);
//
//    (*arr) = (Usuario*) malloc(sizeof(Usuario) * cantDeUsuarios);
//
//    if(!(*arr))
//    {
//        printf("\nERROR EN MALLOC\n");
//        return -1;
//    }
//
//    fread((*arr), sizeof(Usuario), cantDeUsuarios, archi);
//
//    return cantDeUsuarios; //validos -> si existe error, devuelve -1
//}
//
//int contarCantDeUsuariosEnArchi(FILE *archi)
//{
//    int cant;
//
//    fseek(archi, 0, SEEK_END);
//    cant = ftell(archi)/sizeof(Usuario);
//    rewind(archi);
//
//    return cant;
//}

int pasarUsuariosArchivoAArrDin (char nombreArchivo[], Usuario **arr)
///Decidí que esta función devuelva los validos. Solo quiero que existan los validos cuando se quiere registrar/logear, no siempre que se inicia el programa. por quisquilloso nomás
{
    FILE *archi = fopen(nombreArchivo, "r+b");

    int validos = -1; //solo se queda así si no se abre el archivo (si devuelve esto se termina el programa)

    if(archi)
    {
        fread(&validos, sizeof(int), 1, archi);

        pasarUsuarioArchiAArrDinArchi(archi, arr, validos);

        fclose(archi);
    }
    else
    {
        if (errno == ENOENT) //"ENOENT" significa que el error es que el archivo NO EXISTE
        {
            validos = 0;
        }else
        {
            printf("\n\nHa ocurrido un error en la apertura del archivo de usuarios. Reinice el programa e intente nuevamente.\n");
        }

    }
        return validos; //tambien decidí que devuelva los validos, porque aparecen al principio del archivo
}

void pasarUsuarioArchiAArrDinArchi (FILE *archi, Usuario **arr, int usuariosRegistradosEnSistema)
{
    int i = 0;

    (*arr) = (Usuario*) malloc(sizeof(Usuario) * usuariosRegistradosEnSistema);
    if(!(*arr))
    {
        printf("\nERROR EN MALLOC. . .\n");
        return;
    }

    while(i < usuariosRegistradosEnSistema)
    {
        (*arr)[i] = leerUsuarioCompletoDeArchi(archi); //rta comentario anterior: confundí leer con que se imprimían todos dios
        i++;
    }
}

int creacionArchivoDeUsuarios (Usuario **arr) //si no existe el archivo usuario, lo crea y añade al primer usuario admin
{
    FILE *archi = fopen(LISTAUSUARIOS, "wb");

    int validos = -1; //se devuelve como "validos" en el main. Es -1 si hay error en fopen

    Usuario *aux;

    if (archi)
    {
        validos = 1;

        fwrite(&validos, sizeof(int), 1, archi); //escribo "1" al principio del archivo, que serían los validos

        aux = malloc(sizeof(Usuario)*1); //hago espacio para 1 usuario en el array dinámico

        if (aux != NULL)
        {
            (*arr) = aux;

            (*arr)[0] = crearUsuarioAdmin(); //coloco al usuario admin en el array

            fwrite(&(*arr)[0], sizeof(Usuario), 1, archi); //y después agrego admin al archivo
        }else
        {
            validos = -1; //error en malloc en este caso
        }

        fclose(archi);
    }else
    {
        printf("\nHa ocurrido un error en la creacion del archivo usuarios. Reinice el programa e intente nuevamente.\n");
    }

    return validos;
}

Usuario leerUsuarioCompletoDeArchi(FILE *archi) //NOTA: antes de llamar a esta función, sí o si hay que mover el indicador de posición 1 posición delante de los validos al inicio del archivo
{
    Usuario usuarioLeido;

    fread(&usuarioLeido, sizeof(Usuario), 1, archi);

    usuarioLeido.bibliotecaUsuario = (Juego*) malloc(sizeof(Juego) * usuarioLeido.validosBiblioteca);
    ///los validos de la biblioteca si obtengo, cuando hago fread de un usuario obtengo todo lo que no sea arreglo dinamico
    /// los validos me sirven para saber cuanto me tengo que mover en el archivo sizeof(Juego) * validosbiblioteca por ej
    /// luego puedo hacer billetera y cuando termino ya tengo un usuario completo, no hay perdida.
    if(!usuarioLeido.bibliotecaUsuario)
    {
        strcpy(usuarioLeido.userName, "ERROR. . .");
        printf("\nERROR EN MALLOC. . .\n");
        return usuarioLeido;
    }

    fread(usuarioLeido.bibliotecaUsuario, sizeof(Juego), usuarioLeido.validosBiblioteca, archi);
    ///ACA cargo la biblioteca de ese usuario en especifico a ese usuario.

    usuarioLeido.carritoDeJuegos = (Juego*) malloc(sizeof(Juego) * usuarioLeido.validosCarrito); //ahora que carrito de juegos no es un array dinámico hay que modificar esto. Me está agarrando sueño así que probablemente mi cerebro esté fallando, pero quiero revisar si es necesario modificar la función que carga los array en el archivo. (no me acuerdo si me fijé)
    if(!usuarioLeido.carritoDeJuegos)
    {
        strcpy(usuarioLeido.userName, "ERROR. . .");
        printf("\nERROR EN MALLOC. . .\n");
        free(usuarioLeido.bibliotecaUsuario);
        return usuarioLeido;
    }

    fread(usuarioLeido.carritoDeJuegos, sizeof(Juego), usuarioLeido.validosCarrito, archi);
    ///ACA cargo el carrito de ese usuario en especifico a ese usuario.

    return usuarioLeido;
    ///devuelvo ese usuario con todos sus parametros cargados
}

void guardarArrUsuariosEnArchivo(char nombreArchivo[], Usuario arr[], int validosUsuarios)
{
    FILE *archi = fopen(nombreArchivo, "wb");

    if(archi)
    {
        fwrite(&validosUsuarios, sizeof(int), 1, archi); //se guardan los validos al principio del archivo
        for(int i = 0 ; i < validosUsuarios ; i++)
        {
            guardarUnUsuarioEnArchi(archi, arr[i]);
        }
        fclose(archi);
        /// en archivo quedaria: int (validos) | usuarioEnespecifico (usuario) |juego1 (juego) | juego2 (juego) | despues seguiria con otro usuario y sus juegos y asi
    }
    else
        printf("\nHubo un error en el guardado de los usuarios. Cualquier cambio realizado no se ha guardado.\n");
}

void guardarUnUsuarioEnArchi(FILE *archi, Usuario usuario)
{
    fwrite(&usuario, sizeof(Usuario), 1, archi);

    fwrite(usuario.bibliotecaUsuario, sizeof(Juego), usuario.validosBiblioteca, archi);

    fwrite(usuario.carritoDeJuegos, sizeof(Juego), usuario.validosCarrito, archi); //creo que era así
}

//


///Funciones de ADMIN
/// Verificar Admin =======================================================================================

int verificarAdmin(char mat[][LIMITE], char usuarioAdmin[], char passwordAdmin[])
{
    int esAdmin = 0;

    if(strcmp(mat[0], usuarioAdmin) == 0 && strcmp(mat[1], passwordAdmin) == 0) //mat[0] es toda la fila, mismo para mat[1]
        esAdmin = 1;

    return esAdmin; //1 si es admin, 0 si no
}
/// Eliminar usuarios como Admin =======================================================================================

void eliminarUsuarioComoAdmin(char nombreDeUsuarioAEliminar[], Usuario arr[], int validos)
{
    int pos = buscarUsuarioPorNombreUsuario(nombreDeUsuarioAEliminar, arr, validos);

    if (pos > -1)
    {
        eliminarUsuario(&arr[pos]);
        printf("\nUsuario [%s] eliminado.\n", nombreDeUsuarioAEliminar);
    }
    else
        printf("\nUsuario [%s] NO encontrado.\n", nombreDeUsuarioAEliminar);
}

/// Eliminar =======================================================================================

void eliminarUsuario(Usuario *usuarioAEliminar)
{
    (*usuarioAEliminar).eliminado = 1;
}

/// Mostrar =======================================================================================

void mostrarUsuarioConMayorCantDeJuegos (Usuario arr[], int validos)
{ //Nota: esto no se usa tampoco? //No es que no se usa, lo pedia la consigna, lo metemos por ahi y fue
    //cuál consigna lo pide?
    int pos = buscarUsuarioMayorCantDeJuegosComprados(arr, validos);

    if (pos > -1)
        mostrarDatosUsuario(arr[pos]);
    else
        printf("\nNingun usuario tiene juegos.\n");
}

int buscarUsuarioMayorCantDeJuegosComprados (Usuario arr[], int validos)
{
    int pos = 0;
    Usuario uMayorJuegos = arr[0];

    for (int i = 0 ; i < validos - 1 ; i++)
    {
        if(uMayorJuegos.validosBiblioteca < arr[i + 1].validosBiblioteca)
        {
            uMayorJuegos = arr [i + 1];
            pos = i + 1;
        }
    }

    if(uMayorJuegos.validosBiblioteca == 0)
        pos = -1;

    return pos; //devuelve la pos del usuario con la mayor cantidad de juegos, si es -1 nadie tiene juegos
}

void mostrarUsuarioPorNombreUsuario (char nombreDeUsuario[], Usuario arr[], int validos)
{
    int pos = buscarUsuarioPorNombreUsuario(nombreDeUsuario, arr, validos);

    if (pos > -1 && arr[pos].eliminado == 0)
        mostrarDatosUsuario(arr[pos]);
    else
        printf("\nUsuario [%s] NO encontrado.\n", nombreDeUsuario);
}

int buscarUsuarioPorNombreUsuario (char nombreDeUsuario[], Usuario arr[], int validos)
{
    int flag = -1;

    for (int i = 0 ; i < validos && flag == -1; i++)
    {
        if(strcmp(nombreDeUsuario, arr[i].userName) == 0)
            flag = i;
    }

    return flag; //-1 si no existe, mayor a -1 si existe, devuelve la posicion del usuario.
}

void mostrarDatosUsuario(Usuario usuarioCargado)
{
    printf("\n=============DATOS DEL USUARIO (%s)==================\n", usuarioCargado.userName);

    printf("Nombre de usuario: %s\n", usuarioCargado.userName);
    //printf("Password: %s\n", usuarioCargado.password);
    printf("Dinero en la cuenta: $%.2f\n", usuarioCargado.billetera);
    printf("Cantidad de juegos en libreria: %i\n",usuarioCargado.validosBiblioteca);
    printf("Cantidad de juegos en carrito: %i\n",usuarioCargado.validosCarrito);

    printf("\n===============FIN DE LA MUESTRA================\n");
}

void mostrarArrUsuarios(Usuario arr[], int validos)
{
    for (int i = 0 ; i < validos ; i++)
        mostrarDatosUsuario(arr[i]);
}

/// Billetera =======================================================================================
void deshacerUltimaCompra(Pila *historialId, Usuario *usuarioAReembolsarJuego)
{
    if(!pilavacia(historialId))
    {
        Juego ultimoJuegoComprado;

        ultimoJuegoComprado.id = desapilar(historialId);

        Juego juegoAQuitar = buscarJuegoPorId(ultimoJuegoComprado.id);

        if(ultimoJuegoComprado.id != -1)
        {
            float montoAReembolsar = juegoAQuitar.precioJuego;

            quitarJuegoDeBibliotecaUsuario(&(*usuarioAReembolsarJuego).bibliotecaUsuario, &(*usuarioAReembolsarJuego).validosBiblioteca, juegoAQuitar);

            (*usuarioAReembolsarJuego).billetera += montoAReembolsar;
        }
        else
            printf("\nERROR, EL JUEGO A REEMBOLSAR NO EXISTE. . .\n");
    }
    else
        printf("\nNO TIENES UN JUEGO PARA REEMBOLSAR. . .\n");
}

void debitarDineroAlUsuario (Usuario *usuarioADebitar, float montoADebitar)
{
    float sueldoDeUsuario = (*usuarioADebitar).billetera;

    if((sueldoDeUsuario - montoADebitar) < 0)
        printf("\nMonto insuficiente en la cuenta\n");
    else
    {
        (*usuarioADebitar).billetera -= montoADebitar;
        printf("\nMonto actual en la cuenta: %.2f\n", (*usuarioADebitar).billetera);
    }
}

void cargarDineroAlUsuario(Usuario *usuarioACargarDinero)
{
    float saldoACargar;

    printf("\n=============INGRESAR DINERO A LA CUENTA================\n");
    printf("Datos Guardados de la Tarjeta\n\nTarjeta: 12325-55458-9923\n");
    printf("CVV: 155\n");
    printf("Ingrese saldo que desea ingresar a la cuenta: ");

    while (scanf("%f", &saldoACargar) != 1 || saldoACargar <= 0)
    {
        printf("\nTipo de dato incorrecto/Insuficiente. . .\nIngrese saldo que desea ingresar a la cuenta: ");
        fflush(stdin);
    }

    (*usuarioACargarDinero).billetera += saldoACargar;

    printf("\n=============FINALIZACION DE INGRESO================\n");
}

/// Carrito =======================================================================================


float cargarACarritoUsuario(Juego **carrito, int *validosCarrito, Juego juegoAComprar) // devuelve lo que se debe de debitar al usuario
{
    float sumaJuegosEnCarrito = 0;

    (*validosCarrito) += 1;

    (*carrito) = (Juego *) realloc((*carrito), sizeof(Juego) * (*validosCarrito)); //puede convenga crear un aux para esto en vez de igualarlo directamente, si devuelve null realloc se pierde todo
    if (!(*carrito))
    {
        printf("\nERROR EN REALLOC. . .\n");
        (*validosCarrito) -= 1;
        return -1;
    }
    (*carrito)[(*validosCarrito) - 1] = juegoAComprar;

    sumaJuegosEnCarrito = sumarPrecioJuegos((*carrito), (*validosCarrito), 0); //le paso un puntero simple (un arreglo)

    return sumaJuegosEnCarrito;

    //tengo que ver si la dejo asi esta o la cambio, o le paso los parametros individuales o la variable especifica de ese usuario(de tipo usuario)
}

float sumarPrecioJuegos (Juego arr[], int validos, int i) // devuelve suma del precio de un juego/s
{
    float sumaTotal = 0;

    if(i == validos - 1)
        sumaTotal = arr[i].precioJuego;
    else
        sumaTotal = arr[i].precioJuego + sumarPrecioJuegos(arr, validos, i + 1); //wow q recursivo

    return sumaTotal;
}

/// Biblioteca personal =======================================================================================
void quitarJuegoDeBibliotecaUsuario(Juego **arr, int *validosBiblioteca, Juego juegoAQuitar) //siendo el arr de tipo juego la biblioteca de ese usuario y
                                                                                            //SABIENDO QUE ESE USUARIO TIENE ESE JUEGO POR VERIFICACION PREVIA/FUERA DE LA FUNCION
{
    int flag = 0;

    for(int i = 0 ; i < (*validosBiblioteca) && flag == 0 ; i++)
    {
        if((*arr)[i].id == juegoAQuitar.id)
        {
            flag = 1;
            (*arr)[i] = (*arr)[((*validosBiblioteca) - 1)];
            (*validosBiblioteca) -= 1; //pasa el juego a eliminar al final para hacer realloc
        }
    }

    (*arr) = (Juego*) realloc((*arr), sizeof(Juego) * (*validosBiblioteca));
    if(!(*arr))
    {
        printf("\nERROR EN REALLOC. . .\n");
        return;
    }
}

void cargarABibliotecaUsuario(Usuario *usuarioACargar, Juego juegoACargar) //verificacion si el usuario tiene o no el juego se hace previamente
{
    (*usuarioACargar).validosBiblioteca += 1;

    (*usuarioACargar).bibliotecaUsuario = (Juego*) realloc((*usuarioACargar).bibliotecaUsuario, sizeof(Juego) * (*usuarioACargar).validosBiblioteca);

    if (!(*usuarioACargar).bibliotecaUsuario)
    {
        printf("\nERROR EN REALLOC. . .\n");
        (*usuarioACargar).validosBiblioteca -= 1;
        return;
    }

    (*usuarioACargar).bibliotecaUsuario[((*usuarioACargar).validosBiblioteca - 1)] = juegoACargar;

    int contarDimHistorial = contarDimPila((*usuarioACargar).historialDeJuego);

    if(contarDimHistorial >= 50)
        reajustarDimPilaTope(&(*usuarioACargar).historialDeJuego, juegoACargar.id);
    else
        apilar(&(*usuarioACargar).historialDeJuego, juegoACargar.id);
}

/// Pilas =======================================================================================

void reajustarDimPilaTope(Pila *pila, int datoAIngresar) // agregar dato al principio en una pila llena
{
    Pila aux;
    inicpila(&aux);

    while(!pilavacia(pila))
        apilar(&aux, desapilar(pila));

    desapilar(&aux); //desapilo el valor mas viejo

    while(!pilavacia(&aux))
        apilar(pila, desapilar(&aux));

    apilar(pila, datoAIngresar);
}

int contarDimPila(Pila pila)
{
    Pila aux;
    inicpila(&aux);

    int cont = 0;

    while(!pilavacia(&pila))
    {
        apilar(&aux, desapilar(&pila));
        cont++;
    }
    return cont;
}

///Consulta?

int verificarUsuarioRegistrado(Usuario arr[], int validos, char username[], char password[])
{
    int flag = -1;

    for(int i = 0 ; i < validos && flag == 0; i++)
    {
        if(strcmp(arr[i].userName, username) == -1 && strcmp(arr[i].password, password) == -1)
            flag = i;
    }

    return flag; //Devuelve la pos de ese usuario para luego hacer usuario de la sesion iniciada = arr[esa posicion que devuelve
                //devuelve -1 si la contraseña o usuario son incorrectos
}

/// Mostrar Juegos del carrito de ese Usuario
void mostrarCarritoDeUsuario (Usuario usuario)
{
    for(int i = 0 ; i < usuario.validosCarrito ; i++)
    {
        printf("\n=============Juego en Carrito (U: %s)#%i================\n", usuario.userName, i+1);
        leerUnJuego(usuario.carritoDeJuegos[i]);
        printf("\n======================================\n");
    }
}
