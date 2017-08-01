#!/usr/bin/env python
"""
StupidZip 0.7
Usage: sz [-vh] [FILE or DIRECTORY]...
Decompress compressed FILEs or DIRECTORYs in-place, and
compress uncompressed FILEs or DIRECTORYs in-place.

Optional Arguments:
  -v, --verbose  verbose mode
  -h, --help     give this help
      --version  give this help

At least one FILE or DIRECTORY path must be provided.

Report bugs to <https://github.com/theJollySin/StupidZip/issues>.
"""
import os
import sys

# CONFIGURABLE DECOMPRESSION SETTINGS  (VERBOSE? True / False)
TWO_PART = {'.tar.bz2': {False: 'tar xjf %s && rm -f %s', True: 'tar xjfv %s && rm -f %s'},
            '.tar.gz':  {False: 'tar xzf %s && rm -f %s', True: 'tar xzfv %s && rm -f %s'},
            '.tar.xz':  {False: 'tar xJf %s && rm -f %s', True: 'tar xJfv %s && rm -f %s'}}

ONE_PART = {'.bz2':     {False: 'bzip2 -d %s',            True: 'bzip2 -dv %s'},
            '.gz':      {False: 'gunzip %s',              True: 'gunzip -v %s'},
            '.jar':     {False: 'jar xf %s && rm -f %s',  True: 'jar xfv %s && rm -f %s'},
            '.tar':     {False: 'tar xf %s && rm -f %s',  True: 'tar xfv %s && rm -f %s'},
            '.tbz2':    {False: 'tar xjf %s && rm -f %s', True: 'tar xjfv %s && rm -f %s'},
            '.tgz':     {False: 'tar xzf %s && rm -f %s', True: 'tar xzfv %s && rm -f %s'},
            '.zip':     {False: 'unzip %s && rm -f %s',   True: 'unzip -v %s && rm -f %s'}}

# CONFIGURABLE COMPRESSION OPTION  (VERBOSE? True / False)
COMPRESS = {False: 'tar zcf %s.tar.gz %s && rm -rf %s', True: 'tar zcfv %s.tar.gz %s && rm -rf %s'}

# CONSTANTS (DO NOT TOUCH)
HELP_FLAGS = ['-h', '--h', '-help', '--help', '--version']
VERBOSE_FLAGS = ['-v', '--v', '-verbose', '--verbose']


def main():
    """ parse commandline and direct the primary tasks
    """
    # handle help flag
    if [f for f in sys.argv[1:] if f.lower() in HELP_FLAGS]:
        usage()

    # Determine if the user wants a verbose output
    verbose = False
    paths = [f for f in sys.argv[1:] if f.lower() not in VERBOSE_FLAGS]
    if len(paths) == 0:
        usage()
    elif len(paths) < len(sys.argv[1:]):
        verbose = True

    # handle the full list of file / directory paths, one at a time
    for path in paths:
        handle_one_path(path, verbose)


def usage():
    ''' Print the help menu.
    '''
    print(__doc__.strip())
    exit()


def handle_one_path(path, verbose):
    """ Compress or decompress a file or directory.
        This is the meat of the logic for this script.
        It will decide if the path given ends in a known suffix,
        and if so decompress it. Otherwise, it will tar-gzip it.

        NOTE: The suffixes supplied are case-independent.
    """
    # check if the path has a listed two-part ending
    for ending in TWO_PART:
        if path.lower().endswith(ending):
            # decompress it
            os.system(TWO_PART[ending][verbose].replace('%s', path))
            return

    # then check if the path has a listed one-parth ending
    for ending in ONE_PART:
        if path.lower().endswith(ending):
            # decompress it
            os.system(ONE_PART[ending][verbose].replace('%s', path))
            return

    # if not, then compress it
    path = path.rstrip('/').rstrip('\\')
    os.system(COMPRESS[verbose].replace('%s', path))


if __name__ == '__main__':
    main()
