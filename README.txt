GLScry - OpenGL Performance Analysis Tool
Copyright (C) 2004-2005 Iowa State University

Authors:
    Chad Austin   aegis@aegisknight.org
    Dirk Reiners  dreiners@iastate.edu

Web:
    http://aegisknight.org/glscry


Overview
========

GLScry is a high-level OpenGL performance analysis tool.  It provides
a set of low-level benchmarking primitives and a Python interface for
writing high-level tests to measure things such as fill rate with
different states enabled, state change costs, vertex cache effect,
texture upload rates vs. format, existence of early Z techniques, cost
of lights, performance of vertex buffer formats, etc.

GLScry is open source software, licensed under the terms of the GNU
Lesser Public License (LGPL).  See COPYRIGHT.txt for details.


Building
========

If you're on Windows, smile.  There are prebuilt executables
available.  That said, if you want to compile from source anyway,
continue reading.

GLScry is tested on three platforms:  Win32, Cygwin, and Linux.  The
build system is the same on all of them.  You need Python, SCons,
Boost.Python, SDL, and OpenGL.  If you're on Win32, the last three are
taken care of.

Type "scons" from a command prompt and wait...  If you get an error,
you may need to set an option.  Type "scons -h" for a list of them.

Send us an e-mail if you have any more trouble.


Usage
=====

    General

The current frontend to GLScry is the 'run.py' script.  Type 'run.py
-h' for options.  You can either use the -a argument to run all of the
tests or pass a specific test filename as an argument.  The test
results are dumped in data/hostname/ where hostname is the name of
your computer.  Run the .gnuplot files through gnuplot to generate the
graph images.

    Windows Build

The instructions for running GLScry tests from the Windows
distribution are the same as above, except that run.py has been
compiled into an executable named run.exe.  Just drag one or more test
scripts onto it to run them.  If you'd like to run all of the
available tests, use the RunAllTests.bat batch file.

To generate graphs on Windows, a RunGnuplot.exe frontend is provided.
As above, drag the gnuplot scripts onto it to create the graph PNG
images.
