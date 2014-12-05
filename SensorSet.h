#include<Arduino.h>

class SensorSet
{
	private:
		int pins[6];
		unsigned int commitPin;
		bool isBlack(int pin);
		bool allWhite();
		int bitShift(bool[]);
	public:
		SensorSet(int, int, int , int , int, int, int);
		int getInt();
		String getChar(int num, int shift);
		bool* getRaw();
		void print();
		void printSmall();
		void printValues();
};
