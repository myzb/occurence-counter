#if !defined(OS_WINDOWS)
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#else
#include <conio.h>
#endif

#include "utils.h"


#if !defined(OS_WINDOWS)
// Linux (POSIX) implementation of _kbhit().
// Morgan McGuire, morgan@cs.brown.edu
static int _kbhit() {
    static const int STDIN = 0;
    static int initialized = 0;
    int bytesWaiting;

    if (!initialized) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    }
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}


static char _getch(void) {
    char c;
    if (fread(&c, 1, 1, stdin) < 1) return 0;
    return c;
}
#endif


char get_keystroke(void)
{
    if (_kbhit()) {
        char c = _getch();
        if (c >= 32) return c;
    }
    return 0;
}
