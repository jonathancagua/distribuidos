
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

  while(1){
    /* Loop */
    IO_toggleLed();
    CRONO_delayMs(300);
    ESP_LOGI(TAG, "%i", i++);
  }

}
