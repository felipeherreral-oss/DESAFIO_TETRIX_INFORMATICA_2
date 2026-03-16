#include <iostream>
#include "tablero.h"

int main() {
    Tablero miJuego;

    // Prueba con un ancho de 10 (esto forzará al sistema a usar 2 bytes por fila)
    int ancho = 10;
    int alto = 15;

    std::cout << "Iniciando tablero de " << ancho << "x" << alto << "..." << std::endl;

    // 1. Inicializar
    inicializarTablero(miJuego, ancho, alto);

    // 2. Pruebas de encendido atómico
    // Dibujemos un marco simple
    for(int y = 0; y < alto; ++y) {
        colocarBloque(miJuego, 0, y);          // Columna inicial (Bit 7 del byte 0)
        colocarBloque(miJuego, ancho - 1, y);  // Columna final (Bit del byte 1)
    }

    // Dibujemos una pieza de prueba (un cuadrado de 2x2 en el centro)
    colocarBloque(miJuego, 4, 5);
    colocarBloque(miJuego, 5, 5);
    colocarBloque(miJuego, 4, 6);
    colocarBloque(miJuego, 5, 6);

    // 3. Visualizar
    imprimirTablero(miJuego);

    // 4. Prueba de apagado (quitar un bloque del cuadrado)
    std::cout << "\nQuitando el bloque (5,6)...\n" << std::endl;
    quitarBloque(miJuego, 5, 6);

    imprimirTablero(miJuego);

    // 5. IMPORTANTE: Liberar memoria
    liberarTablero(miJuego);
    std::cout << "Memoria liberada correctamente." << std::endl;

    return 0;
}
