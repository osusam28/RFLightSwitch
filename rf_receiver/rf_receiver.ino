#include <VirtualWire.h>

const int led_pin = 13;
const int receive_pin = 2;
const int relay_pin = 11;

bool toggle = false;

void setup()
{
    // Initialise the IO and ISR
    vw_set_rx_pin(receive_pin);
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

    pinMode(led_pin, OUTPUT);
    pinMode(relay_pin, OUTPUT);
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    char c;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        for (int i = 0; i < buflen; i++)
	{
	    c = (char)buf[i];
	}
        if(c == 's')
        {
          digitalWrite(led_pin, HIGH);
          toggle = !toggle;
          if(toggle == true)
          {
            digitalWrite(relay_pin, HIGH);
          }
          else
          {
            digitalWrite(relay_pin, LOW);
          }
          digitalWrite(led_pin, LOW);
        }
    }
}
