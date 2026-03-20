#ifndef ENTRADA_H
#define ENTRADA_H

// ============================================================
//  LIMITES DEL TABLERO
//  Modifica estos valores para cambiar los rangos permitidos.
//  El ancho siempre debe ser multiplo de 8.
// ============================================================
#define ANCHO_MINIMO   8
#define ANCHO_MAXIMO   64    // <- cambia este valor libremente
#define ALTO_MINIMO    8
#define ALTO_MAXIMO    20    // <- cambia este valor libremente

// Acciones
#define ACCION_IZQUIERDA  'a'
#define ACCION_DERECHA    'd'
#define ACCION_BAJAR      's'
#define ACCION_ROTAR      'w'
#define ACCION_SALIR      'q'

char  leerAccion();
int   pedirAncho();
int   pedirAlto();

#endif // ENTRADA_H
