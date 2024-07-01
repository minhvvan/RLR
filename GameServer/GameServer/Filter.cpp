<<<<<<< Updated upstream
#include "pch.h"
#include "Filter.h"
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> filterWords = { "씨발", "섹스", "개새끼" };

std::string FilterMessage(const std::string& message) {
    std::string filteredMessage = message;
    for (const std::string& word : filterWords) {
        size_t pos = 0;
        while ((pos = filteredMessage.find(word, pos)) != std::string::npos) {
            filteredMessage.replace(pos, word.length(), std::string(word.length(), '*'));
            pos += word.length();
        }
    }
    return filteredMessage;
}
=======
#include "pch.h"
#include "Filter.h"
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> filterWords = { "씨발", "섹스", "개새끼" };

std::string FilterMessage(const std::string& message) {
    std::string filteredMessage = message;
    for (const std::string& word : filterWords) {
        size_t pos = 0;
        while ((pos = filteredMessage.find(word, pos)) != std::string::npos) {
            filteredMessage.replace(pos, word.length(), std::string(word.length(), '*'));
            pos += word.length();
        }
    }
    return filteredMessage;
}
>>>>>>> Stashed changes
