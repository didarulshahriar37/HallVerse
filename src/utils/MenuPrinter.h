#ifndef MENU_PRINTER_H
#define MENU_PRINTER_H

#include <iostream> // Assuming iostream is needed for cout

using namespace std;

class MenuPrinter {
public:
    static void showMainMenu();
    static void showAdminMenu();
    static void showStudentMenu();
    static void entryExitMenu();
    static void filingComplaintMenu();
    static void manageStudentsMenu();
    static void bedAvailabilityMenu();
    static void statusUpdateMenu();
    static void workerAssignMenu();
};

#endif
