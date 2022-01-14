#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "device.h"
#include "gpio_arduino.h"

static void taskBlinkRed(void* arg)
{
    while (1)
    {
        gpio_set_level(LED_RED, LED_ON);
        printf("%d Hello Red\n", xPortGetCoreID());
        fflush(stdout);
        vTaskDelay(100/portTICK_RATE_MS);
        gpio_set_level(LED_RED, LED_OFF);
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}

static void taskBlinkGreen(void* arg)
{
    while (1)
    {
        gpio_set_level(LED_GREEN, LED_ON);
        printf("%d Hello Green\n", xPortGetCoreID());
        fflush(stdout);
        vTaskDelay(100/portTICK_RATE_MS);
        gpio_set_level(LED_GREEN, LED_OFF);
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}

void app_main() {
    gpio_pinMode(LED_RED, OUTPUT);
    gpio_pinMode(LED_GREEN, OUTPUT);
    xTaskCreate(taskBlinkRed, "BlinkRed", configMINIMAL_STACK_SIZE+1024, NULL, 5, NULL);
    // xTaskCreate(taskBlinkGreen, "BlinkGreen", configMINIMAL_STACK_SIZE+1024, NULL, 5, NULL);
    xTaskCreatePinnedToCore(taskBlinkGreen, "BlinkGreen", configMINIMAL_STACK_SIZE+1024, NULL, 5, NULL,1);
    //vTaskSuspend(NULL);
/*    
    while (1)
    {
        gpio_set_level(LED_RED, LED_ON);
        printf("Hello World\n");
        fflush(stdout);
        vTaskDelay(100/portTICK_RATE_MS);
        gpio_set_level(LED_RED, LED_OFF);
        vTaskDelay(1000/portTICK_RATE_MS);
    }
*/
}