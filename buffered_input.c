#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>

void sig_handler(int sig_id);
void set_buffered_input(bool enable);

int main()
{
    signal(SIGINT, sig_handler);
    set_buffered_input(false);
    char c;
    while (true)
    {
        c = getchar();
        printf("You pressed %c\n", c);
    }

    return 0;
}

void sig_handler(int sig_id)
{
    (void) sig_id;
    set_buffered_input(true);
    exit(EXIT_SUCCESS);
}

void set_buffered_input(bool enable)
{
    static bool enabled = true;
    static struct termios old;
    struct termios new;

    if (!enable && enabled)
    {
        tcgetattr(STDIN_FILENO, &old);
        new = old;
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new);
        enabled = false;
    }
    else if (enable && !enabled)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        enabled = true;
    }
}
