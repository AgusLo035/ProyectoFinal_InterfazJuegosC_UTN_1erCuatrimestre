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

// Alta / escritura
void guardarJuegosEnArchivo(char nombreArchivo[]);
void cargarJuegoATienda(FILE *archi);
Juego cargarNuevoJuego();
int determinarIDNuevoJuego();

// Baja / eliminar
void eliminarJuegoDeTienda (char nombreArchivo[]);
void marcarJuegoActualComoEliminado (FILE *archi);

// Modificar
void modificarJuego (char nombreArchivo[]); //puede modificarse todo menos la id (y tampoco puede eliminarse el juego porque hay una función aparte para eso)
int menuSelectorModificarJuego (Juego *aux);

// Consulta / lectura
void leerJuegosDeTienda(char nombreArchivo[]);
void leerJuegosArchivo(FILE *archi);
void leerUnJuego(Juego unJuego);
Juego buscarJuegoPorId (int idBuscada); //Abre archivo y busca un juego a partir de su id. Si lo encuentra devuelve el juego. Si no lo encuentra o falla fopen, devuelve -1.
Juego buscarJuegoPorNombre (int nombreJuegoBuscado[]); //Abre archivo y busca un juego a partir de su nombre. Si lo encuentra devuelve el juego. Si no lo encuentra o falla fopen, devuelve -1.

// Filtrado por categoría
int verificarExistenciaJuego (FILE *archi, char nombreBuscado[]); //indica por flag 1 si un juego existe por nombre (lo pongo en esta sección de filtrado porque si no no sé donde)
void leerJuegosFiltradosTienda(char nombreArchivo[], char categoria[]);
int compararJuegoCategoria(Juego juegoAFiltrar, char categoria[]);

// Ordenamiento por selección (nombre A-Z)
void leerJuegosOrdenadosNombreTienda(char nombreArchivo[]);
void ordSeleccionNombreJuego(Juego arr[], int validos);
int posMenorNombreJuego(Juego arr[], int validos, int posInicial);
void mostrarArrJuegosOrdenado(Juego arr[], int validos, char tipoDeOrdenado);

// Ordenamiento por insercion (mostrar juegos del menor a mayor precio)
void leerJuegosOrdenadosPrecioTienda (char nombreArchivo[]);
void ordInsercionPrecioJuego (Juego arr[], int validos);
void ordenarInsertadamente (Juego arr[], int posActual, int posDatoAColocar);

// Pilas
int contarDimPila(Pila pila);
void reajustarDimPilaTope(Pila *pila, int datoAIngresar);

#endif // JUEGO_H_INCLUDED
