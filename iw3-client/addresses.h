/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : addresses.h Header
** - Description : define Addresses for desired games
** - Author      : Hosseinpourziyaie
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** [Copyright © ULTRAMOD/Hosseinpourziyaie 2020] <hosseinpourziyaie@gmail.com>
**
************************************************************************************/

#include "stdafx.h"

void defineAddresses(char* game ,int version)
{
	switch (version) {
	case 568:
		{
			R_RegisterFont = (R_RegisterFont_t)0x5F1EC0;
			R_AddCmdDrawText = (R_AddCmdDrawText_t)0x5F6B00;
			R_AddCmdDrawStretchPic = (R_AddCmdDrawStretchPic_t)0x000000;
			R_TextWidth = (R_TextWidth_t)0x000000;

			Com_Error = (Com_Error_t)0x4FD330;
			Com_Printf = (Com_Printf_t)0x4FCBC0;
			Com_PrintError = (Com_PrintError_t)0x4FCC80;
			Com_Milliseconds = (Com_Milliseconds_t)0x578FB0;

			SE_Load = (SE_Load_t)0x000000;

			Dvar_FindVar = (Dvar_FindVar_t)0x000000;
			Dvar_SetCommand = (Dvar_SetCommand_t)0x000000;
			Dvar_RegisterBool = (Dvar_RegisterBool_t)0x56C350;
			Dvar_RegisterFloat = (Dvar_RegisterFloat_t)0x56C350;
			Dvar_RegisterString = (Dvar_RegisterString_t)0x000000;
			
			Dvar_RegisterInt = (Dvar_RegisterInt_t)0x000000;
			Dvar_RegisterEnum = (Dvar_RegisterEnum_t)0x000000;
			Dvar_GetString = (Dvar_GetString_t)0x000000;


			Cmd_ExecuteSingleCommand = (Cmd_ExecuteSingleCommand_t)0x000000;
			Cbuf_AddText = (Cbuf_AddText_t)0x000000;
			Cmd_AddCommand = (Cmd_AddCommand_t)0x000000;


			dvarName = (dvar_t**)0x000000;
			r_mode = (dvar_t**)0x000000;

			language = (char*)0x000000;

			drawDevStuffHookLoc = 0x000000;
			winMainInitHookLoc = 0x000000;
			localizeAssetHookLoc = 0x000000;
			SELoadLanguageHookLoc = 0x000000;
			SetStringHookLoc = 0x000000;
			loadGameOverlayHookLoc = 0x000000;
			findSoundAliasHookLoc = 0x000000;
			printVersionHookLoc = 0x000000;
		}
		break;
	case 549:
		{
			// does it worth ?
		}
		break;
	default:
		{

		}
	}
}







/*----------------------------------------------------------------------------------------------------------------/

findSoundAlias
\xE8\x00\x00\x00\x00\x56\x6A\x0B\x8B\xF8\xE8\x00\x00\x00\x00\x83\xC4\x10\x85\xC0 x????xxxxxx????xxxxx





\x51\x53\x8B\x1D\x00\x00\x00\x00\x55\x56\x57\xC7\x44\x24\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00 xxxx????xxxxxx?????x????
/----------------------------------------------------------------------------------------------------------------*/