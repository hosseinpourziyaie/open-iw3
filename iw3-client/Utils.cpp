// ==========================================================
// alterIWnet project
// 
// Component: aiw_client
// Sub-component: steam_api
// Purpose: Various generic utility functions.
//
// Initial author: NTAuthority
// Started: 2010-09-10
// ==========================================================

#include "StdInc.h"
#include <ShellAPI.h>

using namespace std;
void Main_UnprotectModule(HMODULE hModule);

// unmanaged as this uses vararg natively
#pragma unmanaged
void Trace(char* source, char* message, ...)
{
	va_list args;
	char buffer[1024];
	char buffer2[1024];

	va_start(args, message);
	_vsnprintf(buffer, sizeof(buffer), message, args);
	va_end(args);

	_snprintf(buffer2, sizeof(buffer2), "[%s] %s\n", source, buffer);

	OutputDebugStringA(buffer2);
}

// a funny thing is how this va() function could possibly come from leaked IW code.
#define VA_BUFFER_COUNT		4
#define VA_BUFFER_SIZE		4096

static char g_vaBuffer[VA_BUFFER_COUNT][VA_BUFFER_SIZE];
static int g_vaNextBufferIndex = 0;

const char *va( const char *fmt, ... )
{
	va_list ap;
	char *dest = &g_vaBuffer[g_vaNextBufferIndex][0];
	g_vaNextBufferIndex = (g_vaNextBufferIndex + 1) % VA_BUFFER_COUNT;
	va_start(ap, fmt);
	vsprintf( dest, fmt, ap );
	va_end(ap);
	return dest;
}

extern int printError;
extern errorParm_s printErrorType;
extern char* printErrorMessage;

void Com_Error_Thread(errorParm_s type, const char* message, ...)
{	
	va_list ap;
	char *dest = &g_vaBuffer[g_vaNextBufferIndex][0];
	g_vaNextBufferIndex = (g_vaNextBufferIndex + 1) % VA_BUFFER_COUNT;
	va_start(ap, message);
	vsprintf( dest, message, ap );
	va_end(ap);

	printErrorType = type;
	printErrorMessage = dest;
	printError = true;
}

unsigned int _gameFlags;

typedef struct  
{
	const wchar_t* argument;
	unsigned int flag;
} flagDef_t;

flagDef_t flags[] =
{
	{ L"dump", GAME_FLAG_DUMPDATA },
	{ L"dedicated", GAME_FLAG_DEDICATED },
	{ 0, 0 }
};

void DetermineGameFlags()
{
	int numArgs;
	LPCWSTR commandLine = GetCommandLineW();
	LPWSTR* argv = CommandLineToArgvW(commandLine, &numArgs);

	for (int i = 0; i < numArgs; i++)
	{
		if (argv[i][0] != L'-') continue;

		for (wchar_t* c = argv[i]; *c != L'\0'; c++)
		{
			if (*c != L'-')
			{
				for (flagDef_t* flag = flags; flag->argument; flag++)
				{
					if (!wcscmp(c, flag->argument))
					{
						_gameFlags |= flag->flag;
						break;
					}
				}
				break;
			}
		}
	}

	LocalFree(argv);
}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString=new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void callVoid(DWORD address)
{
	__asm
	{
		call address
	}
}

vector<string> explode(const string& str, const string& delimiters)
{
	vector<string> tokens;

	auto subStrBeginPos = str.find_first_not_of(delimiters, 0);
	auto subStrEndPos = str.find_first_of(delimiters, subStrBeginPos);

	while(string::npos != subStrBeginPos || string::npos != subStrEndPos)
	{
		tokens.push_back(str.substr(subStrBeginPos, subStrEndPos-subStrBeginPos));

		subStrBeginPos = str.find_first_not_of(delimiters, subStrEndPos);
		subStrEndPos = str.find_first_of(delimiters, subStrBeginPos);
	}

	return tokens;
}

unsigned int oneAtATimeHash(char* inpStr)
{
	unsigned int value = 0,temp = 0;
	for(size_t i=0;i<strlen(inpStr);i++)
	{
		char ctext = tolower(inpStr[i]);
		temp = ctext;
		temp += value;
		value = temp << 10;
		temp += value;
		value = temp >> 6;
		value ^= temp;
	}
	temp = value << 3;
	temp += value;
	unsigned int temp2 = temp >> 11;
	temp = temp2 ^ temp;
	temp2 = temp << 15;
	value = temp2 + temp;
	if(value < 2) value += 2;
	return value;
}

bool UnprotectModule(const char* moduleName)
{
	HMODULE module = GetModuleHandle(moduleName);

	if(module)
	{
		Main_UnprotectModule(module);
		return true;
	}
	return false;
}

#define	MAX_INFO_STRING		1024
#define	MAX_INFO_KEY		  1024
#define	MAX_INFO_VALUE		1024

/*
===================
Info_RemoveKey
===================
*/
void Info_RemoveKey( char *s, const char *key ) {
	char	*start;
	char	pkey[MAX_INFO_KEY];
	char	value[MAX_INFO_VALUE];
	char	*o;

	if (strchr (key, '\\')) {
		return;
	}

	while (1)
	{
		start = s;
		if (*s == '\\')
			s++;
		o = pkey;
		while (*s != '\\')
		{
			if (!*s)
				return;
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value;
		while (*s != '\\' && *s)
		{
			if (!*s)
				return;
			*o++ = *s++;
		}
		*o = 0;

		if (!strcmp (key, pkey) )
		{
			strcpy (start, s);	// remove this part
			return;
		}

		if (!*s)
			return;
	}

}

/*
==================
Info_SetValueForKey

Changes or adds a key/value pair
==================
*/
void Info_SetValueForKey( char *s, const char *key, const char *value ) {
	char    newi[MAX_INFO_STRING];
	const char* blacklist = "\\;\"";

	if ( strlen( s ) >= MAX_INFO_STRING ) {
		Com_Printf( 0, "Info_SetValueForKey: oversize infostring");
		return;
	}

	for(; *blacklist; ++blacklist)
	{
		if (strchr (key, *blacklist) || strchr (value, *blacklist))
		{
			Com_Printf (0, "Can't use keys or values with a '%c': %s = %s\n", *blacklist, key, value);
			return;
		}
	}

	Info_RemoveKey (s, key);
	if (!value || !strlen(value))
		return;

	_snprintf (newi, sizeof(newi), "\\%s\\%s", key, value);

	if (strlen(newi) + strlen(s) >= MAX_INFO_STRING)
	{
		Com_Printf (0, "Info string length exceeded\n");
		return;
	}

	strcat (newi, s);
	strcpy (s, newi);
}


size_t Com_AddToString(const char* string, char* buffer, size_t current, size_t length, bool escapeSpaces)
{
	const char* i = string;
	size_t margin = (escapeSpaces) ? 2 : 0;
	bool hadSpaces = false;

	if (length - current <= 0)
	{
		return current;
	}

	if (escapeSpaces)
	{
		if ((length - current) > margin)
		{
			while (*i != 0)
			{
				if (*i == ' ')
				{
					buffer[current++] = '"';
					hadSpaces = true;
					break;
				}

				i++;
			}
		}
	}

	i = string;
	while (*i != '\0')
	{
		if (length - current > margin)
		{
			buffer[current++] = *i;
		}

		i++;
	}

	if (hadSpaces)
	{
		buffer[current++] = '"';
	}

	return current;
}

#define	BIG_INFO_STRING		8192  // used for system info key only
#define	BIG_INFO_KEY		  8192
#define	BIG_INFO_VALUE		8192

/*
===============
Info_ValueForKey

Searches the string for the given
key and returns the associated value, or an empty string.
FIXME: overflow check?
===============
*/
char *Info_ValueForKey( const char *s, const char *key )
{
	char	pkey[BIG_INFO_KEY];
	static	char value[2][BIG_INFO_VALUE];	// use two buffers so compares
	// work without stomping on each other
	static	int	valueindex = 0;
	char	*o;

	if ( !s || !key ) {
		return "";
	}

	if ( strlen( s ) >= BIG_INFO_STRING ) {
		//Com_Error( ERR_DROP, "Info_ValueForKey: oversize infostring" );
		return "";
	}

	valueindex ^= 1;
	if (*s == '\\')
		s++;
	while (1)
	{
		o = pkey;
		while (*s != '\\')
		{
			if (!*s)
				return "";
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value[valueindex];

		while (*s != '\\' && *s)
		{
			*o++ = *s++;
		}
		*o = 0;

		if (!_stricmp (key, pkey) )
			return value[valueindex];

		if (!*s)
			break;
		s++;
	}

	return "";
}

// Allocate memory and zero out the buffer
void* malloc_n(size_t size)
{
	void* memPtr = malloc(size);
	memset(memPtr, 0, size);
	return memPtr;
}

DWORD FindPattern(DWORD p_StartAddress, DWORD p_SearchLength, PBYTE p_Pattern, const char* p_Mask)
{
	size_t s_MaskLength = strlen(p_Mask);

	for (DWORD i = 0; i < p_SearchLength - s_MaskLength; ++i)
	{
		int s_FoundBytes = 0;
		for (DWORD j = 0; j < s_MaskLength; ++j)
		{
			BYTE s_ByteRead = *(BYTE*)(void*)(p_StartAddress + i + j);

			if (s_ByteRead != p_Pattern[j] && p_Mask[j] != '?')
				break;

			++s_FoundBytes;

			if (s_FoundBytes == s_MaskLength)
				return p_StartAddress + i;
		}
	}

	return NULL;
}