/** \file	main.h
 *  Mar 2022
 *  Maestría en SIstemas Embebidos / Sistemas embebidos distribuidos
 *  \brief	Contiene las bibliotecas y definiciones generales de configuración
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "sdkconfig.h"

/* Configuración general  */
#include "config.h"

/* Nivel de abstracción APID */
#include "../components/apid/include/io.h"
#include "../components/apid/include/crono.h"

#endif /* MAIN_H_ */
