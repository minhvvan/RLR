// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

/**
 * 
 */
class RLR_API FNetworkReceiver : public FRunnable
{
public:
    FNetworkReceiver(FSocket* InSocket);
    virtual ~FNetworkReceiver();

    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;

private:
    void ProcessReceivedData(const uint8* Data, int32 Size);

    FSocket* Socket;
    FThreadSafeBool bStopRequested;
};


