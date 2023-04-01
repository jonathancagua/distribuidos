##!/bin/bash
# Configuración del broker y topic a escuchar.
# Configuración inicial:
broker="test.mosquitto.org"
port="1883"
topic="test/topicjc"
archivo="recibidos.txt"

#--------------------------------------------------
# Ponemos el cliente de mosquitto a escuchar
#mosquitto_sub -t $topic -h $broker -p $port -v | while read value;    do
mosquitto_sub -t $topic -h $broker -p $port | while read value;    do
ts=$(date "+%d/%m/%Y %H:%M:%S") # Agregamos una marca de tiempo en la variable ts (opcional).
# Guardamos valores:
echo "RSSI $value [DB] $ts" >> $archivo   # guardamos datos en archivo
echo "$value"                  # mostramos el resultado por consola
done