set(srcs "src/io.c" "src/crono.c" "src/wifi.c" "src/mqtt.c" "src/sd.c")
idf_component_register( SRCS "${srcs}"
					INCLUDE_DIRS ".."
					REQUIRES driver esp_wifi mqtt nvs_flash fatfs esp_adc_cal )