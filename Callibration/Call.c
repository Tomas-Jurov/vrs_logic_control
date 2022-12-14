/*
 * Call.c
 *
 *  Created on: 14. 12. 2022
 *      Author: mario
 */

#include "logic_control.h"



//***************calibration variables************************************************//
uint16_t lr;
uint16_t fb;
uint16_t ud;
uint16_t yv;

uint16_t lr_center, lr_min, lr_max;
uint16_t fb_center, fb_min, fb_max;
uint16_t ud_center, ud_min, ud_max;
uint16_t yv_center, yv_min, yv_max;

uint16_t cal_lr;
uint16_t cal_fb;
uint16_t cal_ud;
uint16_t cal_yv;

//************setup******************************************************************//

void setup() {
  calibrate();
}

void loop() {
  lr = *RC_Commands;
  fb = *(RC_Commands+1);
  ud = *(RC_Commands+2);
  yv = *(RC_Commands+3);
}

void calibrate() {
  Serial.println("\n---calibrating joystick---\n");
  Serial.println("place the joystick in the center position");
  cal_lr = 0;
  cal_fb = 0;
  cal_ud = 0;
  cal_yv = 0;
  delay(2500);
  Serial.print("calibrating center");
  for (int16_t i = 0; i < 100; i++) {
    Serial.print(".");
    cal_lr += *RC_Commands;
    delay(5);
    cal_fb += *(RC_Commands+1);
    delay(5);
    cal_ud += *(RC_Commands+2);
    delay(5);
    cal_yv += *(RC_Commands+3);
    delay(5);
  }
  lr_center = (cal_lr/100);
  fb_center = (cal_fb/100);
  ud_center = (cal_ud/100);
  yv_center = (cal_yv/100);
  Serial.print("\nCorrection X: ");Serial.print(lr_center);
  Serial.print("\nCorrection Y: ");Serial.println(fb_center);
  Serial.print("\nCorrection Y: ");Serial.println(ud_center);
  Serial.print("\nCorrection Y: ");Serial.println(yv_center);

  Serial.println("\nplace the joystick 1 in the bottom-left corner");
  lr_min = 0;    //reset the values
  fb_min = 0;
  delay(2500);
  Serial.print("calibrating position");
  for (int16_t i = 0; i < 100; i++) {    //take 100 readings
	  Serial.print(".");
	  lr_min += *RC_Commands;
	  delay(5);
	  fb_min += *(RC_Commands+1);
	  delay(5);
  }
  lr_min /= 100;
  fb_min /= 100;
  Serial.println();
  Serial.print("X: "); Serial.println(lr_min);
  Serial.print("Y: "); Serial.println(fb_min);

  Serial.println("\nplace the joystick 1 in the top-right corner");
  lr_max = 0;    //reset the values
  fb_max = 0;
  delay(2500);
  Serial.print("calibrating position");
  for (int16_t i = 0; i < 100; i++) {    //take 100 readings
	 Serial.print(".");
	 lr_max += *RC_Commands;
	 delay(5);
	 fb_max += *(RC_Commands+1);
	 delay(5);
  }
  lr_max /=  100;
  fb_max /=  100;
  Serial.println();
  Serial.print("X: "); Serial.println(lr_max);
  Serial.print("Y: "); Serial.println(fb_max);

  Serial.println("\nplace the joystick 2 in the bottom-left corner");
  ud_min = 0;    //reset the values
  yv_min = 0;
  delay(2500);
  Serial.print("calibrating position");
  for (int16_t i = 0; i < 100; i++) {    //take 100 readings
	  Serial.print(".");
      ud_min += *(RC_Commands+2);
      delay(5);
      yv_min += *(RC_Commands+3);
      delay(5);
  }
  ud_min /= 100;
  yv_min /= 100;
  Serial.println();
  Serial.print("X: "); Serial.println(lr_min);
  Serial.print("Y: "); Serial.println(fb_min);

  Serial.println("\nplace the joystick 2 in the top-right corner");
  ud_max = 0;    //reset the values
  yv_max = 0;
  delay(2500);
  Serial.print("calibrating position");
  for (int16_t i = 0; i < 100; i++) {    //take 100 readings
	  Serial.print(".");
      ud_max += *(RC_Commands+2);
      delay(5);
      yv_max += *(RC_Commands+3);
      delay(5);
  }
  ud_max /=  100;
  yv_max /=  100;
  Serial.println();
  Serial.print("X: "); Serial.println(lr_max);
  Serial.print("Y: "); Serial.println(fb_max);

  if(lr_max < lr_min){
	  uint16_t val = lr_max;
    lr_max = lr_min;
    lr_min = val;
  }
  if(fb_max < fb_min){
	  uint16_t val = fb_max;
    fb_max = fb_min;
    fb_min = val;
  }

  if(ud_max < ud_min){
  	  uint16_t val = ud_max;
      ud_max = ud_min;
      ud_min = val;
    }
    if(yv_max < yv_min){
  	  uint16_t val = yv_max;
      yv_max = yv_min;
      yv_min = val;
    }

  Serial.print("\nrange lr: ");Serial.print(lr_min);Serial.print(" - ");Serial.println(lr_max);
  Serial.print("range fb: ");Serial.print(fb_min);Serial.print(" - ");Serial.println(fb_max);
  Serial.print("\nrange ud: ");Serial.print(ud_min);Serial.print(" - ");Serial.println(ud_max);
    Serial.print("range yv: ");Serial.print(yv_min);Serial.print(" - ");Serial.println(yv_max);

  Serial.println("\n---calibration done---\n");
}
