
#include "main.h"
#include "driver/gpio.h"
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
		if(strcmp("encendido" , data)==0) {
			bandera = true;
			IO_setLed(1);
			ESP_LOGE(TAG, "ENCENDIDO");
		}
		else if(strcmp("apagado" , data)==0) {
			bandera = false;
			IO_setLed(0);
			ESP_LOGE(TAG, "APAGADO");
		}
		else{
			ESP_LOGE(TAG, "mensaje no valido test/topic");
		}
	}
}


void app_main(void)
{
	/* Inicializaciones */
  #if 0
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
#endif
	/*WIFI_userInit("jcagua" ,"ezm");
	MQTT_userInit("test.mosquitto.org");
	CRONO_sntpInit();
	char timestamp[64]="";
	int64_t epoch;*/
	//gpio_set_pull_mode(GPIO_NUM_19, GPIO_PULLUP_ONLY);
	//gpio_set_pull_mode(GPIO_NUM_15, GPIO_PULLUP_ONLY);
	SD_mount();
	/*FILE *f = SD_open("usuario.txt", "r");
	char delay_milis[32];
	char user_message[200];

	SD_gets(f, delay_milis, sizeof(delay_milis));
	SD_gets(f, user_message, sizeof(user_message));
	SD_close(f);
	int d = atoi(delay_milis);*/

	/*
	f = SD_open("tiempos.txt", "w");
	SD_printf(f, "Lectura de diferentes tiempos de formatos ");
	for (int var = 0; int var < 50; ++int var) {
		epoch = CRONO_getTime(timestamp, sizeof(timestamp));
		SD_printf(f, "epoch %lli -- Timestamp %s",epoch, timestamp);
		CRONO_delayMs(500);
	}
	*/
	while(1){
		CRONO_delayMs(1000);
		/*
		CRONO_delayMs(d);

		MQTT_publish("test/%s ", user_message);
		printf("MAIN: Mensaje %s: \n", user_message);
		printf("MAIN: Delay %i \n'", d);*/
/*
		epoch = CRONO_getTime(timestamp, sizeof(timestamp));
		printf("MAIN: Timestamp %s: \n", timestamp);
		printf("MAIN: Epoch %lli: \n'", epoch);*/
	}

	// All done, unmount partition and disable SDMMC or SPI peripheral
	//SD_unmount();

}
