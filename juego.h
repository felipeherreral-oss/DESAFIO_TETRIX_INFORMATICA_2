#ifndef JUEGO_H
#define JUEGO_H

#include "piezas.h"
#include "tablero.h"

// ============================================================
//  Estado global del juego
// ============================================================
typedef struct {
    Tablero tablero;        // el tablero actual
    Pieza   piezaActual;    // pieza cayendo ahora
    Pieza   piezaSiguiente; // preview de la siguiente pieza
    int     puntuacion;     // puntaje acumulado
    int     filasEliminadas;// total de filas borradas
    int     enJuego;        // 1 = jugando, 0 = game over
} EstadoJuego;

// Inicializa todo el estado del juego
void  inicializarJuego(EstadoJuego* estado, int anchoTablero, int altoTablero);

// Libera toda la memoria del estado
void  liberarJuego(EstadoJuego* estado);

// Procesa un turno completo: aplica accion, baja pieza, fija si toca fondo
// Devuelve 1 si el juego continua, 0 si es game over
int   procesarTurno(EstadoJuego* estado, char accion);

// Actualiza la puntuacion segun filas eliminadas
void  actualizarPuntuacion(EstadoJuego* estado, int filasEliminadas);

#endif // JUEGO_H
