#include "Arduino.h"
#include "SensorSet.h"

const int THRES[] = { 800, 760, 760, 760, 760, 800 }; //The unique black/white threshold for each sensor (0 - 5)


// Create an instance of the SensorSet with the given pin values
SensorSet::SensorSet(int _pin1, int _pin2, int _pin3, int _pin4, int _pin5, int _pin6, int _commitPin)
{
//	lower[] = {'\0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', "'o", 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '\t', '\n', '`', '[', ']', ';', "'", '', '.', '/', '-', '='};
//	upper[] = {'\0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ')', '!', '@', '#', '$', '%', '^', '&', '*', '(', ' ', '\t', '\n', '|', '{', '}', ':', '"', '', '>', '?', '_', "+'"};
	commitPin = _commitPin;
	pins[0] = _pin1;
	pins[1] = _pin2;
	pins[2] = _pin3;
	pins[3] = _pin4;
	pins[4] = _pin5;
	pins[5] = _pin6;
	for (int i = 0; i < 6; i++)
	{
		pinMode(pins[i], INPUT_PULLUP);
	}
	pinMode(commitPin, INPUT_PULLUP);
}

// Determines whether the given sensor (i) sees black or dark
bool SensorSet::isBlack(int i)
{
	int pin = pins[i];
	return (digitalRead(pin) == LOW);
}

bool SensorSet::allWhite()
{
	for (int i = 0; i < 6; i++)
	{
		if (isBlack(i))
		{
			return false;
		}
	}
	return true;
}

//Return the integer representation of the binary value read from all 6 sensors
int SensorSet::getInt()
{
	bool val[6] = {0,0,0,0,0,0};
	while (digitalRead(commitPin) != LOW) // While the button has not been pressed
	{
		for (int i = 0; i < 6; i ++)
		{
			if (isBlack(i))
			{
				val[i] = true;
			}
		}
	}
	delay(250);
	int intVal = bitShift(val);
	Serial.println(intVal);
	return intVal;
}

int SensorSet::bitShift(bool val[])
{
	int x = 0;
	for (int i = 0; i < 6; i++) 
		if (val[i] > 0) 
			x += 1 << i;
	return x;
}

// Prints a verbose message of the analogRead and status of each sensor
void SensorSet::print()
{
	for (int i = 0; i < 6; i++)
	{
		Serial.print("Pin ");
		Serial.print(pins[i]);
		Serial.print(" ");
		Serial.print(analogRead(i));
		Serial.print(" ");
		Serial.print(isBlack(i));
		Serial.print(", ");
	}
	Serial.println(" ");
}

// Print the boolean results for each of the sensors
void SensorSet::printSmall()
{
	for (int i = 0; i < 6; i++)
	{
		Serial.print(isBlack(i));
		Serial.print(" ");
	}
	Serial.println(" ");
}

//Print just the raw analog values from the sensors
void SensorSet::printValues()
{
	for (int i = 0; i < 6; i++)
	{
		Serial.print(analogRead(pins[i]));
		Serial.print(" ");
	}
	Serial.println(" ");
}

//Returns an array of booleans representing each sensor's current reading
bool* SensorSet::getRaw()
{
	bool vals[6];
	for (int i = 0; i < 6; i++)
	{
		vals[i] = isBlack(i);
	}
	return vals;
}


//Get the associated char with the current value
String SensorSet::getChar(int num, int shift)
{
	shift = !shift;
	switch (num)
	{	
		case 0:
			return "\0";
			break;
		case 1:
			if (shift) return "a";
			else return "A";
			break;
		case 2:
			if (shift) return "b";
			else return "B";
			break;
		case 3:
			if (shift) return "c";
			else return "C";
			break;
		case 4:
			if (shift) return "d";
			else return "D";
			break;
		case 5:
			if (shift) return "e";
			else return "E";
			break;
		case 6:
			if (shift) return "f";
			else return "F";
			break;
		case 7:
			if (shift) return "g";
			else return "G";
			break;
		case 8:
			if (shift) return "h";
			else return "H";
			break;
		case 9:
			if (shift) return "i";
			else return "I";
			break;
		case 10:
			if (shift) return "j";
			else return "J";
			break;
		case 11:
			if (shift) return "k";
			else return "K";
			break;
		case 12:
			if (shift) return "l";
			else return "L";
			break;
		case 13:
			if (shift) return "m";
			else return "M";
			break;
		case 14:
			if (shift) return "n";
			else return "N";
			break;
		case 15:
			if (shift) return "o";
			else return "O";
			break;
		case 16:
			if (shift) return "p";
			else return "P";
			break;
		case 17:
			if (shift) return "q";
			else return "Q";
			break;
		case 18:
			if (shift) return "r";
			else return "R";
			break;
		case 19:
			if (shift) return "s";
			else return "S";
			break;
		case 20:
			if (shift) return "t";
			else return "T";
			break;
		case 21:
			if (shift) return "u";
			else return "U";
			break;
		case 22:
			if (shift) return "v";
			else return "V";
			break;
		case 23:
			if (shift) return "w";
			else return "W";
			break;
		case 24:
			if (shift) return "x";
			else return "X";
			break;
		case 25:
			if (shift) return "y";
			else return "Y";
			break;
		case 26:
			if (shift) return "z";
			else return "Z";
			break;
		case 27:
			if (shift) return "0";
			else return ")";
			break;
		case 28:
			if (shift) return "1";
			else return "!";
			break;
		case 29:
			if (shift) return "2";
			else return "@";
			break;
		case 30:
			if (shift) return "3";
			else return "#";
			break;
		case 31:
			if (shift) return "4";
			else return "$";
			break;
		case 32:
			if (shift) return "5";
			else return "%";
			break;
		case 33:
			if (shift) return "6";
			else return "^";
			break;
		case 34:
			if (shift) return "7";
			else return "&";
			break;
		case 35:
			if (shift) return "8";
			else return "*";
			break;
		case 36:
			if (shift) return "9";
			else return "(";
			break;
		case 37:
			if (shift) return " ";
			else return " ";
			break;
		case 38:
			if (shift) return "\t";
			else return "\t";
			break;
		case 39:
			if (shift) return "\n";
			else return "\n";
			break;
		case 40:
			if (shift) return "`";
			else return "|";
			break;
		case 41:
			if (shift) return "[";
			else return "{";
			break;
		case 42:
			if (shift) return "]";
			else return "}";
			break;
		case 43:
			if (shift) return ";";
			else return ":";
			break;
		case 44:
			if (shift) return "'";
			else return "\"";
			break;
		case 45:
			if (shift) return ",";
			else return "<";
			break;
		case 46:
			if (shift) return ".";
			else return ">";
			break;
		case 47:
			if (shift) return "/";
			else return "?";
			break;
		case 48:
			if (shift) return "-";
			else return "_";
			break;
		case 49:
			if (shift) return "=";
			else return "+";
			break;
	}
}
