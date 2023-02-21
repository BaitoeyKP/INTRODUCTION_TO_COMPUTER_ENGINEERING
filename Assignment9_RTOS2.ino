#include <Arduino_FreeRTOS.h>
#include "queue.h"
#include <semphr.h>

#define RED 8
#define YELLOW 9
#define GREEN 10
#define SW1 5
#define SW2 6
#define SW3 7
#define Semaphore_Y 0
#define Semaphore_G 1
#define Time 1

QueueHandle_t blinkQueue;
SemaphoreHandle_t xBinarySemaphore[2];

long dTime = 0;
size_t debounce = 200;

void setup()
{
  pinMode(RED, OUTPUT);
  digitalWrite(RED, HIGH);
  pinMode(YELLOW, OUTPUT);
  digitalWrite(YELLOW, HIGH);
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, HIGH);
  xBinarySemaphore[Semaphore_Y] = xSemaphoreCreateBinary();
  xBinarySemaphore[Semaphore_G] = xSemaphoreCreateBinary();
  blinkQueue = xQueueCreate(10, sizeof(int32_t));
  xTaskCreate(vSenderTask, "Sender Task 1", 100, SW1, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 2", 100, SW2, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 3", 100, SW3, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, RED, 1, NULL);
}

void vSenderTask(void *pvParameters)
{
  int32_t valueToSend = 0;
  int SW = (int32_t)pvParameters;
  pinMode(SW, INPUT);
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  int SW_NOW = SW - 6;
  while (1)
  {
    if (SW != SW1)
    {
      if ((digitalRead(SW) == LOW && millis() - dTime > debounce) && xSemaphoreTake(xBinarySemaphore[SW_NOW], Time) == pdTRUE)
      {
        valueToSend = SW;
        xQueueSend(blinkQueue, &valueToSend, xTicksToWait);
        vTaskDelay( pdMS_TO_TICKS( 200 ) );
      }
    }
    else if (digitalRead(SW) == LOW && millis() - dTime > debounce)
    {
      valueToSend = SW;
      xQueueSend(blinkQueue, &valueToSend, xTicksToWait);
      vTaskDelay( pdMS_TO_TICKS( 200 ) );
    }
  }
}

void vReceiverTask(void *pvParameters)
{
  int32_t valueReceived;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100); //แปลง ms เป็นหน่วย ticks
  long RED_TIME = 0;
  long YELLOW_TIME = -2000;
  long GREEN_TIME = 0;
  while (1)
  {
    qStatus = xQueueReceive(blinkQueue, &valueReceived, xTicksToWait);
    if (qStatus == pdPASS)
    {
      if (valueReceived == SW1 && digitalRead(RED) == HIGH)
      {
        digitalWrite(RED, LOW);
        RED_TIME = millis();
      }
      else if (valueReceived == SW1)
      {
        RED_TIME = -3000;
      }
      else if (valueReceived == SW2 && millis() - YELLOW_TIME >= 2000)
      {
        digitalWrite(YELLOW, LOW);
        YELLOW_TIME = millis();
      }
      else if (valueReceived == SW3 && digitalRead(GREEN) == HIGH)
      {
        digitalWrite(GREEN, LOW);
        GREEN_TIME = millis();
      }
      else if (valueReceived == SW3)
      {
        GREEN_TIME = -3000;
      }
    }
    //LED_YELLOW blink
    if (millis() - YELLOW_TIME > 1500)
    {
      digitalWrite(YELLOW, HIGH);
    }
    else if (millis() - YELLOW_TIME > 1000)
    {
      digitalWrite(YELLOW, LOW);
    }
    else if (millis() - YELLOW_TIME > 500)
    {
      digitalWrite(YELLOW, HIGH);
    }
    //LED_RED
    if (millis() - RED_TIME > 3000)
    {
      digitalWrite(RED, HIGH);
    }
    //LED_GREEN
    if (millis() - GREEN_TIME > 3000)
    {
      digitalWrite(GREEN, HIGH);
    }
    //Semaphore
    if (digitalRead(RED) == HIGH)
    {
      if (digitalRead(GREEN) == HIGH)
      {
        xSemaphoreGive(xBinarySemaphore[Semaphore_Y]);
        xSemaphoreGive(xBinarySemaphore[Semaphore_G]);
      }
      else
      {
        xSemaphoreTake(xBinarySemaphore[Semaphore_Y], Time);
        xSemaphoreGive(xBinarySemaphore[Semaphore_G]);
      }
    }
    else
    {
      xSemaphoreTake(xBinarySemaphore[Semaphore_Y], Time);
      xSemaphoreTake(xBinarySemaphore[Semaphore_G], Time);
    }
  }
}

void loop() {}
