// RAMusage.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>

int main()
{
	MEMORYSTATUSEX memoria;
	int i;
	unsigned long long int usada;
	memoria.dwLength = sizeof(memoria);

	for (i = 0; i < 20; i++)
	{
		GlobalMemoryStatusEx(&memoria);
		usada = memoria.ullTotalPhys - memoria.ullAvailPhys;
		printf("Hay %llu memoria RAM  con %llu disponible\n", memoria.ullTotalPhys, memoria.ullAvailPhys);
		printf("Usada %llu\t %u pC \n\n",usada, memoria.dwMemoryLoad);
		Sleep(1000);
	}

	getchar();
	return 0;
}

