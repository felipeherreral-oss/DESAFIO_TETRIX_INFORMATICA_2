#ifndef TABLERO_H
#define TABLERO_H

#include <cstdint>
#include "piezas.h"

// ============================================================
//  El tablero se representa como un arreglo dinamico de filas.
//  Cada fila es un uint8_t* de (anchoTablero/8) bytes.
//  Un bit en 1 = celda ocupada, 0 = celda libre.
// ============================================================
typedef struct {
    uint8_t** filas;        // arreglo dinamico de punteros a filas
    int       alto;         // numero de filas
    int       ancho;        // numero de columnas (multiplo de 8)
    int       bytesPerFila; // ancho / 8
} Tablero;

// Reserva memoria e inicializa el tablero en cero
void  inicializarTablero(Tablero* tablero, int ancho, int alto);

// Libera toda la memoria dinamica del tablero
void  liberarTablero(Tablero* tablero);

// Devuelve 1 si la celda (fila, col) esta ocupada, 0 si libre
int   obtenerCelda(const Tablero* tablero, int fila, int col);

// Marca la celda (fila, col) como ocupada
void  ocuparCelda(Tablero* tablero, int fila, int col);

// Fija la pieza actual en el tablero (escribe sus bits)
void  fijarPieza(Tablero* tablero, const Pieza* pieza);

// Devuelve 1 si el movimiento de la pieza es valido (sin colision)
int   movimientoValido(const Tablero* tablero, const Pieza* pieza,
                     int deltaFila, int deltaColumna, uint16_t forma);

// Elimina filas completas y baja las superiores.
// Devuelve el numero de filas eliminadas.
int   limpiarFilas(Tablero* tablero);

// Devuelve 1 si la pieza no cabe al generarse (game over)
int   verificarGameOver(const Tablero* tablero, const Pieza* pieza);

#endif // TABLERO_H
