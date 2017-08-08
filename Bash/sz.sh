#!/bin/sh
# POSIX


# Documentation to be printed in usage / help menu
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


# Take a single file/directory and dearchive it if possible, otherwise archive it
# Input Parameter 1: a file / directory path
function archive_action {
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
    compress_verbose="tar zcfv path.tar.gz path && rm -rf path"

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
    
    # strip possible trailing slashes
    new_path=$1
    if [[ $1 == */ || $1 == *\\ ]]
    then
        new_path=${new_path:0:${#new_path}-1}
    fi

    # the file/directory must need to be archived
    if [[ $verbose == true ]]
    then
        eval ${compress_verbose//path/$new_path}
    else
        eval ${compress//path/$new_path}
    fi
}


# Loop through all files / directories and (de)compress them
# Input Parameters: list of input files / directories
function all_archive_actions {
    for file in ${@}
    do
        archive_action $file
    done
}


# END FUNCTION DECLARATIONS


# variables for command-line parsing
files=()
num_files=0
verbose=false


# Command-Line Parsing
for n in $(seq 1 $#); do
    case $1 in
        -h|--h|-help|--help)
            usage
            exit
            ;;
        -v|--v|-verbose|--verbose)
            verbose=true
            ;;
        -?)          # Bad flag given.
            usage
            exit
            ;;
        *)
            files[num_files]=$1
            (( num_files += 1 ))
    esac
    shift
done


# Finally, do the actually compressing and decompressing.
all_archive_actions ${files[@]}
