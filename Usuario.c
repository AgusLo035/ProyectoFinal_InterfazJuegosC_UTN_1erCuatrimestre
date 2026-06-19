#include "usuario.h"

// ── Pasar usuarios de archivo a ARREGLO  ──────────────────────────────────────────────────────────────────

int pasarUsuariosDeArchivoAArr (char nombreArchivo[], Usuario **arr)
{
    FILE *archi = fopen(nombreArchivo, "rb");
    int validos = 0;

    if(archi)
    {
        validos = pasarUsuariosAArr(archi, arr);
        fclose(archi);
    }
    else
        printf("\nEl archivo %s NO existe/NO se pudo abrir. . .\n", nombreArchivo);

    return validos;
}

int pasarUsuariosAArr(FILE *archi, Usuario **arr)
{
    int cantDeUsuarios = contarCantDeUsuariosEnArchi(archi);

    (*arr) = (Usuario*) malloc(sizeof(Usuario) * cantDeUsuarios);

    if(!(*arr))
    {
        printf("\nERROR EN MALLOC\n");
        return -1;
    }

    fread((*arr), sizeof(Usuario), cantDeUsuarios, archi);

    return cantDeUsuarios; //validos
}

int contarCantDeUsuariosEnArchi(FILE *archi)
{
    int cant;

    fseek(archi, 0, SEEK_END);
    cant = ftell(archi)/sizeof(Usuario);
    rewind(archi);

    return cant;
}

///Funciones de ADMIN
// ── Verificar Admin   ──────────────────────────────────────────────────────────────────

int verificarAdmin(char mat[][LIMITE], char usuarioAdmin[], char passwordAdmin[])
{
    int esAdmin = 0;

    if(strcmp(mat[0], usuarioAdmin) == 0 && strcmp(mat[1], passwordAdmin) == 0) //mat[0] es toda la fila, mismo para mat[1]
        esAdmin = 1;

    return esAdmin; //1 si es admin, 0 si no
}
// ── Eliminar usuarios como Admin   ──────────────────────────────────────────────────────────────────

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

// ── Eliminar──────────────────────────────────────────────────────────────────

void eliminarUsuario(Usuario *usuarioAEliminar)
{
    (*usuarioAEliminar).eliminado = 1;
}

// ── Mostrar──────────────────────────────────────────────────────────────────

void mostrarUsuarioConMayorCantDeJuegos (Usuario arr[], int validos)
{
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
    printf("Juegos obtenidos: %i\n",usuarioCargado.validosBiblioteca);
    printf("Juegos en Carrito: %i\n",usuarioCargado.validosCarrito);

    printf("\n===============FIN DE LA MUESTRA================\n");
}

void mostrarArrUsuarios(Usuario arr[], int validos)
{
    for (int i = 0 ; i < validos ; i++)
        mostrarDatosUsuario(arr[i]);
}

// ── Registro ──────────────────────────────────────────────────────────────────

Usuario registrarUsuario()
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
    usuarioCargado.carritoDeJuegos   = NULL;
    usuarioCargado.validosCarrito    = 0;

    usuarioCargado.eliminado = 0;

    inicpila(&usuarioCargado.historialDeJuego);

    printf("\n=============FIN DE LA CREACION DEL USUARIO================\n");

    return usuarioCargado;
}

int cargarArrDeUsuariosDinamico (Usuario **arr) //Carga de arreglo din, no es lo mismo que la funcion de pasar de archi a arreglo
{
    int i = 0;
    int continuar = 1;

    (*arr) = (Usuario*) malloc(sizeof(Usuario));
    if(!(*arr))
    {
        printf("\nERROR EN MALLOC.\n");
        return -1;
    }

    do
    {
        (*arr)[i] = registrarUsuario();
        i++;

        printf("\nDesea registrar otro usuario? 1. SI 0.NO: ");

        while(scanf("%i", &continuar) != 1)
        {
            printf("\nIngrese 1 o 0. . .\nDesea registrar otro usuario? 1. SI 0.NO: ");
            fflush(stdin);
        }

        if(continuar == 1)
        {
            (*arr) = (Usuario*) realloc((*arr), sizeof(Usuario) * (i+1));
            if(!(*arr))
            {
                printf("\nERROR EN REALLOC\n");
                return -1;
            }
        }
    }while(continuar == 1);

    return i;
}

// ── Billetera ─────────────────────────────────────────────────────────────────
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



// ── Carrito ───────────────────────────────────────────────────────────────────

float cargarACarritoUsuario(Juego **arr, int *validosCarrito, Juego juegoAComprar) // devuelve lo que se debe de debitar al usuario
{
    float sumaJuegosEnCarrito = 0;

    (*validosCarrito) += 1;

    (*arr) = (Juego *) realloc((*arr), sizeof(Juego) * (*validosCarrito));
    if (!(*arr))
    {
        printf("\nERROR EN REALLOC. . .\n");
        (*validosCarrito) -= 1;
        return -1;
    }
    (*arr)[(*validosCarrito) - 1] = juegoAComprar;

    sumaJuegosEnCarrito = sumarPrecioJuegos((*arr), (*validosCarrito), 0); //le paso un puntero simple (un arreglo)

    return sumaJuegosEnCarrito;

    //tengo que ver si la dejo asi esta o la cambio, o le paso los parametros individuales o la variable especifica de ese usuario(de tipo usuario)
}

float sumarPrecioJuegos (Juego arr[], int validos, int i) // devuelve suma del precio de un juego/s
{
    float sumaTotal = 0;

    if(i == validos - 1)
        sumaTotal = arr[i].precioJuego;
    else
        sumaTotal = arr[i].precioJuego + sumarPrecioJuegos(arr, validos, i + 1);

    return sumaTotal;
}

// ── Biblioteca personal ──────────────────────────────────────────────────────
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

// ──  Pilas ──────────────────────────────────────────────────────

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
