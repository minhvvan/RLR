<<<<<<< Updated upstream
#pragma once
#include "pch.h"
#include <unordered_map>
#include <string>
#include <winsock2.h>

struct User {
    SOCKET socket;
    std::string username;
    std::string location;  // 위치 정보
    std::string guild;     // 길드 정보
    std::string party;     // 파티 정보
    std::string raid;      // 레이드 정보
    std::string country;   // 국가 정보
    std::string continent; // 대륙 정보
};

enum ChatScope {
    GENERAL,   // 일반
    WHISPER,   // 귓속말
    NEARBY,    // 동료
    PARTY,     // 파티
    GUILD,     // 길드
    RAID,      // 레이드
    COUNTRY,   // 국가
    CONTINENT,  // 대륙
    WORLD       // 세계
};

extern std::mutex clientsMutex;

extern std::unordered_map<std::string, User> users;

// 컨텐츠별 메세지
void SendMessageToScope(const std::string& senderId, const std::string& message, ChatScope scope);
// 1명에게 보내는 메세지
void  SendMessageToUser(const std::string& username, const std::string& message);
void  BroadcastMessage(const std::string& message);
// 모두에게 보내는 메세지
void  SendToClient(SOCKET clientSocket, const std::string& message);



=======
#pragma once
#include "pch.h"
#include <unordered_map>
#include <string>
#include <winsock2.h>

struct User {
    SOCKET socket;
    std::string username;
    std::string location;  // 위치 정보
    std::string guild;     // 길드 정보
    std::string party;     // 파티 정보
    std::string raid;      // 레이드 정보
    std::string country;   // 국가 정보
    std::string continent; // 대륙 정보
};

enum ChatScope {
    GENERAL,   // 일반
    WHISPER,   // 귓속말
    NEARBY,    // 동료
    PARTY,     // 파티
    GUILD,     // 길드
    RAID,      // 레이드
    COUNTRY,   // 국가
    CONTINENT,  // 대륙
    WORLD       // 세계
};

extern std::mutex clientsMutex;

extern std::unordered_map<std::string, User> users;

// 컨텐츠별 메세지
void SendMessageToScope(const std::string& senderId, const std::string& message, ChatScope scope);
// 1명에게 보내는 메세지
void  SendMessageToUser(const std::string& username, const std::string& message);
void  BroadcastMessage(const std::string& message);
// 모두에게 보내는 메세지
void  SendToClient(SOCKET clientSocket, const std::string& message);



>>>>>>> Stashed changes
