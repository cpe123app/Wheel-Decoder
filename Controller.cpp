#include "controller.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

Controller::Controller() : sensor(6, 5, 4, 3, 2, 7, 8), BTSerial(9, 10)
{
    //intMem = {};
    //stringMem = {};
    pinOne = 9; // TODO might change these pins
    pinTwo = 1;
}

// Returns a string built from encoded binary
String Controller::getString()
{
    int curr = sensor.getInt();
    String message = "";
    bool shift = false;
    bool caps = false;
    while (curr != 63) 
    {
        if (curr == 50){
            shift = true;
        }
        else if (curr == 51)
        {
            caps = !caps;
        }
        else
        {       
            if (caps || shift)
            {
            	message = String(message + sensor.getChar(curr, 0));
            }
            else
            {
            	message = String(message + sensor.getChar(curr, 0));
            }
        }
        curr = sensor.getInt();
    } 
    return message;
}

// Returns an integer built from bitwise appendations of read 6-bit integers
int Controller::getInteger(){
    int curr = sensor.getInt();
    curr %= 32;
    int num = 0;    
    int digit = 1;
    while (curr != 63){
        num += curr*digit;
        digit *= 32;
        curr = sensor.getInt();
    }
    return num;
}

// Stores an integer in Controller.intMem, working integer memory
void Controller::storeInt() {
    int memPtr = sensor.getInt();
    int value = getInteger();
    if (memPtr >= 0 && memPtr < 32) {
        intMem[memPtr] = value;
    }
}

// Stores a string in Controller.strMem, working string memory
void Controller::storeString() {
    int memPtr = sensor.getInt();
    String value = getString();
    if (memPtr >= 0 && memPtr < 16) {
        strMem[memPtr] = value;
    }
}

// Prints strings to BTSerial
void Controller::printBTStrVal(){ 
    BTSerial.println(getString());
}

// Prints integers to BTSerial
void Controller::printBTIntVal(){
    BTSerial.println(getInteger());
}

// Prints stored strings to BTSerial
void Controller::printBTLoc(){
    int loc = sensor.getInt();
    if (loc >= 32){
        BTSerial.println(strMem [loc-32]);
    }else{
        BTSerial.println(strMem [loc]);    
    }
    
}

// Prints integers to Serial
void Controller::printSerialStrVal(){
	Serial.println(getString());
    //Serial.println(strMem[sensor.getInt()]);
}

// Prints integers to Serial
void Controller::printSerialIntVal(){
    Serial.println(getInteger());
}

// Prints stored strings to Serial
void Controller::printSerialLoc(){
    int loc = sensor.getInt();
    if (loc >= 32){
        Serial.println(strMem [loc-32]);
    } else {
        Serial.println(intMem [loc]);    
    }
}

// Adds two integers and stores the result
void Controller::add(){
    int numa = intMem[sensor.getInt()];
    int numb = intMem[sensor.getInt()];
    intMem[sensor.getInt()] = numa+numb;
}

// Subtracts two integers and stores the result
void Controller::subtract(){
    int numa = intMem[sensor.getInt()];
    int numb = intMem[sensor.getInt()];
    intMem[sensor.getInt()] = numa-numb;    
}

// Multiplies two integers and stores the result
void Controller::multiply(){
    int numa = intMem[sensor.getInt()];
    int numb = intMem[sensor.getInt()];
    intMem[sensor.getInt()] = numa*numb;    
}

// Divides two integers and stores the result
void Controller::divide(){
    int numa = intMem[sensor.getInt()];
    int numb = intMem[sensor.getInt()];
    intMem[sensor.getInt()] = numa/numb;    
}

// Not implemented in hardware-Plays musical notes
void Controller::playSound() {
    int myPin = sensor.getInt();
    int myNote;
    int freq;
    while (myNote != 0) {
        myNote = sensor.getInt();
        // TODO: Translate ints in {0..63} to notes and play them through the speaker
        // myNote => freq
        int freq = 0;
        tone(myPin, freq, 1000);
    }
}

// Skips N instructions if two stored integers are equal
void Controller::jumpIfEqual(){
	if (intMem[sensor.getInt()] == intMem[sensor.getInt()]){
		int skip = sensor.getInt();
		for( int i = 0; i < skip; i++) sensor.getInt();
	} else sensor.getInt();
}

// Skips N instructions if two stored integers are not equal
void Controller::jumpIfNotEqual(){
	if (intMem[sensor.getInt()] != intMem[sensor.getInt()]){
		int skip = sensor.getInt();
		for( int i = 0; i < skip; i++) sensor.getInt();
	} else sensor.getInt();
}

// digital reads a pin
void Controller::pinOneRead() {
    int location = sensor.getInt();
    intMem[location] = digitalRead(pinOne);
}

// digital reads a different pin
void Controller::pinTwoRead() {
    int location = sensor.getInt();
    intMem[location] = digitalRead(pinOne);
}

// digital write HIGH a pin
void Controller::pinOneOn() {
    digitalWrite(pinOne, HIGH);
}

// digital write HIGH another pin
void Controller::pinTwoOn() {
    digitalWrite(pinTwo, HIGH);
}

// digital write LOW a pin
void Controller::pinOneOff() {
    digitalWrite(pinOne, LOW);
}

// digital write LOW another pin
void Controller::pinTwoOff() {
    digitalWrite(pinTwo, LOW);
}

// sets a pin's pinmode to input
void Controller::setPinOneInput() {
    pinMode(pinOne, INPUT_PULLUP);
}

// sets another pin's pinmode to input
void Controller::setPinTwoInput() {
    pinMode(pinTwo, INPUT_PULLUP);
}

// sets a pin's pinmode to output
void Controller::setPinOneOutput() {
    pinMode(pinOne, OUTPUT);
}

// sets another pin's pinmode to output
void Controller::setPinTwoOutput() {
    pinMode(pinTwo, OUTPUT);
}
