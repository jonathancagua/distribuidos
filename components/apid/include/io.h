/** \file io.h
 *  Mar 2022
 *  Maestría en SIstemas Embebidos - Sistemas embebidos distribuidos
 */

#ifndef IO_H_
#define IO_H_

/* Prototipos */
void IO_gpioInit();
int IO_setLed(int);
void IO_toggleLed(void);

#endif /* IO_H_ */
