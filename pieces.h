#ifndef PIECES_H
#define PIECES_H

#include <cstdint>

// ============================================================
//  CONSTANTES PÚBLICAS
//  Otros módulos pueden usar estas constantes directamente.
// ============================================================

#define PIECE_BOX_SIZE   4      // Cada pieza vive en una caja 4x4
#define NUM_PIECE_TYPES  7      // I, O, T, S, Z, J, L

// Identificadores de cada tipo de pieza (índices en la tabla)
#define PIECE_I  0
#define PIECE_O  1
#define PIECE_T  2
#define PIECE_S  3
#define PIECE_Z  4
#define PIECE_J  5
#define PIECE_L  6

// ============================================================
//  TIPO DE DATO PRINCIPAL
//  Una pieza en juego: tipo, rotación actual y posición
//  en el tablero. Otros módulos trabajan con este struct.
// ============================================================

typedef struct {
    int type;       // PIECE_I .. PIECE_L
    int rotation;   // 0 .. (maxRotations-1)
    int row;        // fila superior de la caja 4x4 en el tablero
    int col;        // columna izquierda de la caja 4x4 en el tablero
} Piece;

// ============================================================
//  API PÚBLICA — funciones que otros módulos pueden llamar
// ============================================================

// Devuelve 1 si el bit (r, c) de la pieza está ocupado, 0 si no.
// r: 0-3 (fila dentro de la caja 4x4)
// c: 0-3 (columna dentro de la caja 4x4)
int pieceGetBit(int type, int rotation, int r, int c);

// Rota la pieza al siguiente estado de rotación (modifica piece->rotation).
void pieceRotate(Piece* piece);

// Genera una pieza nueva aleatoria centrada en boardWidth.
// Escribe el resultado en *out. No reserva memoria dinámica.
void pieceSpawn(Piece* out, int boardWidth);

// Devuelve cuántas rotaciones distintas tiene un tipo de pieza.
int pieceRotationCount(int type);

// Debug: imprime la pieza en consola con '#' y '.'.
// Solo usar durante desarrollo; el módulo de UI lo reemplazará.
void piecePrint(int type, int rotation);

#endif // PIECES_H
