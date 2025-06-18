#pragma once
#include "TypingSession.h"
#include <vector>
#include <map>

struct AnalysisResult {
    double accuracy;
    std::vector<int> errorPositions;
    double averageSpeed;
    std::map<char, int> backspaceStats;
    std::vector<double> intervalsMs;
};

class Analyzer {
public:
    static AnalysisResult analyze(const TypingSession& session);
};