 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Seif Adel
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define Port_PBCFG_SW_MAJOR_VERSION              (1U)
#define Port_PBCFG_SW_MINOR_VERSION              (0U)
#define Port_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define Port_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define Port_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define Port_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((Port_PBCFG_AR_RELEASE_MAJOR_VERSION != Port_AR_RELEASE_MAJOR_VERSION)\
 ||  (Port_PBCFG_AR_RELEASE_MINOR_VERSION != Port_AR_RELEASE_MINOR_VERSION)\
 ||  (Port_PBCFG_AR_RELEASE_PATCH_VERSION != Port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((Port_PBCFG_SW_MAJOR_VERSION != Port_SW_MAJOR_VERSION)\
 ||  (Port_PBCFG_SW_MINOR_VERSION != Port_SW_MINOR_VERSION)\
 ||  (Port_PBCFG_SW_PATCH_VERSION != Port_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration = {
						PIN0, PORTA, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN1, PORTA, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN2, PORTA, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN3, PORTA, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN4, PORTA, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN5, PORTA, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN6, PORTA, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN7, PORTA, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN8, PORTB, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN9, PORTB, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN10, PORTB, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN11, PORTB, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN12, PORTB, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN13, PORTB, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN14, PORTB, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN15, PORTB, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN16, PORTC, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN17, PORTC, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN18, PORTC, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN19, PORTC, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN20, PORTD, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN21, PORTD, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN22, PORTD, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN23, PORTD, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN24, PORTD, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN25, PORTD, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN26, PORTD, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN27, PORTD, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN28, PORTE, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN29, PORTE, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN30, PORTE, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN31, PORTE, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN32, PORTE, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN33, PORTE, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN34, PORTF, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PortConf_LED1_CHANNEL_NUM, PortConf_LED1_PORT_NUM, OUTPUT, OFF, DIO, STD_HIGH, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN36, PORTF, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PIN37, PORTF, INPUT, OFF, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
						PortConf_SW1_CHANNEL_NUM, PortConf_LED1_PORT_NUM, INPUT, PULL_UP, DIO, STD_LOW, UNCHANGABLE, UNCHANGABLE_MODE,
};