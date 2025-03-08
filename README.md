# Labour Room Management System (LRMS)

## 📌 Overview
The **Labour Room Management System (LRMS)** is a simple C++ application built using **wxWidgets** for the UI. It is designed to store and manage information about childbirth in a labour room. The system records birth details in a **CSV file** and provides **weekly and monthly statistics**.

## ✨ Features
- 📋 **Record childbirth details** (e.g., date, time, baby’s weight, mother's name, etc.)
- 📊 **Generate weekly and monthly birth statistics**
- 🖥️ **Graphical User Interface (GUI)** using wxWidgets
- 📁 **Stores data in a simple CSV file** for easy access and analysis

## 🛠️ Technologies Used
- **C++** (Core logic)
- **wxWidgets** (GUI framework)
- **CSV File Handling** (Data storage)

## 🚀 Installation & Setup
### Prerequisites
- Install **wxWidgets** (Ensure wxWidgets is set up in your development environment)
- A C++ compiler (MSVC, GCC, or Clang)
- Visual Studio (if using Windows) or any C++ IDE

### Steps to Run
1. **Clone the Repository**
   ```sh
   git clone https://github.com/your-username/lrms.git
   cd lrms
   ```
2. **Build the Project**
   - If using Visual Studio, open the `.sln` file and build the solution.
   - If using a terminal:
     ```sh
     g++ -o lrms main.cpp `wx-config --cxxflags --libs`
     ```
3. **Run the Application**
   ```sh
   ./lrms
   ```

```

## 📜 License
This project is licensed under the **MIT License**.

---
💡 **Contributions & Feedback** are welcome! Feel free to submit issues or pull requests. 😊

