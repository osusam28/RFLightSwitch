#include <LowPower.h>
#include <avr/sleep.h>
#include <VirtualWire.h>

int led_pin = 13;
const int transmit_pin = 3;
const int button_pin = 2;
const int button_led = 10;

void setup()
{
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);
  pinMode(led_pin, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(button_led, OUTPUT);
  digitalWrite(button_led, HIGH);
  interrupts();
}

byte count = 1;
bool button_pressed = false;

void loop()
{
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  sleep_enable();
  
  attachInterrupt(0, awake, LOW);
  
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
//  sleep_mode();
  
  detachInterrupt(0);
  
  char msg[1] = {'s'};
  
  if(digitalRead(button_pin) == HIGH && button_pressed == false)
  {
    digitalWrite(button_led, LOW); 
    digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, 1);
    vw_wait_tx(); // Wait until the whole message is gone
    delay(100);
    digitalWrite(button_led, HIGH);
    digitalWrite(led_pin, LOW);
    button_pressed = true;
    delay(500);
  }
  
  if(digitalRead(button_pin) == LOW)
  {
    button_pressed = false;
  }
}

void awake()
{
  
}
