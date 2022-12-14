/*
 * Call.c
 *
 *  Created on: 14. 12. 2022
 *      Author: mario
 */

#include "logic_control.h"
#include <stdio.h>



//***************calibration variables************************************************//

uint8_t lr1=0;
uint8_t fb1=0;
uint8_t ud1=0;
uint8_t yv1=0;

uint16_t lr1_center, lr1_min, lr1_max;
uint16_t fb1_center, fb1_min, fb1_max;
uint16_t ud1_center, ud1_min, ud1_max;
uint16_t yv1_center, yv1_min, yv1_max;

uint16_t cal_lr1;
uint16_t cal_fb1;
uint16_t cal_ud1;
uint16_t cal_yv1;

//************setup******************************************************************//

/*void setup() {
  calibrate();
}
*/
void loop() {
  lr1 = *RC_Commands;
  fb1 = *(RC_Commands+1);
  ud1 = *(RC_Commands+2);
  yv1 = *(RC_Commands+3);
}

void calibrate(void) {
  printf("\n---calibrating joystick---\n");
  printf("place the joystick in the center position");
  cal_lr1 = 0;
  cal_fb1 = 0;
  cal_ud1 = 0;
  cal_yv1 = 0;
  HAL_Delay(2500);
  printf("\nCalibrating center");
  for (int16_t i = 0; i < 100; i++) {
    printf(".");
    cal_lr1 += *RC_Commands;
    HAL_Delay(5);
    cal_fb1 += *(RC_Commands+1);
    HAL_Delay(5);
    cal_ud1 += *(RC_Commands+2);
    HAL_Delay(5);
    cal_yv1 += *(RC_Commands+3);
    HAL_Delay(5);
  }
  lr1_center = (cal_lr1/100);
  fb1_center = (cal_fb1/100);
  ud1_center = (cal_ud1/100);
  yv1_center = (cal_yv1/100);
  printf("\nCorrection X: ");printf("%d",lr1_center);
  printf("\nCorrection Y: ");printf("%d",fb1_center);
  printf("\nCorrection X: ");printf("%d",ud1_center);
  printf("\nCorrection Y: ");printf("%d",yv1_center);

  printf("\nPlace the joystick 1 in the bottom-left corner");
  lr1_min = 0;    //reset the values
  fb1_min = 0;
  HAL_Delay(2500);
  printf("\nCalibrating position");
  for (int16_t i = 0; i < 100; i++) {    //take 100 readings
	  printf(".");
	  lr1_min += *RC_Commands;
	  HAL_Delay(5);
	  fb1_min += *(RC_Commands+1);
	  HAL_Delay(5);
  }
  lr1_min /= 100;
  fb1_min /= 100;
  printf("\nX: %d%",lr1_min); /*printf("%d",lr1_min);*/
  printf("\nY: %d%",fb1_min); /*printf("%d",fb1_min);*/

  printf("\nPlace the joystick 1 in the top-right corner");
  lr1_max = 0;    //reset the values
  fb1_max = 0;
  HAL_Delay(2500);
  printf("\nCalibrating position");
  for (int16_t i = 0; i < 100; i++) {    //take 100 readings
	 printf(".");
	 lr1_max += *RC_Commands;
	 HAL_Delay(5);
	 fb1_max += *(RC_Commands+1);
	 HAL_Delay(5);
  }
  lr1_max /=  100;
  fb1_max /=  100;
  printf("X: %d%",lr1_max); /*printf("%d",lr1_max);*/
  printf("Y: %d%",fb1_max);/* printf("%d",fb1_max);*/

  printf("\nPlace the joystick 2 in the bottom-left corner");
  ud1_min = 0;    //reset the values
  yv1_min = 0;
  HAL_Delay(2500);
  printf("\nCalibrating position");
  for (int16_t i = 0; i < 100; i++) {    //take 100 readings
	  printf(".");
      ud1_min += *(RC_Commands+2);
      HAL_Delay(5);
      yv1_min += *(RC_Commands+3);
      HAL_Delay(5);
  }
  ud1_min /= 100;
  yv1_min /= 100;
  printf("\nX: %d%",ud1_min); /*printf("%d",ud1_min);*/
  printf("\nY: %d%",yv1_min); /*printf("%d",yv1_min);*/

  printf("\nPlace the joystick 2 in the top-right corner");
  ud1_max = 0;    //reset the values
  yv1_max = 0;
  HAL_Delay(2500);
  printf("\nCalibrating position");
  for (int16_t i = 0; i < 100; i++) {    //take 100 readings
	  printf(".");
      ud1_max += *(RC_Commands+2);
      HAL_Delay(5);
      yv1_max += *(RC_Commands+3);
      HAL_Delay(5);
  }
  ud1_max /=  100;
  yv1_max /=  100;
  printf("\nX: %d",ud1_max); /*printf("%d",ud1_max);*/
  printf("\nY: %d",yv1_max); /*printf("%d",yv1_max);*/

  if(lr1_max < lr1_min){
	uint16_t val = lr1_max;
    lr1_max = lr1_min;
    lr1_min = val;
  }
  if(fb1_max < fb1_min){
	  uint16_t val = fb1_max;
    fb1_max = fb1_min;
    fb1_min = val;
  }

  if(ud1_max < ud1_min){
  	  uint16_t val = ud1_max;
      ud1_max = ud1_min;
      ud1_min = val;
    }
    if(yv1_max < yv1_min){
  	  uint16_t val = yv1_max;
      yv1_max = yv1_min;
      yv1_min = val;
    }

  printf("\nRange lr1: %d - %d",lr1_min,lr1_max);/*;printf("%d",lr1_min);printf(" - ");printf("%d",lr1_max);*/
  printf("\nRange fb1: %d - %d",fb1_min,fb1_max);/*printf("%d",fb1_min);printf(" - ");printf("%d",fb1_max);*/
  printf("\nRange ud1: %d - %d",ud1_min,ud1_max);/*printf("%d",ud1_min);printf(" - ");printf("%d",ud1_max);*/
  printf("\nRange yv1: %d - %d",yv1_min,yv1_max);/*printf("%d",yv1_min);printf(" - ");printf("%d",yv1_max);*/

  printf("\n---calibration done---\n");
}
