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
    struct driver_pantalla_s driver;
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

/* === Definiciones de funciones publicas ================================== */

pantalla_p crearpantalla (uint8_t digitos, driver_pantalla_p driver){
    pantalla_p pantalla = instancias;

    pantalla->digitos = digitos;
    pantalla->digito_activo = digitos - 1;
    memset(pantalla->memoria, 0, sizeof(pantalla->memoria));

    pantalla->driver.apagarpantalla = driver->apagarpantalla;
    pantalla->driver.encendersegmento = driver->encendersegmento;
    pantalla->driver.encenderdigito = driver->encenderdigito;
    pantalla->driver.apagarpantalla();
    
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
    pantalla->driver.apagarpantalla();
    if (pantalla->digito_activo == pantalla->digitos - 1){
        pantalla->digito_activo = 0;
    } else {
        pantalla->digito_activo = pantalla->digito_activo + 1;
    }
    pantalla->driver.encendersegmento(pantalla->memoria[pantalla->digito_activo]);
    pantalla->driver.encenderdigito(pantalla->digito_activo);
    

};

/* === Ciere de documentacion ============================================== */

/** @} Final de la definición del modulo para doxygen */