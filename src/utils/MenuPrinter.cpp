#include "MenuPrinter.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Shows the main menu
void MenuPrinter::showMainMenu() {
    cout << "\n========== MAIN MENU ==========" << "\n";
    cout << "1. Login\n";
    cout << "2. Exit\n";
    cout << "Enter your choice: ";
}

// Shows the student menu after logging in as a student
void MenuPrinter::showStudentMenu() {
    cout << "\n========== STUDENT MENU ==========" << "\n";
    cout << "1. View Profile\n";
    cout << "2. Update Email\n";
    cout << "3. Update Emergency Contact\n";
    cout << "4. File Complaint\n";
    cout << "5. View My Complaints\n";
    cout << "6. Log Entry/Exit\n";
    cout << "7. Reset Password\n";
    cout << "8. Logout\n";
    cout << "Enter your choice: ";
}

// Shows the admin menu after logging in as an admin
void MenuPrinter::showAdminMenu() {
    cout << "\n========== ADMIN MENU ==========" << "\n";
    cout << "1. View Dashboard\n";
    cout << "2. Manage Students\n";
    cout << "3. Manage Rooms\n";
    cout << "4. Manage Complaints\n";
    cout << "5. Manage Dues\n";
    cout << "6. Logout\n";
    cout << "Enter your choice: ";
}

// Shows the entry/exit logging menu for students
void MenuPrinter::entryExitMenu() {
    cout << "\n========== ENTRY/EXIT ==========\n";
    cout << "1. Log Entry\n";
    cout << "2. Log Exit\n";
    cout << "3. Go Back\n";
    cout << "Choice: ";
}

// Shows the complaint filing menu for students
void MenuPrinter::filingComplaintMenu() {
    cout << "\n=== FILE A COMPLAINT ===\n";
    cout << "Select Category:\n";
    cout << "  1. Electricity\n";
    cout << "  2. Plumbing\n";
    cout << "  3. Housekeeping\n";
    cout << "  4. Internet\n";
    cout << "  5. Other\n";
    cout << "  6. Go Back\n";
    cout << "Choose (1-6): ";
}

void MenuPrinter::manageStudentsMenu() {
    cout << "\n========== MANAGE STUDENTS ==========\n";
    cout << "1. View All Students\n";
    cout << "2. Add Students\n";
    cout << "3. Remove Student\n";
    cout << "4. View Entry/Exit Logs\n";
    cout << "5. Go Back\n";
    cout << "Choice: ";
}

void MenuPrinter::bedAvailabilityMenu() {
    cout << "\n========== BED AVAILABILITY MENU ==========\n";
    cout << "1. View All Beds\n";
    cout << "2. Search by Hall\n";
    cout << "3. Search by Hall and Room\n";
    cout << "4. Check Specific Bed\n";
    cout << "5. Go Back\n";
    cout << "Enter choice: ";
}

void MenuPrinter::viewAllBedsMenu() {
    cout << "\n╔══════════════════════════════════════════════════╗\n";
    cout << "║           VIEW ALL BEDS — FILTER                 ║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    cout << "║  1.  All Beds       (no filter)                  ║\n";
    cout << "║  2.  Occupied Beds  (assigned to students)       ║\n";
    cout << "║  3.  Vacant Beds    (available for assignment)   ║\n";
    cout << "║  4.  Go Back                                     ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    cout << "  Choice: ";
}


void MenuPrinter::statusUpdateMenu() {
    cout << "\n=== UPDATE COMPLAINT STATUS ===\n";
    cout << "New Status:\n";
    cout << "  1. Pending\n";
    cout << "  2. In-Progress\n";
    cout << "  3. Resolved\n";
    cout << "  4. Go Back\n";
    cout << "Choose (1-4): ";
}

void MenuPrinter::workerAssignMenu() {
    cout << "\n=== ASSIGN WORKER TO COMPLAINT ===\n";
    cout << "Worker Type:\n";
    cout << "  1. Electrician\n";
    cout << "  2. Plumber\n";
    cout << "  3. Carpenter\n";
    cout << "  4. General Maintenance\n";
    cout << "  5. Go Back\n";
    cout << "Choose (1-5): ";
}

void MenuPrinter::manageRoomsMenu() {
    cout << "\n========== MANAGE ROOMS ==========\n";
    cout << "1. Check Bed Availability\n";
    cout << "2. Change Student Room\n";
    cout << "3. Add Rooms\n";
    cout << "4. Go Back\n";
    cout << "Choice: ";
}

void MenuPrinter::manageComplaintsMenu() {
    cout << "\n========== MANAGE COMPLAINTS ==========\n";
    cout << "1. View Complaints\n";
    cout << "2. Update Complaint Status\n";
    cout << "3. Assign Worker to Complaint\n";
    cout << "4. Go Back\n";
    cout << "Choice: ";
}

void MenuPrinter::manageDuesMenu() {
    cout << "\n========== MANAGE DUES ==========\n";
    cout << "1. Verify Payment\n";
    cout << "2. Add Penalty\n";
    cout << "3. Add Hall Fee (All Students)\n";
    cout << "4. Go Back\n";
    cout << "Choice: ";
}

void MenuPrinter::viewComplaintsMenu(int pending, int inProgress, int resolved) {
    int total = pending + inProgress + resolved;
    cout << "\n╔══════════════════════════════════════════════════╗\n";
    cout << "║             COMPLAINTS OVERVIEW                  ║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    cout << "║  Total Complaints : " << left << setw(29) << total        << "║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    cout << "║  🕐 Pending       : " << left << setw(29) << pending      << "║\n";
    cout << "║     (Awaiting worker assignment)                 ║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    cout << "║  ⚙  In-Progress   : " << left << setw(29) << inProgress   << "║\n";
    cout << "║     (Currently being handled by workers)         ║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    cout << "║  ✓  Resolved      : " << left << setw(29) << resolved     << "║\n";
    cout << "║     (Completed complaints)                       ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    cout << "\n  View Subsection:\n";
    cout << "  1. Pending     (" << pending    << ")\n";
    cout << "  2. In-Progress (" << inProgress << ")\n";
    cout << "  3. Resolved    (" << resolved   << ")\n";
    cout << "  4. Go Back\n";
    cout << "  Choice: ";
}
