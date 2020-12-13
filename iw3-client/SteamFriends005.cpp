/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : SteamBase.cpp Source
** - Description : ISteamFriends005 implementation
** - Author      : OSW Corp?
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** 
**
************************************************************************************/

#include "stdafx.h"
#include "SteamFriends005.h"
#include <time.h>

static char g_userName[256];
static bool g_nameSet = false;

char* GetUsername();

const char *CSteamFriends005::GetPersonaName()
{
	const char* username = GetUsername();
	//Com_Printf(0, "[CSteamFriends005] -> %s\n", username);

	return username;
}

void CSteamFriends005::SetPersonaName( const char *pchPersonaName )
{
	//Com_Printf(0, "[CSteamFriends005] SetPersonaName\n");
}

EPersonaState CSteamFriends005::GetPersonaState()
{
	//Com_Printf(0, "[CSteamFriends005] GetPersonaState\n");
	return k_EPersonaStateOnline;
}

int CSteamFriends005::GetFriendCount( EFriendFlags iFriendFlags )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendCount\n");
	return 0;
}

CSteamID CSteamFriends005::GetFriendByIndex( int iFriend, int iFriendFlags )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendByIndex\n");
	return CSteamID();
}

EFriendRelationship CSteamFriends005::GetFriendRelationship( CSteamID steamIDFriend )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendRelationship\n");
	return k_EFriendRelationshipNone;
}

EPersonaState CSteamFriends005::GetFriendPersonaState( CSteamID steamIDFriend )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendPersonaState\n");
	return k_EPersonaStateOffline;
}

const char *CSteamFriends005::GetFriendPersonaName( CSteamID steamIDFriend )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendPersonaName\n");
	return "UnknownFriend";
}

int CSteamFriends005::GetFriendAvatar( CSteamID steamIDFriend, int eAvatarSize )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendAvatar\n");
	return 0;
}

bool CSteamFriends005::GetFriendGamePlayed( CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendGamePlayed\n");
	return false;
}

const char *CSteamFriends005::GetFriendPersonaNameHistory( CSteamID steamIDFriend, int iPersonaName )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendPersonaNameHistory\n");
	return "";
}

bool CSteamFriends005::HasFriend( CSteamID steamIDFriend, EFriendFlags iFriendFlags )
{
	//Com_Printf(0, "[CSteamFriends005] HasFriend\n");
	return false;
}

int CSteamFriends005::GetClanCount()
{
	//Com_Printf(0, "[CSteamFriends005] GetClanCount\n");
	return 0;
}

CSteamID CSteamFriends005::GetClanByIndex( int iClan )
{
	//Com_Printf(0, "[CSteamFriends005] GetClanByIndex\n");
	return CSteamID();
}

const char *CSteamFriends005::GetClanName( CSteamID steamIDClan )
{
	//Com_Printf(0, "[CSteamFriends005] GetClanName\n");
	return "c14n";
}

int CSteamFriends005::GetFriendCountFromSource( CSteamID steamIDSource )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendCountFromSource\n");
	return 0;
}

CSteamID CSteamFriends005::GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend )
{
	//Com_Printf(0, "[CSteamFriends005] GetFriendFromSourceByIndex\n");
	return CSteamID();
}

bool CSteamFriends005::IsUserInSource( CSteamID steamIDUser, CSteamID steamIDSource )
{
	//Com_Printf(0, "[CSteamFriends005] IsUserInSource\n");
	return false;
}

void CSteamFriends005::SetInGameVoiceSpeaking( CSteamID steamIDUser, bool bSpeaking )
{
	//Com_Printf(0, "[CSteamFriends005] SetInGameVoiceSpeaking\n");
}

void CSteamFriends005::ActivateGameOverlay( const char *pchDialog )
{
	//Com_Printf(0, "[CSteamFriends005] ActivateGameOverlay\n");
}

void CSteamFriends005::ActivateGameOverlayToUser( const char *pchDialog, CSteamID steamID )
{
	//Com_Printf(0, "[CSteamFriends005] ActivateGameOverlayToUser\n");
}

void CSteamFriends005::ActivateGameOverlayToWebPage( const char *pchURL )
{
	//Com_Printf(0, "[CSteamFriends005] ActivateGameOverlayToWebPage(%s)\n", pchURL);
}

void CSteamFriends005::ActivateGameOverlayToStore( AppId_t nAppID )
{
	//Com_Printf(0, "[CSteamFriends005] ActivateGameOverlayToStore\n");
}

void CSteamFriends005::SetPlayedWith( CSteamID steamIDUserPlayedWith )
{
	//Com_Printf(0, "[CSteamFriends005] SetPlayedWith\n");
}