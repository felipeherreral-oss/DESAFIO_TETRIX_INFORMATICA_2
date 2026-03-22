#include "juego.h"
#include "entrada.h"
#include <cstdlib>

// ============================================================
//  PUNTUACION
//  Clasico sistema Tetris: mas filas a la vez = mas puntos
//  1 fila = 100  |  2 = 300  |  3 = 500  |  4 = 800
// ============================================================
static const int PUNTOS_POR_FILAS[5] = {0, 100, 300, 500, 800};

void inicializarJuego(EstadoJuego* estado, int anchoTablero, int altoTablero) {
    inicializarTablero(&estado->tablero, anchoTablero, altoTablero);

    generarPieza(&estado->piezaActual,    anchoTablero);
    generarPieza(&estado->piezaSiguiente, anchoTablero);

    estado->puntuacion      = 0;
    estado->filasEliminadas = 0;
    estado->enJuego         = 1;
}

void liberarJuego(EstadoJuego* estado) {
    liberarTablero(&estado->tablero);
}

void actualizarPuntuacion(EstadoJuego* estado, int filasEliminadas) {
    if (filasEliminadas > 4) filasEliminadas = 4;  // maximo 4 a la vez
    estado->puntuacion      += PUNTOS_POR_FILAS[filasEliminadas];
    estado->filasEliminadas += filasEliminadas;
}

int procesarTurno(EstadoJuego* estado, char accion) {
    Tablero* t = &estado->tablero;
    Pieza*   p = &estado->piezaActual;

    if (accion == ACCION_SALIR) {
        estado->enJuego = 0;
        return 0;
    }

    if (accion == ACCION_IZQUIERDA) {
        if (movimientoValido(t, p, 0, -1, p->forma)) {
            p->columna--;
        }
    }

    if (accion == ACCION_DERECHA) {
        if (movimientoValido(t, p, 0, 1, p->forma)) {
            p->columna++;
        }
    }

    if (accion == ACCION_ROTAR) {
        uint16_t formaRotada = calcularRotacion(p->forma);
        if (movimientoValido(t, p, 0, 0, formaRotada)) {
            // Solo rotar si la forma rotada no colisiona
            rotarPieza(p);
        }
    }

    // Gravedad: bajar siempre (sea por accion S o por turno)
    if (accion == ACCION_BAJAR) {
        if (movimientoValido(t, p, 1, 0, p->forma)) {
            p->fila++;
        } else {
            // No puede bajar: fijar pieza en el tablero
            fijarPieza(t, p);

            // Limpiar filas completas y sumar puntos
            int eliminadas = limpiarFilas(t);
            actualizarPuntuacion(estado, eliminadas);

            // La siguiente pieza pasa a ser la actual
            estado->piezaActual    = estado->piezaSiguiente;
            generarPieza(&estado->piezaSiguiente, t->ancho);

            // Verificar game over con la nueva pieza
            if (verificarGameOver(t, &estado->piezaActual)) {
                estado->enJuego = 0;
                return 0;
            }
        }
    }

    return 1;
}

/*
```

    ---

    ## Mapa de dependencias final
```
    main.cpp
  ├── juego.h/cpp
  │     ├── tablero.h/cpp
  │     │     └── piezas.h/cpp
  │     └── piezas.h/cpp
  ├── render.h/cpp
  │     └── juego.h  (EstadoJuego)
  └── entrada.h/cpp  (sin dependencias propias)
*/
