#include "juego.h"

// ── Alta ────────────────────────────────────────────────────────────────────

void guardarJuegosEnArchivo(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "a+b");
    if (archi)
    {
        cargarJuegoATienda(archi);
        fclose(archi);
    }
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE. . .\n");
}

void cargarJuegoATienda(FILE *archi)
{
    int flag = 0;

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

Juego cargarNuevoJuego() //le (había) agregado archi para que pueda identificar qué numero de ID poner en base a cuántos juegos hay
{
    Juego nuevoJuego;
    printf("\n=============CREACION DEL JUEGO NUEVO================\n");
    printf("Ingrese el nombre del juego: ");
    limpiarStdin();
    scanf(" %49[^\n]", nuevoJuego.nombreJuego);
    printf("\nIngrese la categoria del juego: ");
    limpiarStdin();
    scanf(" %49[^\n]", nuevoJuego.categoriaJuego);
    printf("\nIngrese el precio del juego: ");
    while(scanf("%f", &nuevoJuego.precioJuego) != 1 || nuevoJuego.precioJuego < 0) // Verifica si el juego tiene precio negativo, si es 0 es gratis
    {
        printf("\nTipo de dato invalido. . .\nIngrese el precio del juego: ");
        limpiarStdin();
    }

    nuevoJuego.id = determinarIDNuevoJuego (); //En caso de ocurrir cualquier error dentro de la función (específicamente que no abra el archivo), la ID del juego va a ser -1.
    nuevoJuego.eliminado = 0;

    //TEMA ID
    //[nota para hacer yo] para id tal vez contar los juegos que hay en archivo en otra función y darle la cantidad actual+1 como id.
    //Puede haber problemas con eso si se elimina un juego, pero en ese caso verifico si la id ya existe en la función madre a esta y le sumo
    //Me dejo esto anotado en caso de que nos digan es necesario borrar estructuras directamente del archivo (creando otro sin los marcados como eliminados)

    printf("\n=============FIN DE LA CREACION================\n");

    return nuevoJuego;
}

int determinarIDNuevoJuego()//Se ignora la ID de juegos eliminados (nota debajo)
{// SE ASUME QUE la tienda de juegos (JUEGOSTIENDA / el archivo con los juegos globales) SIEMPRE va a estar precargado en el sistema
// Esto para emular los juegos que existen globalmente
    FILE *archi = fopen(JUEGOSTIENDA, "rb");

    int cantJuegos = -1;

    if (archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        cantJuegos = ftell(archi)/sizeof(Juego);
        fclose(archi);
    }else
    {
        printf("\n\nHa ocurrido un error en la lectura del archivo. No puedo asignarse ID.");
    }

    return cantJuegos; //las IDs empiezan en 0
}

// ── Consulta / lectura ────────────────────────────────────────────────────────

void leerJuegosDeTienda(char nombreArchivo[]) //abre el archivo y llama a la función que lee todos los juegos
{
    FILE *archi = fopen(nombreArchivo, "rb");
    if (archi)
    {
        leerJuegosArchivo(archi);
        fclose(archi);
    }
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE/NO existe. . .\n");
}

void leerJuegosArchivo(FILE *archi) //lee todos los juegos del archivo que recibe
{
    Juego aux;
    int contador = 0; //contador es solo estético para el printf de abajo

    while (fread(&aux, sizeof(Juego), 1, archi) > 0)
    {
        if (aux.eliminado == 0)
        {
            printf("\n=============Juego #%i================\n", contador + 1);
            leerUnJuego(aux);
            printf("\n======================================\n");
            contador++;
        }
    }
    if(contador == 0)
        printf("\nNO HAY JUEGOS QUE MOSTRAR. . .\n");
}

void leerUnJuego(Juego unJuego)
{
    printf("Nombre del juego: %s\n", unJuego.nombreJuego);
    printf("Categoria del juego: %s\n", unJuego.categoriaJuego);
    printf("Precio del juego: %.2f\n", unJuego.precioJuego);
    printf("ID del juego: %i\n", unJuego.id);
}

Juego buscarJuegoPorNombre (char nombreJuegoBuscado[]) //devuelve Juego buscado por nombre
{
    FILE *archi =  fopen(JUEGOSTIENDA, "rb");

    Juego aux;
    aux.id = -1; //devuelve el juego con esta id en caso de no poder abrirse el archivo

    int flag = 0;

    if (archi != NULL)
    {
        flag = verificarExistenciaJuego(archi, nombreJuegoBuscado); //esto deja el indicado de posicion delante del juego que quiero (si lo encuentra)

        if (flag != 0)
        {
            fseek(archi,-(long)sizeof(Juego), SEEK_CUR); //retrocedo un paso para obtener el juego
            fread(&aux, sizeof(Juego), 1, archi);
        }

        fclose (archi);
    }else
    {
        printf("\nHubo un error en la apertura del archivo.\n");
    }

    return aux;
}

Juego buscarJuegoPorId (int idBuscada) //función separada porque parece solo la vamos a usar en relación al usuario
{
    FILE *archi =  fopen(JUEGOSTIENDA, "rb"); // solo quiero leer el archivo, nunca escribir en el

    Juego aux;
    aux.id = -1; //devuelve el juego con esta id en caso de no poder abrirse el archivo

    int flag = 0;

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(Juego), 1, archi) > 0 && flag == 0)
        {
            if (aux.id == idBuscada && aux.eliminado == 0) // Verifico la id obtenida con la buscada y si el juego no esta eliminado
            {
                flag = 1;
            }
        }

        if (flag == 0) //si no se encontró, va a seguirse teniendo la id del ultimo valor leído, lo reemplazo por -1 para marcar error
        {
            aux.id = -1;
        }
        ///No se que tan necesario sea verificar si existe, porque eso lo haria otra funcion. Basicamente, porque si existe la id en la pila
        ///Es porque el juego se compro, es una id valida, como mucho si el juego se borra del archivo, igual hice una verificacion. (Igual es poco probable que salte ese error al tener una tienda fija)

        fclose (archi);

    }else
    {
        printf("\nHubo un error en la apertura del archivo.\n");
    }

    return aux;
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
        limpiarStdin();
        scanf(" %49[^\n]", juegoAEliminar);

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
        printf("Ocurrio un error en la carga del archivo.");
}

void marcarJuegoActualComoEliminado (FILE *archi) //se asume el indicador de posición está inmediatamente después del "juego actual"
{
    Juego aux;

    fseek(archi, -(long)sizeof(Juego), SEEK_CUR); //retrocedo para posicionarme y leer
    fread(&aux, sizeof(Juego), 1, archi);
    aux.eliminado = 1;

    fseek(archi, -(long)sizeof(Juego), SEEK_CUR);  //retrocedo para posicionarme y reemplazar
    fwrite(&aux, sizeof(Juego), 1, archi);
}

// ── Modificación (buscar dato, modificarlo, eliminarlo) ───────────────────────────--

//Puede modificarse cualquier cosa MENOS la ID

void modificarJuego (char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "r+b");

    if (archi != NULL)
    {
        char nombreJuegoBuscado[LIMITE];
        int flag = 0;

        printf("\nCual es el nombre del juego que desea modificar? ");
        limpiarStdin();
        scanf(" %49[^\n]", nombreJuegoBuscado);

        flag = verificarExistenciaJuego(archi, nombreJuegoBuscado);

        if (flag > 0)
        {
            int cambio;
            Juego aux; //creo un auxiliar
            fseek(archi, -(long)sizeof(Juego), SEEK_CUR);
            fread(&aux, sizeof(Juego), 1, archi); //el auxiliar ahora contiene los datos del juego

            cambio = menuSelectorModificarJuego(&aux); //se modifica lo que se necesita en otra función, devuelve la opcion que se eligió en el menú
            if (cambio >= 1 && cambio <= 3)
            {

                fseek(archi, -(long)sizeof(Juego), SEEK_CUR); // casteo a sizeof long y luego lo hago negativo para moverme un juego atras
                fwrite(&aux, sizeof(Juego), 1, archi);
                printf("\nEl cambio se ha realizado correctamente.\n");
            }
        }
        else
            printf("\nNo se ha encontrado el juego buscado. Intente de nuevo.\n");

        fclose(archi);

    }else
    {
        printf("\nHa ocurrido un error en la apertura del archivo.\n");
    }

}

int menuSelectorModificarJuego (Juego *aux)
{
    int opcion;

    printf("\nIngrese que es lo que quiere modificar del juego seleccionado: \n");
    printf("'1' -> Cambiar el nombre.\n");
    printf("'2' -> Cambiar la categoria.\n");
    printf("'3' -> Cambiar el precio.\n");
    printf("'4' -> No quiero cambiar nada.\n");

    do
    {
        limpiarStdin();
        printf("\nSu decision: ");
        scanf("%i", &opcion);
        switch(opcion)
        {
        case 1:
            printf("\nIngrese el nuevo nombre del juego: ");
            limpiarStdin();
            scanf(" %49[^\n]", (*aux).nombreJuego);
            break;
        case 2:
            printf("\nIngrese la nueva categoria del juego: ");
            limpiarStdin();
            scanf(" %49[^\n]", (*aux).categoriaJuego);
            break;
        case 3:
            printf("\nIngrese el nuevo precio del juego: ");
            limpiarStdin();
            while(scanf(" %f", &(*aux).precioJuego) != 1)
            {
                limpiarStdin();
                printf("\nIngrese el nuevo precio del juego: ");
            }
            break;
        case 4:
            printf("\nSaliendo del menu...\n\n");
            break;
        default:
            printf("\nHa ingresado un valor invalido. Intente de nuevo.\n");
            break;
        }
        limpiarStdin();

    }while (opcion < 1 || opcion > 4);

    return opcion; //devuelve opcion para reemplazar y poner un printf en la función madre
}


// ── Filtrado por categoría ────────────────────────────────────────────────────


int verificarExistenciaJuego (FILE *archi, char nombreBuscado[]) //leer en juego.h por qué lo puse acá (considerar cambiar de lugar maybe?)
{
    rewind(archi); //para poder verificar si un juego existe debo recorrer todo el archivo

    int flag = 0; //0 significa "no existe"

    Juego juegoEnArchivo; //sería un "aux"

    while(fread(&juegoEnArchivo, sizeof(Juego), 1, archi) > 0 && flag != 1) //lee todos los juegos en archivo hasta encontrar el buscado o llegar al final
                                                        // Y verifica que el juego no este eliminado, el juego podria volver a existir en un futuro
    {
        if(strcmpi(juegoEnArchivo.nombreJuego, nombreBuscado) == 0 && juegoEnArchivo.eliminado != 1)
            flag = 1; //Si los nombres coinciden, el juego ya existe en la tienda
    }

    return flag; //recordatorio que el indicador queda inmediatamente después del archivo encontrado (si se encontró)
}

void leerJuegosFiltradosTienda(char nombreArchivo[], char categoria[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    Juego aux;
    int contador = 0;

    if(archi)
    {
        while (fread(&aux, sizeof(Juego), 1, archi) > 0)
        {
            if (compararJuegoCategoria(aux, categoria))
            {
                printf("\n=============Juego #%i - Categoria: %s================\n", contador + 1, categoria);
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
        fclose(archi);
    }
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE. . .\n");
}

int compararJuegoCategoria(Juego juegoAFiltrar, char categoria[])
{
    int juegoDeCategoria = 0;

    if((strcmpi(juegoAFiltrar.categoriaJuego, categoria) == 0 && juegoAFiltrar.eliminado == 0)) // Compara si la categoria coincide con la recibida por parametro y si el juego no esta eliminado
        juegoDeCategoria = 1;

    return juegoDeCategoria; //si es 0, el juego, no pertenece a esa categoria.
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
        mostrarArrJuegosOrdenado(arr, validos, 'n');
        fclose(archi); //estaba fuera del else, pero el archivo solo se cierra si se pudo abrir
    }
    else
        printf("\nERROR, EL ARCHIVO NO PUDO ABRIRSE. . .\n");
}

void ordSeleccionNombreJuego(Juego arr[], int validos)
{
    int posMenor;
    Juego aux;

    for (int i = 0; i < validos - 1; i++)
    {
        posMenor = posMenorNombreJuego(arr, validos, i);
        aux = arr[i];
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
    int cantEliminados = 0;
    for(int i = 0; i < validos; i++)
        cantEliminados += arr[i].eliminado;

    if(cantEliminados < validos) // Si los juegos eliminados es igual que los validos significa que hay juegos en la tienda pero estan todos eliminados
    {
        for (int i = 0; i < validos; i++)
        {
            if(arr[i].eliminado == 0)
            {
                if (tipoDeOrdenado == 'n')
                    printf("\n=============Juegos [A-Z]===============\n");
                else
                    printf("\n=======Juegos [menor $ -> mayor $]=======\n");
                leerUnJuego(arr[i]);
                printf("\n======================================\n");
            }
        }
    }
    else
        printf("\nNO HAY JUEGOS PARA MOSTRAR. . .\n");
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
        ///fijate que hay una funcion para esto, si queres usala, si no, no. lmao
        //encontré la función que me decís pero esa es específicamente para usuarios

        Juego arr[validos]; //creo el array de juegos

        rewind(archi); //vuelvo al inicio del archivo para el siguiente paso

        fread(arr, sizeof(Juego), validos, archi); //paso todos los juegos al array

        ordInsercionPrecioJuego(arr, validos);

        mostrarArrJuegosOrdenado(arr, validos, 'p');

        fclose(archi);

    }else
    {
        printf("\nHa ocurrido un error en la apertura del archivo.\n");
    }
}

void ordInsercionPrecioJuego (Juego arr[], int validos)
{
    int posActual = 0;

    while (posActual < validos-1)
    {
        ordenarInsertadamente(arr, posActual, posActual+1);
        posActual++;
    }
}

void ordenarInsertadamente (Juego arr[], int posActual, int posDatoAColocar) //ir buscando en la "zona ordenada" donde colocar el valor, mientras mueve los valores en el camino 1 a la derecha
{
    Juego aux = arr[posDatoAColocar];

    while (posActual >= 0 && arr[posActual].precioJuego > aux.precioJuego)
    {
        arr[posActual+1] = arr[posActual];
        posActual--;
    }
    arr[posActual+1] = aux;
}
