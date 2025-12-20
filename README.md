## PROJECT NAME
HallVerse - A Console-based Hall Management System

## FOLDER STRUCTURE
HallManagementSystem/
│
├── src/
│   ├── main/
│   │   ├── Main.cpp
│   │   └── App.cpp
│   │
│   ├── models/
│   │   ├── Student.h
│   │   ├── Student.cpp
│   │   ├── Admin.h
│   │   ├── Admin.cpp
│   │   ├── Complaint.h
│   │   ├── Complaint.cpp
│   │   ├── Worker.h
│   │   ├── Worker.cpp
│   │   ├── WorkAssignment.h
│   │   ├── WorkAssignment.cpp
│   │   ├── EntryExitRecord.h
│   │   └── EntryExitRecord.cpp
│   │
│   ├── managers/
│   │   ├── StudentManager.h
│   │   ├── StudentManager.cpp
│   │   ├── ComplaintManager.h
│   │   ├── ComplaintManager.cpp
│   │   ├── WorkerManager.h
│   │   ├── WorkerManager.cpp
│   │   ├── WorkAssignmentManager.h
│   │   ├── WorkAssignmentManager.cpp
│   │   ├── EntryExitManager.h
│   │   ├── EntryExitManager.cpp
│   │   ├── DashboardManager.h
│   │   ├── DashboardManager.cpp
│   │   ├── AuthenticationManager.h
│   │   └── AuthenticationManager.cpp
│   │
│   ├── services/
│   │   ├── FileHandler.h
│   │   ├── FileHandler.cpp
│   │   ├── Hasher.h
│   │   └── Hasher.cpp
│   │
│   └── utils/
│       ├── MenuPrinter.h
│       ├── MenuPrinter.cpp
│       ├── InputHelper.h
│       ├── InputHelper.cpp
│       ├── DateTimeHelper.h
│       └── DateTimeHelper.cpp
│
├── data/
│   ├── students.csv
│   ├── admins.csv
│   ├── complaints.csv
│   ├── workers.csv
│   ├── assignments.csv
│   └── entry_exit.csv
│
├── build/
│
└── README.md