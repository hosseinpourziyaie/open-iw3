/************************************************************************************
____________________________  OPEN-IW3 COD4 CLIENT  __________________________******
***********************************************************************************
**
** - Name        : stdafx.h Header
** - Description : Standard includes for the code.
** - Author      : Hosseinpourziyaie
** - Note        : -----------------------------
** - Started on  : N/A    | Ended on : N/A
**
** [Copyright © ULTRAMOD/Hosseinpourziyaie 2020] <hosseinpourziyaie@gmail.com>
**
************************************************************************************/

#pragma once

#define _CRT_SECURE_NO_WARNINGS

// Windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// C/C++ headers
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <winsock.h>
#include <stdint.h>

// OSW headers
#define NO_STEAM // to reduce header amount needed
#include "CCallback.h"
#include "ISteamUser012.h"
#include "ISteamClient008.h"
#include "ISteamUserStats010.h"

// custom headers
#include "SteamBase.h"
#include "Utils.h"
#include "Hooking.h"

#include "definitions.h"

//#include "..\dependencies\tools\buildnumber.h"
#define BUILDNUMBER_STR "8"


//#define USING_IW_MASTER

#define CUSTOM_MASTER_IP "192.168.1.2"
#define CUSTOM_MASTER_PORT 20810

#define FS_BASEGAME "data"

#define VERSION "1.0." BUILDNUMBER_STR

#define VERSIONSTRING "OPEN-IW3 " VERSION

#define CONSOLESTRING VERSIONSTRING " (built " __DATE__ " " __TIME__ ")"


char* GetUsername();
