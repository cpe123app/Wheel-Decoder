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

void Controller::storeInt() {
    int memPtr = sensor.getInt();
    int value = getInteger();
    if (memPtr >= 0 && memPtr < 32) {
        intMem[memPtr] = value;
    }
}

void Controller::storeString() {
    int memPtr = sensor.getInt();
    String value = getString();
    if (memPtr >= 0 && memPtr < 16) {
        strMem[memPtr] = value;
    }
}

void Controller::printBTStrVal(){ 
    BTSerial.println(strMem[sensor.getInt()]);
}

void Controller::printBTIntVal(){
    BTSerial.println(intMem[sensor.getInt()]);
}

void Controller::printBTLoc(){
    int loc = sensor.getInt();
    if (loc >= 32){
        BTSerial.println(strMem [loc-32]);
    }else{
        BTSerial.println(strMem [loc]);    
    }
    
}

void Controller::printSerialStrVal(){
	Serial.println(getString());
    //Serial.println(strMem[sensor.getInt()]);
}

void Controller::printSerialIntVal(){
    Serial.println(getInteger());
}

void Controller::printSerialLoc(){
    int loc = sensor.getInt();
    if (loc >= 32){
        Serial.println(strMem [loc-32]);
    } else {
        Serial.println(intMem [loc]);    
    }
}

void Controller::add(){
    int numa = intMem[sensor.getInt()];
    int numb = intMem[sensor.getInt()];
    intMem[sensor.getInt()] = numa+numb;
}

void Controller::subtract(){
    int numa = intMem[sensor.getInt()];
    int numb = intMem[sensor.getInt()];
    intMem[sensor.getInt()] = numa-numb;    
}

void Controller::multiply(){
    int numa = intMem[sensor.getInt()];
    int numb = intMem[sensor.getInt()];
    intMem[sensor.getInt()] = numa*numb;    
}

void Controller::divide(){
    int numa = intMem[sensor.getInt()];
    int numb = intMem[sensor.getInt()];
    intMem[sensor.getInt()] = numa/numb;    
}

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

void Controller::jumpIfEqual(){
	if (intMem[sensor.getInt()] == intMem[sensor.getInt()]){
		int skip = sensor.getInt();
		for( int i = 0; i < skip; i++) sensor.getInt();
	} else sensor.getInt();
}

void Controller::jumpIfNotEqual(){
	if (intMem[sensor.getInt()] != intMem[sensor.getInt()]){
		int skip = sensor.getInt();
		for( int i = 0; i < skip; i++) sensor.getInt();
	} else sensor.getInt();
}

void Controller::pinOneRead() {
    int location = sensor.getInt();
    intMem[location] = digitalRead(pinOne);
}

void Controller::pinTwoRead() {
    int location = sensor.getInt();
    intMem[location] = digitalRead(pinOne);
}

void Controller::pinOneOn() {
    digitalWrite(pinOne, HIGH);
}

void Controller::pinTwoOn() {
    digitalWrite(pinTwo, HIGH);
}

void Controller::pinOneOff() {
    digitalWrite(pinOne, LOW);
}

void Controller::pinTwoOff() {
    digitalWrite(pinTwo, LOW);
}

void Controller::setPinOneInput() {
    pinMode(pinOne, INPUT_PULLUP);
}

void Controller::setPinTwoInput() {
    pinMode(pinTwo, INPUT_PULLUP);
}

void Controller::setPinOneOutput() {
    pinMode(pinOne, OUTPUT);
}

void Controller::setPinTwoOutput() {
    pinMode(pinTwo, OUTPUT);
}
