from distutils.core import setup
import py2exe

import os
from glob import glob

options = {'py2exe': { 'includes': ['platform',
                                    'pprint'] } }

# Most of the data files should somehow be generated from the build
# system.

msvcr71 = os.path.join(os.environ['WINDIR'], 'system32', 'msvcr71.dll')
msvcp71 = os.path.join(os.environ['WINDIR'], 'system32', 'msvcp71.dll')
docs = glob('doc/*.txt')
tests = glob('test/*.py')

setup(options=options,
      console=['run.py',
               'scripts/win32-dist/RunGnuplot.py'],
      data_files=[('', ['COPYRIGHT.txt',
                        'README.txt',
                        'ChangeLog',
                        'scripts/win32-dist/RunAllTests.bat',
                        'third-party/vc7/gnuplot/bin/wgnuplot.exe',
                        msvcr71]),
                  ('lib', ['lib/SDL.dll',
                           'lib/glscry.py',
                           'lib/_glscry.dll',
                           msvcp71]),
                  ('doc', docs),
                  ('test', tests)])
