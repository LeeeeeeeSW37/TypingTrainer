#pragma once
#include "TypingSession.h"
#include <string>

class FileManager {
public:
    static bool saveSession(const TypingSession& session, const std::string& filename);
    static TypingSession loadSession(const std::string& filename);
};