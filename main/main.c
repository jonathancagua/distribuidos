
#include "main.h"
#include "driver/gpio.h"
#include "config.h"

const char *TAG = "MAIN";
static bool bandera = true;
static const char* topico = "test/ledjc";
static const char* topico_rss = "test/topicjc";
void app_1(void);
void app_2(void);
void app_3(void);
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

	app_3();

}
void app_0(){
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


void app_1(void){
	WIFI_init();
	MQTT_userInit("test.mosquitto.org");
	CRONO_sntpInit();
	char timestamp[64]="";
	int64_t epoch;
	while(1){
		CRONO_delayMs(1000);
		epoch = CRONO_getTime(timestamp, sizeof(timestamp));
		printf("MAIN: Timestamp %s: \n", timestamp);
		printf("MAIN: Epoch %lli: \n'", epoch);
	}
}

void app_2(void)
{
	/* Inicializaciones */

	WIFI_init();
	MQTT_init();

	SD_mount();
	FILE *f = SD_open("usuario.txt", "r");
	char delay_milis[32];
	char user_message[200];

	SD_gets(f, delay_milis, sizeof(delay_milis));
	SD_gets(f, user_message, sizeof(user_message));
	SD_close(f);
	int d = atoi(delay_milis);

	while(1){
		CRONO_delayMs(d);
		MQTT_publish(topico_rss, user_message);
		printf("MAIN: Mensaje: %s \n", user_message);
		printf("MAIN: Delay: %i \n'", d);
	}

	// All done, unmount partition and disable SDMMC or SPI peripheral
	SD_unmount();

}



void app_3(void)
{
	/* Inicializaciones */
	WIFI_init();
	MQTT_userInit("test.mosquitto.org");
	CRONO_sntpInit();
	SD_mount();
	char timestamp[64]="";
	int64_t epoch;
	FILE *f = SD_open("tiempos.txt", "w");
	SD_printf(f, "Lectura de diferentes tiempos de formatos \n");
	for (int var = 0; var < 10; var++) {
		epoch = CRONO_getTime(timestamp, sizeof(timestamp));
		SD_printf(f, "epoch %lli -- Timestamp %s \n",epoch, timestamp);
		CRONO_delayMs(500);
	}
	SD_close(f);

	while(1){
		CRONO_delayMs(1000);
	}
	SD_unmount();

}
