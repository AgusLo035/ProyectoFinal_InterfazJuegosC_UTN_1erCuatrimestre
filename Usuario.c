#include "usuario.h"

/// Registro =======================================================================================

Usuario registrarUsuario(Usuario arr[], int validos) //crea y devuelve un solo usuario.
{
    Usuario usuarioCargado;

    char inputTeclado[VERIFICARLIMITE]; //51 para verificacion de caracteres permitidos (50)

    int existe = 0;

    printf("\n=============CREACION DEL USUARIO================\n");

    do // Mientras el nombre de usuario no este disponible
    {
        if(existe == 1)
            printf("\nUH-OH!, este nombre de usuario no esta disponible!\n");

        do // Mientras los caracteres ingresados supere el LIMITE
        {
            printf("Ingrese el nombre de usuario: ");
            limpiarStdin();
            scanf(" %50[^\n]", inputTeclado);
            if(strlen(inputTeclado) >= LIMITE)
                printf("\nVuelva a ingresar un nombre dentro del rango!\n");

        }while(strlen(inputTeclado) >= LIMITE);

        for(int i = 0 ; i < validos && existe == 0 ; i++) // Busca si el nombre de usuario existe
        {
            if(strcmp(arr[i].userName, inputTeclado) == 0)
                existe = 1;
        }

    }while(existe == 1);



    strcpy(usuarioCargado.userName, inputTeclado); // Al pasar la verificacion anterior, se copian los valores ingresados al nuevo usuario a registrar


    do // Mientras la contrasenia supere el rango
    {

        printf("\nPASSWORD: ");
        limpiarStdin();
        scanf(" %50[^\n]", inputTeclado);
        if(strlen(inputTeclado) >= LIMITE)
            printf("\nVuelva a ingresar un password dentro del rango!\n");

    }while(strlen(inputTeclado) >= LIMITE);

    strcpy(usuarioCargado.password, inputTeclado); // Al pasar la verificacion anterior, se copian los valores ingresados al nuevo usuario a registrar

    usuarioCargado.billetera         = 0;
    usuarioCargado.bibliotecaUsuario = NULL;
    usuarioCargado.validosBiblioteca = 0;

    usuarioCargado.carritoDeJuegos = NULL;
    usuarioCargado.validosCarrito = 0;

    usuarioCargado.eliminado = 0;

    inicpila(&usuarioCargado.historialDeJuego);

    // TODOS los parametros restantes se inicializan en 0/NULL

    printf("\n=============FIN DE LA CREACION DEL USUARIO================\n");

    return usuarioCargado;
}

Usuario crearUsuarioAdmin() // Se crea un usuario administrador dependiendo de la matriz admin
{
    Usuario admin;

    strcpy(admin.userName, matAdmin[0]);
    strcpy(admin.password, matAdmin[1]);
    admin.eliminado = 0;
    admin.billetera = 1000; // Inicializado en 1000 porque es admin

    inicpila(&admin.historialDeJuego);

    admin.carritoDeJuegos = NULL;
    admin.validosCarrito = 0;

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
//            limpiarStdin();
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

void agregarUsuarioAArr (Usuario **arr, int *cantUsuarios) //recibe el array, aumenta validos por 1, ingresa al usuario en el array. Es básicamente una opción de registro.
{                                                         // Siendo la cantidad usuarios los validos que existen en el main hasta el momento
    (*cantUsuarios) += 1; // Se suma +1 a la cant de usuarios que existen

    Usuario *aux = (Usuario*) realloc((*arr), sizeof(Usuario) * (*cantUsuarios)); //hago un espacio para el nuevo usuario

    if (aux != NULL)
    {
        aux[((*cantUsuarios)-1)] = registrarUsuario((*arr), (*cantUsuarios) - 1); //agrego al usuario en la posición nueva
                                                                             // cantUsuarios - 1 porque la ultima pos aun no existe, no fue creada (devuelta por la funcion de registrar)
        printf("\nUsuario creado exitosamente.\n");
        (*arr) = aux; // se iguala el arreglo de usuarios con la nueva dir de memoria que contiene los usuarios y el nuevo registrado.
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
int creacionArchivoDeUsuarios (Usuario **arr) //si no existe el archivo usuarios, lo crea y añade al primer usuario admin
{                                           /// SOLO se hace si no existe ^^^, se ejecuta una unica vez hasta que el archivo de usuarios sea eliminado
    FILE *archi = fopen(LISTAUSUARIOS, "wb"); // El archivo de usuarios es creado por primera vez

    int validos = -1; //se devuelve como "validos" en el main. Es -1 si hay error en fopen

    Usuario *aux; // Variable usuario puntero que almacenara el arreglo dinamico

    if (archi)
    {
        validos = 1;

        fwrite(&validos, sizeof(int), 1, archi); //escribo "1" al principio del archivo, que serían los validos

        aux = malloc(sizeof(Usuario)*1); // Creo un arreglo dinamico que almacena 1 usuario

        if (aux != NULL)
        {
            (*arr) = aux; // La dir de memoria del arr aux se iguala al que se encuentra en el main

            (*arr)[0] = crearUsuarioAdmin(); //coloco al usuario admin como primer usuario en el arreglo dinamico del main

            fwrite(&(*arr)[0], sizeof(Usuario), 1, archi); // Se escribe el usuario admin en el archivo
            /// Al ser la primera vez que se crea el archivo, el admin NO tiene juegos en su biblioteca ni juegos a comprar
            // Ambos de sus validos en biblioteca y carrito son 0, no es necesario pasarlos al archivo
        }
        else
        {
            printf("\nERROR EN MALLOC. . .\n");
            validos = -1; //error en malloc en este caso
        }

        fclose(archi);
    }
    else
        printf("\nHa ocurrido un error en la creacion del archivo usuarios. Reinice el programa e intente nuevamente.\n");

    return validos;
}

int pasarUsuariosArchivoAArrDin (char nombreArchivo[], Usuario **arr) //Trae los validos, usuarios y sus respectivas biblioteca y carritos a un array. Devuelve los validos que obtuvo del principio del archivo.
{
    FILE *archi = fopen(nombreArchivo, "r+b");

    int validos = -1; //solo se queda así si no se abre el archivo (si devuelve esto se termina el programa) ERROR

    if(archi)
    {
        fread(&validos, sizeof(int), 1, archi); // los validos de todos los usuarios es el primer y unico dato entero que se encuentra al principio del archivo
                                                // A partir de ahi, se trabaja con usuarios y sus arreglos dinamicos
        int flag = pasarUsuarioArchiAArrDinArchi(archi, arr, validos); // Paso el archivo a un Arreglo dinamico de usuarios que es con lo que trabajaremos en el main
                                                                        // Los validos obtenidos son lo primero que esta en el archivo
        if(flag == -1) // Si ocurre un error, el archivo se cierra y devuelve -1, error
        {
            printf("\nERROR -1, MALLOC. . .\n");
            fclose(archi);
            return flag;
        } // -1 si ocurre un error
        else if(flag == -2)
        {// -2 es solo una advertencia, no un error
            printf("\nADVERTENCIA -2, NO EXISTEN USUARIOS EN EL SISTEMA. . .\n");
            fclose(archi);
            return 0; // Al no existir usuarios, se devuelve 0 como validos
        }
        fclose(archi);
    }
    else
    {
        if (errno == ENOENT) //"ENOENT" significa que el error es que el archivo NO EXISTE
            validos = 0; // el archivo no existe, no hay usuarios. Devuelvo 0 usuarios validos
        else
            printf("\n\nHa ocurrido un error en la apertura del archivo de usuarios. Reinice el programa e intente nuevamente.\n");
    }

    return validos; // se devuelven los validos obtenidos del archivo o un ERROR
}

int pasarUsuarioArchiAArrDinArchi (FILE *archi, Usuario **arr, int usuariosRegistradosEnSistema) // Paso los validos obtenidos del mismo archivo
{
    int i = 0;

    if (usuariosRegistradosEnSistema == 0)
        return -2; //NO existen usuarios en el sistema

    //SI EXISTEN USUARIOS EN EL SISTEMA, sigo abajo

    (*arr) = (Usuario*) malloc(sizeof(Usuario) * usuariosRegistradosEnSistema); // Creo un arreglo dinamico con la dimension obtenida
    if(!(*arr))
    {
        printf("\nERROR EN MALLOC. . .\n");
        return -1; // Devuelvo ERROR, la funcion de arriba devolvera -1 tambien, o sea, error
    }

    while(i < usuariosRegistradosEnSistema)
    {
        (*arr)[i] = leerUsuarioCompletoDeArchi(archi);// Se carga el arreglo en cada posicion con su usuario correspondiente dentro del archivo
                                                    // Cuando devuelve el usuario, puede seguir con el siguiente hasta que termine la carga
        if(strcmp((*arr)[i].userName, "ERROR. . .") == 0 && (*arr)[i].billetera == -1) // Ambos tienen que cumplir por si a los profes se les ocurre llamar a un usuario "ERROR. . ."
        {
            printf("\nERROR: Fallo la carga del usuario #%d. Carga interrumpida.\n", i + 1);
            free(*arr); // se libera todo el arreglo de usuario, porque tendria usuarios corruptos (usuarios con Error y billetera -1)
            (*arr) = NULL; // El arr pasa a estar inicializado en null
            return -1; // Devuelvo ERROR si ocurrio un error en la carga "leerUsuarioCompletoDeArchi", principalemnte en malloc
        }
        i++;
    }
    return 1; // Si no hubo errores
}

Usuario leerUsuarioCompletoDeArchi(FILE *archi) ///NOTA: antes de llamar a esta función, sí o si hay que mover el indicador de posición 1 posición delante de los validos al inicio del archivo
{                                              // Esta funcion lee un usuario dentro del archivo
    Usuario usuarioLeido;

    fread(&usuarioLeido, sizeof(Usuario), 1, archi); // Leo un usuario, sus parametros biblioteca y carrito pierden su dir de memoria al cargarse al archivo.
                                                    // Por eso en la carga de un usuario al archivo, luego de escribirlo, se escribe su biblioteca y carrito.

    if(usuarioLeido.validosBiblioteca > 0) // Se verifica que tenga al menos 1 juego para no hacer malloc con dimension 0
        usuarioLeido.bibliotecaUsuario = (Juego*) malloc(sizeof(Juego) * usuarioLeido.validosBiblioteca); // Se crea la biblioteca de ese usuario con la cantidad de Juegos que tenia antes de cerrarse el programa
    else
        usuarioLeido.bibliotecaUsuario = NULL; // Si es 0 se inicializa en NULL, el usuario no tiene juegos
    ///los validos de la biblioteca si obtengo, cuando hago fread de un usuario obtengo todo lo que no sea arreglo dinamico
    /// los validos me sirven para saber cuanto me tengo que mover en el archivo sizeof(Juego) * validosbiblioteca por ej
    /// luego puedo hacer billetera y cuando termino ya tengo un usuario completo, no hay perdida de datos.

    if(!usuarioLeido.bibliotecaUsuario && usuarioLeido.validosBiblioteca > 0) // Verifico si hubo error en malloc y sus validos son mayor a 0
    {
        strcpy(usuarioLeido.userName, "ERROR. . .");
        usuarioLeido.billetera = -1; // Esto es para verificar tambien que el saldo sea -1, ya q es imposible, y por si los profes quieren llamar un usuario "ERROR. . ."
        printf("\nERROR EN MALLOC. . .\n");
        return usuarioLeido; // Devuelve un usuario con ERROR
    }

    fread(usuarioLeido.bibliotecaUsuario, sizeof(Juego), usuarioLeido.validosBiblioteca, archi); // Luego de leer la totalidad de un Usuario, comienzo a leer sus juegos dependiendo de sus validos en la biblioteca
    ///ACA cargo la biblioteca de ese usuario en especifico a ese usuario.

    if(usuarioLeido.validosCarrito > 0) // Se verifica que tenga al menos 1 juego en carrito para no hacer malloc con dimension 0
        usuarioLeido.carritoDeJuegos = (Juego*) malloc(sizeof(Juego) * usuarioLeido.validosCarrito); // Se crea el carrito de compra de ese usuario con los juegos que tenia antes de que el programa termine, igual que biblioteca
    else
        usuarioLeido.carritoDeJuegos = NULL;// Si es 0 se inicializa en NULL, el usuario no tiene juegos en su carrito

    if(!usuarioLeido.carritoDeJuegos && usuarioLeido.validosCarrito > 0) // Lo mismo que en la biblioteca, el problema es por malloc, no porque tenga 0 la dim del carrito
    {
        strcpy(usuarioLeido.userName, "ERROR. . .");
        usuarioLeido.billetera = -1;
        printf("\nERROR EN MALLOC. . .\n");
        free(usuarioLeido.bibliotecaUsuario); // Se libera la memoria de la biblioteca en caso de que ocurra un error con carrito
        return usuarioLeido;// devuelvo usuario ERROR
    }

    fread(usuarioLeido.carritoDeJuegos, sizeof(Juego), usuarioLeido.validosCarrito, archi);
    ///ACA cargo el carrito de ese usuario en especifico a ese usuario.

    return usuarioLeido;
    ///devuelvo ese usuario con todos sus parametros completos
}

int guardarArrUsuariosEnArchivo(char nombreArchivo[], Usuario *arr, int validosUsuarios) //Guarda todos los usuarios en archivo. Nota: utiliza "wb", se elimina el archivo ya existente
{ //por el tema mencionado en case 2 del menu de switch en main, debo hacer que devuelva un flag de error si se falla en abrir el archivo
    int flag = -1;

    FILE *archi = fopen(nombreArchivo, "wb");

    if(archi)
    {
        flag = 1;
        fwrite(&validosUsuarios, sizeof(int), 1, archi); //se guardan los validos al principio del archivo, lo primero que guarda
        for(int i = 0 ; i < validosUsuarios ; i++)
        {
            guardarUnUsuarioEnArchi(archi, arr[i]); // Guarda cada uno de los usuarios
        }
        fclose(archi);
        /// en archivo quedaria: int (validos) | usuarioEnespecifico (usuario) |juego1 (juego) | juego2 (juego) | despues seguiria con otro usuario y sus juegos y asi
    }
    else
        printf("\nHubo un error en el guardado de los usuarios. Cualquier cambio realizado no se ha guardado.\n");

    return flag; // Si ocurre un error en la apertura del archivo, devuelve -1
}

void guardarUnUsuarioEnArchi(FILE *archi, Usuario usuario) //Guarda los datos de un usuario en el archivo
{
    fwrite(&usuario, sizeof(Usuario), 1, archi); // Escribo el usuario con sus parametros biblioteca y carrito con sus dir de memoria actuales
                                                //                                                                            ^^ al volver a iniciar el programa su dir de memoria cambia, por eso reescribo la vieja con la nueva y sus datos anteriores
    if(usuario.validosBiblioteca > 0) // Se verifica en biblioteca y carrito que tenga juegos para guardar, si no, no se guardan
        fwrite(usuario.bibliotecaUsuario, sizeof(Juego), usuario.validosBiblioteca, archi); // Escribo los juegos correspondiente a ese usuario a continuacion
    if(usuario.validosCarrito > 0)
        fwrite(usuario.carritoDeJuegos, sizeof(Juego), usuario.validosCarrito, archi); // Escribo los juegos que se encuentran en el carrito a continuacion
}


///Funciones de ADMIN
/// Verificar Admin =======================================================================================

int verificarAdmin(char mat[][LIMITE], char usuarioAdmin[], char passwordAdmin[]) // Verificacion en el main si el usuario ingresado es admin o no
{
    int esAdmin = 0;

    if(strcmp(mat[0], usuarioAdmin) == 0 && strcmp(mat[1], passwordAdmin) == 0) //mat[0] es toda la fila, mismo para mat[1]
        esAdmin = 1;

    return esAdmin; //1 si es admin, 0 si no
}
/// Eliminar usuarios como Admin =======================================================================================

void eliminarUsuarioComoAdmin(char nombreDeUsuarioAEliminar[], Usuario arr[], int validos)
{
    if (strcmp(nombreDeUsuarioAEliminar, "admin") != 0) //solo permito eliminar si el nombre ingresado no es admin
    {
        int pos = buscarUsuarioPorNombreUsuario(nombreDeUsuarioAEliminar, arr, validos); // Se busca el usuario a eliminar

        if (pos > -1)
        {
            eliminarUsuario(&arr[pos]); // paso la dir de memoria de ese usuario para hacer un borrado logico del sistema
            printf("\nUsuario [%s] eliminado.\n", nombreDeUsuarioAEliminar);
        }
        else
            printf("\nUsuario [%s] NO encontrado.\n", nombreDeUsuarioAEliminar);
    }
    else
        printf("\nNo puede eliminarse el usuario admin.\n");
}

/// Eliminar =======================================================================================

void eliminarUsuario(Usuario *usuarioAEliminar)
{
    (*usuarioAEliminar).eliminado = 1; // Cambio el parametro del usuario a ELIMINADO / 1
}

/// Mostrar =======================================================================================

void mostrarUsuarioConMayorCantDeJuegos (Usuario arr[], int validos)
{
    int pos = buscarUsuarioMayorCantDeJuegosComprados(arr, validos); // Busca la pos donde se encuentra el usuario con mayor juegos

    if (pos > -1)
        mostrarDatosUsuario(arr[pos]); // Muestra el usuario con mayor cant de juegos
    else
        printf("\nNingun usuario tiene juegos.\n");
}

int buscarUsuarioMayorCantDeJuegosComprados (Usuario arr[], int validos)
{
    int pos = 0;
    Usuario uMayorJuegos = arr[0];

    for (int i = 0 ; i < validos - 1 ; i++)
    {
        if(uMayorJuegos.validosBiblioteca < arr[i + 1].validosBiblioteca)// comparo la cant de juegos del actual con el siguiente
        {
            uMayorJuegos = arr [i + 1]; // El mayor pasa a ser el siguiente, se repite hasta llegar al final - 1 porque no tendria con que comparar el ultimo
            pos = i + 1;
        }
    }

    if(uMayorJuegos.validosBiblioteca == 0) // Si nadie tiene juegos devuelvo -1 para indicarlo
        pos = -1;

    return pos; //devuelve la pos del usuario con la mayor cantidad de juegos, si es -1 nadie tiene juegos
}

void mostrarUsuarioPorNombreUsuario (char nombreDeUsuario[], Usuario arr[], int validos) // Busco un usuario por su nombre y se muestra
{
    int pos = buscarUsuarioPorNombreUsuario(nombreDeUsuario, arr, validos); // Se busca la pos donde se encuentra ese usuario con ese nombre

    if (pos > -1 && arr[pos].eliminado == 0)
        mostrarDatosUsuario(arr[pos]);
    else
        printf("\nUsuario [%s] NO encontrado.\n", nombreDeUsuario);
}

int buscarUsuarioPorNombreUsuario (char nombreDeUsuario[], Usuario arr[], int validos) // Busca la pos del usuario con ese nombre
{
    int flag = -1;

    for (int i = 0 ; i < validos && flag == -1; i++)
    {
        if(strcmp(nombreDeUsuario, arr[i].userName) == 0) // Comparo nombre de usuario con cada uno en el arreglo hasta encontrarlo o no
            flag = i;
    }

    return flag; //-1 si no existe, mayor a -1 si existe, devuelve la posicion del usuario.
}

void mostrarDatosUsuario(Usuario usuarioCargado) // Printf de los datos del usuario
{
    printf("\n=============DATOS DEL USUARIO (%s)==================\n", usuarioCargado.userName);

    printf("Nombre de usuario: %s\n", usuarioCargado.userName);
    //printf("Password: %s\n", usuarioCargado.password);
    printf("Dinero en la cuenta: $%.2f\n", usuarioCargado.billetera);
    printf("Cantidad de juegos en libreria: %i\n",usuarioCargado.validosBiblioteca);
    printf("Cantidad de juegos en carrito: %i\n",usuarioCargado.validosCarrito);

    printf("\n===============FIN DE LA MUESTRA================\n");
}

void mostrarArrUsuarios(Usuario arr[], int validos) // Muestro un arreglo de usuarios
{
    for (int i = 0 ; i < validos ; i++)
        mostrarDatosUsuario(arr[i]);
}

/// Billetera =======================================================================================
void deshacerUltimaCompra(Pila *historialId, Usuario *usuarioAReembolsarJuego) // Recibo la dir de memoria de la pila y el usuario por referencia
{
    if(!pilavacia(historialId)) // Si pila no esta vacia y tiene juegos para reembolsar
    {
        Juego ultimoJuegoComprado;

        ultimoJuegoComprado.id = desapilar(historialId); // Desapilo la id del ultimo juego comprado

        Juego juegoAQuitar = buscarJuegoPorId(ultimoJuegoComprado.id); // Lo busco en la tienda por id y lo devuelvo, -1 si esta eliminado o error

        if(juegoAQuitar.id != -1) // Verifico que no haya error
        {
            float montoAReembolsar = juegoAQuitar.precioJuego; // El monto a reembolsarse al usuario es el mismo que el precio de ESE juego

            quitarJuegoDeBibliotecaUsuario(&(*usuarioAReembolsarJuego).bibliotecaUsuario, &(*usuarioAReembolsarJuego).validosBiblioteca, juegoAQuitar); // Quito el juego de la biblioteca de ese usuario

            (*usuarioAReembolsarJuego).billetera += montoAReembolsar; // Sumo a la billetera del usuario el monto reembolsado
        }
        else
            printf("\nERROR, EL JUEGO A REEMBOLSAR NO EXISTE (Quitado de la tienda). . .\n");
    }
    else
        printf("\nNO TIENES UN JUEGO PARA REEMBOLSAR. . .\n");
}

int debitarDineroAlUsuario (Usuario *usuarioADebitar, float montoADebitar) // Dir de memoria del usuario para modificar su billetera
{
    int suficiente = 0;

    float sueldoDeUsuario = (*usuarioADebitar).billetera;

    if((sueldoDeUsuario - montoADebitar) < 0)
        printf("\nMonto insuficiente en la cuenta\n");
    else
    {
        (*usuarioADebitar).billetera -= montoADebitar;
        printf("\nMonto actual en la cuenta: %.2f\n", (*usuarioADebitar).billetera);
        suficiente = 1;
    }
    return suficiente; // Devuelvo si el usuario tiene el monto suficiente (1. Suficiente, 0. NO suficiente)
}

void cargarDineroAlUsuario(Usuario *usuarioACargarDinero)
{
    float saldoACargar;

    printf("\n=============INGRESAR DINERO A LA CUENTA================\n");
    printf("Datos Guardados de la Tarjeta\n\nTarjeta: 12325-55458-9923\n");
    printf("CVV: 155\n");
    printf("Ingrese saldo que desea ingresar a la cuenta: ");

    while (scanf("%f", &saldoACargar) != 1 || saldoACargar <= 0) // Se verifica que el tipo de dato sea correcto y mayor a 0
    {
        printf("\nTipo de dato incorrecto/Insuficiente. . .\nIngrese saldo que desea ingresar a la cuenta: ");
        limpiarStdin();
    }

    (*usuarioACargarDinero).billetera += saldoACargar; // Se suma a la billetera del usuario el saldo a cargar

    printf("\n=============FINALIZACION DE INGRESO================\n\n");
}

/// Carrito =======================================================================================


//Decidí cambiar esto porque no sé cómo mandarlo al llamar la función
//Recibe el usuario entero, adentro se encarga de modificar todo
float cargarACarritoUsuario(Usuario *usuarioRecibido, Juego juegoAComprar) // devuelve lo que se debe de debitar al usuario
{
    float flag = 0;

    if (verificarSiJuegoEnBibliotecaUsuario(usuarioRecibido, juegoAComprar) == 1)
    {
        flag = 1;
    }

    for(int i = 0 ; i < (*usuarioRecibido).validosCarrito && flag == 0 ; i++)
    {
        if(strcmp((*usuarioRecibido).carritoDeJuegos[i].nombreJuego, juegoAComprar.nombreJuego) == 0)
            flag = 1;
    }

    if(!flag)
    {
        Juego *carritoAux = (*usuarioRecibido).carritoDeJuegos; //creo auxiliares para no inutlizar al usuario si sale mal realloc
        int validosCarritoAux = (*usuarioRecibido).validosCarrito;

        float sumaJuegosEnCarrito = 0;

        validosCarritoAux += 1; // Aumenta en 1 la dim del carrito para poder agregar otro juego

        carritoAux = (Juego *) realloc(carritoAux, sizeof(Juego) * validosCarritoAux); // Se aumenta la dim dependiendo de los validos
        if (!carritoAux)
        {
            printf("\nERROR EN REALLOC. . .\n"); // Realloc fallo y no aumento la dim del carrito, queda con su dir de memoria y validos anteriores
            validosCarritoAux -= 1;
            return -1; // Devuelvo ERROR
        }
        carritoAux[(validosCarritoAux) - 1] = juegoAComprar; // Agrego el juego que se desea comprar en la ultima posicion del carrito

        sumaJuegosEnCarrito = sumarPrecioJuegos(carritoAux, validosCarritoAux, 0); //Le paso el arreglo de juegos para contar el monto total que existe en carrito

        (*usuarioRecibido).carritoDeJuegos = carritoAux;
        (*usuarioRecibido).validosCarrito = validosCarritoAux;

        return sumaJuegosEnCarrito; // Devuelve la suma de todos los juegos en el carrito, no lo debita
    }
    else
    { //comento el printf de abajo y queda para nosotros, voy a hacer que devuelva el valor y recién ahí haga el printf
//        printf("\nYA tienes este juego en el carrito. . .\n");
        return -2; // -2 Indica que ya tienes este juego en el carrito o biblioteca, -1 indica error
    }
}

float sumarPrecioJuegos (Juego arr[], int validos, int i) // devuelve suma del precio de un juego/s
{
    float sumaTotal = 0;

    if (validos != 0) //agregué que si validos es 0 devuelva 0
    {
        if(i == validos - 1) // la condicion de corte es cuando la pos llegue al final del arreglo
            sumaTotal = arr[i].precioJuego;
        else
            sumaTotal = arr[i].precioJuego + sumarPrecioJuegos(arr, validos, i + 1); // Sumo lo que tenga en esta pos mas lo que siga, me acerco a la condicion de corte con pos + 1
    }

    return sumaTotal; // Devuelvo la suma de los precios de los juegos
}

int verificarSiJuegoEnCarritoUsuario (Usuario *usuarioRecibido, Juego juegoRecibido) //Devuelve 1 si encontró, 0 si no lo hizo
{
    int validosCarrit = (*usuarioRecibido).validosCarrito;
    Juego *carrit = (*usuarioRecibido).carritoDeJuegos;

    int flag = 0;

    for(int i = 0 ; i < validosCarrit && flag == 0; i++) // Busco hasta llegar al final de carrito o encontrar el juego recibido por parametro
    {
        if(strcmp(carrit[i].nombreJuego, juegoRecibido.nombreJuego) == 0)
            flag = 1;
    }

    return flag;
}

float sumarJuegosEnCarrito(Usuario usuario)
{
    float montoTotal = 0;

    for(int i = 0 ; i < usuario.validosCarrito ; i++)
        montoTotal += usuario.carritoDeJuegos[i].precioJuego;

    return montoTotal;
}
/// ^^^ Esta funcion se llama en el main antes de ejecutar "comprarJuegosDelCarrito()"

void comprarJuegosDelCarrito(Usuario *usuarioAComprarJuegos) // Compro TODOS los juegos que existen en el carrito
{// La verificacion se hace previamente de acceder a esta funcion con la funcion ya hecha de contar el monto total de un arreglo de juegos y si el usuario tiene ese monto disponible para comprar
    float montoADebitar = 0;

    int nuevaDimBiblioteca = (*usuarioAComprarJuegos).validosCarrito + (*usuarioAComprarJuegos).validosBiblioteca; // Sumo la dim del carrito y la dim de la biblioteca para tener la nueva dim total de la biblioteca

    Juego *juegoAux = (Juego*) realloc((*usuarioAComprarJuegos).bibliotecaUsuario, sizeof(Juego) * nuevaDimBiblioteca); // Cambio la dim de la biblioteca
                                // Si es null ^ actua como malloc
    if(!juegoAux)
    {
        printf("\nERROR EN MALLOC. . . NO se compro ningun juego, la biblioteca y el carrito no sufrieron cambios. . .\n");
        return; // No se pudo redimensionar
    }
    (*usuarioAComprarJuegos).bibliotecaUsuario = juegoAux; // Se pudo redimensionar la biblioteca

    int valBiblioteca = (*usuarioAComprarJuegos).validosBiblioteca; // Comienzo a partir del ultimo juego que estaba en la biblioteca
    int x = 0; // primer elemento que se encuentra en el carrito

    for (int i = valBiblioteca ; i < nuevaDimBiblioteca ; i++)
    {//Paso los elementos a partir de la primer posicion del carrito a la biblioteca despues del ultimo juego que tenia el usuario en la biblioteca

        int contDimPila = contarDimPila((*usuarioAComprarJuegos).historialDeJuego);

        if(contDimPila >= 50)
            reajustarDimPilaTope(usuarioAComprarJuegos.historialDeJuego, (*usuarioAComprarJuegos).carritoDeJuegos[x].id);
        else
            apilar(&(*usuarioAComprarJuegos).historialDeJuego, (*usuarioAComprarJuegos).carritoDeJuegos[x].id);

        (*usuarioAComprarJuegos).bibliotecaUsuario[i] = (*usuarioAComprarJuegos).carritoDeJuegos[x];
        montoADebitar += (*usuarioAComprarJuegos).carritoDeJuegos[x].precioJuego; // suma de monto a debitar de los juegos
        x++;
        // me voy desplazando en el carrito por cada juego hasta terminar de recorrerlo
    }

    //cuando se termina de copiar los juegos del carrito a la biblioteca se libera la memoria
    free((*usuarioAComprarJuegos).carritoDeJuegos);
    (*usuarioAComprarJuegos).carritoDeJuegos = NULL;
    (*usuarioAComprarJuegos).validosCarrito = 0;
    (*usuarioAComprarJuegos).validosBiblioteca = nuevaDimBiblioteca;
    // Los validos pasan a ser la nueva dim

    debitarDineroAlUsuario(usuarioAComprarJuegos, montoADebitar); // Se le debita el usuario el total sumado previamente

}
//esta funcion quita todos los juegos de la tienda y los carga al arreglo dinamico de biblioteca
//Tambien le debita el total de todos los juegos al usuario
/// LA VERIFICACION si el usuario tiene el monto sufciente hagamosla en el main en vez de en la funcion
/// ^^importante

/// Biblioteca personal =======================================================================================
void quitarJuegoDeBibliotecaUsuario(Juego **arr, int *validosBiblioteca, Juego juegoAQuitar) //siendo el arr de tipo juego la biblioteca de ese usuario y SABIENDO QUE ESE USUARIO TIENE ESE JUEGO POR VERIFICACION PREVIA/FUERA DE LA FUNCION
            //Recibo la dir de memoria de la biblioteca del usuario que se va a modificar, dir de memoria de sus validos y el juego a quitar.
{
    int flag = 0;

    for(int i = 0 ; i < (*validosBiblioteca) && flag == 0 ; i++) // Mientras NO se haya encontrado el juego a eliminar en la biblioteca del usuario
    {
        if((*arr)[i].id == juegoAQuitar.id) // Si se encuentra por id
        {
            flag = 1;
            (*arr)[i] = (*arr)[((*validosBiblioteca) - 1)];
            (*validosBiblioteca) -= 1; //pasa el juego a eliminar al final para hacer realloc
            //Intercambio lugares con el ultimo elemento de la biblioteca para reducir su dim en 1
        }
    }

    if((*validosBiblioteca) == 0) // Si al quitarse el juego la biblioteca se queda sin juegos, entonces
    {
        free((*arr)); // libero la memoria
        (*arr) = NULL; // Al tener 0 juegos vuelve a ser null
        return; // El programa termina en vez de seguir con cosas innecesarias
    }

    Juego *aux = (Juego*) realloc((*arr), sizeof(Juego) * (*validosBiblioteca)); // Utilizo los nuevos validos como dim (Reducido)

    if(!aux)
    {
        printf("\nERROR EN REALLOC. . . NO se quito el Juego de la biblioteca. . .\n");
        (*validosBiblioteca) += 1; // sus validos vuelven a como estaban antes, su biblioteca NO fue modificada
        return;
    }

    (*arr) = aux; // NO hubo error, la biblioteca se disminuyo en 1 quitando el ultimo
}

void cargarABibliotecaUsuario(Usuario *usuarioACargar, Juego juegoACargar) //verificacion si el usuario tiene o no el juego se hace previamente en el main
{
    (*usuarioACargar).validosBiblioteca += 1;

    Juego *aux = (Juego*) realloc((*usuarioACargar).bibliotecaUsuario, sizeof(Juego) * (*usuarioACargar).validosBiblioteca); // Aumenta en 1 la dim de la biblioteca del usuario para aniadir un juego

    if (!aux)
    {
        printf("\nERROR EN REALLOC. . . NO se aniadio ningun juego a la biblioteca. . .\n");
        (*usuarioACargar).validosBiblioteca -= 1; // Validos vuelve a su valor org, no hubo modificaciones en la biblioteca
        return;
    }

    (*usuarioACargar).bibliotecaUsuario  = aux; // Pudo modificarse correctamente biblioteca

    (*usuarioACargar).bibliotecaUsuario[((*usuarioACargar).validosBiblioteca - 1)] = juegoACargar; // Cargo el juego en la ultima posicion del arreglo

    int contarDimHistorial = contarDimPila((*usuarioACargar).historialDeJuego); // Se cuenta la dim de la pila para saber si esta al llena (50 elementos cargados) o no

    if(contarDimHistorial >= 50) // Si la pila esta COMPLETAMENTE llena, se elimina el valor mas viejo para agregar la id del ultimo juego agregado al tope de la pila
        reajustarDimPilaTope(&(*usuarioACargar).historialDeJuego, juegoACargar.id);

    else
        apilar(&(*usuarioACargar).historialDeJuego, juegoACargar.id); // Si pila tiene la dim suficiente, se carga la id del juego al tope
}

int verificarSiJuegoEnBibliotecaUsuario (Usuario *usuarioRecibido, Juego juegoRecibido) //Devuelve 1 si encontró, 0 si no lo hizo
{
    int validosBibl = (*usuarioRecibido).validosBiblioteca;
    Juego *bibl = (*usuarioRecibido).bibliotecaUsuario;

    int flag = 0;

    for(int i = 0 ; i < validosBibl && flag == 0; i++) // Busco hasta llegar al final de biblioteca o encontrar el juego recibido por parametro
    {
        if(strcmp(bibl[i].nombreJuego, juegoRecibido.nombreJuego) == 0)
            flag = 1;
    }

    return flag;
}

/// Pilas =======================================================================================

void reajustarDimPilaTope(Pila *pila, int datoAIngresar) // Elimino el dato mas viejo de la pila y apilo el dato a ingresar en el tope
 {
    Pila aux;
    inicpila(&aux);

    while(!pilavacia(pila)) // Paso de una pila a la otra para eliminar el mas viejo cuando se pasa a aux
        apilar(&aux, desapilar(pila));

    desapilar(&aux); //desapilo el valor mas viejo

    while(!pilavacia(&aux))
        apilar(pila, desapilar(&aux));

    apilar(pila, datoAIngresar); // Ahora pila me queda con 49 elementos y puedo apilar el dato a ingresar en el tope
    // Esta funcion se llama cuando pila esta COMPLETAMENTE llena
}

int contarDimPila(Pila pila) // Le paso pila por copia y devuelvo si dim actual
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

int verificarUsuarioRegistrado(Usuario *arr, int validos, char username[], char password[])
{
    int flag = -1;

    for(int i = 0 ; i < validos && flag == -1; i++)
    {
        if(strcmp(arr[i].userName, username) == 0 && strcmp(arr[i].password, password) == 0 && flag == -1)
            flag = i; // comparo el nombre y contrasenia de cada usuario con el recibido por parametro hasta encontrar similitud
    }

    return flag; //Devuelve la pos de ese usuario para luego hacer usuario de la sesion iniciada = arr[esa posicion que devuelve
                //devuelve -1 si la contraseña o usuario son incorrectos
}

int verificarNombreUsuarioRegistrado(Usuario arr[] , int validos, char username[])
{
    int flag = 0;

    for(int i = 0 ; i < validos && flag == 0; i++)
    {
        if(strcmp(arr[i].userName, username) == 0) // Busco hasta encontrar el nombre recibido por parametro
            flag = 1;
    }

    return flag; //1 si usuario existe, 0 si no existe
}



/// Mostrar Juegos del carrito de usuario específico
void mostrarCarritoDeUsuario (Usuario usuario)
{
    if (usuario.validosCarrito == 0) // Si el usuario no tiene juegos en el carrito, no se muestra nada
    {
        printf("\nNo hay juegos en el carrito.\n\n");
    }else
    {
        for(int i = 0 ; i < usuario.validosCarrito ; i++) // Se muestra las veces iguales a la cantidad de juegos que tiene el usuario en el carrito
        {
            printf("\n=============Juego en Carrito (U: %s)#%i================\n", usuario.userName, i+1);
            leerUnJuego(usuario.carritoDeJuegos[i]);
            printf("\n======================================\n");
        }
    }
}

///Mostrar juegos de biblioteca de usuario especifico
void mostrarBibliotecaDeUsuario (Usuario usuario)
{
    if (usuario.validosBiblioteca == 0) // Si el usuario no tiene juegos en el carrito, no se muestra nada
    {
        printf("\nNo hay juegos en la biblioteca.\n\n");
    }else
    {
        for(int i = 0 ; i < usuario.validosBiblioteca ; i++) // Se muestra las veces iguales a la cantidad de juegos que tiene el usuario en el carrito
        {
            printf("\n=============Juego en Biblioteca (U: %s)#%i================\n", usuario.userName, i+1);
            leerUnJuego(usuario.bibliotecaUsuario[i]);
            printf("\n======================================\n");
        }
    }
}

/// Ordenamientos con usuarios
//seleccion
void ordSeleccionNombreUsuario(Usuario arr[], int validos) // ord por seleccion un arreglo de usuarios por el nombre de usuario
{
    int posMenor;
    Usuario aux;

    for (int i = 0 ; i < validos - 1; i++)
    {
        posMenor = posNombreMenor(arr, validos, i); // Busco la pos donde se encuentra el menor nombre a partir de la pos actual
        aux = arr[i];
        arr[i] = arr[posMenor];
        arr[posMenor] = aux; // Cambio el elemento en la pos actual con el elemento en la pos obtenida
    }
}

int posNombreMenor (Usuario arr[], int validos, int posInicial) // Se busca la pos donde se encuentra el menor elemento (el nombre)
{
    int posMenor = posInicial;

    char nombreMenor[LIMITE];
    strcpy(nombreMenor, arr[posMenor].userName); // El primer elemento comienza siendo el menor para comenzar a comparar

    for (int i = posMenor + 1 ; i < validos ; i++)
    {
        if(strcmpi(nombreMenor, arr[i].userName) > 0)
        {
            posMenor = i;
            strcpy(nombreMenor, arr[i].userName);
        }
    }
    return posMenor; // Devuelvo la posicion obtenida
}

//insercion
void ordInsercionUsuarioJuegos(Usuario arr[], int validos)
{
    for (int i = 0 ; i < validos - 1 ; i++)
    {
        insertarUsuarioMenorCantJuegos(arr, i, arr[i+1]); // Tomo el usuario en su posicion siguiente para insertarlo en su pos correcta
    }
}

void insertarUsuarioMenorCantJuegos(Usuario arr[], int pos, Usuario usuarioAinsertar) // En un arreglo, se inserta un usuario en donde corresponda comparando con los anteriores
{
    // comienza en la pos anterior al que se le inserta
    int i;

    for(i = pos ; i >= 0 && usuarioAinsertar.validosBiblioteca < arr[i].validosBiblioteca ; i--)
    {                   // Se compara el usuario a insertar (cant de juegos) con sus posiciones anteriores
        arr[i + 1] = arr[i]; // Se va moviendo el elemento de esta posicion con su siguiente
    }
    arr[i + 1] = usuarioAinsertar;
}

void mostrarUsuariosOrdenadosCantJuegos(Usuario arr[], int validos)
{
    Usuario *aux = NULL; // Se utiliza un aux para no modificar el original

    aux = (Usuario*) malloc(sizeof(Usuario) * validos);
    if(!aux)
    {
        printf("ERROR EN MALLOC. . .");
        return;
    }

    for(int i = 0 ; i < validos ; i++)
    {
        aux[i] = arr[i]; // cargo el arreglo aux para mostrarlo
    }

    ordInsercionUsuarioJuegos(aux, validos);
    mostrarArrUsuarios(aux, validos);

    free(aux); // se libera la memoria de aux
}

void mostrarUsuariosOrdenadosNombre (Usuario arr[], int validos)
{
    Usuario *aux = NULL; // Se utiliza un aux para no modificar el original

    aux = (Usuario*) malloc(sizeof(Usuario) * validos);
    if(!aux)
    {
        printf("ERROR EN MALLOC. . .");
        return;
    }

    for(int i = 0 ; i < validos ; i++)
    {
        aux[i] = arr[i]; // cargo el arreglo aux para mostrarlo
    }

    ordSeleccionNombreUsuario(aux, validos);
    mostrarArrUsuarios(aux, validos);

    free(aux); // se libera la memoria de aux
}

