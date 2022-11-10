/* Copyright 2022, Laboratorio de Microprocesadores 
 * Facultad de Ciencias Exactas y Tecnología 
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, German Moyano <germoyanoh1@gmail.com>
 */

/** \brief Definiciones necesarias para manejar la pantalla en TP4
 ** 
 ** \addtogroup hal HAL
 ** \brief Capa de abstraccion de Hardware
 ** @{ */

/* === Inclusiones de cabeceras ============================================ */

#include <pantalla.h>
#include "chip.h"
#include "poncho.h"
#include <string.h>
/* === Definicion y Macros privados ======================================== */

#ifndef MAX_DIGITOS_PANTALLA
    #define MAX_DIGITOS_PANTALLA 8
#endif

/* === Declaraciones de tipos de datos privados ============================ */

struct pantalla_s
{
    uint8_t digitos;
    uint8_t digito_activo;
    uint8_t memoria[MAX_DIGITOS_PANTALLA];
};


/* === Definiciones de variables privadas ================================== */

static struct pantalla_s instancias[1];

/* === Definiciones de variables publicas ================================== */

/* === Declaraciones de funciones privadas ================================= */

static const uint8_t IMAGEN[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,                  //=0
    SEGMENT_B | SEGMENT_C,                                                                  //=1
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,                              //=2
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,                              //=3
    SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,                                          //=4
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,                              //=5
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,                  //=6
    SEGMENT_A | SEGMENT_B | SEGMENT_C,                                                      //=7
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,      //=8
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,                              //=9

};

/* === Definiciones de funciones privadas ================================== */

void escribirnumero(uint8_t segmento) {
    Chip_GPIO_SetValue(LPC_GPIO_PORT, SEGMENTS_GPIO, segmento);
}

void seleccionardigito(uint8_t digito) {
    Chip_GPIO_SetValue(LPC_GPIO_PORT, DIGITS_GPIO, (1 << digito));
}

void limpiarpantalla() {
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DIGITS_GPIO, DIGITS_MASK);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEGMENTS_GPIO, SEGMENTS_MASK);
}

/* === Definiciones de funciones publicas ================================== */

pantalla_p crearpantalla (uint8_t digitos){
    pantalla_p pantalla = instancias;

    pantalla->digitos = digitos;
    pantalla->digito_activo = digitos - 1;

    memset(pantalla->memoria, 0, sizeof(pantalla->memoria));

    limpiarpantalla();
    return pantalla;
}

void escribirpantallabcd(pantalla_p pantalla, uint8_t * numero, uint8_t tamano){
    memset(pantalla->memoria, 0, sizeof(pantalla->memoria));
    for (int index = 0; index < tamano; index++) {
        if (index >= pantalla->digitos-1) break;
        pantalla->memoria[index] = IMAGEN[numero[index]];
    }
};

void refrescarpantalla(pantalla_p pantalla){
    limpiarpantalla();
    if (pantalla->digito_activo == pantalla->digitos - 1){
        pantalla->digito_activo = 0;
    } else {
        pantalla->digito_activo = pantalla->digito_activo + 1;
    }
    escribirnumero(pantalla->memoria[pantalla->digito_activo]);
    seleccionardigito(pantalla->digito_activo);
 

};

/* === Ciere de documentacion ============================================== */

/** @} Final de la definición del modulo para doxygen */