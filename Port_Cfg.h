 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: PORT_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Seif Adel
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define Port_CFG_SW_MAJOR_VERSION              (1U)
#define Port_CFG_SW_MINOR_VERSION              (0U)
#define Port_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define Port_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define Port_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define Port_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define Port_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define Port_VERSION_INFO_API                (STD_ON)
 
/* Pre-compile option for SetPinDirection Info API */
#define PortSetPinDirectionApi               (STD_ON)

/* Number of the configured Dio Channels */
#define MAX_PORT_PINS                         (39)

/* PORT Configured Port ID's */
#define PortConf_LED1_PORT_NUM             (Port_PortType)5 /* Pin 1 in PORTF */
#define PortConf_SW1_PORT_NUM              (Port_PortType)5 /* Pin 4 in PORTF */
   
/* PORT Configured Channel ID's */
#define PortConf_LED1_CHANNEL_NUM             (Port_PinType)1 /* Pin 1 in PORTF */
#define PortConf_SW1_CHANNEL_NUM              (Port_PinType)4 /* Pin 4 in PORTF */
   
/* supported mode in the project */
#define DIO          0
#define UART         1
#define SPI          2
#define I2C          3
#define PWM          4
#define PH           6
#define ID           6
#define TIMER        7
#define WATCHDOG     7
#define CAN          8
#define NMI          8
#define ADC          10 /* assume that we make the user sent number 10 as flag to indicate that he need the pin in analog mode*/

#endif /* PORT_CFG_H */