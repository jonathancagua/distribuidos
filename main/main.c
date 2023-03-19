
#include "main.h"
#include "config.h"

const char *TAG = "MAIN";
static bool bandera = true;
static const char* topico = "test/ledjc";
static const char* topico_rss = "test/topicjc";
/*******************************************************************************
 Programa principal
******************************************************************************/
void funcion(const char * topic, const char * data){
	if(strcmp(topico , topic)==0) {
		printf("MQTT: Mensaje recibido: %s\n", data);
		if(strcmp("encendido" , topic)==0) {
			bandera = true;
			IO_setLed(1);
		}
		else if(strcmp("apagado" , topic)==0) {
			bandera = false;
			IO_setLed(0);
		}
		else{
			ESP_LOGE(TAG, "mensaje no valido test/topic");
		}
	}
}


void app_main(void)
{
	/* Inicializaciones */
	int i = 0;
	WIFI_init();
	IO_gpioInit();
	MQTT_init();
	MQTT_subscribe_handler(&funcion);
	int rssi;
	char msg[50];
	MQTT_subscribe("test/ledjc");
	MQTT_publish(topico, "encendido");
	while(1){
	/* Loop */
		if(true == bandera){
			rssi = WIFI_getRSSI();
			sprintf(msg,"%i",rssi);
			MQTT_publish(topico_rss, msg);
			ESP_LOGI(TAG, "test/topic");
		}
		CRONO_delayMs(500);

	}

}
