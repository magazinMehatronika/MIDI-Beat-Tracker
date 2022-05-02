#include <MIDI.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5







using namespace midi;
MIDI_CREATE_DEFAULT_INSTANCE();

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);


int sync = 0;
int counter = 0;

int modeSel = 0;

bool enabler = false;

void setup()
{
    MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages

    delay(250); // wait for the OLED to power up
    display.begin(0x3C, true); // Address 0x3C default
    display.setRotation(1);

    
    display.clearDisplay();


    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);

}

void loop()
{

   digitalWrite(LED_BUILTIN, LOW);

  if(!digitalRead(BUTTON_A)) modeSel = 0;
  if(!digitalRead(BUTTON_B)) modeSel = 1;
  if(!digitalRead(BUTTON_C)) modeSel = 2;
   

   if(MIDI.read()){
            switch(MIDI.getType()){      // Get the type of the message we caught

            case Start:

            enabler = true;

            sync = 0;
            counter = 0;
            break;

            case Stop:

            enabler = false;

            display.clearDisplay();
            display.display();

            sync = 0;
            counter = 0;

            break;
            
            case Clock:
            if (enabler == true){
            
            if (sync == 0){

            switch (counter){

             case 0:
              display.clearDisplay();
              
              display.setTextSize(4,8);
              display.setTextColor(SH110X_WHITE);
              display.setCursor(0,0);

              switch(modeSel){
                case 0:
                display.print("One");
                break;
                case 1:
                display.print("Je'n");
                break;
                case 2:
                display.print("Ja--");
                break;
              }
              

              display.display();
              counter++;
              break;

              case 1:
              display.clearDisplay();


              display.setTextSize(4,8);
              display.setTextColor(SH110X_WHITE);
              display.setCursor(0,0);

              switch(modeSel){
                case 0:
                display.print("Two");
                break;
                case 1:
                display.print("Dva");
                break;
                case 2:
                display.print("--pa");
                break;
              }
              display.display();
              counter++;
              break;

              case 2:
              display.clearDisplay();

              display.setTextSize(4,8);
              display.setTextColor(SH110X_WHITE);
              display.setCursor(0,0);

              switch(modeSel){
                case 0:
                display.print("Three");
                break;
                case 1:
                display.print("Tri");
                break;
                case 2:
                display.print("pa--");
                break;
              }
              display.display();
              counter++;
              break;

              case 3:
              display.clearDisplay();

              display.setTextSize(4,8);
              display.setTextColor(SH110X_WHITE);
              display.setCursor(0,0);

              switch(modeSel){
                case 0:
                display.print("Four");
                break;
                case 1:
                display.print("Cet");
                break;
                case 2:
                display.print("--pa");
                break;
              }
              display.display();
              counter = 0;
              break;
              
            }
            
            digitalWrite(LED_BUILTIN, HIGH);
            delay(10);                // Wait for a second
            digitalWrite(LED_BUILTIN, LOW);
            sync = 24;
            }
            sync--;
            break;
           }

   }
   }
}
