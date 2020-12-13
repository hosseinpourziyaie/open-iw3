/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : HeadQuarters.cpp Source
** - Description : Main Core for version detection and Initialize
** - Author      : Hosseinpourziyaie
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** [Copyright © ULTRAMOD/Hosseinpourziyaie 2020] <hosseinpourziyaie@gmail.com>
**
************************************************************************************/

#include "stdafx.h"

void echoError(int version, char* game)
{
	if (version == 0) MessageBox(0, va("could not recognize game. skipping open-iw3 load"), "OPEN-IW3", MB_ICONWARNING);
	else MessageBox(0, va("%s build %d is currently not supported!", game, version), "OPEN-IW3", MB_ICONWARNING);
}

void Patch_IW3_568();

void Sys_Initiate()
{
	//MessageBox(0, va("[DEBUG] Username : %s" , GetUsername()), "OPEN-IW3", MB_ICONINFORMATION);

	DetermineGameFlags();

	// --------------------------- IW3 ---------------------------
	// IW3 - Version 1.7.568 (Mutliplayer)
	if(!strcmp((char*)0x6E0568, "568"))
	{
		Patch_IW3_568();
	}

	// IW3 - Version 1.5.549 (Singleplayer)
	else if(*(int*)0x4FB20C == 549) // or 0x43CCA6
	{
		echoError(549, "IW3");
	}

	else echoError(000, "N/A");
}

char* GetUsername()
{
	static char UserName[1024];
	DWORD size = 1024;
	GetUserNameA( UserName, &size );
	return &(UserName[0]);
}