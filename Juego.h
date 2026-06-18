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
Juego buscarJuegoPorId (int idBuscada); //verificar que el Juego que devuelve no tenga id -1 (significa error/que no se encontró)

// Baja / eliminar
void eliminarJuegoDeTienda (char nombreArchivo[]);
void marcarJuegoActualComoEliminado (FILE *archi);

// Modificar
void modificarJuego (char nombreArchivo[]); //puede modificarse todo menos la id (y tampoco puede eliminarse el juego porque hay una función aparte para eso)
int menuSelectorModificarJuego (Juego *aux);

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
