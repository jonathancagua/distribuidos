
#include "main.h"
#include "driver/gpio.h"

const char *TAG = "MAIN";
static bool bandera = false;
static const char* topico = "test/ledjc";
static const char* topico_rss = "test/topicjc";
static const char* topico_ldr = "test/topicjc";
volatile int samples[SAMPLES_SIZE];
volatile int n = 0;
void app_1(void);
void app_2(void);
void app_3(void);
void app_4(void);
void app_5(void);
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

	app_5();

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

/**
Requerimientos de la actividad:
El nodo debe poder configurar la red WiFi, la dirección de broker y la
cantidad de mediciones a realizar (no mayor a 100)
leyendo estos parámetros desde un archivo de texto config.txt en la SD.

El nodo debe sensar la señal RSSI y guardar en un archivo CSV lecturas.csv una tabla con
las lecturas tomadas periodicamente. Las lecturas deben hacerse con un delay de 1 segundo
y la tabla debe tener dos columnas: una para el tiempo <timestamp-GMT>
 y la otra para la potencia <RSSI>.

Además, cada lectura de potencia realizada debe transmitirse en tiempo real por MQTT al
 cliente en la PC, donde se deberá mostrar por consola cada lectura recibida con su timestamp asociado.

Desde la App deben poder iniciarse las capturas. Además debe configurarse un LED
en el mismo dashboard para que se prenda cuando el nodo haya recibido el comando
de inicio y se apague cuando se haya concluído y guardado todos los datos en el nodo.
 */
void app_4(void)
{

	SD_mount();
	FILE *f = SD_open("config.txt", "r");
	int rssi;
	char timestamp[64]="";
	char msg[100];

	int64_t epoch;
	char user_cantidad[32];
	char user_broken[40]={0};
	char user_ssid[40]={0};
	char user_pw[40]={0};
	SD_gets(f, user_ssid, sizeof(user_ssid));
	ESP_LOGI(TAG, "SSID %s",user_ssid);
	SD_gets(f, user_pw, sizeof(user_pw));
	ESP_LOGI(TAG, "PWD %s",user_pw);
	SD_gets(f, user_broken, sizeof(user_broken));
	ESP_LOGI(TAG, "user_broken %s",user_broken);
	SD_gets(f, user_cantidad, sizeof(user_cantidad));
	ESP_LOGI(TAG, "user_cantidad %s",user_cantidad);
	int n = strlen(user_ssid);
	user_ssid[n-1]='\0';
	n = strlen(user_pw);
	user_pw[n-1]='\0';
	n = strlen(user_broken);
	user_broken[n-1]='\0';
	int muestreo = atoi(user_cantidad);
	WIFI_userInit(user_ssid,user_pw);
	MQTT_userInit(user_broken);
	MQTT_subscribe_handler(&funcion);
	MQTT_subscribe("test/ledjc");
	MQTT_publish(topico, "apagado");
	CRONO_sntpInit();
	while(1){
		if(true == bandera){
			if(muestreo <= 100){
				f = SD_open("lecturas.csv", "w");
				for (int var = 0; var < muestreo; ++var) {
					CRONO_delayMs(1000);
					rssi = WIFI_getRSSI();
					epoch = CRONO_getTime(timestamp, sizeof(timestamp));
					SD_printf(f, "%i %s \n",rssi, timestamp);
					sprintf(msg,"%s %i",timestamp,rssi);
					MQTT_publish(topico_rss, msg);
					ESP_LOGI(TAG, "Enviando");
					if(false == bandera){
						break;
						ESP_LOGI(TAG, "Stop grabanding");
					}
				}
				ESP_LOGI(TAG, "Se Cierra SD");
				bandera = false;
				MQTT_publish(topico, "apagado");
				SD_close(f);
			}
			else{
				ESP_LOGE(TAG, "Asignando muestreo");
			}
		}
		CRONO_delayMs(1000);
	}

	SD_unmount();

}

void app_6(void)
{
	IO_adcInit();
	IO_gpioInit();
	IO_pwmInit();
	CRONO_timerInit();

	int x;


	CRONO_timerStart(10);
	while(n<SAMPLES_SIZE){
		printf("GRABANDO: %i muestras de %i\n", n, SAMPLES_SIZE);
		CRONO_delayMs(500);
	}
	CRONO_timerStop();
	printf("GRABACIÓN FINALIZADA\n");

	CRONO_delayMs(250);

	printf("INICIANDO REPRODUCCIÓN\n");
	for(n=0;n<SAMPLES_SIZE;n++){
	   IO_pwmSet(samples[n] / 4096.0 *100);
	   IO_monitorGraph(samples[n]);
	   CRONO_delayMs(10);
	}
	IO_pwmSet(0);
	printf("REPRODUCCIÓN FINALIZADA\n");
	n = 0;

	while(1){
		/*x = IO_readAdc();
		CRONO_delayMs(250);
		ESP_LOGE(TAG, "Sensor %i ", x);*/

		printf("FINLALIZADO: %i\n", n++);
		IO_toggleLed();
		CRONO_delayMs(1000);
	}
}

//20 ms 50hz
//
void app_5(void)
{

	SD_mount();

	char timestamp[64]="";
	char msg_ldr[100];
	char msg[100];
	int muestreo = 50;
	int64_t epoch;
	WIFI_init();
	CRONO_timerInit();
	IO_adcInit();

	MQTT_init();
	MQTT_subscribe_handler(&funcion);
	MQTT_subscribe(topico);
	MQTT_publish(topico, "apagado");

	CRONO_sntpInit();
	epoch = CRONO_getTime(timestamp, sizeof(timestamp));
	sprintf(msg,"%s.csv",timestamp);
	ESP_LOGI(TAG, "%s",msg);
	FILE *f = SD_open(msg, "w");
	while(1){
		if(true == bandera){
			CRONO_timerStart(20);
			while(true == bandera){
				sprintf(msg_ldr,"%d", samples[n-1]);
				MQTT_publish(topico_ldr, msg_ldr);
				printf("Index %i , valor = %d muestras de %i\n",n,samples[n-1], SAMPLES_SIZE);
				if(n == SAMPLES_SIZE){
					break;
				}
				CRONO_delayMs(500);
			}
			bandera = false;
			CRONO_timerStop();
			ESP_LOGE(TAG, "Desactivado muestreo");
			for(int i = 0; i< n;i++)
				SD_printf(f, "%d\n", samples[i]);
			ESP_LOGE(TAG, "Terminado de grabar");
			MQTT_publish(topico, "apagado");
			SD_close(f);
			n = 0;
		}
		else{
			CRONO_delayMs(1000);
		}

	}

	SD_unmount();

}
