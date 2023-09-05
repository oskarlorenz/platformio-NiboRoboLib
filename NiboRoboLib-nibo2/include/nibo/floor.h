/*  BSD-License:

Copyright (c) 2007 by Nils Springob, nicai-systems, Germany

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  * Neither the name nicai-systems nor the names of its contributors may be
    used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*! @file    floor.h
 *  @brief   Routinen zum Auslesen der Werte der Bodensensoren
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2007-07-13
 */

#ifndef NIBO_FLOOR_H_
#define NIBO_FLOOR_H_
#if defined(NIBO_USE_FLOOR) || defined (DOXYGEN)

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Floor IR-Licht einschalten
 */
#define floor_enable_ir() set_output_bit(IO_LINE_FLOOR_EN)

/*!
 * Floor IR-Licht ausschalten
 */
#define floor_disable_ir() clear_output_bit(IO_LINE_FLOOR_EN)

/*!
 * Verzögerung der Sensoren, nach ein/ausschalten des IR-Lichts
 */
#define FLOOR_SENS_DALAY_US 15

enum {
  LINE_LEFT,
  LINE_RIGHT,
  FLOOR_LEFT,
  FLOOR_RIGHT,
};

#define floor_l  floor_relative[FLOOR_LEFT]
#define floor_r  floor_relative[FLOOR_RIGHT]
#define line_l   floor_relative[LINE_LEFT]
#define line_r   floor_relative[LINE_RIGHT]

/*! @obsolete */
void floor_update();

/*! @obsolete */
extern uint16_t floor_absolute [4]; 

/*! @obsolete */
extern uint16_t floor_relative [4];


/*!
 * Bodensensoren initialisieren
 */
void floor_init();


/*!
 * Ergebnisse aus analogen Roh-Werten berechnen und normalisieren
 */
uint16_t floor_get(uint8_t idx);


/*!
 * Ergebnisse aus analogen Roh-Werten berechnen und normalisieren
 */
uint16_t floor_getAbs(uint8_t idx);


uint16_t floor_getRaw0(uint8_t idx);

uint16_t floor_getRaw1(uint8_t idx);

uint16_t floor_getRawDiff(uint8_t idx);

/*!
 * Bodensensor wird auf schwarzer Fläche kalibriert
 */
void floor_calibrateBlackCh(uint8_t idx);


/*!
 * Bodensensor wird auf weisser Fläche kalibriert
 */
void floor_calibrateWhiteCh(uint8_t idx);


/*!
 * alle Bodensensoren werden auf schwarzer Fläche kalibriert
 */
void floor_calibrateBlack();


/*!
 * alle Bodensensoren werden auf weisser Fläche kalibriert
 */
void floor_calibrateWhite();


/*!
 * Kalibrierdaten aus EEPROM lesen
 */
void floor_readPersistent();


/*!
 * Kalibrierdaten ins EEPROM schreiben
 */
void floor_writePersistent();


#ifdef __cplusplus
} // extern "C"
#endif

#endif // NIBO_USE_FLOOR
#endif // NIBO_FLOOR_H_
