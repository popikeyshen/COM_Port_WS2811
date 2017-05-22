// COM_READ_Visual_studio_2017.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <iostream>

// application reads from the specified serial port and reports the collected data
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	int a = 1;
	if (a == 1)
	{
		printf("App START!\n\n");

		Serial* SP = new Serial("\\\\.\\COM5");    // adjust as needed

		if (SP->IsConnected())
			printf("Connected\n");

		char incomingData[256] = "";			// don't forget to pre-allocate memory
												//printf("%s\n",incomingData);
		int dataLength = 255;
		int readResult = 0;

		while (SP->IsConnected())
		{
			//readResult = SP->ReadData(incomingData, dataLength);
			//  printf("Bytes read: (0 means no data available) %i\n",readResult);
			//	incomingData[readResult] = 0;
			//	printf("%s", incomingData);

			//unsigned char g=1;
			//printf("%d",sizeof(g));

			printf(" 3 motor, 5 - leds (rgb), 6 leds 0ff ");
			printf("command: ");
			int command;
			cin >> command;

			printf("data1 (start): ");
			int start;
			cin >> start;
			printf("data2 (end): ");
			int end;
			cin >> end;
			printf("data3 (r): ");
			int r;
			cin >> r;
			printf("data4 (g): ");
			int g;
			cin >> g;
			printf("data5 (b): ");
			int b;
			cin >> b;

			//char buf[5]={CRC,CMD,SIZE,NUMBER,data,CTL};
			char CTL = 0xF7;
			char CHK = 0x01;
			char SIZE = 0x05;
			char CMD = (char)command;   

			// start id   /   end id   /     r/ g/ b
			char DATA1 = (char)start, DATA2 = (char)end, DATA3 = (char)r, DATA4 = (char)g, DATA5 = (char)b;

			char CRC = CTL + CHK + SIZE + CMD + DATA1 + DATA2 + DATA3 + DATA4 + DATA5;

			//char z[] = {CRC,DATA5,DATA4,DATA3,DATA2,DATA1,CMD,SIZE,CHK,CTL};

			char a[] = { CTL,CHK,SIZE,CMD,DATA1,DATA2,DATA3,DATA4,DATA5,CRC };

			char five[256] ;
			for(int i=0;i<10;i++)
			{ 
				five[i] = a[i];
			}
			for (int i = 10; i<255; i++)
			{
				five[i] = 0;
			}

			SP->WriteData(five,strlen(five));
			Sleep(500);

			//CHK = ~CHK;
		}
		return 0;
	}

}
