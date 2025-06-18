#pragma once
#include "KeyEvent.h"
#include <vector>
#include <string>

class TypingSession {
private:
    std::vector<KeyEvent> events;
    std::string referenceText;
public:
    TypingSession(const std::string& reference);
    void addEvent(char ch, bool isBackspace);
    const std::vector<KeyEvent>& getEvents() const;
    const std::string& getReferenceText() const;
};