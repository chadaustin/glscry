from distutils.core import setup
import py2exe

options = {'py2exe': { 'includes': ['platform',
                                    'pprint'] } }
setup(options=options,
      console=['run.py'])
