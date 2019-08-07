#include <Arduino.h>
#include "driver/uart.h"

#define UART_NUM UART_NUM_2

QueueHandle_t uart_queue;
static void uart_init() {
  uart_config_t uart_config = {
      .baud_rate = 115200,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
      .rx_flow_ctrl_thresh = 122,
  };
  // Configure UART parameters
  assert(uart_param_config(UART_NUM, &uart_config) == ESP_OK);
  assert(uart_set_pin(UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) == ESP_OK);
  assert(uart_driver_install(UART_NUM, 256, 1024, 10, &uart_queue, 0) == ESP_OK);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  uart_init();
  pinMode(13, OUTPUT);
}

uint8_t i = 0;
void loop() {
  const char i_ = i;
  uart_tx_chars(UART_NUM, &i_, 1);
  uart_wait_tx_done(UART_NUM, -1);

  Serial.print('A');
  digitalWrite(13, i & 1);
  i++;
  delayMicroseconds(100);
}