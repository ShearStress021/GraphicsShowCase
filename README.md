# Graphical ShowCase project

A collection of graphics programming projects exploring different approaches to creating windows, handling graphics, and working with low-level graphics APIs

The goal is **learning by building** — from basic triangle rendering to more advanced rendering techniques.

---

## 🛠️ Tech Stack

- **Language:** C++ (C++17 / C++20)
- **Build System:**
  - CMake

---
## Project Structure
- **VulkanApi:**
    - simpleTriangle
- **WindowApi:**
    - cube console3d


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
