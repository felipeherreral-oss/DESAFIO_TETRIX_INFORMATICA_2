#ifndef PIEZAS_H
#define PIEZAS_H

#include <cstdint>

// ============================================================
//  CONSTANTES
// ============================================================
#define TAMANO_CAJA      4
#define NUM_TIPOS_PIEZA  7

#define PIEZA_I  0
#define PIEZA_O  1
#define PIEZA_T  2
#define PIEZA_S  3
#define PIEZA_Z  4
#define PIEZA_J  5
#define PIEZA_L  6

// ============================================================
//  MASCARAS DE ROTACION (publicas para el modulo atomico)
//  ROT_ORIGEN[i] = bitpos del bit i en la figura original
//  ROT_DESTINO[i] = bitpos donde ese bit va en la figura rotada
// ============================================================
extern const uint8_t ROT_ORIGEN[16];
extern const uint8_t ROT_DESTINO[16];

// ============================================================
//  ESTRUCTURA PRINCIPAL
// ============================================================
typedef struct {
    int      tipo;      // PIEZA_I .. PIEZA_L
    int      rotacion;  // 0..3, cuenta de rotaciones aplicadas
    int      fila;      // fila en el tablero
    int      columna;   // columna en el tablero
    uint16_t forma;     // estado actual de bits 4x4
} Pieza;

// ============================================================
//  API PUBLICA
// ============================================================

// Devuelve la forma base (rot 0) de un tipo de pieza
uint16_t    obtenerBase(int tipo);

// Calcula la rotacion 90 horaria de cualquier forma 4x4
// El compañero reemplaza esta logica con su version atomica
uint16_t    calcularRotacion(uint16_t forma);

// Rota la pieza: recalcula pieza->forma y actualiza pieza->rotacion
void        rotarPieza(Pieza* pieza);

// Extrae el bit en (fila, col) de una forma dada
int         obtenerBit(uint16_t forma, int fila, int col);

// Genera una pieza nueva aleatoria centrada en anchoBtablero
void        generarPieza(Pieza* salida, int anchoTablero);

// Cuantas rotaciones distintas tiene un tipo
int         contarRotaciones(int tipo);

// Debug: imprime la forma en consola
void        imprimirForma(uint16_t forma);

#endif // PIEZAS_H
