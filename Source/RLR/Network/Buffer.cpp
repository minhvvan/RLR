// Fill out your copyright notice in the Description page of Project Settings.

#include "Network/Buffer.h"

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

/*----------------
	SendBuffer
-----------------*/

SendBuffer::SendBuffer(int32 bufferSize)
{
	_buffer.SetNumUninitialized(bufferSize);
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::CopyData(const void* data, int32 len)
{
	if (len > _buffer.Num())
	{
		_buffer.SetNumUninitialized(len);
	}
	FMemory::Memcpy(_buffer.GetData(), data, len);
	_writeSize = len;
}

void SendBuffer::Close(int32 writeSize)
{
	_writeSize = writeSize;
}

/*--------------
	RecvBuffer
----------------*/

RecvBuffer::RecvBuffer(int32 bufferSize) : _bufferSize(bufferSize)
{
	_capacity = bufferSize * BUFFER_COUNT;
	_buffer.SetNumUninitialized(_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	int32 dataSize = DataSize();
	if (dataSize == 0)
	{
		_readPos = _writePos = 0;
	}
	else
	{
		if (FreeSize() < _bufferSize)
		{
			FMemory::Memcpy(_buffer.GetData(), _buffer.GetData() + _readPos, dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}
	}
}

bool RecvBuffer::OnRead(int32 numOfBytes)
{
	if (numOfBytes > DataSize())
		return false;

	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(int32 numOfBytes)
{
	if (numOfBytes > FreeSize())
		return false;

	_writePos += numOfBytes;
	return true;
}
