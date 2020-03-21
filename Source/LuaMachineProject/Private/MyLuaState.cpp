// Fill out your copyright notice in the Description page of Project Settings.

#include "MyLuaState.h"

UMyLuaState::UMyLuaState()
{
	Table.Add(TEXT("HelloWorldString"), FString(TEXT("Hello World I am UE4")));
	Table.Add(TEXT("FunnyNumber"), FLuaValue(17.223f));

}


