#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMN_LEN 100
const char *USAGE = "StupidZip\n" \
    "Usage: sz [-vh] [FILE or DIRECTORY]...\n" \
    "Decompress compressed FILEs or DIRECTORYs in-place, and\n" \
    "compress uncompressed FILEs or DIRECTORYs in-place.\n\n" \
    "Optional Arguments:\n" \
    "  -v, --verbose  verbose mode\n" \
    "  -h, --help     give this help\n\n" \
    "At least one FILE or DIRECTORY path must be provided.\n\n" \
    "Report bugs to <https://github.com/theJollySin/StupidZip/issues>.\n";


/**
 * A simple, example C script to run a given POSIX command-line.
 */
int main(int argc, char *argv[])
{
    char cmd[MAX_CMN_LEN] = "", **p;
    
    fprintf(stdout, "\nWARNING: This is a placeholder script.  StupidZip not implemented yet in C.\n\n");

    if (argc < 2) /*no command specified*/
    {
        fprintf(stderr, USAGE);
        exit(EXIT_FAILURE);
    }
    else
    {
        // placeholder: all this does is parrot the incoming command
        strcat(cmd, argv[1]);
        for (p = &argv[2]; *p; p++)
        {
            strcat(cmd, " ");
            strcat(cmd, *p);
        }
        system(cmd);
    }

    return 0;
}
