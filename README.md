# Elevator Simulator (Qt/C++)

A desktop application simulating an elevator system with floor buttons, status display, and optional ESP32 serial communication for real hardware integration.  
Built using **Qt 6** and **modern C++17**.

---

## ✨ Features
- 🖥️ Interactive Qt-based GUI with floor buttons and elevator status display  
- 🛗 Logic for floor requests, movement, and highlighting active floors  
- 🔌 Serial communication with ESP32 (USB) for real-time simulation  
- ⚙️ Modular design for easy extension (e.g., additional floors, UI styling, logging)  

---

## 🛠️ Requirements
- **Qt 6.x** (tested with Qt 6.9)  
- **CMake 3.16+**  
- A **C++17 compatible compiler** (GCC, Clang, or MSVC)  
- (Optional) **ESP32 board + USB serial drivers**  

---

## 🚀 Build Instructions

```bash
# Clone repository
git clone https://github.com/babarcha/ElevatorSimu.git
cd ElevatorSimu

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build project
cmake --build . --config Release -j
