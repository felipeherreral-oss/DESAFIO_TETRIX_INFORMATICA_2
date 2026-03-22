#include <cstdlib>
#include <ctime>
#include "juego.h"
#include "render.h"
#include "entrada.h"

int main() {
    srand((unsigned int)time(0));

    // ── Configuración inicial ──────────────────────────────
    int ancho = pedirAncho();
    int alto  = pedirAlto();

    // ── Inicialización ─────────────────────────────────────
    EstadoJuego estado;
    inicializarJuego(&estado, ancho, alto);

    // ── Game loop ──────────────────────────────────────────
    while (estado.enJuego) {

        // 1. Dibujar estado actual ANTES de pedir acción
        limpiarPantalla();
        dibujarTablero(&estado);
        dibujarInfo(&estado);

        // 2. Leer acción del usuario
        char accion = leerAccion();

        // 3. Procesar turno y capturar si el juego continúa
        //    procesarTurno devuelve 1 si sigue, 0 si game over
        //    También actualiza estado.enJuego internamente,
        //    pero lo usamos directo para salir sin esperar
        //    una vuelta más del while.
        int continua = procesarTurno(&estado, accion);

        if (!continua) {
            estado.enJuego = 0;  // forzar salida limpia del while
        }
    }

    // ── Pantalla final ─────────────────────────────────────
    limpiarPantalla();
    dibujarTablero(&estado);   // mostrar tablero final
    dibujarGameOver(&estado);  // mensaje de game over + puntuación

    // ── Liberar memoria ────────────────────────────────────
    liberarJuego(&estado);

    return 0;
}
