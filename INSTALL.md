# Installing StupidZip

> WARNING: Install Instructions are under development. Help me improve them for your favorite `Nix distro!

The goal of this Install guide is to help you install `StupidZip` in your typical Linux, Unix, or Mac (Nix) distro. `StupidZip` is only designed for POSIX-compliant operating systems; sorry Windows is not currently supported.

The first thing to know is that three functionally identical versions of `StupidZip` come in this package, one for each of the languages: `BASH`, `Python`, and `C`. These all work exactly the same, and are only provided so that you can hack the tool in a language you like. This is, afterall, just a personal convenience tool, you should be able to personalize it.

Follow the instructions below for whichever language you prefer.


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
