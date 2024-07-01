#include "pch.h"
#include "Whisper.h"
#include "UserManager.h"
#include "ClientHandler.h"
#include <iostream>

void HandleWhisperMessage( const std::string& sender, const std::string& receiver, const std::string& message) {
        
    std::string senderMessage = "[귓속말] << "+ sender+ " : " + message;
    std::string recvMessage = "[귓속말] " + sender + " >> " + " : " + message;
    SendMessageToUser(sender, senderMessage);

    SendMessageToUser(receiver, recvMessage);
   
    
    
}
