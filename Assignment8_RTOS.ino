#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED 8
#define YELLOW 9
#define GREEN 10
#define SW1 5
#define SW2 6
#define SW3 7

QueueHandle_t blinkQueue;
int GREEN_status;

void setup() {
  Serial.begin(9600);
  blinkQueue = xQueueCreate(10, sizeof(int32_t));
  xTaskCreate(vSenderTask, "Red Sender Task", 100, SW1, 1, NULL);
  xTaskCreate(vSenderTask, "Yellow Sender Task", 100, SW2, 1, NULL);
  xTaskCreate(vSenderTask, "Green Sender Task", 100, SW3, 1, NULL);
  xTaskCreate(vReceiverTask, "Red Receiver Task", 100, RED, 1, NULL);
  xTaskCreate(vReceiverTask, "Yellow Receiver Task", 100, YELLOW, 1, NULL);
  xTaskCreate(vReceiverTask, "Green Receiver Task", 100, GREEN, 1, NULL);
}

void vSenderTask(void *pvParameters)
{
  int32_t valueToSend = 0;
  int SW = (int32_t)pvParameters;
  long DELAY_SW3;
  pinMode(SW, INPUT);
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  while (1)
  {
    if (digitalRead(SW) == LOW) {
      valueToSend = SW;
    }
    else {
      valueToSend = 0;
    }
    if (valueToSend) {
      xQueueSend(blinkQueue, &valueToSend, xTicksToWait);
      vTaskDelay(20);
      if (SW == SW3) {
        DELAY_SW3 = millis();
        while (millis() - DELAY_SW3 < 3000);
      }
    }
  }
}

void vReceiverTask(void *pvParameters)
{
  int32_t valueReceived;
  BaseType_t qStatus;
  int LED = (int32_t)pvParameters;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100); //แปลง ms เป็นหน่วย ticks
  pinMode(RED, OUTPUT);
  digitalWrite(RED, HIGH);
  pinMode(YELLOW, OUTPUT);
  digitalWrite(YELLOW, HIGH);
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, HIGH);
  int YELLOW_status = 0;
  long RED_TIME = 0;
  long GREEN_TIME = 0;
  while (1)
  {
    qStatus = xQueueReceive(blinkQueue, &valueReceived, xTicksToWait);
    if (qStatus == pdPASS) {
      if (valueReceived == SW1 && LED == RED) {
        Serial.println("R");
        digitalWrite(RED, LOW);
        RED_TIME = millis();
        while (millis() - RED_TIME < 3000);
        digitalWrite(RED, HIGH);
      }
      else if (valueReceived == SW2 && LED == YELLOW) {
        Serial.println("Y");
        YELLOW_status = !YELLOW_status;
      }
      else if (valueReceived == SW3 && LED == GREEN) {
        Serial.println("G");
        GREEN_status = 1;
        digitalWrite(GREEN, LOW);
        GREEN_TIME = millis();
        while (millis() - GREEN_TIME < 500);
        digitalWrite(GREEN, HIGH);
        GREEN_TIME = millis();
        while (millis() - GREEN_TIME < 500);
        digitalWrite(GREEN, LOW);
        GREEN_TIME = millis();
        while (millis() - GREEN_TIME < 500);
        digitalWrite(GREEN, HIGH);
        GREEN_TIME = millis();
        while (millis() - GREEN_TIME < 500);
        digitalWrite(GREEN, LOW);
        GREEN_TIME = millis();
        while (millis() - GREEN_TIME < 500);
        digitalWrite(GREEN, HIGH);
        GREEN_TIME = millis();
        while (millis() - GREEN_TIME < 500);
        GREEN_status = 0;
      }
      else if (valueReceived == SW3 || GREEN_status == 0) {
        int32_t valueToSend = valueReceived;
        xQueueSend(blinkQueue, &valueToSend, xTicksToWait);
        vTaskDelay(1);
      }
    }
    if (YELLOW_status && LED == YELLOW) {
      digitalWrite(YELLOW, LOW);
      vTaskDelay(10);
      digitalWrite(YELLOW, HIGH);
      vTaskDelay(10);
    }
  }
}

void loop() {}
