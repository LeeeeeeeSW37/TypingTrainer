#include "Trainer.h"
#include <sstream>
#include <set>

std::vector<std::string> Trainer::generateTrainingSentences(
    const std::vector<int>& errorPositions,
    const std::string& reference)
{
    std::vector<std::string> words;
    std::vector<std::pair<int, int>> ranges;
    std::istringstream iss(reference);
    int cursor = 0;
    std::string w;
    while (iss >> w) {
        size_t pos = reference.find(w, cursor);
        if (pos == std::string::npos) break;
        words.push_back(w);
        ranges.emplace_back((int)pos, (int)(pos + w.size()));
        cursor = (int)pos + (int)w.size();
    }

    std::set<int> idxs;
    for (int p : errorPositions) {
        for (int i = 0; i < (int)ranges.size(); ++i) {
            // C++17 없이 호환되도록 변경
            int s = ranges[i].first;
            int e = ranges[i].second;
            if (p >= s && p < e) {
                idxs.insert(i);
                break;
            }
        }
    }

    std::vector<std::string> result;
    for (int i : idxs)
        result.push_back(words[i]);
    return result;
}
