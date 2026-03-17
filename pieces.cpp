#include "pieces.h"
#include <cstdio>   // printf (solo para piecePrint)
#include <cstdlib>  // rand

// ============================================================
//  TABLA DE PIEZAS — privada, no visible fuera de este módulo
//
//  Cada pieza se codifica en uint16_t:
//  bit 15 = fila 0 col 0  ...  bit 12 = fila 0 col 3
//  bit 11 = fila 1 col 0  ...  bit  8 = fila 1 col 3
//  bit  7 = fila 2 col 0  ...  bit  4 = fila 2 col 3
//  bit  3 = fila 3 col 0  ...  bit  0 = fila 3 col 3
// ============================================================

// Número de rotaciones distintas por tipo
static const int ROTATION_COUNT[NUM_PIECE_TYPES] = {
    2,  // I
    1,  // O
    4,  // T
    2,  // S
    2,  // Z
    4,  // J
    4   // L
};

// Tabla: pieces[tipo][rotacion] = mascara 4x4 en uint16_t
//
// Verificación visual de cada valor:
//   0x0F00 → 0000 1111 0000 0000 → fila1 llena (pieza I horizontal)
//   0x4444 → 0100 0100 0100 0100 → col1 llena  (pieza I vertical)
//   etc.
static const uint16_t PIECES[NUM_PIECE_TYPES][4] = {
    // PIECE_I
    // Rot0: . . . .    Rot1: . # . .
    //       # # # #          . # . .
    //       . . . .          . # . .
    //       . . . .          . # . .
    { 0x0F00, 0x4444, 0x0F00, 0x4444 },

    // PIECE_O
    // Rot0: . # # .
    //       . # # .
    //       . . . .
    //       . . . .
    { 0x6600, 0x6600, 0x6600, 0x6600 },

    // PIECE_T
    // Rot0: . # . .    Rot1: . # . .    Rot2: . . . .    Rot3: . # . .
    //       # # # .          . # # .          # # # .          # # . .
    //       . . . .          . # . .          . # . .          . # . .
    { 0x4E00, 0x4640, 0x0E40, 0x4C40 },

    // PIECE_S
    // Rot0: . # # .    Rot1: # . . .
    //       # # . .          # # . .
    //       . . . .          . # . .
    { 0x6C00, 0x8C40, 0x6C00, 0x8C40 },

    // PIECE_Z
    // Rot0: # # . .    Rot1: . # . .
    //       . # # .          # # . .
    //       . . . .          # . . .
    { 0xC600, 0x4C80, 0xC600, 0x4C80 },

    // PIECE_J
    // Rot0: # . . .    Rot1: # # . .    Rot2: . . . .    Rot3: . # . .
    //       # # # .          # . . .          # # # .          . # . .
    //       . . . .          # . . .          . . # .          # # . .
    { 0x8E00, 0xC880, 0x0E20, 0x44C0 },

    // PIECE_L
    // Rot0: . . # .    Rot1: # . . .    Rot2: . . . .    Rot3: # # . .
    //       # # # .          # # # .          # # # .          . # . .
    //       . . . .          . . . .          # . . .          . # . .
    { 0x2E00, 0x8C40, 0x0E80, 0xC440 }
};

// ============================================================
//  IMPLEMENTACIÓN DE LA API PÚBLICA
// ============================================================

int pieceGetBit(int type, int rotation, int r, int c) {
    // Calcula qué bit del uint16_t corresponde a (r, c)
    // fila 0 → bits 15-12, fila 1 → bits 11-8, etc.
    int bitIndex = 15 - (r * PIECE_BOX_SIZE + c);
    return (PIECES[type][rotation] >> bitIndex) & 1;
}

void pieceRotate(Piece* piece) {
    piece->rotation = (piece->rotation + 1) % ROTATION_COUNT[piece->type];
}

void pieceSpawn(Piece* out, int boardWidth) {
    out->type     = rand() % NUM_PIECE_TYPES;
    out->rotation = 0;
    out->row      = 0;
    // Centrar la caja 4x4 horizontalmente
    out->col      = (boardWidth / 2) - (PIECE_BOX_SIZE / 2);
}

int pieceRotationCount(int type) {
    return ROTATION_COUNT[type];
}

void piecePrint(int type, int rotation) {
    printf("Piece %d  Rot %d:\n", type, rotation);
    for (int r = 0; r < PIECE_BOX_SIZE; r++) {
        for (int c = 0; c < PIECE_BOX_SIZE; c++) {
            printf("%c ", pieceGetBit(type, rotation, r, c) ? '#' : '.');
        }
        printf("\n");
    }
    printf("\n");
}
