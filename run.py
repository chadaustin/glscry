import os
import string
import sys

pythonpath = os.environ.get('PYTHONPATH')
if pythonpath:
    pythonpath = pythonpath + ':' + os.getcwd()
else:
    pythonpath = os.getcwd()
os.environ['PYTHONPATH'] = pythonpath

os.system(sys.executable + ' ' + string.join(sys.argv[1:]))
