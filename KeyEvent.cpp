#include "KeyEvent.h"
KeyEvent::KeyEvent(char ch, bool backspace)
    : character(ch), isBackspace(backspace),
      timestamp(std::chrono::steady_clock::now()) {}