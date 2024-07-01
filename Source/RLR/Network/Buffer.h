// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class RLR_API Buffer
{
public:
	Buffer();
	~Buffer();
};

class RLR_API SendBuffer : public TSharedFromThis<SendBuffer>
{
public:
	SendBuffer(int32 bufferSize);
	~SendBuffer();

	uint8* GetBuffer() { return _buffer.GetData(); }
	int32 WriteSize() const { return _writeSize; }
	int32 Capacity() const { return _buffer.Num(); }
	
	void CopyData(const void* data, int32 len);
	void Close(int32 writeSize);

private:
	TArray<uint8> _buffer;
	int32 _writeSize = 0;
};

class RLR_API RecvBuffer
{
	enum { BUFFER_COUNT = 10 };

public:
	RecvBuffer(int32 bufferSize);
	~RecvBuffer();

	void Clean();
	bool OnRead(int32 numOfBytes);
	bool OnWrite(int32 numOfBytes);

	uint8* ReadPos() { return _buffer.GetData() + _readPos; }
	uint8* WritePos() { return _buffer.GetData() + _writePos; }
	int32 DataSize() const { return _writePos - _readPos; }
	int32 FreeSize() const { return _capacity - _writePos; }

private:
	int32 _capacity = 0;
	int32 _bufferSize = 0;
	int32 _readPos = 0;
	int32 _writePos = 0;
	TArray<uint8> _buffer;
};
