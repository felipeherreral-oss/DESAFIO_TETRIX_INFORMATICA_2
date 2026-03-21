#include <cstdlib>
#include <ctime>
#include "juego.h"
#include "render.h"
#include "entrada.h"

int main() {
    srand((unsigned int)time(0));

    int ancho = pedirAncho();
    int alto  = pedirAlto();

    EstadoJuego estado;
    inicializarJuego(&estado, ancho, alto);

    while (estado.enJuego) {
        limpiarPantalla();
        dibujarTablero(&estado);
        dibujarInfo(&estado);

        char accion = leerAccion();
        procesarTurno(&estado, accion);
    }

    limpiarPantalla();
    dibujarGameOver(&estado);
    liberarJuego(&estado);

    return 0;
}
