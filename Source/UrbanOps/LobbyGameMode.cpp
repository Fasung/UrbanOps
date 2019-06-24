// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "FE_UserData.h"
#include "Engine.h"
//#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

ALobbyGameMode::ALobbyGameMode()
{
	if (FFE_UserDataModule::IsInitializedTest())
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Yellow, TEXT("True!"));
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Yellow, TEXT("False!"));
	}


	GameModeType = EGameMode::LOBBY_MODE;
}

FString ALobbyGameMode::GetPathDebug()
{
	return FFE_UserDataModule::GetLibraryPath();
}