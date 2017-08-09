#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMN_LEN 512
const char *USAGE = "StupidZip\n" \
    "Usage: sz [-vh] [FILE or DIRECTORY]...\n" \
    "Decompress compressed FILEs or DIRECTORYs in-place, and\n" \
    "compress uncompressed FILEs or DIRECTORYs in-place.\n\n" \
    "Optional Arguments:\n" \
    "  -v, --verbose  verbose mode\n" \
    "  -h, --help     give this help\n\n" \
    "At least one FILE or DIRECTORY path must be provided.\n\n" \
    "Report bugs to <https://github.com/theJollySin/StupidZip/issues>.\n";
/* file types for compression and decompression */
const int NUM_FILE_TYPES = 10;
const char *FILE_TYPES[] = {".tar.bz2",
                            ".tar.gz",
                            ".tar.xz",
                            ".bz2",
                            ".gz",
                            ".jar",
                            ".tar",
                            ".tbz2",
                            ".tgz",
                            ".zip"};
const char *DECOMPRESS[] = {"tar xjf path && rm -f path",
                            "tar xzf path && rm -f path",
                            "tar xJf path && rm -f path",
                            "bzip2 -d path",
                            "gunzip path",
                            "jar xf path && rm -f path",
                            "tar xf path && rm -f path",
                            "tar xjf path && rm -f path",
                            "tar xzf path && rm -f path",
                            "unzip path && rm -f path"};
const char *DECOMPRESS_VERBOSE[] = {"tar xjfv path && rm -f path",
                                    "tar xzfv path && rm -f path",
                                    "tar xJfv path && rm -f path",
                                    "bzip2 -dv path",
                                    "gunzip -v path",
                                    "jar xfv path && rm -f path",
                                    "tar xfv path && rm -f path",
                                    "tar xjfv path && rm -f path",
                                    "tar xzfv path && rm -f path",
                                    "unzip path && rm -f path"};
const char *COMPRESS = "tar zcf ?.tar.gz ? && rm -rf ?";
const char *COMPRESS_VERBOSE = "tar zcfv ?.tar.gz ? && rm -rf ?";
const int NUM_HELP_FLAGS = 4;
const int NUM_VERBOSE_FLAGS = 4;
const char *HELP_FLAGS[] = {"-h", "--h", "-help", "--help"};
const char *VERBOSE_FLAGS[] = {"-v", "--v", "-verbose", "--verbose"};


/**
 * Custom string replacement method, designed for custom (de)compress strings.
 * Copy the `from` string to the `to` string, but
 * replace all `?` in `from` with `str`.
 */
void replace_all_questions(char *str, const char *from, char *to) {
    int s = 0, f = 0, t = 0;

    /* loop over characters in from array */
    while (from[f] != '\0')
    {
        if (from[f] == '?')
        {
            /* if char in `from` array is '?', do replacement */
            s = 0;
            while (str[s] != '\0')
            {
                to[t] = str[s];
                s += 1;
                t += 1;
            }
        }
        else
        {
            /* normally, just copy `from` to `to` */
            to[t] = from[f];
            t += 1;
        }
        f += 1;
    }
    /* null terminate the string */
    to[t] = '\0';
}



/**
 * Parse commandline and direct the primary tasks.
 */
int main(int argc, char *argv[])
{
    int i = 0, f = 0, verbose = 0, verbose_index = -999;
    char command[MAX_CMN_LEN] = "";

    /* make suer that some command is passed to this program */
    if (argc < 2)
    {
        fprintf(stdout, USAGE);
        exit(EXIT_FAILURE);
    }

    /* check for flags */
    for (i=1; i < argc; i++)
    {
        if (argv[i][0] == '-') {
            for (f=0; f < NUM_HELP_FLAGS; f++) {
                fprintf(stdout, USAGE);
                return 0;
            }
            for (f=0; f < NUM_VERBOSE_FLAGS; f++) {
                verbose = 1;
                verbose_index = i;
                break;
            }
        }
    }

    /*  placeholder: all this does is parrot the tar-zip incoming files */
    for (i=1; i < argc; i++)
    {
        if (i == verbose_index)
        {
            /* skip verbose flags; they aren't files */
            continue;
        }

        /* do the actual tar-gzipping */
        if (verbose == 1)
        {
            replace_all_questions(argv[i], COMPRESS_VERBOSE, command);
        }
        else
        {
            replace_all_questions(argv[i], COMPRESS, command);
        }
        system(command);
    }

    fprintf(stdout, "\nWARNING: This C version of StupidZip is not yet implemented.\n\n");
    return 0;
}
