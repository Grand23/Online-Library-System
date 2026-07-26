#include "Library.h"
#include <windows.h>

int main() {
    // Set console to UTF-8 for better character support
    SetConsoleOutputCP(CP_UTF8);
    
    Library library;
    library.mainMenu();
    
    return 0;
}
