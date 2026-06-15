#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define LIMITE 50
#define JUEGOSTIENDA "tienda.bin"

typedef struct
{
    char nombreJuego[LIMITE];
    char categoriaJuego[LIMITE];
    float precioJuego;
}Juego;

// Alta / escritura
void  guardarJuegosEnArchivo(char nombreArchivo[], char modo[]);
void  cargarJuegoATienda(FILE *archi);
Juego cargarNuevoJuego();

// Consulta / lectura
void leerJuegosDeTienda(char nombreArchivo[]);
void leerJuegosArchivo(FILE *archi);
void leerUnJuego(Juego unJuego);

// Filtrado por categoría
void leerJuegosFiltradosTienda(char nombreArchivo[], char categoria[]);
int  compararJuegoCategoria(Juego juegoAFiltrar, char categoria[]);

// Ordenamiento por selección (nombre A-Z)
void leerJuegosOrdenadosNombreTienda(char nombreArchivo[]);
void ordSeleccionNombreJuego(Juego arr[], int validos);
int  posMenorNombreJuego(Juego arr[], int validos, int posInicial);
void mostrarArrJuegosOrdenado(Juego arr[], int validos);


#endif // JUEGO_H_INCLUDED
