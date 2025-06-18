#pragma once
#include <vector>
#include <string>

namespace Trainer {
    // errorCounts: referenceText �� �ε����� ��Ÿ �߻� Ƚ��
    // reference: ��ü ���� ����
    std::vector<std::string> generateTrainingSentences(
        const std::vector<int>& errorCounts,
        const std::string& reference);
}
