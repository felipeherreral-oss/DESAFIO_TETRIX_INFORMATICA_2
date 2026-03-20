#include "tablero.h"
#include <cstdlib>
#include <cstdio>

// ============================================================
//  MANEJO DE BITS POR CELDA
//
//  Cada fila es un arreglo de bytesPerFila bytes (uint8_t).
//  La columna col corresponde a:
//    byte  = col / 8         → qué byte de la fila
//    bit   = 7 - (col % 8)  → qué bit dentro del byte (MSB primero)
// ============================================================

void inicializarTablero(Tablero* tablero, int ancho, int alto) {
    tablero->ancho        = ancho;
    tablero->alto         = alto;
    tablero->bytesPerFila = ancho / 8;

    // Reservar arreglo de punteros a filas
    tablero->filas = (uint8_t**)malloc(alto * sizeof(uint8_t*));

    for (int f = 0; f < alto; f++) {
        // Reservar cada fila e inicializar en 0
        tablero->filas[f] = (uint8_t*)malloc(tablero->bytesPerFila * sizeof(uint8_t));
        for (int b = 0; b < tablero->bytesPerFila; b++) {
            tablero->filas[f][b] = 0x00;
        }
    }
}

void liberarTablero(Tablero* tablero) {
    for (int f = 0; f < tablero->alto; f++) {
        free(tablero->filas[f]);
        tablero->filas[f] = 0;   // buena practica: nullificar puntero
    }
    free(tablero->filas);
    tablero->filas = 0;
}

int obtenerCelda(const Tablero* tablero, int fila, int col) {
    int byte = col / 8;
    int bit  = 7 - (col % 8);
    return (tablero->filas[fila][byte] >> bit) & 1;
}

void ocuparCelda(Tablero* tablero, int fila, int col) {
    int byte = col / 8;
    int bit  = 7 - (col % 8);
    tablero->filas[fila][byte] |= (uint8_t)(1 << bit);
}

void fijarPieza(Tablero* tablero, const Pieza* pieza) {
    for (int f = 0; f < TAMANO_CAJA; f++) {
        for (int c = 0; c < TAMANO_CAJA; c++) {
            if (obtenerBit(pieza->forma, f, c)) {
                int filaTablero = pieza->fila    + f;
                int colTablero  = pieza->columna + c;
                // Solo fijar si esta dentro del tablero
                if (filaTablero >= 0 && filaTablero < tablero->alto &&
                    colTablero  >= 0 && colTablero  < tablero->ancho) {
                    ocuparCelda(tablero, filaTablero, colTablero);
                }
            }
        }
    }
}

int movimientoValido(const Tablero* tablero, const Pieza* pieza,
                     int deltaFila, int deltaColumna, uint16_t forma) {
    for (int f = 0; f < TAMANO_CAJA; f++) {
        for (int c = 0; c < TAMANO_CAJA; c++) {
            if (obtenerBit(forma, f, c)) {
                int nuevaFila = pieza->fila    + f + deltaFila;
                int nuevaCol  = pieza->columna + c + deltaColumna;

                // Verificar fronteras
                if (nuevaFila < 0 || nuevaFila >= tablero->alto)  return 0;
                if (nuevaCol  < 0 || nuevaCol  >= tablero->ancho) return 0;

                // Verificar colision con celdas ocupadas
                if (obtenerCelda(tablero, nuevaFila, nuevaCol))   return 0;
            }
        }
    }
    return 1;
}

int limpiarFilas(Tablero* tablero) {
    int filasEliminadas = 0;
    int bytesPerFila    = tablero->bytesPerFila;

    for (int f = tablero->alto - 1; f >= 0; f--) {
        // Una fila esta completa si todos sus bytes son 0xFF
        int completa = 1;
        for (int b = 0; b < bytesPerFila; b++) {
            if (tablero->filas[f][b] != 0xFF) {
                completa = 0;
                break;
            }
        }

        if (completa) {
            filasEliminadas++;

            // Liberar la fila completa
            free(tablero->filas[f]);

            // Bajar todas las filas superiores un lugar
            // usando manipulacion de punteros (solo reasignar punteros)
            for (int k = f; k > 0; k--) {
                tablero->filas[k] = tablero->filas[k - 1];
            }

            // Crear nueva fila vacia en la cima
            tablero->filas[0] = (uint8_t*)malloc(bytesPerFila * sizeof(uint8_t));
            for (int b = 0; b < bytesPerFila; b++) {
                tablero->filas[0][b] = 0x00;
            }

            // Revisar la misma fila f de nuevo (ahora tiene el contenido de f-1)
            f++;
        }
    }
    return filasEliminadas;
}

int verificarGameOver(const Tablero* tablero, const Pieza* pieza) {
    // Game over si la pieza recien generada colisiona en su posicion inicial
    return !movimientoValido(tablero, pieza, 0, 0, pieza->forma);
}
