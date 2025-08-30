/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xSemaphore1 = NULL;
SemaphoreHandle_t xSemaphore2 = NULL;
SemaphoreHandle_t xSemaphore3 = NULL;

void Task1(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore1, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 1] Executou - SthefanieAiko\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); // 1 segundo
            xSemaphoreGive(xSemaphore2); // Libera Tarefa 2
        }
    }
}

void Task2(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore2, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 2] Executou - SthefanieAiko\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); // 1 segundo
            xSemaphoreGive(xSemaphore3); // Libera Tarefa 3
        }
    }
}

void Task3(void *pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore3, portMAX_DELAY) == pdTRUE)
        {
            printf("[Tarefa 3] Executou - SthefanieAiko\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); // 1 segundo
            xSemaphoreGive(xSemaphore1); // Volta para Tarefa 1
        }
    }
}

void app_main(void)
{
    // Criação dos semáforos binários
    xSemaphore1 = xSemaphoreCreateBinary();
    xSemaphore2 = xSemaphoreCreateBinary();
    xSemaphore3 = xSemaphoreCreateBinary();

    if (xSemaphore1 == NULL || xSemaphore2 == NULL || xSemaphore3 == NULL)
    {
        printf("Falha ao criar semáforos\n");
        return;
    }

    // Criação das 3 tarefas
    xTaskCreate(Task1, "Task1", 2048, NULL, 5, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 5, NULL);
    xTaskCreate(Task3, "Task3", 2048, NULL, 5, NULL);

    // Libera inicialmente a Tarefa 1
    xSemaphoreGive(xSemaphore1);
}
