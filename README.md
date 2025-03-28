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

## 📈 Benchmark Results

## Circle

## Radius = 5
| Balls | Avg Substep Time (μs) | Framerate | Collision Checks | Collisions Resolved | Total Substep Time (μs) | Total Physics Time (μs) |
|-------|------------------------|-----------|------------------|----------------------|--------------------------|--------------------------|
| 0 | 0 | 125000 | 0 | 0 | 0 | 0 |
| 10 | 484 | 119.289 | 87 | 0 | 1452 | 450 |
| 50 | 666 | 132.328 | 666 | 0 | 1998 | 644 |
| 100 | 712 | 129.116 | 1096 | 52 | 2136 | 596 |
| 250 | 991.333 | 128.999 | 7032 | 603 | 2974 | 911 |
| 500 | 1342 | 111.21 | 20843 | 2084 | 4026 | 1276 |
| 600 | 1635.33 | 124.549 | 26795 | 2779 | 4906 | 1512 |
| 800 | 2073.67 | 124.549 | 39027 | 4620 | 6221 | 1965 |
| 1000 | 2542.33 | 104.778 | 50976 | 5718 | 7627 | 2611 |
| 1100 | 2739 | 94.038 | 56925 | 6668 | 8217 | 2778 |
| 1200 | 2972 | 85.4409 | 63472 | 7716 | 8916 | 2856 |
| 1300 | 3123.33 | 81.8063 | 69729 | 8515 | 9370 | 3040 |
| 1400 | 3442.67 | 75.7289 | 75695 | 9261 | 10328 | 3280 |
| 1500 | 3879.67 | 62.22 | 81991 | 10361 | 11639 | 4153 |
| 1600 | 4480.67 | 55.9065 | 88397 | 11208 | 13442 | 4003 |
| 1700 | 4608.33 | 61.8276 | 94331 | 11992 | 13825 | 4497 |
| 1800 | 5319.67 | 60.0492 | 99333 | 12692 | 15959 | 4599 |
| 1900 | 4534.67 | 53.9055 | 106526 | 13439 | 13604 | 4521 |
| 2000 | 5271.33 | 47.6349 | 112294 | 13631 | 15814 | 5127 |

**Note:** FPS dropped below 60 at **1060 balls**.

## Radius = 2
| Balls | Avg Substep Time (μs) | Framerate | Collision Checks | Collisions Resolved | Total Substep Time (μs) | Total Physics Time (μs) |
|-------|------------------------|-----------|------------------|----------------------|--------------------------|--------------------------|
| 0 | 0 | 166667 | 0 | 0 | 0 | 0 |
| 10 | 2211.67 | 107.089 | 27 | 0 | 6635 | 2151 |
| 50 | 2565 | 128.584 | 88 | 0 | 7695 | 2365 |
| 100 | 2943 | 123.426 | 258 | 20 | 8829 | 2420 |
| 250 | 2737 | 110.278 | 6146 | 578 | 8211 | 2763 |
| 500 | 3180 | 92.43 | 18174 | 2255 | 9540 | 3035 |
| 600 | 3257.33 | 88.3392 | 23711 | 2878 | 9772 | 3207 |
| 800 | 4753 | 68.465 | 35487 | 4329 | 14259 | 4197 |
| 1000 | 5383.67 | 59.1751 | 47371 | 5853 | 16151 | 6697 |
| 1100 | 4542.67 | 63.7714 | 53404 | 6509 | 13628 | 4219 |
| 1200 | 5076 | 60.1287 | 59205 | 7422 | 15228 | 4499 |
| 1300 | 4957.33 | 52.3588 | 64976 | 7773 | 14872 | 4908 |
| 1400 | 5159.67 | 53.7432 | 71130 | 8760 | 15479 | 4898 |
| 1500 | 5771.33 | 53.1802 | 76780 | 9255 | 17314 | 5571 |
| 1600 | 5859 | 48.5272 | 83127 | 10180 | 17577 | 5464 |
| 1700 | 6332 | 44.8089 | 88833 | 10992 | 18996 | 6666 |
| 1800 | 5902.67 | 44.615 | 95322 | 11409 | 17708 | 5944 |
| 1900 | 6302.67 | 40.5861 | 101551 | 12810 | 18908 | 6395 |
| 2000 | 6718 | 39.6385 | 107283 | 13279 | 20154 | 6398 |
**Note:** FPS dropped below 60 at **965 balls**.


## Square

## Radius = 5
| Balls | Avg Substep Time (μs) | Framerate | Collision Checks | Collisions Resolved | Total Substep Time (μs) | Total Physics Time (μs) |
|-------|------------------------|-----------|------------------|----------------------|--------------------------|--------------------------|
| 0 | 0 | 142857 | 0 | 0 | 0 | 0 |
| 10 | 492.667 | 132.979 | 87 | 0 | 1478 | 457 |
| 50 | 722 | 124.642 | 666 | 0 | 2166 | 677 |
| 100 | 709.667 | 124.813 | 1350 | 40 | 2129 | 643 |
| 250 | 1179.33 | 111.198 | 6358 | 613 | 3538 | 1061 |
| 500 | 1828.67 | 130.702 | 21750 | 2229 | 5486 | 1913 |
| 600 | 2115.33 | 129.116 | 27036 | 2911 | 6346 | 2078 |
| 800 | 3325.33 | 93.6856 | 39578 | 4904 | 9976 | 2648 |
| 1000 | 3429.67 | 73.7953 | 51512 | 5986 | 10289 | 3515 |
| 1100 | 3684.33 | 75.8093 | 57393 | 7335 | 11053 | 3535 |
| 1200 | 4243 | 62.0925 | 63487 | 7660 | 12729 | 4776 |
| 1300 | 5128 | 41.1455 | 69550 | 8609 | 15384 | 5069 |
| 1400 | 5476.67 | 27.8886 | 75497 | 9016 | 16430 | 4767 |
| 1500 | 6079.67 | 40.2431 | 80936 | 9931 | 18239 | 7389 |
| 1600 | 8498 | 48.0146 | 86884 | 10782 | 25494 | 9266 |
| 1700 | 6214 | 45.798 | 92659 | 11134 | 18642 | 5665 |
| 1800 | 9417 | 31.9724 | 97588 | 12177 | 28251 | 9553 |
| 1900 | 8631 | 42.7661 | 103360 | 12908 | 25893 | 9615 |
| 2000 | 7367 | 30.0102 | 109504 | 13938 | 22101 | 7134 |

**Note:** FPS dropped below 60 at **930 balls**.


## Radius = 2
| Balls | Avg Substep Time (μs) | Framerate | Collision Checks | Collisions Resolved | Total Substep Time (μs) | Total Physics Time (μs) |
|-------|------------------------|-----------|------------------|----------------------|--------------------------|--------------------------|
| 0 | 0 | 200000 | 0 | 0 | 0 | 0 |
| 10 | 3239.67 | 114.025 | 27 | 0 | 9719 | 3428 |
| 50 | 2111 | 125.565 | 88 | 0 | 6333 | 2106 |
| 100 | 2253.33 | 134.862 | 311 | 7 | 6760 | 2234 |
| 250 | 2828.33 | 117.165 | 4609 | 557 | 8485 | 3201 |
| 500 | 3297.67 | 90.8595 | 15127 | 2236 | 9893 | 3208 |
| 600 | 3516.67 | 84.0477 | 19426 | 3122 | 10550 | 3391 |
| 800 | 5145 | 61.3459 | 28616 | 3819 | 15435 | 4603 |
| 1000 | 4733.33 | 60.957 | 38926 | 5240 | 14200 | 4627 |
| 1100 | 4913.33 | 54.5375 | 45022 | 5612 | 14740 | 4679 |
| 1200 | 5571 | 52.3259 | 50910 | 6821 | 16713 | 5613 |
| 1300 | 6036 | 47.5579 | 56797 | 7708 | 18108 | 6390 |
| 1400 | 5760 | 48.398 | 62926 | 8629 | 17280 | 5531 |
| 1500 | 6612 | 39.1543 | 68727 | 8702 | 19836 | 6519 |
| 1600 | 6386 | 43.0089 | 74489 | 9427 | 19158 | 6097 |
| 1700 | 6899.67 | 41.3736 | 80859 | 10972 | 20699 | 6613 |
| 1800 | 7069.67 | 38.0344 | 86913 | 11620 | 21209 | 6931 |
| 1900 | 7397.33 | 37.9781 | 92406 | 11202 | 22192 | 7185 |
| 2000 | 9760.33 | 36.0633 | 98611 | 12364 | 29281 | 10868 |

**Note:** FPS dropped below 60 at **780 balls**.
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
