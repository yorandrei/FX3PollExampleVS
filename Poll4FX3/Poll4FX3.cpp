// Poll4FX3.cpp : This simple Windows console program polls for 30 seconds looking for an attached FX3 board.
//
//	This program is built with an embedded static MFC library so that it will run run on all Win32 platforms
//
//	john@usb-by-example.com
//

#include "stdafx.h"
unsigned char TestData[] = "Hello Systems Lab!!!";

int _tmain(int argc, _TCHAR* argv[])
{
	CCyUSBDevice *USBDevice;
	int Seconds, i;
	LONG BytesWritten = 0;

	printf("\nPoll for FX3 device V0.3\n");

	for (Seconds = 30; Seconds>0; Seconds--)
	{
		USBDevice = new CCyUSBDevice(NULL, CYUSBDRV_GUID, true);
		for (i = 0; i < USBDevice->DeviceCount(); i++)
		{
			USBDevice->Open(i);
			printf("\nDev VID = %d, PID = %d", USBDevice->VendorID, USBDevice->ProductID);
			// A BulkLoop device will have a VID=0x04B4 and a PID=0x00F0
			if ((USBDevice->VendorID == 0x04B4) && (USBDevice->ProductID == 0x00F0))
			{
				BytesWritten = sizeof(TestData);
				USBDevice->BulkOutEndPt->XferData(TestData, BytesWritten);
				printf("\nSent %d bytes to FX3", BytesWritten);
				break;
			}
			USBDevice->Close();
		}
		if (BytesWritten) break;
		delete USBDevice;
		printf("%d \r", Seconds);
		Sleep(1000);
	}
	if (Seconds == 0) printf("Sorry, no FX3 devices found");
	printf("\nUse CR to EXIT\n");
	// The DOS box typically exits so fast that the developer doesn't see any messages
	// Hold the box open until the user enters a character, any character
	while (!_kbhit()) {}
	return 0;
}