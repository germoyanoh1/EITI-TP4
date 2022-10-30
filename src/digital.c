/* Copyright 2022, Laboratorio de Microprocesadores 
 * Facultad de Ciencias Exactas y Tecnología 
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, German Moyano <germoyanoh1@gmail.com>
 */

/** \brief Definicion de Entradas y salidas digitales
 ** 
 ** \addtogroup hal HAL
 ** \brief Capa de abstraccion de Hardware
 ** @{ */

/* === Inclusiones de cabeceras ============================================ */

#include "digital.h"
#include "chip.h"

/* === Definicion y Macros privados ======================================== */

#ifndef SALIDAS_INSTANCIAS
    #define SALIDAS_INSTANCIAS     4
#endif

#ifndef ENTRADAS_INSTANCIAS
    #define ENTRADAS_INSTANCIAS     6
#endif

/* === Declaraciones de tipos de datos privados ============================ */

struct salida_digital_s {
    uint8_t gpio;
    uint8_t bit;
    bool ocupada;
};

struct entrada_digital_s {
    uint8_t gpio;
    uint8_t bit;
    bool ocupada;
    bool ultimoestado;
};

/* === Definiciones de variables privadas ================================== */

static struct salida_digital_s instancia[SALIDAS_INSTANCIAS] = {0};

static struct entrada_digital_s instanciaent[ENTRADAS_INSTANCIAS] = {0};

/* === Definiciones de variables publicas ================================== */

/* === Declaraciones de funciones privadas ================================= */

/* === Definiciones de funciones privadas ================================== */

salida_digital_p salidadigitalocupada (void) {
    salida_digital_p salida = NULL;
    for (int index = 0 ; index < SALIDAS_INSTANCIAS ; index++) {
        if (instancia[index].ocupada == false) {
            instancia[index].ocupada = true;
            salida = &instancia[index];
            break;
        }
    }
    return salida;
}

entrada_digital_p entradadigitalocupada (void) {
    entrada_digital_p entrada = NULL;
    for (int index = 0 ; index < ENTRADAS_INSTANCIAS ; index++) {
        if (instanciaent[index].ocupada == false) {
            instanciaent[index].ocupada = true;
            entrada = &instanciaent[index];
            break;
        }
    }
    return entrada;
}
/* === Definiciones de funciones publicas ================================== */

salida_digital_p crearsalidadigital(uint8_t gpio, uint8_t bit){
    salida_digital_p salida = salidadigitalocupada ();
    if (salida){
        salida->gpio = gpio;
        salida->bit = bit;
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, salida->gpio, salida->bit, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, salida->gpio, salida->bit, true);
    }
    return salida;
}

void activarsalidadigital(salida_digital_p salida){
    if(salida){
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, salida->gpio, salida->bit, true);
    }
}

void desactivarsalidadigital(salida_digital_p salida){
    if(salida){
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, salida->gpio, salida->bit, false);
    }
}

void cambiarsalidadigital(salida_digital_p salida){
    if(salida){
        Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, salida->gpio, salida->bit);
    }
}

entrada_digital_p crearentradadigital(uint8_t gpio, uint8_t bit){
    entrada_digital_p entrada = entradadigitalocupada ();
    if (entrada){
        entrada->gpio = gpio;
        entrada->bit = bit;
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, entrada->gpio, entrada->bit, false);
    }
    return entrada;
}

bool estadoentradadigital (entrada_digital_p entrada){
    bool estado = false;
    if(entrada){
        if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, entrada->gpio, entrada->bit) == 0){
            estado = true;
        }
    }
    return estado;
}

bool entradadigitalcambio (entrada_digital_p entrada) {
    bool estado = estadoentradadigital(entrada);
    bool resultado = estado && !entrada->ultimoestado;
    entrada->ultimoestado = estado;
    return resultado;
}

bool entradadigitalactiva (entrada_digital_p entrada) {
    bool estado = estadoentradadigital(entrada);
    bool resultado = estado && !entrada->ultimoestado;
    entrada->ultimoestado = estado;
    return resultado;
}

bool entradadigitalinactiva (entrada_digital_p entrada) {
    bool estado = estadoentradadigital (entrada);
    bool resultado = !estado && !entrada->ultimoestado;
    entrada->ultimoestado = estado;
    return resultado;
}
/* === Ciere de documentacion ============================================== */

/** @} Final de la definición del modulo para doxygen */