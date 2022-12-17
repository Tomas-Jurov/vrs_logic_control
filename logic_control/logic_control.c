/*
 * logic_control.c
 *
 *  Created on: 11. 12. 2022
 *      Author: Tomáš
 */
#include "usart.h"
#include <string.h>
#include <stdbool.h>
int8_t lr = 0;
int8_t fb = 0;
int8_t ud = 0;
int8_t yv = 0;
int8_t cm = 4;

int8_t deadzone= 20;
int8_t x_speed = 0;
int8_t y_speed = 0;
int8_t z_speed = 0;
int8_t yaw_speed = 0;

int8_t oneMin = 0;
int8_t oneMax = 0;

uint32_t RC_Commands[4];
bool not_in_air = true;
bool rc_control_on = false;
bool not_down = true;
uint32_t start_time;
bool watch_dog = false;
char takeoff[] = "takeoff\r\n";
char here[] = "here\r\n";
char buffer[500];


bool funcb(){
	return true;
}

void get_and_send_data(void){
	//min max , data na mapovanie

	//toto neviem co s tym chces robit
	lr = map(*RC_Commands,806,4032,-100,100);
	fb = map(*(RC_Commands+1),347,3400,-100,100);
	ud = map(*(RC_Commands+2),3155,840,-100,100);
	yv = map(*(RC_Commands+3),3117,467,-100,100);


	if((map((*RC_Commands),(*RC_Commands),4032,0,100)<=(map((*RC_Commands),(*RC_Commands)+deadzone,4032,0,100)))&&(map((*RC_Commands),(*RC_Commands),829,0,-100)>=(map((*RC_Commands),(*RC_Commands)-deadzone,829,0,-100)))){
		x_speed = 0;
	}
	if((map((*RC_Commands),(*RC_Commands),4032,0,100))>(map((*RC_Commands),(*RC_Commands)+deadzone,4032,0,100))){
		x_speed = map((*RC_Commands),(*RC_Commands),4032,0,100);
	}
	if((map((*RC_Commands),(*RC_Commands),829,0,-100))<(map((*RC_Commands),(*RC_Commands)-deadzone,829,0,-100))){
		x_speed = (map((*RC_Commands),(*RC_Commands),829,0,-100));
	}
	///////////////////////////////////////////////////////
	if((map((*RC_Commands+1),(*RC_Commands+1),3400,0,100)<=(map((*RC_Commands+1),(*RC_Commands+1)+deadzone,3400,0,100)))&&(map((*RC_Commands+1),(*RC_Commands+1),347,0,-100)>=(map((*RC_Commands+1),(*RC_Commands+1)-deadzone,347,0,-100)))){
		y_speed = 0;
	}
	if((map((*RC_Commands+1),(*RC_Commands+1),3400,0,100))>(map((*RC_Commands+1),(*RC_Commands+1)+deadzone,3400,0,100))){
		y_speed = map((*RC_Commands+1),(*RC_Commands+1),3400,0,100);
	}
	if((map((*RC_Commands+1),(*RC_Commands+1),347,0,-100))<(map((*RC_Commands+1),(*RC_Commands+1)-deadzone,347,0,-100))){
		y_speed = (map((*RC_Commands+1),(*RC_Commands+1),347,0,-100));
	}

	/////////////////////////////////////////////////////////////////
	if((map((*RC_Commands+2),(*RC_Commands+2),3155,0,100)<=(map((*RC_Commands+2),(*RC_Commands+2)+deadzone,3155,0,100)))&&(map((*RC_Commands+2),(*RC_Commands+2),840,0,-100)>=(map((*RC_Commands+2),(*RC_Commands+2)-deadzone,840,0,-100)))){
		z_speed = 0;
	}
	if((map((*RC_Commands+2),(*RC_Commands+2),3155,0,100))>(map((*RC_Commands+2),(*RC_Commands+2)+deadzone,3155,0,100))){
		z_speed = map((*RC_Commands+2),(*RC_Commands+2),3155,0,100);
	}
	if((map((*RC_Commands+2),(*RC_Commands+2),840,0,-100))<(map((*RC_Commands+2),(*RC_Commands+2)-deadzone,840,0,-100))){
		z_speed = (map((*RC_Commands+2),(*RC_Commands+2),840,0,-100));
	}
	///////////////////////////////////////////////////
	if((map((*RC_Commands+3),(*RC_Commands+3),3117,0,100)<=(map((*RC_Commands+3),(*RC_Commands+3)+deadzone,3117,0,100)))&&(map((*RC_Commands+3),(*RC_Commands+3),467,0,-100)>=(map((*RC_Commands+3),(*RC_Commands+3)-deadzone,467,0,-100)))){
		yaw_speed = 0;
	}
	if((map((*RC_Commands+3),(*RC_Commands+3),3117,0,100))>(map((*RC_Commands+3),(*RC_Commands+3)+deadzone,3117,0,100))){
		yaw_speed = map((*RC_Commands+3),(*RC_Commands+3),3117,0,100);
	}
	if((map((*RC_Commands+3),(*RC_Commands+3),467,0,-100))<(map((*RC_Commands+3),(*RC_Commands+3)-deadzone,467,0,-100))){
		yaw_speed = (map((*RC_Commands+3),(*RC_Commands+3),467,0,-100));
	}


    if(lr<-80 && fb<-90 && ud<-90 && yv>90 && (not_in_air==true)){
    	bool success = funcb();
		cm = 110;
		HAL_UART_Transmit_IT(&huart2, (uint8_t *)&cm, 1);
		HAL_Delay(1);
		if(success){
			HAL_Delay(2000);
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
	   if(ud < -90 && (not_down==true) && (watch_dog==true) && (HAL_GetTick()-start_time)>1500){
	        rc_control_on=false;
	        cm = 112;
			HAL_UART_Transmit_IT(&huart2, (uint8_t *)&cm, 1);
			HAL_Delay(1);
	        //success = me.land();
	        bool success = funcb();
	        //print('landed');
	        if(success){
	            not_down=false;
	            watch_dog=false;
	            not_in_air=true;
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
