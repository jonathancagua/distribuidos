/** \file	crono.c
 *  Feb 2022
 *  Maestría en Sistemas Embebidos - Sistemas emebebidos distribuidos
 * \brief Contiene las funciones para manejo de tiempos y reloj del sistema */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_sntp.h"
#include "esp_timer.h"
#include "esp_sleep.h"
#include "sdkconfig.h"

/*  APID  */
#include "crono.h"

/* TAGs */


/**************************** DELAYs & SLEEPs *********************************/

/******************************************************************************
CRONO_delayMs(): introduce un delay de "delay_ms" milisegundos
******************************************************************************/
void CRONO_delayMs(int time_ms){

  vTaskDelay(time_ms / portTICK_PERIOD_MS);

}


/******************************************************************************
CRONO_sleepMs(): pone a dormir al dispositivo durante "time_ms" milisegundos
*******************************************************************************/
void CRONO_sleepMs(uint64_t time_ms){

  esp_sleep_enable_timer_wakeup(time_ms * 1000);
  esp_light_sleep_start();

}
