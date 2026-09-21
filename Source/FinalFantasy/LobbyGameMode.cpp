// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "MultiplayerSessionsSubsystem.h"
#include "Engine/Engine.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PreInitializeComponents() {

	Super::PreInitializeComponents();

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance) {
		MultiplayerSubsessionSystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num(); // Get the number of players in the game state

		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Yellow, FString::Printf(TEXT("Player %s has joined the lobby. Total players: %d"), *NewPlayer->GetName(), NumberOfPlayers));
			GEngine->AddOnScreenDebugMessage(
				1, 
				600.f, 
				FColor::Yellow, 
				FString::Printf(TEXT("Total players: %d"), NumberOfPlayers)
			);

			if (NumberOfPlayers >= 2 && MultiplayerSubsessionSystem) 
			{
				MultiplayerSubsessionSystem->StartSession();
			}

			APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				
				GEngine->AddOnScreenDebugMessage(
					-1,
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT(" %s Has joined the Game"), *PlayerState->GetPlayerName())
				);
			}


		}


		  
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{

		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num(); // Get the number of players in the game state

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				600.f,
				FColor::Yellow,
				FString::Printf(TEXT("Total players: %d"), NumberOfPlayers - 1)
			);

			GEngine->AddOnScreenDebugMessage(
				-1,
				60.f,
				FColor::Cyan,
				FString::Printf(TEXT(" %s Has exited the Game"), *PlayerState->GetPlayerName())
			);
		}
	}
}


