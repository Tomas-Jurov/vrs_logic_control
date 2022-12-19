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
#include "gpio.h"

//USER VARIABLES
int8_t cm = 4;

uint8_t deadzone= 70;
int8_t x_speed = 0;
uint16_t xPosition = 0;
uint16_t xLow = 963;
uint16_t xHigh = 4034;
uint16_t xRest =2905;

int8_t y_speed = 0;
uint16_t yPosition = 0;
uint16_t yLow = 229;
uint16_t yHigh = 3358;
uint16_t yRest = 1778;

int8_t z_speed = 0;
uint16_t zPosition = 0;
uint16_t zLow = 836;
uint16_t zHigh = 3143;
uint16_t zRest = 1930;

int8_t yaw_speed = 0;
uint16_t yawPosition = 0;
uint16_t yawLow = 401;
uint16_t yawHigh = 3046;
uint16_t yawRest = 1746;


uint32_t RC_Commands[4];
bool not_in_air = true;
bool rc_control_on = false;
bool not_down = true;
uint32_t start_time;
bool watch_dog = false;
char takeoff[] = "takeoff\r\n";
char here[] = "here\r\n";
char buffer[500];
uint8_t prev_mode = 0;

void get_and_send_data(void){

	xPosition =*RC_Commands;
	yPosition = *(RC_Commands+1);
	zPosition = *(RC_Commands+2);
	yawPosition = *(RC_Commands+3);

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


    if(x_speed<-80 && y_speed<-90 && z_speed<-90 && yaw_speed>90 && (not_in_air==true)){
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




	if((z_speed<-90) && (not_in_air==false) && watch_dog==false){
	        start_time = HAL_GetTick();
	        watch_dog=true;
	}
	else if(z_speed>-90){
		start_time = HAL_GetTick();
		watch_dog = false;
	}
	   if(z_speed < -90 && (not_in_air==false) && (not_down==true) && (watch_dog==true) && (HAL_GetTick()-start_time)>1000){
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

	if(drone_mode!=prev_mode && drone_mode==1){
		cm = 113;
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&cm, 1);
		HAL_Delay(1);

	}
	else if(drone_mode!=prev_mode && drone_mode ==0){
		cm = 114;
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&cm, 1);
		HAL_Delay(1);
	}

	if(rc_control_on==true){
		if(!drone_mode){
			cm = 111;
			HAL_UART_Transmit_IT(&huart2, (uint8_t *)&cm, 1);
			HAL_Delay(1);
			HAL_UART_Transmit_IT(&huart2, (uint8_t *)&x_speed, 1);
			HAL_Delay(1);
			HAL_UART_Transmit_IT(&huart2, (uint8_t *)&y_speed, 1);
			HAL_Delay(1);
			HAL_UART_Transmit_IT(&huart2, (uint8_t *)&z_speed, 1);
			HAL_Delay(1);
			HAL_UART_Transmit_IT(&huart2, (uint8_t *)&yaw_speed, 1);
			HAL_Delay(1);
		}
	}
	prev_mode = drone_mode;

}
