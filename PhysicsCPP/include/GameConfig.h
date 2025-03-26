#pragma once

class GameConfig {
public:
    // 🌟 Changeable window size
    static void setWindowSize(int width, int height);

    static int WINDOW_WIDTH;
    static int WINDOW_HEIGHT;

    // 🚀 Adjustable settings
    static constexpr bool VSYNC_ENABLED = true;
    static constexpr int FRAME_RATE = 120;

    // ⚙️ Physics settings
    static constexpr float GRAVITY = 9.81f;
    static constexpr float ELASTICITY = 0.9f;
    static constexpr float FRICTION = 0.98f;
    static constexpr int SUBSTEP_COUNT = 3;
    static constexpr float pixelsPerMeter = 100.0f;

    // 🏀 Collision settings
    static constexpr float COLLISION_PUSH_FACTOR = 0.65f;
    static constexpr float BALL_RADIUS = 5.0f;
    static constexpr float BALL_MASS = 1.0f;
    static constexpr float BOUNDARY_RADIUS = 300.0f;
};