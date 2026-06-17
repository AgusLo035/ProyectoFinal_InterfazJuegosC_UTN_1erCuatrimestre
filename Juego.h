#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "pila.h"

#define LIMITE 50
#define VERIFICARLIMITE 51
#define JUEGOSTIENDA "tienda.bin"

typedef struct
{
    char nombreJuego[LIMITE];
    char categoriaJuego[LIMITE];
    float precioJuego;
    int id; //tengo que ver cómo mantener las IDs, con variable global que se guarda en archivo o simplemente los eliminados mantienen su id para siempre
            ///Yo digo que se mantengan las ids. Hace que se sume +1 y fue, si no usando random, pero yo diria que mejor uses +1
    int eliminado; //0 es NO ----1 es SI
}Juego;

// Alta / escritura
void guardarJuegosEnArchivo(char nombreArchivo[]);
void cargarJuegoATienda(FILE *archi);
Juego cargarNuevoJuego();
int determinarIDNuevoJuego (FILE* archi);

// Consulta / lectura
void leerJuegosDeTienda(char nombreArchivo[]);
void leerJuegosArchivo(FILE *archi);
void leerUnJuego(Juego unJuego);

// Baja / eliminar
void eliminarJuegoDeTienda (char nombreArchivo[]);
void marcarJuegoActualComoEliminado (FILE *archi);

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


#endif // JUEGO_H_INCLUDED
