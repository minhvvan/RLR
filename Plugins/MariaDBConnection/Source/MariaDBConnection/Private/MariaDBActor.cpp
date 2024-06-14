// Fill out your copyright notice in the Description page of Project Settings.



#include "MariaDBActor.h"
#include "MariaDBConnection/Mariac/include/mysql.h"
#include <iostream>   


// Sets default values
AMariaDBActor::AMariaDBActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMariaDBActor::BeginPlay()
{
	Super::BeginPlay();
    
    
}

// Called every frame
void AMariaDBActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AMariaDBActor::GetPlayerID() {
    MYSQL* conn = mysql_init(nullptr);
    if (conn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize MySQL connection."));
        return FString();
    }

    conn = mysql_real_connect(conn, "3.39.196.61", "root", "dnflskfk1", "ReLife_Schema", 3306, nullptr, 0);
    if (conn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to database: %s"), ANSI_TO_TCHAR(mysql_error(conn)));
        mysql_close(conn);
        return FString();
    }

    UE_LOG(LogTemp, Warning, TEXT("Connected to database successfully."));
    int queryResult = mysql_query(conn, "SELECT * FROM PLAYER");
    if (queryResult != 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to execute database query: %s"), ANSI_TO_TCHAR(mysql_error(conn)));
        mysql_close(conn);
        return FString();
    }

    // ���� ���࿡ ������ ��쿡�� ����� ������
    MYSQL_RES* result = mysql_store_result(conn);
    if (result == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get query result: %s"), ANSI_TO_TCHAR(mysql_error(conn)));
        mysql_close(conn);
        return FString();
    }

    // ��� ó��
    MYSQL_ROW row = mysql_fetch_row(result);
    FString playerID;
    if (row != nullptr)
    {
        playerID = UTF8_TO_TCHAR(row[1]);
    }

    // ��� ����
    mysql_free_result(result);

    // ���� ����
    mysql_close(conn);
    return playerID;
}