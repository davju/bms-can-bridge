#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

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

void app_main()
{

    int i = 0;

    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 5, NULL);
}
