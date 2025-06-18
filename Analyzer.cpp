#include "Analyzer.h"
#include <chrono>
AnalysisResult Analyzer::analyze(const TypingSession& session) {
    AnalysisResult res;
    const auto& events = session.getEvents();
    const auto& ref    = session.getReferenceText();
    std::string typed;
    for (const auto& ev : events) {
        if (ev.isBackspace) {
            if (!typed.empty()) typed.pop_back();
            res.backspaceStats['\b']++;
        } else {
            typed.push_back(ev.character);
        }
    }
    size_t len = typed.size(), correct = 0;
    for (size_t i = 0; i < len; ++i) {
        if (i < ref.size() && typed[i] == ref[i]) correct++;
        else res.errorPositions.push_back(int(i));
    }
    res.accuracy = len ? double(correct)/len : 0.0;
    double total = 0;
    for (size_t i = 1; i < events.size(); ++i) {
        double dt = std::chrono::duration_cast<std::chrono::milliseconds>(
            events[i].timestamp - events[i-1].timestamp).count();
        res.intervalsMs.push_back(dt);
        total += dt;
    }
    res.averageSpeed = res.intervalsMs.empty() ? 0 : total/res.intervalsMs.size();
    return res;
}