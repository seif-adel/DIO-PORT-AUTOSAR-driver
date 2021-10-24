/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Seif Adel
 ******************************************************************************/
#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)   
#include "Det.h"

/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != Port_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != Port_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != Port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif 

uint16 ALL_PINS_MODES[MAX_PORT_PINS] = {
  0x0103,/* PIN0 */
  0x0103,/* PIN1 */
  0x0005,/* PIN2 */
  0x0005,/* PIN3 */
  0x0005,/* PIN4 */
  0x0005,/* PIN5 */
  0x0029,/* PIN6 */
  0x0029,/* PIN7 */
  0x0083,/* PIN8 */
  0x0083,/* PIN9 */
  0x0089,/* PIN10 */
  0x0089,/* PIN11 */
  0x0195,/* PIN12 */
  0x0195,/* PIN13*/
  0x0095,/* PIN14 */
  0x0095,/* PIN15 */
  0x01D7,/* PIN16 */
  0x01D7,/* PIN17 */
  0x01C3,/* PIN18 */
  0x0183,/* PIN19 */
  0x00BF,/* PIN20 */
  0x00BF,/* PIN21 */
  0x0197,/* PIN22 */
  0x01C7,/* PIN23 */
  0x0083,/* PIN24 */
  0x0083,/* PIN25 */
  0x00D3,/* PIN26 */
  0x01C3,/* PIN27 */
  0x0003,/* PIN28 */
  0x0003,/* PIN29 */
  0x0001,/* PIN30 */
  0x0001,/* PIN31 */
  0x013B,/* PIN32 */
  0x013B,/* PIN33 */
  0x03EF,/* PIN34 */
  0x42E7,/* PIN35 */
  0x40B5,/* PIN36 */
  0x40AD,/* PIN37 */
  0x01E1,/* PIN38 */
}; 
STATIC const Port_ConfigSpecs * Port_PortChannels = NULL_PTR;   /* point to the array of channels*/  
uint8 Port_Status = PORT_NOT_INITIALIZED;
/*volatile const PIN_ACCESS * PIN_ACCESS_Ptr = NULL_PTR;     * point to the required mode array * */
volatile uint32 * PortGpio_Ptr = NULL_PTR;     /* point to the required Port Registers base address */
/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port module.
************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* check if the input configuration pointer is not a NULL_PTR */
  if (NULL_PTR == ConfigPtr)
  {
          Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_Init_SID,
               PORT_E_PARAM_CONFIG);             
  }
  else
#endif
  {
    /*
     * Set the module state to initialized and point to the PB configuration structure using a global pointer.
     * This global pointer is global to be used by other functions to read the PB configuration structures
     */
    Port_Status       = PORT_INITIALIZED;
    Port_PortChannels = ConfigPtr->channels;     /* address of the first Channels structure --> Channels[0] */        
    /* Enable clock for all pins and allow time for clock to start*/
    volatile uint32 delay = 0;
    SYSCTL_REGCGC2_REG |= 0x0000003f;
    delay = SYSCTL_REGCGC2_REG;
/*******************************************************************************************************************************************************************
                                               FOR LOOP TO ITERATE 39 ITERATION FOR 39 PINS 
******************************************************************************************************************************************************************/                
    for(int i=0 ; i<MAX_PORT_PINS ; i++)
    {
     switch((Port_PortChannels+i)->port_num)
     {
      case PORTA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
      break ;
      case PORTB : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
      break ;
      case PORTC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
      break ;
      case PORTD : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
      break ;
      case PORTE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
      break ;
      case PORTF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
      break ;
     }
     /* the output of previuos block is pointer to the base address of the pin */                         
/****************************************************************************************************************************************************
                                               THE BLOCK TO SET THE MODE OF BIN 
***************************************************************************************************************************************************/
     if((Port_PortChannels+i)->mode == DIO)
      {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((Port_PortChannels+i)->pin_num));     /* Clear the PMCx bits for this pin */
      }
     else if ((Port_PortChannels+i)->mode == ADC )
       {
         /* Do nothing */
       }
     else 
      {
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) \
        = *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & (0xFFFFFFF0 << ((Port_PortChannels+i)->pin_num))\
        | ( (0x00000000+(Port_PortChannels+i)->mode) << ((Port_PortChannels+i)->pin_num));
      }                           
/*******************************************************************************************************************************************************************
                                               THE BLOCK TO SPECIAL CONFIGUARTIONS FOR PIN PD7 AND PF0
******************************************************************************************************************************************************************/                    
      if( ((Port_PortChannels+i)->pin_num ==PIN27 && (Port_PortChannels+i)->port_num == PORTD) || ((Port_PortChannels+i)->pin_num ==PIN34 && (Port_PortChannels+i)->port_num == PORTF) ) /* PD7 or PF0 */
      {
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) ,(Port_PortChannels+i)->pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
      }
      else 
      {
        /* Do nothing */
      }             
/*******************************************************************************************************************************************************************
                                               THE BLOCK FOR CONFIGURATIONS RELATED TO DIGITAL OR ANALOG
******************************************************************************************************************************************************************/
     if((Port_PortChannels+i)->mode!= ADC) 
     {
       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (Port_PortChannels+i)->pin_num) ; /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (Port_PortChannels+i)->pin_num); /* enable digital mode for this pin*/ 
     }
     else 
     {
       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (Port_PortChannels+i)->pin_num) ; /* set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (Port_PortChannels+i)->pin_num); /* disable digital mode for this pin*/ 
     }
/*******************************************************************************************************************************************************************
                                               THE BLOCK FOR SET ALTERNATIVE FUNCTION OR NOT
******************************************************************************************************************************************************************/  
     if((Port_PortChannels+i)->mode!= DIO)
     {
       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , (Port_PortChannels+i)->pin_num); /* enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
     }
     else 
     {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , (Port_PortChannels+i)->pin_num); /* disable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
     }     
/*******************************************************************************************************************************************************************
                                               THE BLOCK TO CONFIGURE THE INPUT PIN 
******************************************************************************************************************************************************************/
      if((Port_PortChannels+i)->direction ==INPUT) 
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
       /* this block for input bin and internal pull up*/
        if((Port_PortChannels+i)->resistor ==PULL_UP) 
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
        }
        /* this block for input bin and internal pull down*/
        else if ((Port_PortChannels+i)->resistor ==PULL_DOWN) 
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
        }
        /* this block for input bin and no activation for internal resistor*/
        else 
        {
          /* Do nothing */
        }
      }
/****************************************************************************************************************************************************
                                               THE BLOCK TO CONFIGURE THE OUTPUT PIN 
***************************************************************************************************************************************************/
      else 
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
        /* this block for output bin initial value 1*/
        if ((Port_PortChannels+i)->initial_value ==STD_ON) 
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
        }
        /* this block for output bin initial value 0*/
        else 
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
        }
      }
/****************************************************************************************************************************************************
                                                  END OF THE BLOCK
***************************************************************************************************************************************************/                    
    }
    /* end of for loop */
    Port_PortChannels = ConfigPtr->channels;     /* return the global pointer to address of the first Channels structure --> Channels[0] */                
  }
}
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in):  - Pin --> Port Pin ID number
*                   - Direction --> Port Pin Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to change the direction of pin.
************************************************************************************/
#if (PortSetPinDirectionApi == STD_ON)
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
  boolean error = FALSE; 
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* check if the port driver is not initialized*/
      if (Port_Status == PORT_NOT_INITIALIZED)
      {
              Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinDirection_SID,
                   PORT_E_UNINIT);
              error = TRUE;    
      }
      /* check if the input configuration pin is not valid ID pin */
      if (MAX_PORT_PINS <= Pin)
      {
              Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinDirection_SID,
                   PORT_E_PARAM_PIN);
              error = TRUE;      
      }
      /* check if the input configuration pin direction is not changable */
      if (((Port_PortChannels+Pin)-> changeability_direction) == UNCHANGABLE )
      {
              Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinDirection_SID,
                   PORT_E_DIRECTION_UNCHANGEABLE);
              error = TRUE;    
      }
    #endif
      if(error == FALSE)
      { 
         switch((Port_PortChannels+Pin)->port_num)
         {
          case PORTA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
          break ;
          case PORTB : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
          break ;
          case PORTC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
          break ;
          case PORTD : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
          break ;
          case PORTE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
          break ;
          case PORTF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
          break ;
         }
        /* the output of previuos block is pointer to the base address of the pin */
            if(Direction ==INPUT) 
           {
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , (Port_PortChannels+Pin)->pin_num);
           }
            else 
           {
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , (Port_PortChannels+Pin)->pin_num);     
           }
      }
      else 
      {
        /* Do nothing*/
      }
}
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in):  - Pin --> Port Pin ID number
*                   - Mode --> Port Pin Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to sets the port pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{ 
  boolean error = FALSE ;
   #if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* check if the port driver is not initialized*/
        if (Port_Status == PORT_NOT_INITIALIZED)
        {
                Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinMode_SID,
                     PORT_E_UNINIT);
                error = TRUE;     
        }          
        if (MAX_PORT_PINS <= Pin)
        {
                Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinMode_SID,
                     PORT_E_PARAM_PIN);
                error = TRUE;      
        }    
        /* check if the input configuration pin mode is not changable */
        if (((Port_PortChannels+Pin)-> changeability_mode) == UNCHANGABLE_MODE )
        {
                Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinMode_SID,
                     PORT_E_MODE_UNCHANGEABLE);
                error = TRUE;     
        }
        
        if(BIT_IS_clear(ALL_PINS_MODE[Pin],(1<<(Port_PortChannels+Pin)->Mode)) /* mode is not valid*/
        { 
              Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_Init_SID,
                   PORT_E_PARAM_INVALID_MODE);
              error = TRUE; 
        }         
  #endif                 
  if(error == FALSE)
  {  
    switch((Port_PortChannels+Pin)->port_num)
    {
    case PORTA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
    break ;
    case PORTB : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
    break ;
    case PORTC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
    break ;
    case PORTD : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
    break ;
    case PORTE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
    break ;
    case PORTF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
    break ;
    }
  /* the output of previuos block is pointer to the base address of the pin */
    
    if(Mode == DIO) // this if to configure mode in case of the input is DIO 
    {
      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((Port_PortChannels+Pin)->pin_num));     /* Clear the PMCx bits for this pin */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (Port_PortChannels+Pin)->pin_num) ; /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (Port_PortChannels+Pin)->pin_num); /* enable digital mode for this pin*/    
    }   
    else if(Mode == ADC)// this else if to configure mode in case of the input is ADC 
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (Port_PortChannels+Pin)->pin_num) ; /* set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (Port_PortChannels+Pin)->pin_num); /* disable digital mode for this pin*/ 
    }
    else // this else to configure mode in case of the input is not DIO or ADC  
    {
       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) \
      = *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & (0xFFFFFFF0 << ((Port_PortChannels+Pin)->pin_num))\
      |  (0x00000000+Mode << ((Port_PortChannels+Pin)->pin_num));
      
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (Port_PortChannels+Pin)->pin_num) ; /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (Port_PortChannels+Pin)->pin_num); /* enable digital mode for this pin*/ 
    }   
  }  
  else 
  {
    /* Do nothing*/
  }
}       
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in):  None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function refresh all the unchangable pins .
************************************************************************************/
void Port_RefreshPortDirection(void)
{
  boolean error = FALSE;
 #if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* check if the port driver is not initialized*/
  if (Port_Status == PORT_NOT_INITIALIZED)
  {
          Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinMode_SID,
               PORT_E_UNINIT);
          error = TRUE;     
  } 
 #endif
  if(error == FALSE)
  {
   for(int i=0 ; i<MAX_PORT_PINS ; i++)
   {
     if( (Port_PortChannels +i)->changeability_direction == UNCHANGABLE ) 
     {
       switch((Port_PortChannels+i)->port_num)
       {
        case PORTA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
        break ;
        case PORTB : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
        break ;
        case PORTC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
        break ;
        case PORTD : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
        break ;
        case PORTE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
        break ;
        case PORTF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
        break ;
       }
        /* the output of previuos block is pointer to the base address of the pin */
        if((Port_PortChannels +i)->direction == INPUT ) 
           {
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , (Port_PortChannels+i)->pin_num);
           }
        else 
           {
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , (Port_PortChannels+i)->pin_num);     
           }
     }
     else 
     {
       /* Do nothing */
     }
   } /* end of for loop */
  }
  else 
  {
    /* Do nothing */
  }
}
 /************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to get the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif