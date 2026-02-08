# Graphical Show case project

A collection of **graphics programming experiments and projects using Vulkan** and modern **C++**.  
This repository focuses on low-level rendering concepts, GPU programming, and building a deeper understanding of how modern graphics pipelines work.

The goal is **learning by building** — from basic triangle rendering to more advanced rendering techniques.

---

## 🛠️ Tech Stack

- **Language:** C++ (C++17 / C++20)
- **Graphics API:** Vulkan
- **Windowing:**
  - GLFW (primary)
- **Math:**
  - GLM
- **Utilities:**
  - Vulkan Validation Layers
  - volk (optional)
- **Build System:**
  - CMake

---


## 🚀 Getting Started

### Prerequisites

You’ll need:
- A **Vulkan-capable GPU**
- Latest **Vulkan SDK** (from LunarG)
- C++ compiler (GCC / Clang / MSVC)
- CMake 3.20+

Verify Vulkan installation:
```bash
vulkaninfo
````


---
### Build a Specific Game (CMake)

```bash
cd games/game-name
mkdir build
cd build
cmake ..
cmake --build .
