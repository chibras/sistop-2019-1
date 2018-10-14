// usoDelCPU.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>



int main()
{
	FILETIME idle, kernel, user;
	SYSTEMTIME sIdle, sKernel, sUser;
	ULARGE_INTEGER aIdle, nIdle, aKernel, nKernel, aUser, nUser, tIdle, tKernel, tUser;
	unsigned long long int usoCPU;
	int i;

	//------

	GetSystemTimes(&idle, &kernel, &user);

	FileTimeToSystemTime(&idle, &sIdle);
	FileTimeToSystemTime(&kernel, &sKernel);
	FileTimeToSystemTime(&user, &sUser);

	aIdle.LowPart = idle.dwLowDateTime;
	aIdle.HighPart = idle.dwHighDateTime;
	aKernel.LowPart = kernel.dwLowDateTime;
	aKernel.HighPart = kernel.dwHighDateTime;
	aUser.LowPart = user.dwLowDateTime;
	aUser.HighPart = user.dwHighDateTime;

	printf("Tiempo inicio: \n\n");
	printf("Tiempo en Idle: %d horas %d min %d seg %d ms\n", sIdle.wHour, sIdle.wMinute, sIdle.wSecond, sIdle.wMilliseconds);
	printf("Tiempo en Kernel: %d horas %d min %d seg %d ms\n", sKernel.wHour, sKernel.wMinute, sKernel.wSecond, sKernel.wMilliseconds);
	printf("Tiempo en User: %d horas %d min %d seg %d ms\n\n", sUser.wHour, sUser.wMinute, sUser.wSecond, sUser.wMilliseconds);

	Sleep(1000);

	//------

	for (i = 0; i < 100; i++)
	{
		GetSystemTimes(&idle, &kernel, &user);

		//system("cls");

		nIdle.LowPart = idle.dwLowDateTime;
		nIdle.HighPart = idle.dwHighDateTime;
		nKernel.LowPart = kernel.dwLowDateTime;
		nKernel.HighPart = kernel.dwHighDateTime;
		nUser.LowPart = user.dwLowDateTime;
		nUser.HighPart = user.dwHighDateTime;

		tIdle.QuadPart = nIdle.QuadPart - aIdle.QuadPart;
		tUser.QuadPart = nUser.QuadPart - aUser.QuadPart;
		tKernel.QuadPart = nKernel.QuadPart - aKernel.QuadPart;

		usoCPU = ( (tKernel.QuadPart + tUser.QuadPart - tIdle.QuadPart) *100 /(tKernel.QuadPart + tUser.QuadPart) );

		idle.dwHighDateTime = tIdle.HighPart;
		idle.dwLowDateTime = tIdle.LowPart;
		kernel.dwHighDateTime = tKernel.HighPart;
		kernel.dwLowDateTime = tKernel.LowPart;
		user.dwHighDateTime = tUser.HighPart;
		user.dwLowDateTime = tUser.LowPart;

		FileTimeToSystemTime(&idle, &sIdle);
		FileTimeToSystemTime(&kernel, &sKernel);
		FileTimeToSystemTime(&user, &sUser);


		printf("Tiempo %i: \n\n", i);
		printf("Tiempo en Idle: %d horas %d min %d seg %d ms\n", sIdle.wHour, sIdle.wMinute, sIdle.wSecond, sIdle.wMilliseconds);
		printf("Tiempo en Kernel: %d horas %d min %d seg %d ms\n", sKernel.wHour, sKernel.wMinute, sKernel.wSecond, sKernel.wMilliseconds);
		printf("Tiempo en User: %d horas %d min %d seg %d ms\n", sUser.wHour, sUser.wMinute, sUser.wSecond, sUser.wMilliseconds);
		printf("Uso del CPU: %llu\n\n",usoCPU);
		
		aIdle.QuadPart = nIdle.QuadPart;
		aKernel.QuadPart = nKernel.QuadPart;
		aUser.QuadPart = nUser.QuadPart;

		Sleep(1000);
	}

	getchar();
    return 0;
}

