/** \file	io.c
 *  Mar 2022
 *  Maestría en Sistemas Embebidos - Sistemas embebidos distribuidos
 * \brief Contiene funciones principalmente para el manejo de distintos periféricos */

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* APID */
#include "../include/config.h"
#include "../include/io.h"

/* TAGs */
static const char *TAG = "IO/GPIO";

/********************************** GPIO **************************************/

/******************************************************************************
IO_gpioInit(): inicializa perifericos de entrada/salida
*******************************************************************************/
void IO_gpioInit(){

  /* Configure the IOMUX register for pad BLINK_GPIO (some pads are muxed to GPIO
     on reset already, but some default to other functions and need to be switched
     to GPIO. Consult the Technical Reference for a list of pads and their default
     functions.) */

  gpio_reset_pin(BLINK_GPIO);
  /* Set the GPIO as a push/pull output */
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
  ESP_LOGI(TAG, "GPIO %d MODE %d ",BLINK_GPIO , GPIO_MODE_OUTPUT );
  gpio_set_level(BLINK_GPIO, 0);


}

/******************************************************************************
 IO_setLed(): Setea el estado del LED configurado por defecto en el módulo ESP32
******************************************************************************/
int IO_setLed(int estado){

  gpio_set_level(BLINK_GPIO, estado);
  return estado;

}

/******************************************************************************
 IO_toggleLed(): Togglea estado del LED configurado por defecto en el módulo ESP32
******************************************************************************/
void IO_toggleLed(void){

 static int estado = 0;
 estado = 1 - estado;
 gpio_set_level(BLINK_GPIO, estado);

}
