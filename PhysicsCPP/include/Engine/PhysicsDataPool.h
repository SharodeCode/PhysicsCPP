#pragma once
#include <vector>

struct FlatBallData {
    float x, y;
    float lastX, lastY;
    float radius;
};

class PhysicsDataPool {
public:
    std::vector<FlatBallData> ballData;

    // Allocate a slot, return index
    int allocateBall(float x, float y, float radius) {
        ballData.push_back({ x, y, x, y, radius });
        return (int)ballData.size() - 1;
    }

    FlatBallData& get(int index) { return ballData[index]; }
};
