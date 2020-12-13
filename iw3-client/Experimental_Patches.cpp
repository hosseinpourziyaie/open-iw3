/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : Experimental_Patches.cpp Source
** - Description : un-finished experimental patches for reasons
** - Author      : Hosseinpourziyaie
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** [Copyright © ULTRAMOD/Hosseinpourziyaie 2020] <hosseinpourziyaie@gmail.com>
**
************************************************************************************/

#include "stdafx.h"


//typedef const char *(__cdecl * SEH_SafeTranslateString_t)(const char *pszReference);
//SEH_SafeTranslateString_t SEH_SafeTranslateString = (SEH_SafeTranslateString_t)0x000000;
//
//typedef const char *(__cdecl * UI_SafeTranslateString_t)(const char *reference);
//UI_SafeTranslateString_t UI_SafeTranslateString = (UI_SafeTranslateString_t)0x54ACA0;


//typedef snd_alias_list_t* (__cdecl * Com_FindSoundAlias_t)(const char *name);
//Com_FindSoundAlias_t Com_FindSoundAlias = (Com_FindSoundAlias_t)0x489570;
//
//typedef void (__cdecl * R_RenderScene_t)(refdef_s *refdef);
//R_RenderScene_t R_RenderScene = (R_RenderScene_t)0x5FAF00;
//
//
//snd_alias_list_t* FindSoundAliasHookFunc(const char* name)
//{
//	MessageBox(0, va("%s!", name), "[DEBUG]", MB_ICONWARNING);
//
//	return Com_FindSoundAlias(name);
//
//	//IDK whats wrong with it???
//}
//
//CallHook R_RenderSceneHook;
//float	WHITE[4] = { 1,1,1,1 };
//
//void DrawDemoWarning()
//{
//	void *objectivefont = R_RegisterFont("fonts/objectivefont", sizeof("fonts/objectivefont"));
//
//	char buff[16] = "Hello, World <3";
//	R_AddCmdDrawText(buff, 0x7FFFFFFF, objectivefont, 0, 0, 3.0f, 3.0f, 0.0f, WHITE, 0);
//}
//
//void __declspec(naked) R_RenderSceneHookStub()
//{
//	__asm
//	{
//		call DrawDemoWarning
//			jmp R_RenderSceneHook.pOriginal
//	}
//}
//
//
//void R_RenderSceneXREFHookFunc(refdef_s *refdef)
//{
//	MessageBox(0, va("Im getting called!"), "OPEN-IW3", MB_ICONWARNING);
//
//	// ...
//	void *objectivefont = R_RegisterFont("fonts/objectivefont", sizeof("fonts/objectivefont"));
//
//	char buff[16] = "Hello, World <3";
//	R_AddCmdDrawText(buff, 0x7FFFFFFF, objectivefont, 0, 0, 3.0f, 3.0f, 0.0f, WHITE, 0);
//
//	R_RenderScene(refdef);
//}

void IW3_568_Experimental()
{
	//---------------------    UNFINISHED PATCHES     ---------------------//

	// in IW4M they used to hook SCR_UpdateFrame to Draw stuff
	//  I couldnt figure equivalent func offset for that in cod4  

	//call(0x61005B, R_RenderSceneXREFHookFunc, PATCH_CALL); 

	//R_RenderSceneHook.initialize(0x61005B, R_RenderSceneHookStub);
	//R_RenderSceneHook.installHook();


	//call(0x565599, FindSoundAliasHookFunc, PATCH_CALL); 
}