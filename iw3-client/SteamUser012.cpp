/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : SteamBase.cpp Source
** - Description : ISteamUser012 implementation
** - Author      : OSW Corp?
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** 
**
************************************************************************************/

#include "stdafx.h"
#include "SteamUser012.h"

HSteamUser CSteamUser012::GetHSteamUser()
{
	return NULL;
}

bool CSteamUser012::LoggedOn()
{
	return true;
}

CSteamID CSteamUser012::GetSteamID()
{
	return CSteamID();
}

int CSteamUser012::InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
#ifdef USE_NP
	if (Legacy_IsLegacyMode())
	{
#endif
		unsigned int steamID = GetSteamID().GetAccountID();
		memcpy(pAuthBlob, &steamID, 4);

		return 4;
#ifdef USE_NP
	}

	//memset(pAuthBlob, 0xdd, cbMaxAuthBlob);
	if (!NP_GetUserTicket(pAuthBlob, cbMaxAuthBlob, steamIDGameServer.ConvertToUint64()))
	{
		Com_Error(2, "Could not get NP user ticket.");
	}

	return sizeof(NPAuthenticateTicket);
#endif
}

void CSteamUser012::TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
{
}

void CSteamUser012::TrackAppUsageEvent(CGameID gameID, EAppUsageEvent eAppUsageEvent, const char *pchExtraInfo)
{
}

bool CSteamUser012::GetUserDataFolder(char *pchBuffer, int cubBuffer)
{
	return true;
}

void CSteamUser012::StartVoiceRecording()
{
}

void CSteamUser012::StopVoiceRecording()
{
}

EVoiceResult CSteamUser012::GetCompressedVoice(void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten)
{
	return k_EVoiceResultOK;
}

EVoiceResult CSteamUser012::DecompressVoice(void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten)
{
	return k_EVoiceResultOK;
}

HAuthTicket CSteamUser012::GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	return 0;
}

EBeginAuthSessionResult CSteamUser012::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	return k_EBeginAuthSessionResultOK;
}

void CSteamUser012::EndAuthSession(CSteamID steamID)
{

}

void CSteamUser012::CancelAuthTicket(HAuthTicket hAuthTicket)
{

}

uint32 CSteamUser012::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
	return 1;
}
