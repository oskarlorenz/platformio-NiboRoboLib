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

/*! @file    analog.h
 *  @brief   Zugriff auf die analogen Eingänge.
 *           Die analogen Eingänge und die Betriebsspannung werden automatisch gemessen, dazu müssen die globalen Interrupts aktiviert sein!
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2013-09-06
 */

#ifndef _NIBOBEE_ANALOG_H_
#define _NIBOBEE_ANALOG_H_


#ifdef __cplusplus
extern "C" {
#endif


enum {
  ANALOG_INPUT20,  //!< INPUT2 (opt. Pin aus)
  ANALOG_INPUT30,  //!< INPUT3 (opt. Pin aus)
  ANALOG_INPUT21,  //!< INPUT2 (opt. Pin an)
  ANALOG_INPUT31,  //!< INPUT3 (opt. Pin an)
  ANALOG_LINE_L0,  //!< Liniensensor links (IR-LED aus)
  ANALOG_LINE_R0,  //!< Liniensensor rechts (IR-LED aus)
  ANALOG_FLOOR_L0, //!< Bodensensor links (IR-LED aus)
  ANALOG_FLOOR_R0, //!< Bodensensor rechts (IR-LED aus)
  ANALOG_LINE_L1,  //!< Liniensensor links (IR-LED an)
  ANALOG_LINE_R1,  //!< Liniensensor rechts (IR-LED an)
  ANALOG_FLOOR_L1, //!< Bodensensor links (IR-LED an)
  ANALOG_FLOOR_R1, //!< Bodensensor rechts (IR-LED an)
  ANALOG_SUPPLY,   //!< Versorgungsspannung
};


/*!
 * Initialisierung des Liniensensors.
 * Der AD-Wandler misst im Interruptmodus automatisch alle Werte, und schaltet
 * auch die IR-LEDs der Bodensensoren bei Bedarf ein und aus.
 * Die Interrupts müssen aktiviert sein, damit die Sensorwerte gemessen werden!
 */
void analog_init();


/*!
 * Stoppt die automatische Messung der analogen Spannungen.
 */
void analog_end();


/*!
 * Liefert den Wert des analogen Eingangs mit dem index @param idx zurück.
 * Die Interrupts müssen aktiviert sein, damit die Werte gemessen werden!
 */
uint16_t analog_getValue(uint8_t idx);


/*!
 * Liefert einen Zufallswert zurück. Der Wert errechnet sich aus der Summe
 * aller gemessenen Analog-Spannungen. Der Wert selbst sollte nur als Seed
 * (Enropiequelle) verwendet werden, da er monoton wachsend ist. Der Wert
 * wird um so zufälliger, je mehr analoge Messungen vorher durchgeführt
 * wurden.
 * @return Random Seed
 */
uint16_t analog_getRandomSeed();


/*!
 * Diese Funktion wird nach einem kompletten Durchgang aller Sampling-Kanäle aufgerufen, falls sie definiert wurde....
 */
void analog_irq_hook();


void analog_wait_update();

#ifdef __cplusplus
} // extern "C"
#endif


#endif // _NIBOBEE_ANALOG_H_

