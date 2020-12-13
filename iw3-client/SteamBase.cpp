/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : SteamBase.cpp Source
** - Description : Basic Steam interface functions for usage in main
** - Author      : OSW Corp?
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** 
**
************************************************************************************/

#include "stdafx.h"
#include "SteamFriends005.h"
#include "SteamUser012.h"
#include "SteamUserStats010.h"
#include "SteamMatchmaking007.h"

// define so the template can be compiled
std::map<SteamInterface_t, void*> CSteamBase::_instances;
std::map<SteamAPICall_t, bool> CSteamBase::_calls;
std::map<SteamAPICall_t, CCallbackBase*> CSteamBase::_resultHandlers;
std::vector<SteamAPIResult_t> CSteamBase::_results;
std::vector<CCallbackBase*> CSteamBase::_callbacks;
int CSteamBase::_callID;

void* CSteamBase::CreateInterface(SteamInterface_t interfaceID)
{
	// even though this might be done nicer, I'm doing it using a switch statement now
	switch (interfaceID)
	{
 		case INTERFACE_STEAMFRIENDS005:
 			return new CSteamFriends005;
		case INTERFACE_STEAMUSER012:
			return new CSteamUser012;
		case INTERFACE_STEAMUSERSTATS010:
			return new CSteamUserStats010;
		case INTERFACE_STEAMMATCHMAKING007:
			return new CSteamMatchmaking007;
	}

	return NULL;
}

void* CSteamBase::GetInterface(SteamInterface_t interfaceID)
{
	// note the WTF in std::map - I still prefer the BCL
	if (_instances.find(interfaceID) == _instances.end())
	{
		// not found yet, so create it
		_instances[interfaceID] = CreateInterface(interfaceID);
	}

	return _instances[interfaceID];
}

void CSteamBase::RegisterCallback(CCallbackBase *handler, int callback)
{
	handler->SetICallback(callback);
	_callbacks.push_back(handler);
}

void CSteamBase::RegisterCallResult(SteamAPICall_t call, CCallbackBase *result)
{
	_resultHandlers[call] = result;
}

SteamAPICall_t CSteamBase::RegisterCall()
{
	_callID++;

	_calls[_callID] = false;
	
	return _callID;
}

void CSteamBase::ReturnCall(void *data, int size, int type, SteamAPICall_t call)
{
	SteamAPIResult_t result;

	_calls[call] = true;

	result.call = call;
	result.data = data;
	result.size = size;
	result.type = type;

	_results.push_back(result);
}

void CSteamBase::RunCallbacks()
{
	std::vector<SteamAPIResult_t>::iterator iter;

	for (iter = _results.begin(); iter < _results.end(); iter++)
	{
		SteamAPIResult_t result = *iter;

		if (_resultHandlers.find(result.call) != _resultHandlers.end())
		{
			_resultHandlers[result.call]->Run(result.data, false, result.call);
		}

		std::vector<CCallbackBase*>::iterator cbiter;

		for (cbiter = _callbacks.begin(); cbiter < _callbacks.end(); cbiter++)
		{
			CCallbackBase* cb = *cbiter;

			if (cb && cb->GetICallback() == result.type)
			{
				cb->Run(result.data, false, 0);
			}
		}

		free(result.data);
	}

	_results.clear();
}

__declspec(dllexport) ISteamFriends* __cdecl SteamFriends()
{
	////Com_Printf(0, "[SteamAPI] SteamFriends\n");
	return (ISteamFriends*)CSteamBase::GetInterface(INTERFACE_STEAMFRIENDS005);
	//return (ISteamFriends*)g_pSteamFriendsEmu;
}

__declspec(dllexport) ISteamUserStats* __cdecl SteamUserStats()
{
	//Trace("S_API", "SteamUserStats");
	return (ISteamUserStats*)CSteamBase::GetInterface(INTERFACE_STEAMUSERSTATS010);
	//return (ISteamUserStats*)g_pSteamUStatsEmu;
}

__declspec(dllexport) void __cdecl SteamAPI_RunCallbacks()
{
	// Prevent debugger shit
}

__declspec(dllexport) void __cdecl SteamAPI_RegisterCallResult(CCallbackBase* pResult, SteamAPICall_t APICall)
{
	//CSteamBase::RegisterCallResult(APICall, pResult);
}

__declspec(dllexport) void __cdecl SteamAPI_RegisterCallback(CCallbackBase *pCallback, int iCallback)
{
	//CSteamBase::RegisterCallback(pCallback, iCallback);
}

__declspec(dllexport) char __cdecl SteamAPI_RestartAppIfNecessary()
{
	return 0;
}

__declspec(dllexport) void __cdecl SteamAPI_Shutdown()
{

}

__declspec(dllexport) void __cdecl SteamAPI_UnregisterCallResult(CCallbackBase* pResult, SteamAPICall_t APICall)
{

}

__declspec(dllexport) void __cdecl SteamAPI_UnregisterCallback(CCallbackBase *pCallback, int iCallback)
{

}

__declspec(dllexport) ISteamMatchmaking* __cdecl SteamMatchmaking()
{
	return (ISteamMatchmaking*)CSteamBase::GetInterface(INTERFACE_STEAMMATCHMAKING007);
}

__declspec(dllexport) ISteamUser* __cdecl SteamUser()
{
	return (ISteamUser*)CSteamBase::GetInterface(INTERFACE_STEAMUSER012);
}

void PatchMW2_SteamFriends()
{
	//*(DWORD*)SteamFriendsLoc = (DWORD)SteamFriends;
}

void PatchMW2_SteamMatchmaking()
{
	//*(DWORD*)0x6D75B0 = (DWORD)SteamMatchmaking;
}

void PatchMW2_SteamUserStats()
{
	//*(DWORD*)SteamUserStatsLoc = (DWORD)SteamUserStats;
	//*(DWORD*)SteamUserStatsInstanceLoc = (DWORD)SteamUserStats();
}

// Version 184 only
void PatchMW2_RunCallbacks()
{
	//if(version == 184)
	//{
	//	*(DWORD*)0x691544 = (DWORD)SteamAPI_RunCallbacks;
	//}
	//else if(version == 177)
	//{
	//	*(DWORD*)0x6D75D0 = (DWORD)SteamAPI_RunCallbacks;
	//}
	//else if (version == 358)
	//{
	//	*(DWORD*)0x7905B4 = (DWORD)SteamAPI_RunCallbacks;
	//}
	//else if (version == 382)
	//{
	//	*(DWORD*)0x7915B4 = (DWORD)SteamAPI_RunCallbacks;
	//}
}