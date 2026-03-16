#include "tablero.h"

// --- ÁTOMO 1: Calcular dónde está el byte ---
int calcularPosicionByte(int x, int y, int bytesPorFila) {
    return (y * bytesPorFila) + (x / 8);
}

// --- ÁTOMO 2: Calcular la máscara (el bit exacto) ---
unsigned char calcularMascaraBit(int x) {
    return (1 << (7 - (x % 8)));
}

// --- ÁTOMO 3: Operaciones lógicas puras ---
void aplicarOR(unsigned char &byte, unsigned char mascara) {
    byte |= mascara;
}

void aplicarANDNOT(unsigned char &byte, unsigned char mascara) {
    byte &= ~mascara;
}

bool verificarBit(unsigned char byte, unsigned char mascara) {
    return (byte & mascara) != 0;
}

// --- IMPLEMENTACIÓN USANDO ÁTOMOS ---

void inicializarTablero(Tablero &t, int ancho, int alto) {
    t.filas = alto;
    t.columnas = ancho;
    t.bytesPorFila = (ancho + 7) / 8;
    t.datos = new unsigned char[t.filas * t.bytesPorFila]{0}; // Inicializa en 0
}

void colocarBloque(Tablero &t, int x, int y) {
    if (x < 0 || x >= t.columnas || y < 0 || y >= t.filas) return;

    int pos = calcularPosicionByte(x, y, t.bytesPorFila);
    unsigned char mask = calcularMascaraBit(x);
    aplicarOR(t.datos[pos], mask); // Uso de átomo
}

void quitarBloque(Tablero &t, int x, int y) {
    if (x < 0 || x >= t.columnas || y < 0 || y >= t.filas) return;

    int pos = calcularPosicionByte(x, y, t.bytesPorFila);
    unsigned char mask = calcularMascaraBit(x);
    aplicarANDNOT(t.datos[pos], mask); // Uso de átomo
}

bool hayBloque(Tablero t, int x, int y) {
    if (x < 0 || x >= t.columnas || y < 0 || y >= t.filas) return false;

    int pos = calcularPosicionByte(x, y, t.bytesPorFila);
    unsigned char mask = calcularMascaraBit(x);
    return verificarBit(t.datos[pos], mask); // Uso de átomo
}

void liberarTablero(Tablero &t) {
    delete[] t.datos;
    t.datos = nullptr;
}


#include <iostream>

void imprimirTablero(Tablero t) {
    // Recorremos fila por fila
    for (int y = 0; y < t.filas; ++y) {
        // Imprimimos el borde izquierdo para que se vea ordenado
        std::cout << "|";

        for (int x = 0; x < t.columnas; ++x) {
            // Usamos nuestro átomo de consulta
            if (hayBloque(t, x, y)) {
                std::cout << " # "; // Representa un bloque de Tetris
            } else {
                std::cout << " . "; // Representa espacio vacío
            }
        }

        std::cout << "|" << std::endl; // Borde derecho
    }

    // Base del tablero
    for (int x = 0; x < t.columnas + 2; ++x) std::cout << "---";
    std::cout << std::endl;
}
