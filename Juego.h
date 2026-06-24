#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "pila.h"

#define LIMITE 50
#define JUEGOSTIENDA "tienda.bin"

typedef struct
{
    char nombreJuego[LIMITE];
    char categoriaJuego[LIMITE];
    float precioJuego;
    int id; //comienzan en 0, los eliminados mantienen su id
    int eliminado; //0 es NO ----1 es SI
}Juego;

void limpiarStdin(); //Toma todos los caracteres de stdin hasta que no quede nada. (fflush stdin no funcionaba)

// Alta / escritura
void guardarJuegosEnArchivo(char nombreArchivo[]); //Guarda cualquier juego creado en archivo.
void cargarJuegoATienda(FILE *archi); //Llama a función de crear juego, no lo crea si el juego ya existe.
Juego cargarNuevoJuego(); //Crea un juego
int determinarIDNuevoJuego(); //Determina qué ID tiene el juego nuevo, basandose en la cantidad de juegos que existan.

// Baja / eliminar
void eliminarJuegoDeTienda (char nombreArchivo[]); //Elimina lógicamente del archivo un juego que exista.
void marcarJuegoActualComoEliminado (FILE *archi); //Marca el juego actual en el archivo como eliminado. Se asume el indicador de posición está inmediatamente después del "juego actual"

// Modificar
void modificarJuego (char nombreArchivo[]); //puede modificarse todo menos la id (y tampoco puede eliminarse el juego porque hay una función aparte para eso)
int menuSelectorModificarJuego (Juego *aux); //Contiene el menú sobre qué variable modificar de un juego.

// Consulta / lectura
void leerJuegosDeTienda(char nombreArchivo[]); //Abre el archivo y llama a la función que muestra todos los juegos.
void leerJuegosArchivo(FILE *archi); //Muestra todos los juegos del archivo que recibe
void leerUnJuego(Juego unJuego); //Muestra los datos de un solo juego.
Juego buscarJuegoPorId (int idBuscada); //Abre archivo y busca un juego a partir de su id. Si lo encuentra devuelve el juego. Si no lo encuentra o falla fopen, devuelve -1.
Juego buscarJuegoPorNombre (char nombreJuegoBuscado[]); //Abre archivo y busca un juego a partir de su nombre. Si lo encuentra devuelve el juego. Si no lo encuentra o falla fopen, devuelve -1.

// Filtrado por categoría
int verificarExistenciaJuego (FILE *archi, char nombreBuscado[]); //indica por flag 1 si un juego existe por nombre (lo pongo en esta sección de filtrado porque si no no sé donde)
void leerJuegosFiltradosTienda(char nombreArchivo[], char categoria[]); //Busca y muestra todos los juegos que sean de la categoria ingresada por parametro.
int compararJuegoCategoria(Juego juegoAFiltrar, char categoria[]); //Verifica que un juego no eliminado pertenezca a la categoria ingresada por parametro.

// Ordenamiento por selección (nombre A-Z)
void leerJuegosOrdenadosNombreTienda(char nombreArchivo[]); //Lee por orden alfabético todos los juegos de la tienda.
void ordSeleccionNombreJuego(Juego arr[], int validos); //Ordena por metodo de seleccion los juegos de la tienda.
int posMenorNombreJuego(Juego arr[], int validos, int posInicial); //Busca la posición del nombre con el nombre mas cerca de la A alfabéticamente hablando.
void mostrarArrJuegosOrdenado(Juego arr[], int validos, char tipoDeOrdenado); //Muestra a los juegos ordenados con un printf especial. tipoDeOrdenado = 'n' refiere a por nombre, cualquier otro valor a por precio

// Ordenamiento por insercion (mostrar juegos del menor a mayor precio)
void leerJuegosOrdenadosPrecioTienda (char nombreArchivo[]); //Ordena todos los juegos de la tienda en order de precio menor a mayor.
void ordInsercionPrecioJuego (Juego arr[], int validos); //Ordena por metodo de inserción los juegos de la tienda (por precio).
void ordenarInsertadamente (Juego arr[], int posActual, int posDatoAColocar); //Va buscando en la "zona ordenada" donde colocar el valor, mientras mueve los valores en el camino 1 a la derecha

// Pilas
int contarDimPila(Pila pila);
void reajustarDimPilaTope(Pila *pila, int datoAIngresar);

#endif // JUEGO_H_INCLUDED
