/*
 * GPS_Driver.c
 *
 *  Created on: Aug 5, 2025
 *      Author: sathyan
 */

#include "GPS_Driver.h"
#include "stdio.h"
#include "string.h"
#include "USART_Driver.h"

#define NMEA_BUF_SIZE 128

static char nmeaBuff[NMEA_BUF_SIZE];
static uint8_t nmeaIdx=0;


static void GPS_ParseNMEASentence(const char *nmeaBuffer)
{
	if(strncmp(nmeaBuffer, "$GNGGA",6) != 0)
		return;

	//Process the $GNGGA Sentence
	char buff[NMEA_BUF_SIZE];
	strncpy(buff,nmeaBuffer, NMEA_BUF_SIZE-1);

	//Pointer to comma separated strings
	const char *lat = NULL, *lon = NULL;
	const char *ns = NULL, *ew = NULL;
	const char *num_sats = NULL, *alt = NULL;

	char *token = NULL;
	char *saveptr = NULL;
	uint8_t field=0;

	token = strtok_r(buff,",",&saveptr);

	while(token != NULL)
	{
		field++;
		switch(field)
		{
			case 3:
				lat = token;
				break;
			case 4:
				ns= token;
				break;
			case 5:
				lon = token;
				break;
			case 6:
				ew = token;
				break;
			case 8:
				num_sats = token;
				break;
			case 10:
				alt = token;
				break;
			default:
				break;
		}
		token = strtok_r(NULL,",",&saveptr);
	}

	//Print the data on UART1
	char outbuf[128];
	int len = snprintf(outbuf,sizeof(outbuf),"Latitude:%s%s, Longitude:%s%s, Altitude:%s, Number of Visible Satellites:%s\r\n",lat,ns,lon,ew,alt,num_sats);
	USART_Transmit_IT(&Usart1Struct, (uint8_t *)outbuf, len);
}

void GPS_ProcessRxByte(uint8_t rxdata)
{

	if(rxdata == '$')
	{
		/*Reset the buff index to point to the start of NMEA buffer*/
		nmeaIdx = 0;
	}
	if(nmeaIdx < NMEA_BUF_SIZE -1)
	{
		nmeaBuff[nmeaIdx++]= rxdata;
	}

	if(rxdata == '\n')
	{
		nmeaBuff[nmeaIdx] = '\0';
		GPS_ParseNMEASentence(nmeaBuff);
	}

}
