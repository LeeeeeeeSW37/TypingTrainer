#include "TypingSession.h"
TypingSession::TypingSession(const std::string& reference)
    : referenceText(reference) {}
void TypingSession::addEvent(char ch, bool isBackspace) {
    events.emplace_back(ch, isBackspace);
}
const std::vector<KeyEvent>& TypingSession::getEvents() const {
    return events;
}
const std::string& TypingSession::getReferenceText() const {
    return referenceText;
}