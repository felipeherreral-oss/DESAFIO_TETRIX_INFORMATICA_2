#include "piezas.h"
#include <cstdio>
#include <cstdlib>

static const uint16_t BASE_PIEZAS[NUM_TIPOS_PIEZA] = {
    0x0F00,  // I
    0x6600,  // O
    0x4E00,  // T
    0x6C00,  // S
    0xC600,  // Z
    0x8E00,  // J
    0x2E00   // L
};

static const int NUM_ROTACIONES[NUM_TIPOS_PIEZA] = {2, 1, 4, 2, 2, 4, 4};

const uint8_t ROT_ORIGEN[16] = {
    15, 14, 13, 12,
    11, 10,  9,  8,
    7,  6,  5,  4,
    3,  2,  1,  0
};

const uint8_t ROT_DESTINO[16] = {
    12,  8,  4,  0,
    13,  9,  5,  1,
    14, 10,  6,  2,
    15, 11,  7,  3
};

uint16_t obtenerBase(int tipo) {
    return BASE_PIEZAS[tipo];
}

uint16_t calcularRotacion(uint16_t forma) {
    uint16_t rotada = 0;
    for (int i = 0; i < 16; i++) {
        int bit = (forma >> ROT_ORIGEN[i]) & 1;
        rotada |= (uint16_t)(bit << ROT_DESTINO[i]);
    }
    return rotada;
}

void rotarPieza(Pieza* pieza) {
    if (NUM_ROTACIONES[pieza->tipo] == 1) return;
    pieza->forma    = calcularRotacion(pieza->forma);
    pieza->rotacion = (pieza->rotacion + 1) % NUM_ROTACIONES[pieza->tipo];
}

int obtenerBit(uint16_t forma, int fila, int col) {
    int indiceBit = 15 - (fila * TAMANO_CAJA + col);
    return (forma >> indiceBit) & 1;
}

void generarPieza(Pieza* salida, int anchoTablero) {
    salida->tipo     = rand() % NUM_TIPOS_PIEZA;
    salida->rotacion = 0;
    salida->fila     = 0;
    salida->columna  = (anchoTablero / 2) - (TAMANO_CAJA / 2);
    salida->forma    = BASE_PIEZAS[salida->tipo];
}

int contarRotaciones(int tipo) {
    return NUM_ROTACIONES[tipo];
}

void imprimirForma(uint16_t forma) {
    for (int f = 0; f < TAMANO_CAJA; f++) {
        for (int c = 0; c < TAMANO_CAJA; c++) {
            printf("%c ", obtenerBit(forma, f, c) ? '#' : '.');
        }
        printf("\n");
    }
    printf("\n");
}
