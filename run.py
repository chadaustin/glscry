import os
import string
import sys

pythonpath = os.environ.get('PYTHONPATH')
if pythonpath:
    pythonpath = pythonpath + ':' + os.getcwd()
else:
    pythonpath = os.getcwd()
os.environ['PYTHONPATH'] = pythonpath

tests = map(os.path.abspath, sys.argv[1:])
try:
    os.mkdir('data')
except OSError:
    pass
os.chdir('data')
    
os.system(sys.executable + ' ' + string.join(tests))
