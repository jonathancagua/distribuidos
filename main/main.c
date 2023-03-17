
#include "main.h"
#include "config.h"

const char *TAG = "MAIN";
/*******************************************************************************
 Programa principal
******************************************************************************/
void app_main(void)
{
  /* Inicializaciones */
  IO_gpioInit();
  int i = 0;
  WIFI_init();
  MQTT_init();
  int rssi;
  char msg[50];
  while(1){
    /* Loop */
	  rssi = WIFI_getRSSI();
	  sprintf(msg,"%i",rssi);
	  MQTT_publish("test/topic1", msg);
	  CRONO_delayMs(1000);
    ESP_LOGI(TAG, "test/topic");
  }

}
