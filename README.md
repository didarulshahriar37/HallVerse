## PROJECT NAME
HallVerse - A Console-based Hall Management System

## FOLDER STRUCTURE
HallVerse/ <br>
│ <br>
├── src/ <br>
│   ├── main/ <br>
│   │   ├── Main.cpp <br>
│   │   └── App.cpp <br>
│   │ <br>
│   ├── models/ <br>
│   │   ├── Student.h <br>
│   │   ├── Student.cpp <br>
│   │   ├── Admin.h <br>
│   │   ├── Admin.cpp <br>
│   │   ├── Complaint.h <br>
│   │   ├── Complaint.cpp <br>
│   │   ├── Worker.h <br>
│   │   ├── Worker.cpp <br>
│   │   ├── WorkAssignment.h <br>
│   │   ├── WorkAssignment.cpp <br>
│   │   ├── EntryExitRecord.h <br>
│   │   └── EntryExitRecord.cpp <br>
│   │ <br>
│   ├── managers/ <br>
│   │   ├── StudentManager.h <br>
│   │   ├── StudentManager.cpp <br>
│   │   ├── ComplaintManager.h <br>
│   │   ├── ComplaintManager.cpp <br>
│   │   ├── WorkerManager.h <br>
│   │   ├── WorkerManager.cpp <br>
│   │   ├── RoomManager.h <br>
│   │   ├── RoomManager.cpp <br>
│   │   ├── WorkAssignmentManager.h <br>
│   │   ├── WorkAssignmentManager.cpp <br>
│   │   ├── EntryExitManager.h <br>
│   │   ├── EntryExitManager.cpp <br>
│   │   ├── DashboardManager.h <br>
│   │   ├── DashboardManager.cpp <br>
│   │   ├── AuthenticationManager.h <br>
│   │   └── AuthenticationManager.cpp <br>
│   │ <br>
│   ├── services/ <br>
│   │   ├── FileHandler.h <br>
│   │   ├── FileHandler.cpp <br>
│   │   ├── Hasher.h <br>
│   │   └── Hasher.cpp <br>
│   │ <br>
│   └── utils/ <br>
│       ├── MenuPrinter.h <br>
│       ├── MenuPrinter.cpp <br>
│       ├── InputHelper.h <br>
│       ├── InputHelper.cpp <br>
│       ├── DateTimeHelper.h <br>
│       └── DateTimeHelper.cpp <br>
│ <br>
├── data/ <br>
│   ├── students.csv <br>
│   ├── admins.csv <br>
│   ├── complaints.csv <br>
│   ├── workers.csv <br>
│   ├── assignments.csv <br>
│   ├── rooms.csv <br>
│   └── entry_exit.csv <br>
│ <br>
├── build/ <br>
│ <br>
└── README.md

## TO RUN THE APP
**Compilation**
```bash
g++ -std=c++17 -Isrc -Isrc/managers -Isrc/models -Isrc/services -Isrc/utils -O2 -g src/main/Main.cpp src/managers/*.cpp src/models/*.cpp src/services/*.cpp src/utils/*.cpp -o build/HallVerse.exe
```
**Run**
```bash
.\build\HallVerse.exe
```

## CONTRIBUTORS
<a align="center" href="https://github.com/didarulshahriar37/HallVerse/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=didarulshahriar37/HallVerse" />
</a>