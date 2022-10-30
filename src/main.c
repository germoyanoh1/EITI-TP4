/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "bsp.h"
#include <stdbool.h>

#include "chip.h"
#include "poncho.h"

/* === Macros definitions ====================================================================== */

//Definimos los bits asociados a cada segmento para construir los numeros
#define SEGMENT_A (1 << 0)
#define SEGMENT_B (1 << 1)
#define SEGMENT_C (1 << 2)
#define SEGMENT_D (1 << 3)
#define SEGMENT_E (1 << 4)
#define SEGMENT_F (1 << 5)
#define SEGMENT_G (1 << 6)
#define SEGMENT_P (1 << 7)

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

static const uint8_t IMAGES[] = {
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

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

void escribirnumero(uint8_t numero) {
    Chip_GPIO_SetValue(LPC_GPIO_PORT, SEGMENTS_GPIO, IMAGES[numero]);
}

void seleccionardigito(uint8_t digito) {
    Chip_GPIO_SetValue(LPC_GPIO_PORT, DIGITS_GPIO, (1 << digito));
}

void limpiarpantalla() {
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DIGITS_GPIO, DIGITS_MASK);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEGMENTS_GPIO, SEGMENTS_MASK);
}
/* === Public function implementation ========================================================= */

int main(void) {   

    uint8_t valor = 0;
    uint8_t posicion = 0;
    bool refrescar = true;

    uint8_t pantalla[4]={1,2,3,4};
    
    placa_p placa = crearplaca();


    while (true) {

        if (refrescar){
            refrescar = false;
            limpiarpantalla();
            escribirnumero(pantala(posicion));
            seleccionardigito(posicion);
        }
 
        
        if (entradadigitalactiva(placa->config_tiempo)){
            if (valor == 9){
                valor = 0;
            } else {
                valor = valor + 1;
            }
            refrescar = true;
        }

        if (entradadigitalactiva(placa->config_alarma)){
            if (valor == 0){
                valor = 9;
            } else {
                valor = valor - 1;
            }
            refrescar = true;
        }

        if (entradadigitalactiva(placa->incrementar)){
            if (posicion == 3){
                posicion = 0;
            } else {
                posicion = posicion + 1;
            }
            refrescar = true;
        }

        if (entradadigitalactiva(placa->decrementar)){
            if (posicion == 0){
                posicion = 3;
            } else {
                posicion = posicion - 1;
            }
            refrescar = true;
        } 
        
        /***********Codigo perdida de tiempo para absorver el rebote al presionar teclas*/
        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 25000; delay++) {
                __asm("NOP");
            }
        }
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
