// Hosting wbesite: https://www.awardspace.com/
// Username: fasung.jakub@yahoo.com
// Password: K1641601
//
// phpAdmin website: https://supportindeed.com/phpMyAdmin4/index.php
// Username: 3055381_urbanops
// Password: 5952960510K1641601

#if defined _WIN32 || defined _WIN64
	#include <Windows.h>
    #define DLLEXPORT __declspec(dllexport)
	#define CURL_STATICLIB
	#include "x64/include/curl/curl.h"
	#include <string>

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
static CURL * curl = nullptr;
static std::string errorMessage = "Does not contain any errors.";
static std::string databaseMessage;
static bool bHasError = false;
static bool bIsCurlInitialized = false;
static bool bIsUserLogIn = false;
static std::string Nickname = "";
static std::string Username = "";
#pragma data_seg()
#pragma comment(linker, "/section:.SHARED,RWS")

/** Override curl functions */
static int WriteCallback(char* data, size_t size, size_t nmemb, std::string* writerData)
{
	if (writerData == nullptr) return 0;

	writerData->append(data, size * nmemb);
	return size * nmemb;
}

extern "C"
{
	DLLEXPORT void Initialize()
	{
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();

		if (curl) bIsCurlInitialized = true;
		else
		{
			errorMessage = "ERROR: Curl could not initialize. Inside Initialize function";
			bHasError = true;
			bIsCurlInitialized = false;
		}
	}

	DLLEXPORT bool IsInitialized()				
	{
		return bIsCurlInitialized;
	}

	DLLEXPORT bool Login()
	{
		if (curl)
		{

			return bIsUserLogIn;
		}


		else
		{
			errorMessage = "ERROR: Curl is not initialize. Inside Login function";
			return false;
		}
	}
	

	// Deprecated: Debug function DELETE THIS
	// Deprecated: Debug function DELETE THIS
	// Deprecated: Debug function DELETE THIS
	DLLEXPORT void SetStatus(bool newStatus)	
	{
		bIsCurlInitialized = newStatus;
	}


	DLLEXPORT const char* GetClientAddress()
	{
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, "http://api.ipify.org/");
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &databaseMessage);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			CURLcode code = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			return databaseMessage.c_str();
		}

		else
		{
			errorMessage = "ERROR: Could not read website.";
			bHasError = true;
			return nullptr;
		}
	}
}