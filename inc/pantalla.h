/* Copyright 2022, EITI
 * Facultad de Ciencias Exactas y Tecnología 
 * Universidad Nacional de Tucuman
 * Copyright 2022, German Moyano
 * All rights reserved.
 *
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

#ifndef PANTALLA_H   /*! @cond    */
#define PANTALLA_H   /*! @endcond */

/** @file pantalla.h
 **
 ** @brief Capa para la placa 
 **
 ** Capa en la que definire los datos/entradas/salidas que utilizare segun la placa y el requerimiento.
 ** 
 ** 
 ** @defgroup Board
 ** @brief Capa Pantalla del TP4
 ** @{ 
 */

/* === Inclusiones de archivos externos ==================================== */

#include <stdint.h>

/* === Cabecera C++ ======================================================== */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros publicos ======================================== */

//Definimos los bits asociados a cada segmento para construir los numeros
#define SEGMENT_A (1 << 0)
#define SEGMENT_B (1 << 1)
#define SEGMENT_C (1 << 2)
#define SEGMENT_D (1 << 3)
#define SEGMENT_E (1 << 4)
#define SEGMENT_F (1 << 5)
#define SEGMENT_G (1 << 6)
#define SEGMENT_P (1 << 7)

/* == Declaraciones de tipos de datos publicos ============================= */
 //referencia a un descriptor para manejar un display de 7 segmentos
typedef struct pantalla_s * pantalla_p;

typedef void(*pantalla_limpiar_p)(void);

typedef void(*pantalla_segmento_p)(uint8_t segmentos);

typedef void(*pantalla_digito_p)(uint8_t digito);

typedef struct driver_pantalla_s {
    pantalla_limpiar_p apagarpantalla;
    pantalla_segmento_p encendersegmento;
    pantalla_digito_p encenderdigito;
} const * driver_pantalla_p;

/* === Declaraciones de variables publicas ================================= */

pantalla_p crearpantalla (uint8_t digitos, driver_pantalla_p driver);

void escribirpantallabcd(pantalla_p pantalla, uint8_t * numero, uint8_t tamano);

void refrescarpantalla(pantalla_p pantalla);

/* === Declaraciones de funciones publicas ================================= */

/* === Ciere de documentacion ============================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif   /* PANTALLA.H */