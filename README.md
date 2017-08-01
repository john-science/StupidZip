# StupidZip

> StupidZip is just smarter.™


## The Goal

Why are we still memorizing tar flags?

![XKCD on tar](https://imgs.xkcd.com/comics/tar.png)

Can't we just have one tool that looks at your file name and does the thing that you obviously want to do?  It is not that complicated.

Look, here is the functionality we want.  Just uncompress the compressed:

    $ sz whatever.tar.gz        # runs: tar xzf whatever.tar.gz
    $ sz whatever.tar           # runs: tar xf whatever.tar
    $ sz whatever.gz            # runs: gunzip whatever.gz
    $ sz whatever.zip           # runs: unzip whatever.zip
    $ sz whatever.bz2           # runs: bzip2 -d whatever.bz2
    $ sz whatever.tar.bz2       # runs: tar xjf whatever.tar.bz2
    $ sz whatever.tar.xz        # runs: tar xJf whatever.tar.xz

And tar-gzip the uncompressed:

    $ sz whatever               # runs: tar zcf whatever.tar.gz whatever

And if you pass a big list of files (or directories) it does the correct thing for each of them.


#### Can we have a verbose flag?

Fine. If you give this program a `-v` flag it will run whatever you are doing in verbose mode; assuming that is possible.


#### What if there are errors?

Any errors will be passed through, exactly as-is, to standard-out.  This includes the error that one of the necessary tools (`tar`, `gzip`, etc) are not installed.


## The "Problem"

BUT!  AH HA!  BUT!  You just thought of this exceptional case where the above would totally fail.

> Congratulations. I don't care.

This program will not be bullet proof.  It will not have the full power of all those other tools.  For that you would need: all those other tools.  This is only meant to be a helpful time-saver for the typical 99% use-case.  And because it always does the same thing, you will clearly know when you need a different tool.


## The Implementation

This tool should work for any POSIX-style commandline.

The first version of this tool will is a single Python script for reference.  For maximum user support, this script will run correctly under all Python v2.x and v3.x environments.  All future versions of this tool must conform to the behaivor in this script: the compression utiltity support, the commandline options, and the error handling.

More versions of this tool will be added to this repository in other languages.  As this is a personal time-saving tool, users will benefit from having a hackable version in their language of choice.
