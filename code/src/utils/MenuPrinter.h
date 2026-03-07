#ifndef MENU_PRINTER_H
#define MENU_PRINTER_H

#include <iostream>

using namespace std;

class MenuPrinter {
public:
    static void showMainMenu();
    static void showAdminMenu();
    static void showStudentMenu();
    static void updateInfoMenu();
    static void entryExitMenu();
    static void fileViewComplaintsMenu();
    static void filingComplaintMenu();
    static void manageStudentsMenu();
    static void bedAvailabilityMenu();
    static void viewAllBedsMenu();
    static void statusUpdateMenu();
    static void workerAssignMenu();
    static void manageRoomsMenu();
    static void manageComplaintsMenu();
    static void viewComplaintsMenu(int pending, int inProgress, int resolved);
    static void studentViewComplaintsMenu(int pending, int inProgress, int resolved);
    static void manageDuesMenu();
    static void showWorkerMenu();
    static void workerManageComplaintsMenu(int pending, int inProgress, int resolved);
    static void workerUpdateInfoMenu();
};

#endif
