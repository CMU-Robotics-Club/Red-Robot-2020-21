/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    MeLightSensorTest.ino
 * @author  MakeBlock
 * @version V1.0.1
 * @date    2015/09/10
 * @brief   Description: this file is sample program for Me Light Sensor module.
 *
 * Function List:
 *    1. int16_t MeLightSensor::read();
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2015/07/24     1.0.0            Rebuild the old lib.
 * Rafael Lee       2015/09/10     1.0.1            Added some comments and macros.
 * </pre>
 */

/* Includes ------------------------------------------------------------------*/
#include "MeMCore.h"

/* Private variables ---------------------------------------------------------*/
MeLightSensor lightSensor(PORT_6);
int value = 0;      /* a variable for the lightSensor's value */


void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
  move_setup();
  set_speed(.4);
}

/**
 * \par Function
 *    loop
 * \par Description
 *    Run continuously, print if light sensor's DAC value.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None.
 * \par Others
 *    None
 */
void loop()
{
  point2bright();
  wait(500);
  forward();
  wait(2000);
    
}

void point2bright()
{
  int t0 = millis();
  int maxval = 0;
  int tmax = 0;
  sharp_left();
  while (millis() - t0 < 2500){
    value = lightSensor.read();
    // print the results to the serial monitor
    //Serial.print("value = ");
    //Serial.println(value);
    // wait 100 milliseconds before the next loop
    if (value>maxval){
      maxval = value;
      tmax = millis()-t0;
    }
    wait(100);
  }
  stop();
  Serial.print("tmax = ");
  Serial.println(tmax);
  Serial.println(maxval);
  wait(300);
  int t1 = millis();
  sharp_left();
  while (millis() - t1 < tmax){
    wait(100);
  }
  stop();
}
