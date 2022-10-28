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

#ifndef BSP_H   /*! @cond    */
#define BSP_H   /*! @endcond */

/** @file bsp.h
 **
 ** @brief Capa para la placa 
 **
 ** Capa en la que definire los datos/entradas/salidas que utilizare segun la placa y el requerimiento.
 ** 
 ** 
 ** @defgroup Board
 ** @brief Capa BSP
 ** @{ 
 */

/* === Inclusiones de archivos externos ==================================== */

/* === Cabecera C++ ======================================================== */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros publicos ======================================== */

#include <digital.h>

/* == Declaraciones de tipos de datos publicos ============================= */

typedef struct placa_s {
    salida_digital_p sonido;

    entrada_digital_p config_tiempo;
    entrada_digital_p config_alarma;
    entrada_digital_p decrementar;
    entrada_digital_p incrementar;
    entrada_digital_p aceptar;
    entrada_digital_p cancelar;

} const * placa_p;

/* === Declaraciones de variables publicas ================================= */

/* === Declaraciones de funciones publicas ================================= */

placa_p crearplaca(void);

/* === Ciere de documentacion ============================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif   /* BSP.H */
