# Installing StupidZip

> WARNING: Install Instructions are under development. Help me make them complete for your favorite distro of Linux, Unix, or Mac!

The goal of this Install guide is to help you install `StupidZip` in your typical Linux, Unix, or Mac (here-to-fore call `Nix) distro. `StupidZip` is only designed for vaguely POSIX-compliant operating systems, sorry Windows is not currently supported.

The first thing to know is that three functionally identical versions of `StupidZip` come in this package, one for each of the languages: `BASH`, `Python`, and `C`. Why does `StupidZip` come with these three versions? So that you can hack it and personalize it in the language of your choice. It is, after all, a personal convenience tool. It seems likely that a user will want to personalize it further. So, pick the version for the language you know (or like) best and follow the instructions below.


## C

Here's the short version:

    sudo rm -f /usr/bin/sz
    cd C
    make
    sudo cp sz /usr/bin/
    sudo chmod 755 /usr/bin/sz

TODO: Explanation (gcc or g++)


# BASH

Here's the short version:

    sudo rm -f /usr/bin/sz
    sudo cp Bash/sz.sh /usr/bin/
    sudo chmod 755 /usr/bin/sz.sh
    sudo ln -s /usr/bin/sz.sh /usr/bin/sz

> TODO: Explanation


# Python

Here's the short version:

    sudo rm -f /usr/bin/sz
    sudo cp Python/sz.py /usr/bin/
    sudo chmod 755 /usr/bin/sz.py
    sudo ln -s /usr/bin/sz.py /usr/bin/sz

> TODO: Explanation
