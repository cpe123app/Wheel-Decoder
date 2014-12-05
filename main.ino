#include "controller.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

Controller cpu;


void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int command = cpu.sensor.getInt();
	/**
		1 = storeInt -> location -> value*
		2 = storeString -> location -> value*
		3 = add -> location -> location -> location 
		4 = subtract -> location -> location -> location
		5 = multiply -> location -> location -> location
		6 = divide -> location -> location -> location
		7 = printToSerial -> location*
		8 = printToBT -> location*
		9 = printToSerialStrVal -> value*
		10 = printToBTStrVal -> value*
		11 = printToSerialIntVal -> value*
		12 = printToBTIntVal -> value*
		13 = pinOneRead -> location
		14 = pinOneOff
		15 = pinOneOn
		16 = setPinOneInput
		17 = setPinOneOutput
		18 = pinTwoRead -> location
		19 = pinTwoOn
		20 = pinTwoOff
		21 = setPinTwoInput
		22 = setPinTwoOutput
		23 = jumpifequals
		24 = jumpifnotequal
		music -> notes* //maybe
		* = goUntilBreak (63 (0b111111))
	**/
	switch(command)
	{
		case 1:
			cpu.storeInt();
		    break;
		case 2:
			cpu.storeString();
		    break;
		case 3:
			cpu.add();
		    break;
		case 4:
			cpu.subtract();
		    break;
		case 5:
			cpu.multiply();
		    break;
		case 6:
			cpu.divide();
		    break;
		case 7:
			cpu.printSerialLoc();
		    break;
		case 8:
			cpu.printBTLoc();
		    break;
		case 9:
			cpu.printSerialStrVal();
		    break;
		case 10:
			cpu.printBTStrVal();
		    break;
		case 11:
			cpu.printSerialIntVal();
		    break;
		case 12:
			cpu.printBTIntVal();
		    break;
		case 13:
			cpu.pinOneRead();
		    break;
		case 14:
			cpu.pinOneOff();
		    break;
		case 15:
			cpu.pinOneOn();
		    break;
		case 16:
			cpu.setPinOneInput();
		    break;
		case 17:
			cpu.setPinOneOutput();
		    break;
		case 18:
			cpu.pinTwoRead();
		    break;
		case 19:
			cpu.pinTwoOff();
		    break;
		case 20:
			cpu.pinTwoOn();
		    break;
		case 21:
			cpu.setPinTwoInput();
		    break;
		case 22:
			cpu.setPinTwoOutput();
		    break;
		case 23:
			cpu.jumpIfEqual();
			break;
		case 24:
			cpu.jumpIfNotEqual();
		case 63:
			// break everything!
		    break;
	}


}
