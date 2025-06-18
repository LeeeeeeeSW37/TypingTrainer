#pragma once
#include <vector>
#include <string>

namespace Trainer {
    // errorCounts: referenceText 각 인덱스별 오타 발생 횟수
    // reference: 전체 연습 문장
    std::vector<std::string> generateTrainingSentences(
        const std::vector<int>& errorCounts,
        const std::string& reference);
}
