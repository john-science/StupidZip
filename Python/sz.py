#!/usr/bin/env python
"""
StupidZip
Usage: sz [-vh] [FILE or DIRECTORY]...
Decompress compressed FILEs or DIRECTORYs in-place, and
tar-gzip uncompressed FILEs or DIRECTORYs in-place.

Optional Arguments:
  -v, --verbose  verbose mode
  -h, --help     give this help

At least one FILE or DIRECTORY path must be provided.

Report bugs to <https://github.com/theJollySin/StupidZip/issues>.
"""
import os
import sys

# CONFIGURABLE DECOMPRESSION SETTINGS  (VERBOSE? True / False)
TWO_PART = {'.tar.bz2': {False: 'tar xjf @ && rm -f @', True: 'tar xjfv @ && rm -f @'},
            '.tar.gz':  {False: 'tar xzf @ && rm -f @', True: 'tar xzfv @ && rm -f @'},
            '.tar.xz':  {False: 'tar xJf @ && rm -f @', True: 'tar xJfv @ && rm -f @'}}

ONE_PART = {'.bz2':     {False: 'bzip2 -d @',           True: 'bzip2 -dv @'},
            '.gz':      {False: 'gunzip @',             True: 'gunzip -v @'},
            '.jar':     {False: 'jar xf @ && rm -f @',  True: 'jar xfv @ && rm -f @'},
            '.tar':     {False: 'tar xf @ && rm -f @',  True: 'tar xfv @ && rm -f @'},
            '.tbz2':    {False: 'tar xjf @ && rm -f @', True: 'tar xjfv @ && rm -f @'},
            '.tgz':     {False: 'tar xzf @ && rm -f @', True: 'tar xzfv @ && rm -f @'},
            '.zip':     {False: 'unzip @ && rm -f @',   True: 'unzip -v @ && rm -f @'}}

# CONFIGURABLE COMPRESSION OPTION  (VERBOSE? True / False)
COMPRESS = {False: 'tar zcf @.tar.gz @ && rm -rf @', True: 'tar zcfv @.tar.gz @ && rm -rf @'}

# CONSTANTS (DO NOT TOUCH)
HELP_FLAGS = ['-h', '--h', '-help', '--help']
VERBOSE_FLAGS = ['-v', '--v', '-verbose', '--verbose']


def main():
    """ parse command-line and direct the primary tasks
    """
    # handle help flag
    if [f for f in sys.argv[1:] if f.lower() in HELP_FLAGS]:
        usage()

    # parse command-line options
    verbose = False
    paths = [f for f in sys.argv[1:] if f.lower() not in VERBOSE_FLAGS]
    if len(paths) == 0:
        # no input files provided
        usage()
    elif len([f for f in paths if f.startswith('-')]) > 0:
        # bad flag provided
        usage()
    elif len(paths) < len(sys.argv[1:]):
        # verbose mode on
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
            os.system(TWO_PART[ending][verbose].replace('@', path))
            return

    # then check if the path has a listed one-parth ending
    for ending in ONE_PART:
        if path.lower().endswith(ending):
            # decompress it
            os.system(ONE_PART[ending][verbose].replace('@', path))
            return

    # if not, then compress it
    path = path.rstrip('/').rstrip('\\')
    os.system(COMPRESS[verbose].replace('@', path))


if __name__ == '__main__':
    main()
