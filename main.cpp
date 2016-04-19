#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <string>

using namespace std;

const int CENTER_PADDING = 5;

void gotoxy (int x, int y, HANDLE outputDeviceHandle);
void printWordOnConsole (HANDLE outputDeviceHandle, int x, int y, string word);
//void ClearScreen();

int main ()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);

    int consoleColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int middleColumn = consoleColumns / 2;

    for (int i = 0, j = consoleRows - 1; j >= 0; i++, j--)
    {
        printWordOnConsole(consoleHandle, middleColumn - CENTER_PADDING, j, "UP");
        printWordOnConsole(consoleHandle, middleColumn + CENTER_PADDING, i, "DOWN");
        sleep(1);
        //system("CLS");
        //ClearScreen();
    }
    //return 0;
}

void printWordOnConsole(HANDLE outputDeviceHandle, int x, int y, string word)
{
    gotoxy (x, y, outputDeviceHandle);
    cout << word;
}

void gotoxy (int x, int y, HANDLE outputDeviceHandle)
{
    COORD coord;
    coord.X = (short) x;
    coord.Y = (short) y;
    SetConsoleCursorPosition(outputDeviceHandle, coord);
}

/*void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    *//* Get the number of cells in the current buffer *//*
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    *//* Fill the entire buffer with spaces *//*
    if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR) ' ',
            cellCount,
            homeCoords,
            &count
    )) return;

    *//* Fill the entire buffer with the current colors and attributes *//*
    if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count
    )) return;

    *//* Move the cursor home *//*
    SetConsoleCursorPosition( hStdOut, homeCoords );
}*/