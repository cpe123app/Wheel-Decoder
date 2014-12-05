#include "SensorSet.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

class Controller 
{
    private:
        int intMem[32];
        String strMem[16];
        int pinOne;
        int pinTwo;
        SoftwareSerial BTSerial;
    public:
        Controller();
        SensorSet sensor;


        String getString();
        int getInteger();

        void storeInt();
        void storeString();

        void add();
        void subtract();
        void multiply();
        void divide();

        void printBTStrVal();
        void printBTIntVal();
        void printBTLoc();
        
        void printSerialStrVal();
        void printSerialIntVal();
        void printSerialLoc();
        
        void playSound();
        
        void jumpIfEqual();
        void jumpIfNotEqual();
        
        void pinOneRead();
        void pinTwoRead();
        void pinOneOn();
        void pinTwoOn();
        void pinOneOff();
        void pinTwoOff();
        void setPinOneInput();
        void setPinTwoInput();
        void setPinOneOutput();
        void setPinTwoOutput();
};
