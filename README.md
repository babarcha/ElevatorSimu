## Elevator Simulator (Qt/C++)

A desktop application simulating an elevator system with floor buttons, status display, and optional ESP32 serial communication for real hardware integration.
Built using Qt 6 and modern C++17.

## ✨ Features

🖥️ Interactive Qt-based GUI with floor buttons and elevator status display

🛗 Logic for floor requests, movement, and highlighting active floors

🔌 Serial communication with ESP32 (USB) for real-time simulation

⚙️ Modular design for easy extension (e.g., additional floors, UI styling, logging)

## 🛠️ Requirements

Qt 6.x (tested with Qt 6.9)

CMake 3.16+

A C++17 compatible compiler (GCC, Clang, or MSVC)

(Optional) ESP32 board + USB serial drivers

## 🚀 Build Instructions
Clone repository

git clone https://github.com/babarcha/ElevatorSimu.git

cd ElevatorSimu

Create build directory

mkdir build && cd build

Configure with CMake

cmake .. -DCMAKE_BUILD_TYPE=Release

Build project

cmake --build . --config Release -j

## ▶️ Run

After building, run the executable:

Linux/macOS:
./build/bin/ElevatorSimulator

Windows:
.\build\Release\ElevatorSimulator.exe

## Usage

Launch the app.

Click on floor buttons in the GUI to request elevator movement.

The elevator moves and highlights the active floor.

If an ESP32 is connected via USB, the app exchanges states (floor requests, movement signals) with the hardware in real time.

## 📸 Screenshots

![Elevator App Screenshot](assets/ElevatorAppScreenShot.PNG)
*Main GUI showing floor buttons and elevator status.*

## 📌 Future Improvements

Planned enhancements for upcoming versions:

🔄 Multi-elevator support (simulate multiple shafts in one building)

📝 JSON/CSV logging of requests and trip history

🎨 Icons, animations, and improved UI styling

🕒 More realistic scheduling (e.g., collective control, peak-hour logic)

📶 Enhanced ESP32 integration with bidirectional communication

## 📄 License

MIT License – feel free to use and modify.
