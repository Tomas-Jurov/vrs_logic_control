/*
 * logic_control.c
 *
 *  Created on: 11. 12. 2022
 *      Author: Tomáš
 */
#include "usart.h"
#include "adc.h"
#include <string.h>
#include <stdbool.h>

int8_t lr = 0;
int8_t fb = 0;
int8_t ud = 0;
int8_t yv = 0;
int8_t cm = 4;

uint8_t deadzone= 30;
int8_t x_speed = 0;
uint16_t xPosition = 0;
uint16_t xLow = 806;
uint16_t xHigh = 4032;
uint16_t xRest =2788;

int8_t y_speed = 0;
uint16_t yPosition = 0;
uint16_t yLow = 347;
uint16_t yHigh = 3400;
uint16_t yRest = 1873;

int8_t z_speed = 0;
uint16_t zPosition = 0;
uint16_t zLow = 840;
uint16_t zHigh = 3155;
uint16_t zRest = 1997;

int8_t yaw_speed = 0;
uint16_t yawPosition = 0;
uint16_t yawLow = 467;
uint16_t yawHigh = 3117;
uint16_t yawRest = 1792;


uint32_t RC_Commands[4];
bool not_in_air = true;
bool rc_control_on = false;
bool not_down = true;
uint32_t start_time;
bool watch_dog = false;
char takeoff[] = "takeoff\r\n";
char here[] = "here\r\n";
char buffer[500];



void get_and_send_data(void){

	xPosition =*RC_Commands;
	yPosition = *(RC_Commands+1);
	zPosition = *(RC_Commands+2);
	yawPosition = *(RC_Commands+3);

	lr = map(xPosition,xLow,xHigh,-100,100);
	fb = map(yPosition,yLow,yHigh,-100,100);
	ud = map(zPosition,zHigh,zLow,-100,100);
	yv = map(yawPosition,yawHigh,yawLow,-100,100);

	if((xPosition <= xRest+deadzone) && (xPosition >= xRest - deadzone)){
			x_speed = 0;
		}
	if(xPosition > xRest+deadzone){
		x_speed = map(xPosition,xRest+deadzone,xHigh,0,100);
	}
	if(xPosition < xRest - deadzone){
		x_speed = map(xPosition,xLow,xRest - deadzone,-100,0);
	}



	if((yPosition <= yRest+deadzone) && (yPosition >= yRest - deadzone)){
		y_speed = 0;
	}
	if(yPosition > yRest+deadzone){
		y_speed = map(yPosition,yRest + deadzone,yHigh,0,100);
	}
	if(yPosition < yRest - deadzone){
		y_speed = map(yPosition,yLow,yRest-deadzone,-100,0);
	}



	if((zPosition <= zRest+deadzone) && (zPosition >= zRest - deadzone)){
		z_speed = 0;
	}
	if(zPosition > zRest+deadzone){
		z_speed = map(zPosition,zRest + deadzone,zHigh,0,-100);
	}
	if(zPosition < zRest - deadzone){
		z_speed = map(zPosition,zLow,zRest - deadzone,100,0);
	}



	if((yawPosition <= yawRest+deadzone) && (yawPosition >= yawRest - deadzone)){
		yaw_speed = 0;
	}
	if(yawPosition > yawRest+deadzone){
		yaw_speed = map(yawPosition,yawRest + deadzone,yawHigh,0,-100);
	}
	if(yawPosition < yawRest - deadzone){

		yaw_speed = map(yawPosition,yawLow,yawRest - deadzone,100,0);
	}


    if(lr<-80 && fb<-90 && ud<-90 && yv>90 && (not_in_air==true)){
		cm = 110;
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&cm, 1);
		HAL_Delay(1);
		uint8_t success = 0;
		HAL_UART_Receive(&huart2,(uint8_t *)&success,1,20000);
		if(success){
			not_in_air=false;
			rc_control_on = true;
			not_down = true;
			//HAL_UART_Transmit_IT(&huart2, takeoff, sizeof(takeoff));
		}
	}




	if((ud<-90) && (not_in_air==false) && watch_dog==false){
	        start_time = HAL_GetTick();
	        watch_dog=true;
	}
	else if(ud>-90){
		start_time = HAL_GetTick();
		watch_dog = false;
	}
	   if(ud < -90 && (not_in_air==false) && (not_down==true) && (watch_dog==true) && (HAL_GetTick()-start_time)>1000){
	        rc_control_on=false;
	        cm = 112;
			HAL_UART_Transmit_IT(&huart2, (uint8_t *)&cm, 1);
			HAL_Delay(1);
	        //success = me.land();
			uint8_t success = 0;
			HAL_UART_Receive(&huart2,(uint8_t *)&success,1,30000);
	        //print('landed');
	        if(success){
	        	not_in_air=true;
	            not_down=false;
	            watch_dog=false;
	        }
	    }


	if(rc_control_on==true){
		cm = 111;
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&cm, 1);
		HAL_Delay(1);
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&lr, 1);
		HAL_Delay(1);
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&fb, 1);
		HAL_Delay(1);
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&ud, 1);
		HAL_Delay(1);
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&yv, 1);
		HAL_Delay(1);
	}

}
