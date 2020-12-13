/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : definitions.h Header
** - Description : Engine structures/functions definitions
** - Author      : N/A
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** [Copyright © ULTRAMOD/Hosseinpourziyaie 2020] <hosseinpourziyaie@gmail.com>
**
************************************************************************************/

#pragma once

//---------------------------------------------------------------------------------------------------------//
//---------------------------                                                   ---------------------------//
//---------------------------                     Structs                       ---------------------------//
//---------------------------                                                   ---------------------------//
//---------------------------------------------------------------------------------------------------------//
typedef struct
{
	int x;					//0x0000
	int y;					//0x0004
	int Width;			    //0x0008
	int Height;			    //0x000C
	char _0x0010[0x10];		//0x0010
	float viewOrigin[3];	//0x0020
	char _0x002C[0x08];		//0x002C
	float* viewAxis[0x3];   //0x0034
	//size: 0x0058
} refdef_s;


typedef enum
{
	DVAR_FLAG_NONE			= 0x0,			//no flags
	DVAR_FLAG_SAVED		    = 0x1,			//saves in config_mp.cfg for clients
	DVAR_FLAG_LATCHED		= 0x2,			//no changing apart from initial value (although it might apply on a map reload, I think)
	DVAR_FLAG_CHEAT			= 0x4,			//cheat
	DVAR_FLAG_REPLICATED	= 0x8,			//on change, this is sent to all clients (if you are host)
	DVAR_FLAG_UNKNOWN10		= 0x10,			//unknown
	DVAR_FLAG_UNKNOWN20		= 0x20,			//unknown
	DVAR_FLAG_UNKNOWN40		= 0x40,			//unknown
	DVAR_FLAG_SERVER		= 0x80,			//server dvar
	DVAR_FLAG_USERCREATED	= 0x100,		//a 'set' type command created it
	DVAR_FLAG_USERINFO		= 0x200,		//userinfo?
	DVAR_FLAG_SERVERINFO	= 0x400,		//in the getstatus oob
	DVAR_FLAG_WRITEPROTECTED= 0x800,		//write protected
	DVAR_FLAG_UNKNOWN1000	= 0x1000,		//unknown
	DVAR_FLAG_READONLY		= 0x2000,		//read only (same as 0x800?)
	DVAR_FLAG_UNKNOWN4000	= 0x4000,		//unknown
	DVAR_FLAG_UNKNOWN8000	= 0x8000,		//unknown
	DVAR_FLAG_UNKNOWN10000  = 0x10000,		//unknown
	DVAR_FLAG_DEDISAVED		= 0x1000000,		//unknown
	DVAR_FLAG_NONEXISTENT	= 0xFFFFFFFF	//no such dvar
} dvar_flag;

typedef enum
{
	DVAR_TYPE_BOOL		= 0,
	DVAR_TYPE_FLOAT		= 1,
	DVAR_TYPE_FLOAT_2	= 2,
	DVAR_TYPE_FLOAT_3	= 3,
	DVAR_TYPE_FLOAT_4	= 4,
	DVAR_TYPE_INT		= 5,
	DVAR_TYPE_ENUM		= 6,
	DVAR_TYPE_STRING	= 7,
	DVAR_TYPE_COLOR		= 8,
	//DVAR_TYPE_INT64	= 9 only in Tx
} dvar_type;
// 67/72 bytes figured out
union dvar_value_t {
		char*	string;
		int		integer;
		float	value;
		bool	boolean;
		float	vec2[2];
		float	vec3[3];
		float	vec4[4];
		BYTE	color[4]; //to get float: multiply by 0.003921568859368563 - BaberZz
		//__int64 integer64; only in Tx
};
union dvar_maxmin_t {
	int i;
	float f;
};
typedef struct dvar_t
{
	//startbyte:endbyte
	const char*		name; //0:3
	const char*		description; //4:7
	unsigned int	flags; //8:11
	char			type; //12:12
	char			pad2[3]; //13:15
	dvar_value_t	current; //16:31
	dvar_value_t	latched; //32:47
	dvar_value_t	default; //48:64
	dvar_maxmin_t min; //65:67
	dvar_maxmin_t max; //68:72 woooo
} dvar_t;

typedef struct cmd_function_s
{
	char pad[24];
} cmd_function_t;

enum errorParm_s
{
	ERR_FATAL,                  // exit the entire game with a popup window
	ERR_DROP,                   // print to console and disconnect from game
	ERR_SERVERDISCONNECT,       // don't kill server
	ERR_DISCONNECT,             // client disconnected from the server
	ERR_NEED_CD                 // pop up the need-cd dialog
};

typedef struct  
{
	char type;
	char pad[3];
	const char** folder;
	const char* file;
} StreamFile;

typedef struct  
{
	char pad[20];
	StreamFile* stream;
	char pad2[76];
} snd_alias_t;

typedef struct  
{
	const char* name;
	snd_alias_t* aliases;
	int numAliases;
} snd_alias_list_t;

/*typedef struct fontEntry_s
{
	unsigned short character;
	unsigned char padLeft;
	unsigned char padTop;
	unsigned char padRight;
	unsigned char width;
	unsigned char height;
	unsigned char const0;
	float uvLeft;
	float uvTop;
	float uvRight;
	float uvBottom;
} fontEntry_t;

typedef struct Font_s
{
	char* name;
	int size;
	int entries;
	Material* image;
	Material* glowImage;
	fontEntry_t* characters;
} Font;*/

//---------------------------------------------------------------------------------------------------------//
//---------------------------                                                   ---------------------------//
//---------------------------                     Functions                     ---------------------------//
//---------------------------                                                   ---------------------------//
//---------------------------------------------------------------------------------------------------------//

// types
typedef void (__cdecl * CommandCB_t)(void);

extern "C"
{
//---------------------------                                                   ---------------------------//
	typedef int (__cdecl * CL_IsCgameInitialized_t)();
extern CL_IsCgameInitialized_t CL_IsCgameInitialized;

//---------------------------                                                   ---------------------------//
typedef void* (__cdecl * R_RegisterFont_t)(const char* font, int imageTrack);
extern R_RegisterFont_t R_RegisterFont;

typedef void (__cdecl * R_AddCmdDrawText_t)(const char* text, int, void* font, float screenX, float screenY, float, float, float rotation, float* color, int);
extern R_AddCmdDrawText_t R_AddCmdDrawText;

typedef void (_cdecl * R_AddCmdDrawStretchPic_t)(float x, float y, float w, float h, float xScale, float yScale, float xay, float yay, const float *color, void* material);
extern R_AddCmdDrawStretchPic_t R_AddCmdDrawStretchPic;

typedef int (__cdecl * R_TextWidth_t)(const char* text, int maxlength, void* font);
extern R_TextWidth_t R_TextWidth;

//---------------------------                                                   ---------------------------//
typedef void(__cdecl * Com_Error_t)(errorParm_s type, const char* message, ...);
extern Com_Error_t Com_Error;

typedef void (__cdecl * Com_Printf_t)(int, const char*, ...);
extern Com_Printf_t Com_Printf;

typedef void (__cdecl * Com_PrintError_t)(int, const char*, ...);
extern Com_PrintError_t Com_PrintError;

typedef int (__cdecl * Com_Milliseconds_t)(void);
extern Com_Milliseconds_t Com_Milliseconds;

//---------------------------                                                   ---------------------------//
typedef char* (__cdecl * SE_Load_t)(char* file, int Unk);
extern SE_Load_t SE_Load;

//---------------------------                                                   ---------------------------//
typedef dvar_t* (__cdecl * Dvar_RegisterBool_t)(const char* name, bool default, int flags, const char* description);
extern Dvar_RegisterBool_t Dvar_RegisterBool;

typedef dvar_t* (__cdecl * Dvar_RegisterFloat_t)(const char* name, float default, float min, float max, int flags, const char* description);
extern Dvar_RegisterFloat_t Dvar_RegisterFloat;

typedef dvar_t* (__cdecl * Dvar_RegisterFloat2_t)(const char* name, float defx, float defy, float min, float max, int flags, const char* description);
extern Dvar_RegisterFloat2_t Dvar_RegisterFloat2;

typedef dvar_t* (__cdecl * Dvar_RegisterFloat3_t)(const char* name, float defx, float defy, float defz, float min, float max, int flags, const char* description);
extern Dvar_RegisterFloat3_t Dvar_RegisterFloat3;

typedef dvar_t* (__cdecl * Dvar_RegisterFloat4_t)(const char* name, float defx, float defy, float defz, float defw, float min, float max, int flags, const char* description);
extern Dvar_RegisterFloat4_t Dvar_RegisterFloat4;

typedef dvar_t* (__cdecl * Dvar_RegisterInt_t)(const char* name, int default, int min, int max, int flags, const char* description);
extern Dvar_RegisterInt_t Dvar_RegisterInt;

typedef dvar_t* (__cdecl * Dvar_RegisterEnum_t)(const char* name, char** enumValues, int default, int flags, const char* description);
extern Dvar_RegisterEnum_t Dvar_RegisterEnum;

typedef dvar_t* (__cdecl * Dvar_RegisterString_t)(const char* name, const char* default, int, const char*);
extern Dvar_RegisterString_t Dvar_RegisterString;

typedef dvar_t* (__cdecl * Dvar_RegisterColor_t)(const char* name, float r, float g, float b, float a, int flags, const char* description);
extern Dvar_RegisterColor_t Dvar_RegisterColor;

typedef dvar_t* (__cdecl * Dvar_FindVar_t)(char* dvar);
extern Dvar_FindVar_t Dvar_FindVar;

typedef char* (__cdecl* Dvar_InfoString_Big_t)(int typeMask);
extern Dvar_InfoString_Big_t Dvar_InfoString_Big;

typedef dvar_t* (__cdecl * Dvar_SetCommand_t)(const char* name, const char* value);
extern Dvar_SetCommand_t Dvar_SetCommand;

typedef int (__cdecl * Dvar_SetStringByName_t)(const char* name, const char* value);
extern Dvar_SetStringByName_t Dvar_SetStringByName;

typedef char* (__cdecl * Dvar_GetString_t)(dvar_t* dvar);
extern Dvar_GetString_t Dvar_GetString;

//---------------------------                                                   ---------------------------//
typedef void (__cdecl * Cmd_ExecuteSingleCommand_t)(int controller, int a2, const char* cmd);
extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;

typedef void (__cdecl * Cbuf_AddText_t)(int a1, const char* cmd);
extern Cbuf_AddText_t Cbuf_AddText;
	
typedef void (__cdecl * SV_GameSendServerCommand_t)(int targetEntity, int a2, const char* command);
extern SV_GameSendServerCommand_t SV_GameSendServerCommand;

typedef void (__cdecl * Cmd_AddCommand_t)(const char* name, CommandCB_t callback, cmd_function_t* data, char);
extern Cmd_AddCommand_t Cmd_AddCommand;

typedef void (__cdecl * Cmd_AddServerCommand_t)(const char* name, CommandCB_t callback, cmd_function_t* data);
extern Cmd_AddServerCommand_t Cmd_AddServerCommand;


};

extern dvar_t** dvarName;
extern dvar_t** r_mode;

extern char* language;

extern DWORD drawDevStuffHookLoc;
extern DWORD winMainInitHookLoc;
extern DWORD localizeAssetHookLoc;
extern DWORD SELoadLanguageHookLoc;
extern DWORD SetStringHookLoc;
extern DWORD loadGameOverlayHookLoc;
extern DWORD findSoundAliasHookLoc;
extern DWORD printVersionHookLoc;
