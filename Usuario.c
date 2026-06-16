#include "usuario.h"
// ── Pasar usuarios de archivo a ARREGLO  ──────────────────────────────────────────────────────────────────

int pasarUsuariosDeArchivoAArr (char nombreArchivo[], Usuario **arr)
{
    FILE *archi = fopen(nombreArchivo, "rb");
    int validos;

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

    if (pos > -1)
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

        printf("\nDesea registrar otro usuario? 1. SI 0.NO\n");
        scanf("%i", &continuar);

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

void cargarDineroAlUsuario(Usuario *usuarioACargarDinero)
{
    float saldoACargar;

    printf("\n=============INGRESAR DINERO A LA CUENTA================\n");
    printf("Datos Guardados de la Tarjeta\n\nTarjeta: 12325-55458-9923\n");
    printf("CVV: 155\n");
    printf("Ingrese saldo que desea ingresar a la cuenta: ");
    do
    {
        scanf("%f", &saldoACargar);
    } while (saldoACargar <= 0);

    (*usuarioACargarDinero).billetera += saldoACargar;

    printf("\n=============FINALIZACION DE INGRESO================\n");
}

// ── Carrito ───────────────────────────────────────────────────────────────────

void cargarACarritoUsuario(Juego **arr, int *validosCarrito, Juego juegoAComprar)
{
    (*validosCarrito) += 1;

    (*arr) = (Juego *) realloc((*arr), sizeof(Juego) * (*validosCarrito));
    if (!(*arr))
    {
        printf("\nERROR EN REALLOC. . .\n");
        return;
    }
    (*arr)[(*validosCarrito) - 1] = juegoAComprar;
}

// ── Biblioteca personal ──────────────────────────────────────────────────────

void cargarABibliotecaUsuario(Juego **arr, int *validosBiblioteca, Juego juegoACargar)
{
    (*validosBiblioteca) += 1;

    (*arr) = (Juego *) realloc((*arr), sizeof(Juego) * (*validosBiblioteca));
    if (!(*arr))
    {
        printf("\nERROR EN REALLOC. . .\n");
        return;
    }
    (*arr)[(*validosBiblioteca) - 1] = juegoACargar;
}
