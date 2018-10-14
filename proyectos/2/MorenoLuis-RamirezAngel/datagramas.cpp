// datagramas.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "iphlpapi.lib")


int main()
{
	int i;
	unsigned int rAnt, rNvo, rTot,eAnt,eNvo;
	float dTot,dEot;
	MIB_IPSTATS *pStats;
	pStats = (MIB_IPSTATS *) malloc (sizeof(MIB_IPSTATS));

	GetIpStatistics(pStats);
	rAnt = pStats->dwInReceives;
	eAnt = pStats->dwOutRequests;//- pStats->dwOutDiscards;
	Sleep(1000);

	for (i = 0; i < 100; i++)
	{
		GetIpStatistics(pStats);
		rNvo = pStats->dwInReceives;
		eNvo = pStats->dwOutRequests;//- pStats->dwOutDiscards;
		//rTot = (rNvo - rAnt);
		dTot = (float)(rNvo - rAnt)*(1.5);
		dEot = (float)(eNvo - eAnt)*(1.5);
		if (dTot > 999)
		{
			dTot = dTot/ 1000;
			printf("Recibo: %g Mbps\t|\t", dTot);
		}
		else
		{
			printf("Recibo: %g kbps\t|\t", dTot);
		}
		if (dEot > 999)
		{
			dTot = dTot / 1000;
			printf("Envio: %g Mbps\n", dEot);
		}
		else
		{
			printf("Envio: %g kbps\n", dEot);
		}
		
		rAnt = rNvo;
		eAnt = eNvo;
		Sleep(1000);
	}
	getchar();
    return 0;
}

