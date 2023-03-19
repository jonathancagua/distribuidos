/** \file config.h
 *  Mar 2022
 *  Maestría en SIstemas Embebidos - Sistemas embebidos distribuidos
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* configuración WIFI */
#define ESP_WIFI_SSID "EASYMETERING 2.4"     // CONFIG_ESP_WIFI_SSID  // "SSID wifi"
#define ESP_WIFI_PASS "ezm12345" // CONFIG_ESP_WIFI_PASS  // "pass wifi"

/*  Configuracion MQTT  */
#define PORT_MQTT 1883            //CONFIG_PORT_MQTT      // default
#define IP_BROKER_MQTT "test.mosquitto.org"   //CONFIG_IP_BROKER_MQTT // Broker MQTT
#define USER_MQTT "usuario"             // Usuario de MQTT
#define PASSWD_MQTT "usuariopassword"   // Contraseña de MQTT

/*  configuración IO */
#define BLINK_GPIO CONFIG_BLINK_GPIO  // port 2 para NodeMcu-23S

/* Configuración SD  */

/* Configuración CRONO  */

/* Configuración SD  */

#endif
