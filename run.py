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


def usage():
    print """\
Usage: python run.py [OPTIONS] [TESTS]

Options:
    -a, --all       Run all tests.
    -h, --help      Show this help text.
"""

def main():
    # Parse options.
    try:
        options, args = getopt.getopt(sys.argv[1:], 'a', ['help', 'all'])
    except getopt.GetoptError:
        usage()
        sys.exit(1)

    allTests = False
    for o, a in options:
        if o in ('-h', '--help'):
            usage()
            sys.exit(0)
        elif o in ('-a', '--all'):
            allTests = True

    # Modify PYTHONPATH
    pythonpath = os.environ.get('PYTHONPATH')
    if pythonpath:
        pythonpath = pythonpath + ':' + os.getcwd()
    else:
        pythonpath = os.getcwd()
    os.environ['PYTHONPATH'] = pythonpath

    # Get test list.
    tests = args
    if allTests:
        tests.extend(glob('test/*.py'))
    tests = map(os.path.abspath, tests)

    # Create directory if it does not exist and switch to it.
    def enterdir(dir):
        try:
            os.mkdir(dir)
        except OSError:
            pass
        os.chdir(dir)

    enterdir('data')
    enterdir(socket.gethostname())

    if not tests:
        print "No tests specified.  Specify a test explicitly or use -a."
        print
        usage()
        sys.exit(1)

    for t in tests:
        print
        print "Running test script '%s'" % t
        os.system(sys.executable + ' ' + t)


if __name__ == '__main__':
    main()
