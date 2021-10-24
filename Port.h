 /******************************************************************************
 *
 * Module: Port
 *
 * File Name:  Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Seif Adel
 ******************************************************************************/

#ifndef Port_H
#define Port_H

/* Id for the company in the AUTOSAR
 * for example Seif Adel's ID = 1000 :) */
#define Port_VENDOR_ID    (1000U)

/* Dio Module Id */
#define Port_MODULE_ID    (120U)

/* Dio Instance Id */
#define Port_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define Port_SW_MAJOR_VERSION           (1U)
#define Port_SW_MINOR_VERSION           (0U)
#define Port_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define Port_AR_RELEASE_MAJOR_VERSION   (4U)
#define Port_AR_RELEASE_MINOR_VERSION   (0U)
#define Port_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != Port_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != Port_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != Port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Port.h files */
#if ((Port_CFG_AR_RELEASE_MAJOR_VERSION != Port_AR_RELEASE_MAJOR_VERSION)\
 ||  (Port_CFG_AR_RELEASE_MINOR_VERSION != Port_AR_RELEASE_MINOR_VERSION)\
 ||  (Port_CFG_AR_RELEASE_PATCH_VERSION != Port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Port.h files */
#if ((Port_CFG_SW_MAJOR_VERSION != Port_SW_MAJOR_VERSION)\
 ||  (Port_CFG_SW_MINOR_VERSION != Port_SW_MINOR_VERSION)\
 ||  (Port_CFG_SW_PATCH_VERSION != Port_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Initializes the Port Driver module.  */
#define Port_Init_SID                  (uint8)0x00

/* Service ID for Sets the port pin direction  */
#define Port_SetPinDirection_SID       (uint8)0x01

/* Service ID for Refreshes port direction.  */
#define Port_RefreshPortDirection_SID  (uint8)0x02

/* Returns the version information of this module */
#define Port_GetVersionInfo_SID        (uint8)0x03

/* Service ID for Sets the port pin mode */
#define Port_SetPinMode_SID     (uint8)0x04


/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID 
requested */
#define PORT_E_PARAM_PIN               (uint8)0x0A

/* Port Pin not configured 
as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE  (uint8)0x0B

/* API Port_Init service called with wrong 
parameter */
#define PORT_E_PARAM_CONFIG            (uint8)0x0C

/* API Port_SetPinMode service called when 
    mode is unchangeable 
*/
#define PORT_E_PARAM_INVALID_MODE      (uint8)0x0D

/*
 * API Port_SetPinMode service called when 
 * mode is unchangeable
 */
#define PORT_E_MODE_UNCHANGEABLE        (uint8)0x0E

/*
 * API service called without module initialization
 */
#define PORT_E_UNINIT                   (uint8)0x0F
   
/* APIs called with a Null Pointer 
 */
#define PORT_E_PARAM_POINTER            (uint8)0x10
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinType;


/*Type definition for Port_PortType used by the Port APIs */
typedef uint8 Port_PortType;


/* Type definition for Port_PinModeType used by the Port APIs */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
/* Non Autosar */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: enum to hold the state of pin direction during runtime (changable or not) */
/* Non Autosar */
typedef enum
{
    CHANGABLE,UNCHANGABLE
}Port_PinDirection_changeability; 

/* Description: enum to hold the state of pin mode during runtime (changable or not) */
/* Non Autosar */
typedef enum
{
    CHANGABLE_MODE,UNCHANGABLE_MODE
}Port_PinMode_changeability;

typedef struct 
{
    Port_PinType pin_num; 
    Port_PortType port_num;
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    Port_PinModeType mode;
    uint8 initial_value; 
    Port_PinDirection_changeability changeability_direction;
    Port_PinMode_changeability changeability_mode;
}Port_ConfigSpecs;
/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 *      5. set the mode of pin 
 *      6. set Pin direction changeable or not during runtime
 *      7. set Pin mode changeable or not during runtime
 *      8. set initial value in case of OUTPUT pin 
 */
typedef struct Port_ConfigType
{
 Port_ConfigSpecs channels[MAX_PORT_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function for PORT Initialization API */
void Port_Init(const Port_ConfigType* ConfigPtr);

/* Function for Sets the port pin direction */
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction); 

/* Refreshes port direction*/
void Port_RefreshPortDirection(void);

/* Sets the port pin mode*/
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);

/* Returns the version information of this module*/ 
#if (DIO_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo); 
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;

/*******************************************************************************
 *                       defines of pins and ports in MCU                                *
 *******************************************************************************/
#ifndef PORTA
#define PORTA 0 
#endif 
#ifndef PORTB
#define PORTB 1
#endif
#ifndef PORTC
#define PORTC 2
#endif
#ifndef PORTD
#define PORTD 3
#endif
#ifndef PORTE
#define PORTE 4
#endif
#ifndef PORTF
#define PORTF 5
#endif

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 0
#define PIN9 1
#define PIN10 2
#define PIN11 3
#define PIN12 4
#define PIN13 5
#define PIN14 6
#define PIN15 7
#define PIN16 4
#define PIN17 5
#define PIN18 6
#define PIN19 7
#define PIN20 0
#define PIN21 1
#define PIN22 2
#define PIN23 3
#define PIN24 4
#define PIN25 5
#define PIN26 6
#define PIN27 7
#define PIN28 0
#define PIN29 1
#define PIN30 2
#define PIN31 3
#define PIN32 4
#define PIN33 5
#define PIN34 0
#define PIN35 1
#define PIN36 2
#define PIN37 3
#define PIN38 4
/**********************************************************************************************************************
 *                       defines of array of pins and each pin contain its supported mode in the reg uint16                               *
 **********************************************************************************************************************/
#endif /* Port_H */
