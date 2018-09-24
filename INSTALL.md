# Installing StupidZip

> WARNING: Install Instructions are under development. Help me make them complete for your favorite distro of Linux, Unix, or Mac!

The goal of this Install guide is to help you install `StupidZip` in your typical Linux, Unix, or Mac (here-to-fore call `Nix) distro. `StupidZip` is only designed for vaguely POSIX-compliant operating systems, sorry Windows is not currently supported.

The first thing to know is that three functionally identical versions of `StupidZip` come in this package, one for each of the languages: `BASH`, `Python`, and `C`. Why does `StupidZip` come with these three versions? So that you can hack it and personalize it in the language of your choice. It is, after all, a personal convenience tool. It seems likely that a user will want to personalize it further. So, pick the version for the language you know (or like) best and follow the instructions below.


## C

TODO: What if a previous version already exists?
TODO: Can I make this script work equally well for other compilers? What are the most common compilers/versions?

    cd C
    gcc sz.c -o sz
    sudo cp sz /usr/bin/
    sudo chmod +x /usr/bin/sz


# BASH

TODO: Is `+x` available to most operating systems?

    sudo cp Bash/sz.sh /usr/bin/
    sudo chmod +x /usr/bin/sz.sh
    sudo ln -s /usr/bin/sz.sh /usr/bin/sz


# Python

TODO: How does this change for the Mac OS?

    sudo cp Python/sz.py /usr/bin/
    sudo chmod +x /usr/bin/sz.py
    sudo ln -s /usr/bin/sz.py /usr/bin/sz
