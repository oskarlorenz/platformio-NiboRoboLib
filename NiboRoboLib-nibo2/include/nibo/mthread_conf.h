#ifndef _MTHREAD_CONF_H_
#define _MTHREAD_CONF_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define MTHREAD_PRIO_MAX      4
#define MTHREAD_FREQ          100

// Use Timer 3 for preemtive scheduler
#define MTHREAD_TMR_vect      TIMER3_COMPA_vect
#define MTHREAD_TMR_OCR       OCR3A
#define MTHREAD_TMR_PS        64
#define MTHREAD_TMR_TIMSK     ETIMSK
#define MTHREAD_TMR_TIMSK_FLG _BV(OCIE3A) 
#define MTHREAD_TMR_TCCRB      TCCR3B
#define MTHREAD_TMR_TCCRB_INIT (_BV(WGM32) | _BV(CS31) | _BV(CS30))

#endif
