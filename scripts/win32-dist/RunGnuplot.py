import os
import sys

def getScriptDirectory(argv=sys.argv):
    return os.path.abspath(os.path.dirname(argv[0]))

def quote(str):
    return '"' + str + '"'

def main(argv=sys.argv):
    wgnuplot = os.path.join(getScriptDirectory(argv), 'wgnuplot.exe')

    for script in argv[1:]:
        script = os.path.abspath(script)
        
        olddir = os.getcwd()
        os.chdir(os.path.dirname(script))
        print os.spawnl(os.P_WAIT, wgnuplot,
                        quote(wgnuplot),
                        quote(os.path.basename(script)))
        os.chdir(olddir)

if __name__ == '__main__':
    sys.exit(main() or 0)
