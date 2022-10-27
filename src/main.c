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

/* === Macros definitions ====================================================================== */

/*solo le asigna un nombre amigable a los numeros, que estan definidos en el manual de la placa*/
/*para referirse, a los leds de salida, como a los pulsadores de entrada*/

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

int main(void) {

    int divisor  = 0;
    placa_p placa = crearplaca();

    while (true) {
        /*********Programacion para encender el led BLUE, al mantener presionada la tecla 1*/
        if (estadoentradadigital(placa->tecla_1)) {
            activarsalidadigital(placa->led_azul); 
        } 
        else {
            desactivarsalidadigital(placa->led_azul);
        }

        /*********Programacion para encender y apagar el led 1, cdo presiono la tecla 2*/

        if(entradadigitalactiva(placa->tecla_2)){
            cambiarsalidadigital(placa->led_uno);
        }

        /*********Codigo que enciende el led 2 con la tecla 3 y lo apaga con la tecla 4*/

        if(estadoentradadigital(placa->tecla_3)){
            activarsalidadigital(placa->led_dos);
        }
        if(estadoentradadigital(placa->tecla_4)){
            desactivarsalidadigital(placa->led_dos);
        }

        /**********Divisor para encender y apagar el led 3 cdo el programa esta corriendo*/
        divisor++;
        if (divisor == 5) {
            divisor = 0;
            cambiarsalidadigital(placa->led_tres);
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
