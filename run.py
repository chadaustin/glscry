#!/usr/bin/env python

import os
import string
import sys
from glob import glob
from optparse import OptionParser

# Parse options.
parser = OptionParser()
parser.add_option('-a', '--all', action='store_true', dest='all',
                  help='Run all tests')
(options, args) = parser.parse_args()

# Modify PYTHONPATH
pythonpath = os.environ.get('PYTHONPATH')
if pythonpath:
    pythonpath = pythonpath + ':' + os.getcwd()
else:
    pythonpath = os.getcwd()
os.environ['PYTHONPATH'] = pythonpath

# Get test list.
tests = []
if options.all:
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
    sys.exit(1)

for t in tests:
    print "Running test '%s'" % t
    os.system(sys.executable + ' ' + t)
    print
