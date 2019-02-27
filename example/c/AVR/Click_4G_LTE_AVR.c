/*
Example for 4G_LTE Click

    Date          : Jan 2018.
    Author        : MikroE Team

Test configuration AVR :
    
    MCU              : ATMEGA32
    Dev. Board       : EasyAVR v7 
    AVR Compiler ver : v7.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes all necessary GPIO pins, UART used for
the communcation with GSM module and UART used for infromation logging
- Application Initialization - Initializes driver, power on module and sends few
command for the default module configuration
- Application Task - running in parallel core state machine and checks for call flag. 
If call detected parser will hang up call.

Additional Functions :

All additional functions such as timer initialization and default handler. 

Notes :

- Echo must be turned off for succefull parsing. ( ATE0 )
- UART polling works much better with HFC enabled.
- In case of usage of other MCUs Timer initialization must be adjusted according to your MCU.

*/

#define __4G_LTE__

#include "Click_4G_LTE_types.h"
#include "Click_4G_LTE_config.h"
#include "Click_4G_LTE_timer.h"

static uint8_t callFlag;

void c4glte_default_handler( uint8_t *rsp, uint8_t *evArgs )
{
    mikrobus_logWrite( rsp, _LOG_TEXT );

//  SKIP <CR> and <LF>
    if (0 == strncmp("RING", rsp + 2, 4))
    {
        callFlag = 1;
    }
}

void systemInit()
{
    callFlag = 0;
    
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_uartInit( _MIKROBUS1, &_C4GLTE_UART_CFG[0] );
//    mikrobus_logInit( _MIKROBUS2, 9600 );
}

void applicationInit()
{
// TIMER INIT
    c4glte_configTimer();

// DRIVER INIT
    c4glte_uartDriverInit((T_C4GLTE_P)&_MIKROBUS1_GPIO, (T_C4GLTE_P)&_MIKROBUS1_UART);
    c4glte_coreInit( c4glte_default_handler, 1500 );

// MODULE POWER ON
    c4glte_hfcEnable( true );
    c4glte_modulePower( true );

// MODULE INIT
    c4glte_cmdSingle( "AT" );
    c4glte_cmdSingle( "AT" );
    c4glte_cmdSingle( "AT" );
    c4glte_cmdSingle( "ATE0" );
    c4glte_cmdSingle( "AT+IFC=2,2" );
    c4glte_cmdSingle( "AT+CMGF=1" );
}

void applicationTask()
{
// CORE STATE MACHINE
    c4glte_process();

    if (0 != callFlag)
    {
        c4glte_cmdSingle( "ATH" );
        Delay_ms( 3000 );

        callFlag = 0;
    }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}

/* -------------------------------------------------------------------------- */