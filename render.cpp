#include "render.h"
#include <cstdio>

void limpiarPantalla() {
    printf("\033[2J\033[H");
}

// ============================================================
//  Verifica si la celda del tablero esta ocupada por la pieza
//  activa (para dibujarla superpuesta sin fijarla aun)
// ============================================================
static int celdaOcupadaPorPieza(const Pieza* pieza, int fila, int col) {
    int filaLocal = fila - pieza->fila;
    int colLocal  = col  - pieza->columna;

    if (filaLocal < 0 || filaLocal >= TAMANO_CAJA) return 0;
    if (colLocal  < 0 || colLocal  >= TAMANO_CAJA) return 0;

    return obtenerBit(pieza->forma, filaLocal, colLocal);
}

void dibujarTablero(const EstadoJuego* estado) {
    const Tablero* t = &estado->tablero;
    const Pieza*   p = &estado->piezaActual;

    // Borde superior
    printf("+");
    for (int c = 0; c < t->ancho; c++) printf("-");
    printf("+\n");

    for (int f = 0; f < t->alto; f++) {
        printf("|");
        for (int c = 0; c < t->ancho; c++) {
            if (celdaOcupadaPorPieza(p, f, c)) {
                printf("[]");   // pieza activa
            } else if (obtenerCelda(t, f, c)) {
                printf("##");   // celda fija
            } else {
                printf(". ");   // vacia
            }
        }
        printf("|\n");
    }

    // Borde inferior
    printf("+");
    for (int c = 0; c < t->ancho; c++) printf("-");
    printf("+\n");
}

void dibujarInfo(const EstadoJuego* estado) {
    printf("\n");
    printf("Puntuacion  : %d\n", estado->puntuacion);
    printf("Filas       : %d\n", estado->filasEliminadas);
    printf("\nSiguiente pieza:\n");
    imprimirForma(estado->piezaSiguiente.forma);
}

void dibujarGameOver(const EstadoJuego* estado) {
    printf("\n");
    printf("==========================\n");
    printf("       GAME  OVER         \n");
    printf("==========================\n");
    printf("Puntuacion final : %d\n",  estado->puntuacion);
    printf("Filas eliminadas : %d\n",  estado->filasEliminadas);
    printf("==========================\n");
}
