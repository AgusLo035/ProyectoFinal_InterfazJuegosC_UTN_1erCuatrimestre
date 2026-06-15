#include "juego.h"

// ── Alta ─────────────────────────────────────────────────────────────────────

void guardarJuegosEnArchivo(char nombreArchivo[], char modo[])
{
    FILE *archi = fopen(nombreArchivo, modo);
    if (archi)
        cargarJuegoATienda(archi);
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE. . .\n");
    fclose(archi);
}

void cargarJuegoATienda(FILE *archi)
{
    int flag = 0;
    Juego juegoEnArchivo;
    Juego nuevoJuego = cargarNuevoJuego();

    rewind(archi);
    flag = verificarExistenciaJuego(archi, nuevoJuego.nombreJuego); //separé la parte de verificar si el juego existe en una función para usarla en otro lado

    if (flag != 1)
        fwrite(&nuevoJuego, sizeof(Juego), 1, archi);
    else
    {
        system("cls");
        printf("\nEl juego '%s' YA existe en la tienda\n\n", nuevoJuego.nombreJuego);
        system("pause");
    }
}

Juego cargarNuevoJuego()
{
    Juego nuevoJuego;
    printf("\n=============CREACION DEL JUEGO NUEVO================\n");
    printf("Ingrese el nombre del juego: ");
    fflush(stdin);
    scanf("%49s", &nuevoJuego.nombreJuego);
    printf("\nIngrese la categoria del juego: ");
    fflush(stdin);
    scanf("%49s", &nuevoJuego.categoriaJuego);
    printf("\nIngrese el precio del juego: ");
    scanf("%f", &nuevoJuego.precioJuego);
    printf("\n=============FIN DE LA CREACION================\n");
    return nuevoJuego;
}

// ── Consulta / lectura ────────────────────────────────────────────────────────

void leerJuegosDeTienda(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    if (archi)
        leerJuegosArchivo(archi);
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE. . .\n");
    fclose(archi);
}

void leerJuegosArchivo(FILE *archi)
{
    Juego aux;
    int contador = 1;

    while (fread(&aux, sizeof(Juego), 1, archi) > 0)
    {
        printf("\n=============Juego #%i================\n", contador);
        leerUnJuego(aux);
        printf("\n======================================\n");
        contador++;
    }
}

void leerUnJuego(Juego unJuego)
{
    printf("Nombre del juego: %s\n",    unJuego.nombreJuego);
    printf("Categoria del juego: %s\n", unJuego.categoriaJuego);
    printf("Precio del juego: %.2f",    unJuego.precioJuego);
}

// --- BAJA (buscar dato en archivo, eliminarlo, guardar cambios) ------------------------------------

//Eliminar un juego de la tienda
void eliminarJuegoDeTienda (char nombreArchivo[]) //BAJA
{
    FILE *archi = fopen(nombreArchivo, "r+b");

    if (archi != NULL)
    {
        int flag = 0;

        char juegoAEliminar[LIMITE];

        printf("\nIngrese el nombre del juego que quiere eliminar: ");
        scanf("%49[^\n]", juegoAEliminar);

        flag = verificarExistenciaJuego(archi, juegoAEliminar);

        Juego aux;

        if (flag == 0)
        {
            printf("\nEl nombre del juego ingresado no existe.\n");
        }else
        {//[NOTA:] Revisar si puedo modularizar despues, considerar tal vez cambiar nombre de esta función?
            fseek(archi, -sizeof(Juego), SEEK_CUR); //retrocedo para posicionarme y leer
            fread(&aux, sizeof(Juego), 1, archi);
            aux.eliminado = 1;
            fseek(archi, -sizeof(Juego), SEEK_CUR);  //retrocedo para posicionarme y reemplazar
            fwrite(&aux, sizeof(Juego), 1, archi);
        }

        fclose(archi);

    }else
    {
        printf("Ocurrio un error en la carga del archivo.");
    }
}


// ── Filtrado por categoría ────────────────────────────────────────────────────

int verificarExistenciaJuego (FILE *archi, char nombreBuscado[]) //leer en juego.h p q lo puse acá (considerar cambiar de lugar maybe?)
{
    int flag = 0; //0 significa "no existe"

    Juego juegoEnArchivo; //sería un "aux"

    while(fread(&juegoEnArchivo, sizeof(Juego), 1, archi) > 0 && flag != 1) //lee todos los juegos en archivo hasta encontrar uno o llegar al final
    {
        if(strcmpi(nombreJuegoActual, nombreBuscado) == 0)
            flag = 1; //Si los nombres coinciden, el juego ya existe en la tienda
    }

    return flag;
}

void leerJuegosFiltradosTienda(char nombreArchivo[], char categoria[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    Juego aux;
    int contador = 0;

    if (archi)
    {
        while (fread(&aux, sizeof(Juego), 1, archi) > 0)
        {
            if (compararJuegoCategoria(aux, categoria))
            {
                printf("\n=============Juego #%i - Categoria: %s================\n",
                       contador + 1, categoria);
                leerUnJuego(aux);
                printf("\n======================================\n");
                contador++;
            }
        }
        if (contador == 0)
        {
            printf("\nNo existen juegos con esa categoria. . .\n\n");
            system("pause");
        }
    }
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE. . .\n");
    fclose(archi);
}

int compararJuegoCategoria(Juego juegoAFiltrar, char categoria[])
{
    return (strcmpi(juegoAFiltrar.categoriaJuego, categoria) == 0) ? 1 : 0;
}

// ── Ordenamiento por selección (nombre A-Z) ───────────────────────────────────

void leerJuegosOrdenadosNombreTienda(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    Juego aux;
    int validos = 0;

    if (archi)
    {
        while (fread(&aux, sizeof(Juego), 1, archi) > 0)
            validos++;

        rewind(archi);
        Juego arr[validos];
        fread(arr, sizeof(Juego), validos, archi);

        ordSeleccionNombreJuego(arr, validos);
        mostrarArrJuegosOrdenado(arr, validos);
    }
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE. . .\n");
    fclose(archi);
}

void ordSeleccionNombreJuego(Juego arr[], int validos)
{
    for (int i = 0; i < validos - 1; i++)
    {
        int   posMenor = posMenorNombreJuego(arr, validos, i);
        Juego aux = arr[i];
        arr[i] = arr[posMenor];
        arr[posMenor] = aux;
    }
}

int posMenorNombreJuego(Juego arr[], int validos, int posInicial)
{
    int posMenor = posInicial;
    char menor[LIMITE];
    strcpy(menor, arr[posInicial].nombreJuego);

    for (int i = posInicial + 1; i < validos; i++)
    {
        if (strcmpi(menor, arr[i].nombreJuego) > 0)
        {
            posMenor = i;
            strcpy(menor, arr[i].nombreJuego);
        }
    }
    return posMenor;
}

void mostrarArrJuegosOrdenado(Juego arr[], int validos)
{
    for (int i = 0; i < validos; i++)
    {
        printf("\n=============Juegos A-Z================\n");
        leerUnJuego(arr[i]);
        printf("\n======================================\n");
    }
}
// ── Ordenamiento por Insercion (Menor precio a mayor) ───────────────────────────────────
