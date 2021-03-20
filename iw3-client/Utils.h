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

using namespace std;

void Trace(char* source, char* message, ...);
const char *va( const char *fmt, ... );

#define GAME_FLAG_DUMPDATA		(1 << 0)
#define GAME_FLAG_DEDICATED		(1 << 1)

#define GAME_FLAG(x)			((_gameFlags & x) == x)

extern unsigned int _gameFlags;
void DetermineGameFlags();
wchar_t *convertCharArrayToLPCWSTR(const char* charArray);
void callVoid(DWORD address);
bool UnprotectModule(const char* moduleName);
vector<string> explode(const string& str, const string& delimiters = " ");
unsigned int oneAtATimeHash(char* inpStr);
void* malloc_n(size_t size);
DWORD FindPattern(DWORD p_StartAddress, DWORD p_SearchLength, PBYTE p_Pattern, const char* p_Mask);
