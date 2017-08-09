#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMN_LEN 1024
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
const char *DECOMPRESS[] = {"tar xjf ? && rm -f ?",
                            "tar xzf ? && rm -f ?",
                            "tar xJf ? && rm -f ?",
                            "bzip2 -d ?",
                            "gunzip ?",
                            "jar xf ? && rm -f ?",
                            "tar xf ? && rm -f ?",
                            "tar xjf ? && rm -f ?",
                            "tar xzf ? && rm -f ?",
                            "unzip ? && rm -f ?"};
const char *DECOMPRESS_VERBOSE[] = {"tar xjfv ? && rm -f ?",
                                    "tar xzfv ? && rm -f ?",
                                    "tar xJfv ? && rm -f ?",
                                    "bzip2 -dv ?",
                                    "gunzip -v ?",
                                    "jar xfv ? && rm -f ?",
                                    "tar xfv ? && rm -f ?",
                                    "tar xjfv ? && rm -f ?",
                                    "tar xzfv ? && rm -f ?",
                                    "unzip ? && rm -f ?"};
const char *COMPRESS = "tar zcf ?.tar.gz ? && rm -rf ?";
const char *COMPRESS_VERBOSE = "tar zcfv ?.tar.gz ? && rm -rf ?";
const int NUM_HELP_FLAGS = 4;
const int NUM_VERBOSE_FLAGS = 4;
const char *HELP_FLAGS[] = {"-h", "--h", "-help", "--help"};
const char *VERBOSE_FLAGS[] = {"-v", "--v", "-verbose", "--verbose"};


/**
 * Custom string replacement function, designed for custom (de)compress strings.
 * Copy the `from` string to the `to` string, but
 * replace all `?` in `from` with `str`.
 */
void replace_all_questions(char *str, const char *from, char *to)
{
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
 * Custom string length function for null-terminated char arrays.
 * This exists because we have only short strings and `int` is
 * a more convenient return type.
 */
int str_len(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i += 1;
    }
    return i;
}


/**
 * If the string ends in a slash, strip that off.
 * This is meant to fix paths for directories, as opposed to files.
 */
void strip_trailing_slash(char *s)
{
    char last_char = s[str_len(s) - 1];
    if (last_char == '/' || last_char == '\\')
    {
        s[str_len(s) - 1] = '\0';
    }
}


/**
 * Parse commandline and direct the primary tasks.
 */
int main(int argc, char *argv[])
{
    int i = 0, j = 0, f = 0, verbose = 0, verbose_index = -999, type_len = 0, path_len = 0, matches = 0;
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
                if (strcmp(argv[i], HELP_FLAGS[f]) == 0)
                {
                    fprintf(stdout, USAGE);
                    return 0;
                }
            }
            for (f=0; f < NUM_VERBOSE_FLAGS; f++) {
                if (strcmp(argv[i], VERBOSE_FLAGS[f]) == 0)
                {
                    verbose = 1;
                    verbose_index = i;
                    break;
                }
            }
        }
    }

    /*  placeholder: all this does is parrot the tar-zip incoming files */
    for (i=1; i < argc; i++)
    {
        /* skip verbose flags; they aren't files */
        if (i == verbose_index)
        {
            continue;
        }

        /* check to see if the file needs to be decompressed */
        path_len = str_len(argv[i]);
        for (f=0; f < NUM_FILE_TYPES; f++)
        {
            type_len = str_len((char*)FILE_TYPES[f]);
            if (type_len >= path_len){
                continue;
            }

            matches = 0;

            /* look through all the compressed file types, and check for a match */
            for (j=0; j < type_len; j++)
            {
                if (argv[i][path_len - type_len + j] == FILE_TYPES[f][j])
                {
                    matches = 1;
                }
                else
                {
                    matches = 0;
                    break;
                }
            }

            if (matches == 1)
            {
                /* do the decompression */
                if (verbose == 1)
                {
                    replace_all_questions(argv[i], DECOMPRESS_VERBOSE[f], command);
                }
                else
                {
                    replace_all_questions(argv[i], DECOMPRESS[f], command);
                }
                system(command);
                break;
            }
        }

        /* If you compressed it, you're done. */
        if (matches)
        {
            continue;
        }

        /* do the tar-gzipping */
        strip_trailing_slash(argv[i]);
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

    return 0;
}
