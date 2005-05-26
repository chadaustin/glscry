#!/usr/bin/env python
# [Begin Copyright Header]
# 
# GLScry - OpenGL Performance Analysis Tool
# Copyright (C) 2004-2005  Iowa State University
# 
# This software is licensed under the terms of the GNU Lesser Public
# License, version 2.1, as published by the Free Software Foundation.
# See the file COPYRIGHT.txt for details.
# 
# Authors:
#   Chad Austin <aegisk@iastate.edu>
#   Dirk Reiners <dreiners@iastate.edu>
# 
# [End Copyright Header]

import os
import string
import sys
from glob import glob
import getopt
import socket


def getScriptDirectory(argv=sys.argv):
    return os.path.abspath(os.path.dirname(argv[0]))


def usage(argv):
    print """\
Usage: [python] run.py [OPTIONS] [TESTS]

Options:
    -a, --all       Run all tests.
    -h, --help      Show this help text.
"""


def main(argv=sys.argv):
    # Parse options.
    try:
        options, args = getopt.getopt(argv[1:], 'a', ['help', 'all'])
    except getopt.GetoptError:
        usage(argv)
        sys.exit(1)

    allTests = False
    for o, a in options:
        if o in ('-h', '--help'):
            usage(argv)
            sys.exit(0)
        elif o in ('-a', '--all'):
            allTests = True


    scriptDir = getScriptDirectory(argv)
    moduleDir = os.path.join(scriptDir, 'lib')
    sys.path.append(moduleDir)

    # Get test list.
    tests = map(os.path.abspath, args)
    if allTests:
        globbed = glob(os.path.join(scriptDir, 'test', '*.py'))
        globbed.sort()
        tests += globbed

    if not tests:
        print "No tests specified.  Specify a test explicitly or use -a."
        print
        usage(argv)
        sys.exit(1)

    # Create data directory if it does not exist and switch to it so
    # the tests output their files there.
    hostname = socket.gethostname()
    datadir = os.path.join(scriptDir, 'data', hostname)
    try:
        os.makedirs(datadir)
    except OSError:
        pass
    os.chdir(datadir)

    print 'Data directory:', datadir

    print '\nQueuing tests for execution:'
    for t in tests:
        print "  " + t

    for t in tests:
        print
        print "Running test script '%s'" % t
        exec open(t) in {}


if __name__ == '__main__':
    sys.exit(main() or 0)
