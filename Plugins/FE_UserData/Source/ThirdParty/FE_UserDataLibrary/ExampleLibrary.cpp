// Hosting wbesite: https://www.awardspace.com/
// Username: fasung.jakub@yahoo.com
// Password: K1641601
//
// phpAdmin website: https://supportindeed.com/phpMyAdmin4/index.php
// Username: 3055381_urbanops
// Password: 5952960510K1641601

#if defined _WIN32 || defined _WIN64
    #include <Windows.h>
	#include <string>

    #define DLLEXPORT __declspec(dllexport)
#else
    #include <stdio.h>
#endif

#ifndef DLLEXPORT
    #define DLLEXPORT
#endif

// Deprecated: Debug function
void Working() { MessageBox(NULL, TEXT("Working Wooop!"), NULL, MB_OK); }

// Code reference https://www.codeguru.com/cpp/misc/misc/ipctechniques/article.php/c305/Sharing-Data-Between-Different-Instances-of-the-Same-Module-DLL-or-EXE.htm
#pragma data_seg(".SHARED")
static bool bIsInitialized = false;
static bool bIsLogIn = false;
static std::string Nickname = "";
static std::string Username = "";

#pragma data_seg()
#pragma comment(linker, "/section:.SHARED,RWS")

extern "C"
{
	DLLEXPORT bool IsInitialized()				{ return bIsInitialized; }

	DLLEXPORT void SetStatus(bool newStatus)	{ bIsInitialized = newStatus; }
}