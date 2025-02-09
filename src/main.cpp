#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "battery.h"

void hello_task(void *pvParameter)
{
    int i = 0;
    while (1)
    {
        printf("Hello from task! %d\n", i);
        i++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main()
{
    printf("Hello from ESP32-QEMU!\n");
}
