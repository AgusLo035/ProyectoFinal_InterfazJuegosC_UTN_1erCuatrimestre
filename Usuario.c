#include "usuario.h"

// ── Registro ──────────────────────────────────────────────────────────────────

Usuario registrarUsuario()
{
    Usuario usuarioCargado;

    printf("\n=============CREACION DEL USUARIO================\n");
    printf("Ingrese el nombre de usuario: ");
    fflush(stdin);
    scanf("%49[^\n]", usuarioCargado.userName);
    printf("\nPASSWORD: ");
    fflush(stdin);
    scanf("%49[^\n]", usuarioCargado.password);
    //HACER PARA CUANDO SI SE PASA DE CARACTERES VOLVER A PEDIR EL USUARIO/CONTRA
    usuarioCargado.billetera         = 0;
    usuarioCargado.bibliotecaUsuario = NULL;
    usuarioCargado.validosBiblioteca = 0;
    usuarioCargado.carritoDeJuegos   = NULL;
    usuarioCargado.validosCarrito    = 0;

    printf("\n=============FIN DE LA CREACION DEL USUARIO================\n");

    return usuarioCargado;
}

int cargarArrDeUsuariosDinamico (Usuario **arr)
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
    if ((*validosCarrito) <= 0)
        (*validosCarrito) = 1;
    else
        (*validosCarrito)++;

    (*arr) = (Juego *) realloc((*arr), sizeof(Juego) * (*validosCarrito));
    if (!(*arr))
    {
        printf("\nERROR EN REALLOC. . .\n");
        return;
    }
    (*arr)[(*validosCarrito) - 1] = juegoAComprar;
}

// ── Biblioteca personal ──────────────────────────────────────────────────────

void cargarABibliotecaUsuario(Juego **arr, int *validos, Juego juegoACargar)
{
    if ((*validos) <= 0)
        (*validos) = 1;
    else
        (*validos) += 1;

    (*arr) = (Juego *) realloc((*arr), sizeof(Juego) * (*validos));
    if (!(*arr))
    {
        printf("\nERROR EN REALLOC. . .\n");
        return;
    }
    (*arr)[(*validos) - 1] = juegoACargar;
}
