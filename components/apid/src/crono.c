/** \file	crono.c
 *  Mar 2022
 *  Maestría en Sistemas Embebidos - Sistemas embebidos distribuidos
 * \brief Contiene las funciones para manejo de tiempos y reloj del sistema */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "sdkconfig.h"

/*  APID  */
#include "../include/config.h"
#include "../include/crono.h"

/* TAGs */

/*********************************** DELAYs  **********************************/

/******************************************************************************
CRONO_delayMs(): introduce un delay de "delay_ms" milisegundos
******************************************************************************/
void CRONO_delayMs(int time_ms){

  vTaskDelay(time_ms / portTICK_PERIOD_MS);

}
