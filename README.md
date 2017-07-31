# StupidZip

> StupidZip is just smarter.™


## The Entire Specification

Why are we memorizing tar flags?  There are an every-growning number of cases to learn: `tar`, `tar.gz`, `tar.xz`, `tar.bz2`, not to mention `zip` and the other plain, no tar, commands.

![XKCD on tar](https://imgs.xkcd.com/comics/tar.png)

Can't we just have one tool that looks at your file name and does the thing that you obviously want to do?  It's not that complicated.

Look, here is the functionality we want.  Just uncompress the compressed:

    $ sz whatever.tar.gz        # runs: tar xzvf whatever.tar.gz
    $ sz whatever.tar           # runs: tar -xf whatever.tar
    $ sz whatever.gz            # runs: gunzip whatever.gz
    $ sz whatever.zip           # runs: unzip whatever.zip
    $ sz whatever.bz2           # runs: bzip2 -d whatever.bz2
    $ sz whatever.tar.bz2       # runs: tar -xjf whatever.tar.bz2
    $ sz whatever.tar.xz        # runs: tar xvfJ whatever.tar.xz

And tar-gzip the uncompressed:

    $ sz whatever               # runs: tar -zcf whatever.tar.gz whatever

And if you pass a big list of files (or directories) it does the correct thing for each of them.


#### Can we have a verbose flag?

Fine. If you give this program a `-v` flag it will run whatever you are doing in verbose mode; assuming that is possible.

But that is the **ONLY** flag this program will ever have.


#### What if there are errors?

They will be passed through, exactly as-is, to standard-out.  This includes the error that one of the necessary tools (`tar`, `gzip`, etc) are not installed.


## The "Problem"

BUT!  AH HA!  BUT!  You just thought of this exceptional case where the above would totally fail.

> Congratulations. I don't care.

This program will not be bullet proof.  It will not have the full power of all those other tools. For that you would need: all those other tools.  This is a helpful time-saver only.


## The Implementation

This tool should work for any POSIX-style commandline interface, but is targeted at Linux in general.

To start, this will be a simply Python script, for portability.  But over time versions will get added in other languages, so people will have a hackable version in the language of their choice.
