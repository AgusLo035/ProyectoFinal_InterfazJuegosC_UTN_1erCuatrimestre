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
    scanf("%49s", nuevoJuego.nombreJuego);
    printf("\nIngrese la categoria del juego: ");
    fflush(stdin);
    scanf("%49s", nuevoJuego.categoriaJuego);
    printf("\nIngrese el precio del juego: ");
    scanf("%f", &nuevoJuego.precioJuego);

    nuevoJuego.eliminado = 0;

    //TEMA ID
    //[nota para hacer yo] para id tal vez contar los juegos que hay en archivo en otra función y darle la cantidad actual+1 como id.
    //Puede haber problemas con eso si se elimina un juego, pero en ese caso verifico si la id ya existe en la función madre a esta y le sumo

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
        if (aux.eliminado != 1)
        {
            printf("\n=============Juego #%i================\n", contador);
            leerUnJuego(aux);
            printf("\n======================================\n");
            contador++;
        }
    }
}

void leerUnJuego(Juego unJuego)
{
    printf("Nombre del juego: %s\n",    unJuego.nombreJuego);
    printf("Categoria del juego: %s\n", unJuego.categoriaJuego);
    printf("Precio del juego: %.2f",    unJuego.precioJuego);
}

// --- BAJA (buscar dato en archivo, eliminarlo, guardar cambios) ------------------------------------
// Después ver cómo hacer que cada vez que se abra/cierre el programa, se quiten del archivo los juegos marcados como "eliminados"

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

        if (flag == 0)
        {
            printf("\nEl nombre del juego ingresado no existe.\n");
        }else
        {
            marcarJuegoActualComoEliminado(archi);
        }

        fclose(archi);

    }else
    {
        printf("Ocurrio un error en la carga del archivo.");
    }
}

void marcarJuegoActualComoEliminado (FILE *archi) //se asume el indicador de posición está inmediatamente después del "juego actual"
{
    Juego aux;

    fseek(archi, -sizeof(Juego), SEEK_CUR); //retrocedo para posicionarme y leer
    fread(&aux, sizeof(Juego), 1, archi);
    aux.eliminado = 1;
    fseek(archi, -sizeof(Juego), SEEK_CUR);  //retrocedo para posicionarme y reemplazar
    fwrite(&aux, sizeof(Juego), 1, archi);
}


// ── Filtrado por categoría ────────────────────────────────────────────────────

int verificarExistenciaJuego (FILE *archi, char nombreBuscado[]) //leer en juego.h por qué lo puse acá (considerar cambiar de lugar maybe?)
{
    int flag = 0; //0 significa "no existe"

    Juego juegoEnArchivo; //sería un "aux"

    while(fread(&juegoEnArchivo, sizeof(Juego), 1, archi) > 0 && flag != 1) //lee todos los juegos en archivo hasta encontrar el buscado o llegar al final
    {
        if(strcmpi(juegoEnArchivo.nombreJuego, nombreBuscado) == 0)
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
    return (strcmpi(juegoAFiltrar.categoriaJuego, categoria) == 0) ? 1 : 0; //no entiendo qué significa esto
}

// ── Ordenamiento por selección (nombre A-Z) ───────────────────────────────────

void leerJuegosOrdenadosNombreTienda(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    Juego aux;
    int validos = 0;

    if (archi)
    {
        while (fread(&aux, sizeof(Juego), 1, archi) > 0) //contamos cuántos juegos hay
            validos++;

        rewind(archi);
        Juego arr[validos]; //creamos un array con la cantidad de juegos que hay
        fread(arr, sizeof(Juego), validos, archi); //metemos todos los juegos dentro

        ordSeleccionNombreJuego(arr, validos);
        mostrarArrJuegosOrdenado(arr, validos, 'p');
        fclose(archi); //estaba fuera del else, pero el archivo solo se cierra si se pudo abrir
    }
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE. . .\n");
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

void mostrarArrJuegosOrdenado(Juego arr[], int validos, char tipoDeOrdenado) //tipoDeOrdenado = 'n' refiere a por nombre, cualquier otro valor a por precio
{
    for (int i = 0; i < validos; i++)
    {
        if (tipoDeOrdenado == 'n')
        {
            printf("\n=============Juegos [A-Z]===============\n");
        }else
        {
            printf("\n=======Juegos [menor $ -> mayor $]=======\n"); //tal vez haya mejor forma de expresarlo que menor $ -> mayor $
        }
        leerUnJuego(arr[i]);
        printf("\n======================================\n");
    }
}

// ── Ordenamiento por Insercion (Menor precio a mayor) ───────────────────────────────────

//Como lo hiciste pasando todos los juegos a un array voy a hacer lo mismo

void leerJuegosOrdenadosPrecioTienda (char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");

    if (archi != NULL)
    {
        fseek(archi, 0, SEEK_END);

        int validos = ftell(archi)/sizeof(Juego); // consigo la cantidad de juegos existentes para poner en array

        Juego arr[validos]; //creo el array de juegos

        rewind(archi); //vuelvo al inicio del archivo para el siguiente paso

        fread(arr, sizeof(Juego), validos, archi); //paso todos los juegos al array



    }else
    {
        printf("\nHa ocurrido un error en la apertura del archivo.\n");
    }
}

void ordInsercionPrecioJuego (Juego arr[], int validos)
{
    for (int i = 0 ; i < validos ; i++)
    {

    }
}













