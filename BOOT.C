/* Demo program that illustrates how to determine the boot drive.  This is
** important in OS/2 2.0 because the Boot Manager allows drives other than
** C: to be the active boot drive for OS/2.  Any software that assumes the
** boot drive IS dirve C: may not function properly.
**
**  Three routines are included:
**
**		main					The test driver
**
**		GetSysInfo			Routine allocates storage and calls DosQuerySysInfo
**								It returns a pointer to a results buffer.  In the
**								test case listed, the buffer contains a single ULONG
**								with the value 3.
**
**		QueryBootDrive		Routine calls GetSysInfo and returns the numeric
**								value of the boot drive (e.g., if the boot drive is
**								drive C: QueryBootDrive returns 3);
**
**
**	NOTE: The driver routine ASSUMES English and single byte characters, etc.
**       The conversion from drive number to letter may NOT be suitable for
**			"internationalization"  The method used is not totally collating
**       sequence independent.
**
** Author: David Moskowitz
** Copyright (c) 1991, Productivity Solutions, Inc.  All Rights reserved.
** Permission is hereby granted for unrestricted use of this code.
**
*/

#define INCL_DOSMISC
#define INCL_NOPMAPI
#include <os2.h>

#include <stdlib.h>
#include <stdio.h>


PUINT GetSysInfo(UINT, UINT);
UINT QueryBootDrive(VOID);

int main (VOID)
{
	UINT result;
	PUINT pResultBuf;

	pResultBuf = GetSysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE);

	printf("\n\tGetSysInfo for QSV_BOOT_DRIVE reports number %u letter %c:\n"
		, *(pResultBuf), *(pResultBuf) + ('A'-1));

	result = QueryBootDrive();
	printf("\n\tQueryBootDrive reports %u letter %c:\n", result
		, result + ('a'-1));

}


UINT QueryBootDrive(VOID)
{
	return (*(GetSysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE)));
}


PUINT GetSysInfo(UINT StartType, UINT EndType)
{
	PUINT pSysInfoBuf;

	UINT cItemsRequested;
	UINT cbBuf;

	cItemsRequested = EndType - StartType + 1;
	cbBuf           = cItemsRequested * 4;

	pSysInfoBuf = (PUINT) calloc(cItemsRequested, cbBuf);

	DosQuerySysInfo(StartType, EndType, (PVOID) pSysInfoBuf, cbBuf);

	return pSysInfoBuf;

//	free(pSysInfoBuf);

}

