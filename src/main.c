/*=============================================================================
 * Copyright (c) 2021, Franco Bucafusco <franco_bucafusco@yahoo.com.ar>
 * 					   Martin N. Menendez <mmenendez@fi.uba.ar>
 * All rights reserved.
 * License: Free
 * Date: 2021/10/03
 * Version: v1.2
 *===========================================================================*/

/*==================[inclusiones]============================================*/
#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"

#include "FreeRTOSConfig.h"
#include "keys.h"
/*==================[definiciones y macros]==================================*/
#define LED2_RATE_MS 2000
#define LED2_RATE pdMS_TO_TICKS(LED2_RATE_MS)

#define WELCOME_MSG  "Ejercicio E_4.\r\n"
#define USED_UART UART_USB
#define UART_RATE 115200
#define MALLOC_ERROR "Malloc Failed Hook!\n"
#define MSG_ERROR_SEM "Error al crear los semaforos.\r\n"
#define LED_ERROR LEDR
/*==================[definiciones de datos internos]=========================*/
gpioMap_t leds_t[] = {LED1,LED2};
gpioMap_t gpio_t[] = {GPIO7,GPIO5,GPIO3,GPIO1};

/*==================[definiciones de datos externos]=========================*/
DEBUG_PRINT_ENABLE;

extern t_key_config keys_config[];
extern TickType_t c1;

#define LED_COUNT   sizeof(leds_t)/sizeof(leds_t[0])
#define GPIO_COUNT  sizeof(gpio_t)/sizeof(gpio_t[0])
/*==================[declaraciones de funciones internas]====================*/
void gpio_init( void );

/*==================[declaraciones de funciones externas]====================*/
TickType_t get_diff();
void clear_diff();

// Prototipo de funcion de la tarea
void tarea_led1( void* taskParmPtr );
void tarea_led2( void* taskParmPtr );
void tarea_tecla( void* taskParmPtr );
/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
    // ---------- CONFIGURACIONES ------------------------------
    boardConfig();									// Inicializar y configurar la plataforma

    gpio_init();

    debugPrintConfigUart( USED_UART, UART_RATE );		// UART for debug messages
    printf( WELCOME_MSG );

    BaseType_t res;

    res = xTaskCreate(
        tarea_led1,                   // Funcion de la tarea a ejecutar
        (const char *)"tarea_led1",   // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
        0,                            // Parametros de tarea
        tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
        0                             // Puntero a la tarea creada en el sistema
    );
    // Gestion de errores
    configASSERT(res == pdPASS);

    res = xTaskCreate(
        tarea_led2,                   // Funcion de la tarea a ejecutar
        (const char *)"tarea_led2",   // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
        0,                            // Parametros de tarea
        tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
        0                             // Puntero a la tarea creada en el sistema
    );
    // Gestion de errores
    configASSERT(res == pdPASS);

    // Inicializo driver de teclas
    keys_Init();

    // Iniciar scheduler
    vTaskStartScheduler();					// Enciende tick | Crea idle y pone en ready | Evalua las tareas creadas | Prioridad mas alta pasa a running

    // ---------- REPETIR POR SIEMPRE --------------------------
    configASSERT( 0 );

    // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
    // directamenteno sobre un microcontroladore y no es llamado por ningun
    // Sistema Operativo, como en el caso de un programa para PC.
    return TRUE;
}

/*==================[definiciones de funciones internas]=====================*/
void gpio_init( void )
{
    for(uint32_t i = 0 ; i < GPIO_COUNT; i++ )
    {
        gpioInit ( gpio_t[i], GPIO_OUTPUT );
    }
}

void tarea_led1( void* taskParmPtr )
{
    //uint32_t index = ( uint32_t ) taskParmPtr;

    // ---------- CONFIGURACIONES ------------------------------
    TickType_t xPeriodicity = c1;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    // ---------- REPETIR POR SIEMPRE --------------------------
    while( TRUE )
    {
        xPeriodicity = getC1();

        gpioWrite(leds_t[0], ON);
        gpioWrite(gpio_t[0], ON);
        vTaskDelay(xPeriodicity >> 1); //Equivalente a dividir por 2
        gpioWrite(leds_t[0], OFF);
        gpioWrite(gpio_t[0], OFF);

        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
    }
}

void tarea_led2( void* taskParmPtr )
{
    //uint32_t index = ( uint32_t ) taskParmPtr;

    // ---------- CONFIGURACIONES ------------------------------
    TickType_t xPeriodicity = LED2_RATE;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    TickType_t c1_tarea_led2;
    // ---------- REPETIR POR SIEMPRE --------------------------
    while( TRUE )
    {
        c1_tarea_led2 = getC1();

        gpioWrite( leds_t[1], ON );
        gpioWrite( gpio_t[1], ON );
        vTaskDelay( c1_tarea_led2<<1); 		//Equivalente a multiplicar por 2
        gpioWrite( leds_t[1], OFF );
        gpioWrite( gpio_t[1], OFF );

        decrementCounter();

        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );

    }
}

/*==================[definiciones de funciones externas]=====================*/

/* hook que se ejecuta si al necesitar un objeto dinamico, no hay memoria disponible */
void vApplicationMallocFailedHook()
{
    printf( MALLOC_ERROR );
    configASSERT( 0 );
}
/*==================[fin del archivo]========================================*/
