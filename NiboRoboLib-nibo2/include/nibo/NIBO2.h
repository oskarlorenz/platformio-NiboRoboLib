/*
  NIBO2 library for ARDUINO
  License: BSD-License
  (c) 2013 by Nils Springob, nicai-systems
*/

#ifndef __NIBO2_H__
#define __NIBO2_H__

#if !defined (__AVR_ATmega128__)
#error NIBO2 "library should be used with a NIBO2 robot as board (ATmega128 MCU)"
#endif


/*! @file    NIBO2.h
 *  @brief   NIBO2 library for ARDUINO
 *  @author  Nils Springob (nils@nicai-systems.de)
 *  @date    2013-09-02
 */


enum {
  LED_OFF    = 0,
  LED_GREEN  = 1,
  LED_RED    = 2,
  LED_ORANGE = 3
};


enum {
  LINE_L   = 0,
  LINE_R   = 1,
  FLOOR_L  = 2,
  FLOOR_R  = 3,
};


enum {
  FLOOR_PASSIVE = 0,
  FLOOR_ACTIVE = 1,
  FLOOR_DIFFERENTIAL =2
};


class NIBO2Class {
  public:
    NIBO2Class();
    void begin();
    unsigned int getVoltage();
    //void checkVoltage();
    void setLed(unsigned char led, unsigned char value);
    unsigned char getLed(unsigned char led);
    void setLedsIntensity(int light);
    void setHeadlightsIntensity(int light);
    void setDisplayIntensity(int light);
    unsigned int getRandomSeed();
    unsigned int getAnalog(unsigned char adc_channel, unsigned char active=0);
    void enableCopro();
    void disableCopro();
    unsigned char getS3();
    unsigned char getJP1();
};

extern NIBO2Class NIBO2;



/*---------------------------------------------------------------------------*/

class EnginePartClass {
  private:
    unsigned char id;
  public:
    EnginePartClass(unsigned char id);
    int getTicks();
    int getSpeed();
    int getCurrent();
};


class EngineClass {
  private:
  public:
    EnginePartClass left;
    EnginePartClass right;
    EngineClass();
    void begin();
    void setPWM(int left, int right);
    void setSpeed(int left, int right);
    void setTargetAbs(int left, int right, unsigned int speed);
    void setTargetRel(int left, int right, unsigned int speed);
    int getTargetDist();
    void stop();
    void stopImmediate();
};

extern EngineClass Engine;


/*---------------------------------------------------------------------------*/


class FloorSensorClass {
  public:
    FloorSensorClass();
    void begin();
    unsigned int get(unsigned char index, unsigned char absolute=0);
    unsigned int getRaw(unsigned char index, unsigned char variant);
    unsigned int getL0(unsigned char absolute=0) {return get(LINE_L, absolute);}
    unsigned int getR0(unsigned char absolute=0) {return get(LINE_R, absolute);}
    unsigned int getL1(unsigned char absolute=0) {return get(FLOOR_L, absolute);}
    unsigned int getR1(unsigned char absolute=0) {return get(FLOOR_R, absolute);}
    void calibrateWhite();
    void calibrateBlack();
    void storeCalibration();   
};

extern FloorSensorClass FloorSensor;


/*---------------------------------------------------------------------------*/


class DistanceSensorClass {
  private:
  public:
    DistanceSensorClass();
    void begin();
    void beginMeasure();
    void beginReceiveRC5();
    unsigned int get(unsigned char dir);
    unsigned char transmitRC5(unsigned int code);
    unsigned int getLastRC5();
};

extern DistanceSensorClass DistSensor;


/*---------------------------------------------------------------------------*/


#endif














