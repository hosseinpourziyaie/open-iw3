/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : definitions.cpp Source
** - Description : Engine structures/functions definitions
** - Author      : N/A
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** [Copyright © ULTRAMOD/Hosseinpourziyaie 2020] <hosseinpourziyaie@gmail.com>
**
************************************************************************************/

#include "stdafx.h"

// function definitions
extern "C"
{
	//---------------------------                                                   ---------------------------//
	CL_IsCgameInitialized_t CL_IsCgameInitialized = (CL_IsCgameInitialized_t)0x000000;
	//---------------------------                                                   ---------------------------//
	R_RegisterFont_t R_RegisterFont = (R_RegisterFont_t)0x000000;
	R_AddCmdDrawText_t R_AddCmdDrawText = (R_AddCmdDrawText_t)0x000000;
	R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic = (R_AddCmdDrawStretchPic_t)0x000000;
	R_TextWidth_t R_TextWidth = (R_TextWidth_t)0x000000;
	//---------------------------                                                   ---------------------------//
	Com_Error_t Com_Error = (Com_Error_t)0x000000;
	Com_Printf_t Com_Printf = (Com_Printf_t)0x000000;
	Com_Milliseconds_t Com_Milliseconds = (Com_Milliseconds_t)0x000000;
	Com_PrintError_t Com_PrintError = (Com_PrintError_t)0x000000;
	//---------------------------                                                   ---------------------------//
	SE_Load_t SE_Load = (SE_Load_t)0x000000;
	//---------------------------                                                   ---------------------------//
	Dvar_RegisterBool_t Dvar_RegisterBool = (Dvar_RegisterBool_t)0x000000;
	Dvar_RegisterFloat_t Dvar_RegisterFloat = (Dvar_RegisterFloat_t)0x000000;
	Dvar_RegisterFloat2_t Dvar_RegisterFloat2 = (Dvar_RegisterFloat2_t)0x000000;
	Dvar_RegisterFloat3_t Dvar_RegisterFloat3 = (Dvar_RegisterFloat3_t)0x000000;
	Dvar_RegisterFloat4_t Dvar_RegisterFloat4 = (Dvar_RegisterFloat4_t)0x000000;
	Dvar_RegisterInt_t Dvar_RegisterInt = (Dvar_RegisterInt_t)0x000000;
	Dvar_RegisterEnum_t Dvar_RegisterEnum = (Dvar_RegisterEnum_t)0x000000;
	Dvar_RegisterString_t Dvar_RegisterString = (Dvar_RegisterString_t)0x000000;
	Dvar_RegisterColor_t Dvar_RegisterColor = (Dvar_RegisterColor_t)0x000000;

	Dvar_FindVar_t Dvar_FindVar = (Dvar_FindVar_t)0x000000;
	Dvar_InfoString_Big_t Dvar_InfoString_Big = (Dvar_InfoString_Big_t)0x000000;
	Dvar_SetCommand_t Dvar_SetCommand = (Dvar_SetCommand_t)0x000000;
	Dvar_SetStringByName_t Dvar_SetStringByName = (Dvar_SetStringByName_t)0x000000;
	Dvar_GetString_t Dvar_GetString = (Dvar_GetString_t)0x000000;
	//---------------------------                                                   ---------------------------//
	Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand = (Cmd_ExecuteSingleCommand_t)0x000000;
	Cbuf_AddText_t Cbuf_AddText = (Cbuf_AddText_t)0x000000;
	SV_GameSendServerCommand_t SV_GameSendServerCommand = (SV_GameSendServerCommand_t)0x000000;
	Cmd_AddCommand_t Cmd_AddCommand = (Cmd_AddCommand_t)0x000000;
	Cmd_AddServerCommand_t Cmd_AddServerCommand = (Cmd_AddServerCommand_t)0x000000;
}



dvar_t** dvarName = (dvar_t**)0x929154;
dvar_t** r_mode = (dvar_t**)0;

char* language = (char*)0x19FF828;

DWORD drawDevStuffHookLoc = 0x57DB09;
DWORD winMainInitHookLoc = 0x4A7910;
DWORD localizeAssetHookLoc = 0x629B97;
DWORD SELoadLanguageHookLoc = 0x629D27;
DWORD SetStringHookLoc = 0x4CE5EE;
DWORD loadGameOverlayHookLoc = 0x604350;
DWORD findSoundAliasHookLoc = 0x631A39;
DWORD printVersionHookLoc = 0x6030C2;
