#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

bool FileManager::saveSession(const TypingSession& session, const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs) return false;
    ofs << session.getReferenceText() << "\n";
    for (auto& ev : session.getEvents()) {
        ofs << ev.character << " " << (ev.isBackspace ? 1 : 0) << "\n";
    }
    return true;
}

TypingSession FileManager::loadSession(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) throw std::runtime_error("Cannot open file");
    std::string ref;
    std::getline(ifs, ref);
    TypingSession sess(ref);
    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        char ch; int bs;
        if (!(iss >> ch >> bs)) continue;
        sess.addEvent(ch, bs != 0);
    }
    return sess;
}