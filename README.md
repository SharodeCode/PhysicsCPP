**PhysicsCPP** is a modular 2D physics sandbox written in modern C++ using SFML. Currently it uses a pure Verlet integration system for simulating rigid body motion and collisions, with plans to add in differnet methods for experimentation. This program is designed for experimentation, learning, and future extensibility.

---

## 🚀 Features

- 🔄 **Sub-stepped Physics** – stable integration via configurable substeps
- 🟣 **Ball Spawner Scene** – spawn colored balls within a circular boundary
- 🧱 **Hollow Circular Boundary** – customizable collision container
- 🧠 **Grid-based Broadphase** – optimized collision detection using spatial hashing
- 🧪 **UI Controls** – buttons for spawning, muting, toggling modes
- 🎨 **Colorful Debug Display** – visualize performance, object count, and FPS

---

## 🔧 Controls

| Action            | How                        |
|------------------|----------------------------|
| Spawn Ball        | Left Click or "Click to Spawn" button |
| Fast Spawn        | Click "Fast Spawn" and hold left click |
| Toggle Mute       | Click "Mute" |
| Toggle Scenes     | Not implemented yet, but scene support is modular |

---

## 🧠 Core Components
Game Loop (Game.cpp) - Manages the window, time stepping, scene updates, and rendering.

Physics Engine (PhysicsEngine.cpp) - Handles overlapping, gravity, substeps, and invokes the collision system.

Collision System (CollisionSystem.cpp) - Implements spatial grid for efficient ball-ball collision detection and resolution. Also resolves collisions with the circular boundary.

Balls (Ball.cpp) - Visual objects with a RigidbodyComponent. Can be spawned individually or in bursts.

Boundary (Boundary.cpp) - Hollow circular container — balls reflect off the inner surface.

UI System (UI.cpp, Button.cpp, UIPanel.cpp) - Minimal UI to spawn balls, toggle fast spawn, and mute audio.

Renderer (Renderer.cpp) - Draws game entities and overlays the UI.

Scene System (BallSpawnerScene.h) - Encapsulates object spawning, scene-specific logic, and forwards objects to the physics engine.




---

## 🛠 Configuration

Edit `GameConfig.h` to change:

- `BALL_RADIUS`
- `GRAVITY`
- `WINDOW_WIDTH`, `WINDOW_HEIGHT`
- `FRAME_RATE`
- `SUBSTEP_COUNT`
- `pixelsPerMeter` (gravity scale)

---

## 🧰 Dependencies

- [SFML](https://www.sfml-dev.org/) – graphics, input, and windowing
- C++17 or later (tested in Visual Studio 2022)

---

## 🧑‍💻 Author

Built by Jacob McIntyre as a learning project to experiment with game physics engines and modular scene systems.

---

## 📜 License

MIT License (optional – or remove if private project)
