#ifndef RENDER_H
#define RENDER_H

#include "juego.h"

// Limpia la pantalla de la consola
void  limpiarPantalla();

// Dibuja el tablero completo con la pieza activa superpuesta
void  dibujarTablero(const EstadoJuego* estado);

// Muestra puntuacion, filas eliminadas y pieza siguiente
void  dibujarInfo(const EstadoJuego* estado);

// Muestra el mensaje de game over
void  dibujarGameOver(const EstadoJuego* estado);

#endif // RENDER_H
