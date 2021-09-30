# Resolución de ejercicio E4 de Guia de ejercitación de RTOS de CESE (2021)
Autor:
Fernando Prokopiuk <fernandoprokopiuk@gmail.com>

Escribir un programa tres tareas:

Tarea 1: Medirá la pulsación de 2 teclas, aplicando anti-rebote. La tecla 1, incrementará un contador (C1) y la tecla 2 lo decrementará (como si fuera un control de volumen). Valor mínimo de C1 = 100. Valor máximo de C1 = 900. Valor inicial C1 = 500. Incrementos/Decrementos de 100 ms.

Tarea 2: Destellará el LED0 con un período de C1 ms (duty cycle 50%).

Tarea 3: Destellará el LED1 con un periodo fijo de 2 s y un tiempo de encendido de 2xC1 ms. En cada ciclo, deberá decrementar C1 en 100.

El tiempo medido se puede comunicar entre tareas a través de una variable global, protegiendo sus operaciones dentro de una sección crítica.



