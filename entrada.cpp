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
        accion = 0;
    }
    return accion;
}
// ============================================================
//  Lee un entero desde consola de forma segura.
//  Si el usuario ingresa letras o caracteres invalidos,
//  limpia el buffer y devuelve -1.
//  Solo usa getchar(), sin string ni librerias extra.
// ============================================================
static int leerEnteroSeguro() {
    char buffer[16];
    int  i      = 0;
    int  c      = 0;
    int  valido = 1;

    // Leer caracter a caracter hasta Enter o fin de buffer
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < 15) {
            buffer[i++] = (char)c;
        }
    }
    buffer[i] = '\0';

    // Verificar que haya al menos un caracter
    if (i == 0) return -1;

    // Verificar que TODOS sean digitos (0-9)
    for (int j = 0; j < i; j++) {
        // Un digito tiene codigo ASCII entre 48 ('0') y 57 ('9')
        if (buffer[j] < 48 || buffer[j] > 57) {
            valido = 0;
            break;
        }
    }

    if (!valido) return -1;

    // Convertir manualmente de chars a entero sin atoi
    int resultado = 0;
    for (int j = 0; j < i; j++) {
        resultado = resultado * 10 + (buffer[j] - 48);
    }
    return resultado;
}
int pedirAncho() {
    int ancho = -1;
    do {
        printf("Ingrese el ancho del tablero\n");
        printf("  (multiplo de 8, entre %d y %d): ", ANCHO_MINIMO, ANCHO_MAXIMO);
        ancho = leerEnteroSeguro();
        if (ancho < ANCHO_MINIMO || ancho > ANCHO_MAXIMO || (ancho & 0x07) != 0) {
            printf("  Error: solo numeros enteros, multiplo de 8.\n");
            ancho = -1;
        }
    } while (ancho == -1);
    return ancho;
}

int pedirAlto() {
    int alto = -1;
    do {
        printf("Ingrese el alto del tablero\n");
        printf("  (entre %d y %d): ", ALTO_MINIMO, ALTO_MAXIMO);
        alto = leerEnteroSeguro();
        if (alto < ALTO_MINIMO || alto > ALTO_MAXIMO) {
            printf("  Error: solo numeros enteros en el rango indicado.\n");
            alto = -1;
        }
    } while (alto == -1);
    return alto;
}
