#pragma once
#include <string>
#include <chrono>

struct KeyEvent {
    char character;
    bool isBackspace;
    std::chrono::steady_clock::time_point timestamp;
    KeyEvent(char ch, bool backspace);
};