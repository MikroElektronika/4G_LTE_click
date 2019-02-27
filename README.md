![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# 4G_LTE Click

- **CIC Prefix**  : C4GLTE
- **Author**      : MikroE Team
- **Verison**     : 1.0.0
- **Date**        : Jan 2018.

---

### Software Support

We provide a library for the 4G_LTE Click on our [LibStock](${LIBSTOCK_LINK}) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library carries generic command parser adopted for AT command based modules. 
Generic parser 

Key functions :

- ``` c4glte_cmdSingle ``` - Sends provided command to the module
- ``` c4glte_setHandler ``` - Handler assignation to the provied command
- ``` c4glte_modulePower ``` - Turn on module

**Examples Description**

Example demo application waits for the call, after call is received the parser will 
get hangup call.

This code snippet shows how generic parser should be properly initialized. 
Before intialization module must be turned on and additionaly to that hardware 
flow control should be also 

Commands :
- First command negotiates baud rate with module
- Second command turns echo off 
- Third command enables hardware flow control - necessary in case of UART polling
- Fourth command setup default message foramt

```.c

// MODULE POWER ON
    c4glte_hfcEnable( true );
    c4glte_modulePower( true );

// MODULE INIT
    c4glte_cmdSingle( "AT" );
    c4glte_cmdSingle( "ATE0" );
    c4glte_cmdSingle( "AT+IFC=2,2" );
    c4glte_cmdSingle( "AT+CMGF=1" );

```

Alongside with the demo application timer initialization functions are provided.
Note that timer is configured acording to default develoment system and 
MCUs, changing the system or MCU may require update of timer init and timer ISR 
functions.

The full application code, and ready to use projects can be found on our 
[LibStock](${LIBSTOCK_LINK}) page.

Other mikroE Libraries used in the example:

- String
- Conversion

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
