#!/bin/sh
# POSIX

# documentation to be printed in usage/help menu
function usage {
  echo "StupidZip"
  echo "Usage: sz [-vh] [FILE or DIRECTORY]..."
  echo "Decompress compressed FILEs or DIRECTORYs in-place, and"
  echo "tar-gzip uncompressed FILEs or DIRECTORYs in-place."
  echo "Optional Arguments:"
  echo "  -v, --verbose  verbose mode"
  echo "  -h, --help     give this help"
  echo "At least one FILE or DIRECTORY path must be provided."
  echo "Report bugs to <https://github.com/theJollySin/StupidZip/issues>."
}


# variables for command-line parsing
files=()
num_files=0
verbose=false


# file types for compression and decompression
file_types=(".tar.bz2" \
            ".tar.gz" \
            ".tar.xz" \
            ".bz2" \
            ".gz" \
            ".jar" \
            ".tar" \
            ".tbz2" \
            ".tgz" \
            ".zip")
decompress=("tar xjf path && rm -f path" \
            "tar xzf path && rm -f path" \
            "tar xJf path && rm -f path" \
            "bzip2 -d path" \
            "gunzip path" \
            "jar xf path && rm -f path" \
            "tar xf path && rm -f path" \
            "tar xjf path && rm -f path" \
            "tar xzf path && rm -f path" \
            "unzip path && rm -f path")
decompress_verbose=("tar xjfv path && rm -f path" \
                    "tar xzfv path && rm -f path" \
                    "tar xJfv path && rm -f path" \
                    "bzip2 -dv path" \
                    "gunzip -v path" \
                    "jar xfv path && rm -f path" \
                    "tar xfv path && rm -f path" \
                    "tar xjfv path && rm -f path" \
                    "tar xzfv path && rm -f path" \
                    "unzip path && rm -f path")
compress="tar zcf path.tar.gz path && rm -rf path"
compress_vebose="tar zcfv path.tar.gz path && rm -rf path"


# take a single file/directory and dearchive it if possible, otherwise archive it
function archive_action {
    # check if the file is already archived, and un-archive it
    for i in $(seq 0 $(( ${#file_types[@]} - 1 )) ); do
        if [[ $1 == *${file_types[i]} ]]
        then
            if [[ $verbose == true ]]
            then
                eval ${decompress_verbose[i]//path/$1}
            else
                eval ${decompress[i]//path/$1}
            fi
            return
        fi
    done

    # the file/directory must need to be archived
    if [[ $verbose == true ]]
    then
        eval ${compress_verbose//path/$1}
    else
        eval ${compress//path/$1}
    fi
}


# COMMAND-LINE PARSING
for n in $(seq 1 $#); do
    case $1 in
        -h|--h|-help|--help)
            usage    # Display a usage synopsis.
            exit
            ;;
        -v|--v|-verbose|--verbose)
            verbose=true
            ;;
        *)
            files[num_files]=$1
            (( num_files += 1 ))
    esac
    shift
done


# LOOP THROUGH ALL FILES/DIRECTORIES AND (DE)COMPRESS THEM
for file in ${files[@]}; do
    archive_action $file
done
