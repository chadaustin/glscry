#!/usr/bin/env python
import glob
import os.path
import sys
import UpdateCopyright


def getScriptDirectory(argv=sys.argv):
    return os.path.abspath(os.path.dirname(argv[0]))
    

def main(argv=sys.argv):
    # Change directory to the root of the project.
    scriptDir = getScriptDirectory(argv)
    projectDir = os.path.normpath(os.path.join(scriptDir, '..'))
    os.chdir(projectDir)
    
    header = 'scripts/header.txt'
    sources = ['run.py', 'src/glscry.py'] + \
              glob.glob('src/_glscry/*.cpp') + \
              glob.glob('src/_glscry/*.h') + \
              glob.glob('src/_glscry/*.c')

    exceptions = ['glew.c', 'glew.h', 'wglew.h', 'glxew.h',
                  'CPUInfo.h', 'CPUInfo.cpp']

    sources = [s for s in sources if os.path.basename(s) not in exceptions]

    #from pprint import pprint
    #pprint(sources)
    #print sources

    return UpdateCopyright.main(['UpdateCopyright.py', header] + sources)


if __name__ == '__main__':
    sys.exit(main() or 0)
