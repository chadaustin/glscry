#!/usr/bin/env python

import os
import string
import sys
from glob import glob
import getopt


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

    # Create data directory if it does not exist and switch to it.
    try:
        os.mkdir('data')
    except OSError:
        pass
    os.chdir('data')

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
