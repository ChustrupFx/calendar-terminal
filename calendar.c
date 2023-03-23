#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

char* getMonthName(const int month) {
setlocale(LC_CTYPE, "");

    char* monthNames[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "Jule",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    return monthNames[month];
        
}

char* buildHeader(const char* monthName) {
    struct winsize terminalSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);

    int monthNameLen = strlen(monthName);
    int halfOfTerminalCol = (int) (terminalSize.ws_col / 2);
    int initOfMonth = halfOfTerminalCol - monthNameLen;

    char* header = malloc((terminalSize.ws_col + 1) * sizeof(char));

    strcat(header, "<");


    int index;

    for (index = 0; index < terminalSize.ws_col - 2; index++) {

        if (index == initOfMonth) {
            strcat(header, monthName);
            index += monthNameLen;
            continue;
        }

        strcat(header, " ");
    }

    strcat(header, ">");

    return header;
}

int main() {
    time_t currentTime = time(NULL);
    struct tm *localT = localtime(&currentTime);

    char *timeToStr = asctime(localT);

    char *monthName = getMonthName(localT->tm_mon);
    char *weekLabels = {
        'S', 'M', 'T', 'W', 'T', 'F', 'S'
    };

    char* header = buildHeader(monthName);
    printf(header);
    printf("\n");


    printf("\n");
    return 0;
}