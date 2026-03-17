#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "pieces.h"

// Limpia la pantalla de forma compatible con Qt consola
void clearScreen() {
    // Secuencia ANSI — funciona en la terminal de Qt Creator y Linux/Mac
    printf("\033[2J\033[H");
}

void printControls() {
    printf("Controles:\n");
    printf("  [w] Rotar\n");
    printf("  [n] Nueva pieza aleatoria\n");
    printf("  [q] Salir\n");
    printf("Accion: ");
}

int main() {
    srand((unsigned int)time(0));

    Piece p;
    pieceSpawn(&p, 16);

    const char* names[NUM_PIECE_TYPES] = {"I", "O", "T", "S", "Z", "J", "L"};

    char input[8];   // buffer para la entrada, sin string
    int running = 1;

    while (running) {
        clearScreen();

        printf("========= PRUEBA DE PIEZAS =========\n\n");
        printf("Pieza: %s  |  Rotacion: %d/%d\n\n",
               names[p.type],
               p.rotation,
               pieceRotationCount(p.type) - 1);

        piecePrint(p.type, p.rotation);

        printControls();

        // Leer entrada
        if (scanf("%7s", input) != 1) continue;

        if (input[0] == 'w' || input[0] == 'W') {
            pieceRotate(&p);

        } else if (input[0] == 'n' || input[0] == 'N') {
            pieceSpawn(&p, 16);

        } else if (input[0] == 'q' || input[0] == 'Q') {
            running = 0;
        }
    }

    clearScreen();
    printf("Saliendo...\n");
    return 0;
}

/*

    ---

    ### Cómo se ve en pantalla cada turno

    ========= PRUEBA DE PIEZAS =========

    Pieza: T  |  Rotacion: 0/3

                               Piece 2  Rot 0:
                                                   . # . .
# # # .
                                                   . . . .
                                                   . . . .

                                               Controles:
                                                           [w] Rotar
                                                               [n] Nueva pieza aleatoria
                                                                   [q] Salir
                                                                       Accion: _
*/
