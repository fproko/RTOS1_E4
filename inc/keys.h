/*=============================================================================
 * Copyright (c) 2021, Franco Bucafusco <franco_bucafusco@yahoo.com.ar>
 * 					   Martin N. Menendez <mmenendez@fi.uba.ar>
 * All rights reserved.
 * License: Free
 * Date: 2021/10/03
 * Version: v1.2
 *===========================================================================*/

#ifndef KEYS_H_
#define KEYS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "sapi.h"

/* public macros ================================================================= */
#define KEYS_INVALID_TIME   -1
#define C1_MS 500
#define C1 pdMS_TO_TICKS(C1_MS)
#define C1_MAX_MS 900
#define C1_MAX pdMS_TO_TICKS(C1_MAX_MS)
#define C1_MIN_MS 100
#define C1_MIN pdMS_TO_TICKS(C1_MIN_MS)
#define INCREMENTO_MS 100
#define INCREMENTO pdMS_TO_TICKS(100)
#define DECREMENTO_MS 100
#define DECREMENTO pdMS_TO_TICKS(100)
/* types ================================================================= */
typedef enum
{
    STATE_BUTTON_UP,
    STATE_BUTTON_DOWN,
    STATE_BUTTON_FALLING,
    STATE_BUTTON_RISING
} keys_ButtonState_t;

typedef struct
{
    gpioMap_t btn;			//config
} t_key_config;

typedef struct
{
    keys_ButtonState_t state;   //variables
    TickType_t time_down;		//timestamp of the last High to Low transition of the key
    TickType_t time_up;		    //timestamp of the last Low to High transition of the key
    TickType_t time_diff;	    //variables
} t_key_data;

/* methods ================================================================= */
void keys_Init( void );
TickType_t get_diff( uint32_t index );
void clear_diff( uint32_t index );
TickType_t getC1(void);
void incrementCounter(void);
void decrementCounter(void);

#endif /* PDM_ANTIRREBOTE_MEF_INC_DEBOUNCE_H_ */
