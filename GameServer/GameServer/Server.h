<<<<<<< Updated upstream
#pragma once
#include "pch.h"
#include <winsock2.h>
#include <windows.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>

extern std::unordered_map<std::string, SOCKET> clients;
extern std::mutex clientsMutex;

void InitializeServer();
void StartServer();
void ShutdownServer();
void WorkerThread(HANDLE completionPort);
=======
#pragma once
#include "pch.h"
#include <winsock2.h>
#include <windows.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>

extern std::unordered_map<std::string, SOCKET> clients;
extern std::mutex clientsMutex;

void InitializeServer();
void StartServer();
void ShutdownServer();
void WorkerThread(HANDLE completionPort);
>>>>>>> Stashed changes
