/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : Patch_IW3_568.cpp Source
** - Description : Game Detection + Patch Core
** - Author      : Hosseinpourziyaie
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** [Copyright © ULTRAMOD/Hosseinpourziyaie 2020] <hosseinpourziyaie@gmail.com>
**
************************************************************************************/

#include "stdafx.h"
#include "addresses.h"

void IW3_568_Experimental();

float cgFov90 = 120.0f;

void Patch_IW3_568()
{
	defineAddresses("IW3" ,568);

	//-----------------------         MAIN PATCHES         -----------------------//

	// CD key requirement removal
	*(DWORD *)0x4712E0 = 0x90C301B0; 

	// Tiring punkbuster removal
	*(BYTE *)0x5776B8 = 0xEB; // JNZ_Punkbuster_1; 'Unable to initialize punkbuster. Punkbuster is disabled'
	*(BYTE *)0x5776D6 = 0xEB; // JNZ_Punkbuster_2; 'Unable to initialize punkbuster. Punkbuster is disabled'
	*(BYTE *)0x5776C3 = 0xEB; // JNZ_Punkbuster_3; 'Unable to initialize punkbuster. Punkbuster is disabled'

	// remove improper quit message
	//*(WORD*)0x577415 = 0xEB50; //[WARNING] causes to stop loading game when any

	// remove computer changed message
	*(WORD*)0x576775 = 0xEB2F;

	//-----------------------       BRANDING PATCHES       -----------------------//

	nop(0x4FEA19, 2); // always play the intro video

	// video file path
	*(DWORD*)0x60D03C = (DWORD)"%s\\" FS_BASEGAME "\\video\\%s.%s"; 	


	// build tag in UI code
	*(DWORD*)0x5434BC = (DWORD)VERSIONSTRING/*"1.7.568"*/;

	// console '%s: %s> ' string
	*(DWORD*)0x46060F = (DWORD)(VERSIONSTRING "> ");

	// version string
	*(DWORD*)0x461B84 = (DWORD)(VERSIONSTRING " (built " __DATE__ " " __TIME__ ")\n");


	// increase font sizes for chat on higher resolutions
	*(BYTE*)0x42D127 = 0xEB;
	*(BYTE*)0x42D141 = 0xEB;


	// set fs_basegame to '' (will apply before fs_game)
	*(DWORD*)0x55E4C9 = (DWORD)FS_BASEGAME;

	//// devraw -> DevData/devraw, and similar
	//*(DWORD*)0x55E788 = (DWORD)"DevData/raw";
	//*(DWORD*)0x55E6D5 = (DWORD)"DevData/raw_shared";
	//*(DWORD*)0x55E6BE = (DWORD)"DevData/devraw";
	//*(DWORD*)0x55E6A7 = (DWORD)"DevData/devraw_shared";

	//-----------------------       DVAR PATCHES       -----------------------//

	// set cg_fov max to 90.0
	*(DWORD*)0x43AD8D = (DWORD)&cgFov90;

	//-----------------------     CONSOLE PATCHES      -----------------------//

	//// don't show splash screen
	//nop(0x57761C, 5);

	//-----------------------    SERVERLIST PATCHES    -----------------------//

#ifdef USING_IW_MASTER
	// IDK why but my iw3mp.exe master address was "FrozenKiller_RuLeZ.com"
	//   maybe cracked copy been hex-edited , anyways lets patch it to iw's ip
	strcpy((PCHAR)0x6D0554, "cod4master.activision.com");
#else
	// change MasterServer IP Address to our custom 
	strcpy((PCHAR)0x6D0554, CUSTOM_MASTER_IP);

	//*(DWORD*)0x47188C = (DWORD)CUSTOM_MASTER_IP;
	//*(DWORD*)0x5337FD = (DWORD)CUSTOM_MASTER_IP;

	//[client] change MasterServer port to our custom target
	*(int*)0x4718C6 = CUSTOM_MASTER_PORT;
	//[server] change MasterServer port to our custom target for HeartBeat packet
	*(int*)0x5336E5 = CUSTOM_MASTER_PORT;

	//[server] make HeartBeat packet compatible with public Quake III dpmaster over github
	strcpy((PCHAR)0x6E7D14, "IW3 6");

	//[client] make getservers packet compatible with public Quake III dpmaster over github
	strcpy((PCHAR)0x6EB87C, "globalservers 1 IW3 6 full empty" );
	strcpy((PCHAR)0x6EB89C, "globalservers 1 IW3 6 full empty" );

#endif

	// server cache rename
	//*(DWORD*)0x4764D9 = (DWORD)FS_BASEGAME "/ServerCacheData.dat";
	//*(DWORD*)0x476545 = (DWORD)FS_BASEGAME "/ServerCacheData.dat";

	//IW3_568_Experimental();
}
