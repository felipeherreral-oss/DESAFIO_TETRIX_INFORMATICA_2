#ifndef TABLERO_H
#define TABLERO_H

struct Tablero {
    unsigned char* datos;
    int filas;
    int columnas;
    int bytesPorFila;
};

// --- Funciones de Gestión ---
void inicializarTablero(Tablero &t, int ancho, int alto);
void liberarTablero(Tablero &t);

// --- Funciones Atómicas de Cálculo ---
// Solo calculan, no modifican nada.
int calcularPosicionByte(int x, int y, int bytesPorFila);
unsigned char calcularMascaraBit(int x);

// --- Funciones Atómicas de Modificación ---
// Solo modifican, no calculan posiciones.
void aplicarOR(unsigned char &byte, unsigned char mascara);
void aplicarANDNOT(unsigned char &byte, unsigned char mascara);
bool verificarBit(unsigned char byte, unsigned char mascara);

// --- Funciones de Alto Nivel (usan las atómicas) ---
void colocarBloque(Tablero &t, int x, int y);
void quitarBloque(Tablero &t, int x, int y);
bool hayBloque(Tablero t, int x, int y);
void imprimirTablero(Tablero t);

#endif
