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
tests = glob('test/*.py')

setup(options=options,
      console=['run.py'],
      data_files=[('', ['scripts/batch/RunAllTests.bat',
                        'COPYRIGHT.txt',
                        'README.txt',
                        msvcr71]),
                  ('lib', ['lib/SDL.dll',
                           'lib/glscry.py',
                           'lib/_glscry.dll',
                           msvcp71]),
                  ('doc', ['doc/dataformat.txt',
                           'doc/links.txt',
                           'doc/terminology.txt']),
                  ('test', tests)])
