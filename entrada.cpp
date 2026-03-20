#include "entrada.h"
#include <cstdio>

char leerAccion() {
    char accion;
    printf("Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ");
    scanf(" %c", &accion);

    // Normalizar a minuscula con bitwise (bit 5 = minuscula en ASCII)
    accion = accion | 0x20;

    // Validar que sea una accion conocida, si no, bajar por defecto
    if (accion != ACCION_IZQUIERDA &&
        accion != ACCION_DERECHA   &&
        accion != ACCION_BAJAR     &&
        accion != ACCION_ROTAR     &&
        accion != ACCION_SALIR) {
        accion = ACCION_BAJAR;
    }
    return accion;
}


int pedirAncho() {
    int ancho = 0;
    do {
        printf("Ingrese el ancho del tablero\n");
        printf("  (multiplo de 8, entre %d y %d): ", ANCHO_MINIMO, ANCHO_MAXIMO);
        scanf("%d", &ancho);
        // (ancho & 0x07) != 0 significa que NO es multiplo de 8
        if (ancho < ANCHO_MINIMO || ancho > ANCHO_MAXIMO || (ancho & 0x07) != 0) {
            printf("  Error: valor invalido.\n");
            ancho = 0;
        }
    } while (ancho == 0);
    return ancho;
}

int pedirAlto() {
    int alto = 0;
    do {
        printf("Ingrese el alto del tablero (minimo 8): \n");
        printf("  (entre %d y %d): ", ALTO_MINIMO, ALTO_MAXIMO);
        scanf("%d", &alto);

        if (alto < ALTO_MINIMO || alto > ALTO_MAXIMO) {
            printf("  Error: valor invalido.\n");
            alto = 0;
        }
    } while (alto == 0);
    return alto;
}


