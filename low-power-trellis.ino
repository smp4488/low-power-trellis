// Low power mode code found here http://donalmorrissey.blogspot.com/2010/04/putting-arduino-diecimila-to-sleep.html

//Low Power
#include <avr/sleep.h>
#include <avr/power.h>
//Trellis
#include <Wire.h>
#include <Adafruit_Trellis.h>
Adafruit_Trellis trellis = Adafruit_Trellis();

int pin2 = 2;


/***************************************************
 *  Name:
 *
 *  Description: Service routine for pin2 interrupt
 *
 ***************************************************/
void pin2Interrupt(void)
{
  /* This will bring us back from sleep. */

  /* We detach the interrupt to stop it from
   * continuously firing while the interrupt pin
   * is low.
   */
  detachInterrupt(0);
}


/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Enters the arduino into sleep mode.
 *
 ***************************************************/
void enterSleep(void)
{

  /* Setup pin2 as an interrupt and attach handler. */
  attachInterrupt(0, pin2Interrupt, LOW);
  delay(100);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  sleep_enable();

  sleep_mode();

  /* The program will continue from here. */

  /* First thing to do is disable sleep. */
  sleep_disable();
}


/***************************************************
 *  Name:        setup
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Setup for the Arduino.
 *
 ***************************************************/
void setup()
{
  Serial.begin(9600);
  Serial.println("Begin Setup");
  // Trellis setup
  trellis.begin(0x70);
  //Test led
  trellis.setLED(0);
  trellis.writeDisplay();
  //trellis.sleep();
  /* Setup the pin direction. */
  pinMode(pin2, INPUT);
  digitalWrite(pin2, HIGH);

  Serial.println("Initialisation complete.");
}



/***************************************************
 *  Name:        loop
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Main application loop.
 *
 ***************************************************/
int seconds=0;
void loop()
{
  delay(1000);
  seconds++;
  Serial.print("Awake for ");
  Serial.print(seconds, DEC);
  Serial.println(" second");

  if(seconds == 3)
  {
     //Sleep Trellis
    //trellis.setLED(0);
    //trellis.writeDisplay();
    //delay(1000);
    trellis.sleep();
    Serial.println("Entering sleep");
    delay(200);
    seconds = 0;
    enterSleep();
  }

}
