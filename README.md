Pueden configurarse varios parámetros en la opción "Práctica 1 Configuration" del menuconfig o en forma manual.

Wifi:     En "config.h" están las deifniciones de ssid y pass. También pueden borrarse
          y agregar las constantes comentadas CONFIG_ESP_WIFI_SSID y CONFIG_ESP_WIFI_PASS
          si se quieren cofigurar dichos parámetros desde el menuconfig.

MQTT:     En "config.h" están las definiciones de broker y puerto. También pueden borrarse
          y agregar las constantes comentadas CONFIG_PORT_MQTT y CONFIG_IP_BROKER_MQTT
          si se quieren cofigurar dichos parámetros desde el menuconfig.

LED:      En "config.h" está la definición del LED para directamente con el puerto definido
          en el menuconfig. Por defecto está seteado en 2. Si se quiere modificar, cambiar
          la definiciíon en "config.h" o definir otro puerto desde el menuconfig.

Delay:    Se define el valor de un delay de proposito general desde el menuconfig.
          En la aplicación, éste debe llamarse como CONFIG_TEST_DELAY_MS

Mensaje:  Se define un mensaje de proposito general desde el menuconfig. En la aplicación
          debe llamarse como CONFIG_TEST_MESSAGE
