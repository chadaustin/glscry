#!/usr/bin/env python

import getopt
import os.path
import sys
import tempfile


beginTag = '[Begin Copyright Header]'
endTag   = '[End Copyright Header]'


def formatPythonComment(header):
    headerLines = [beginTag, ''] + header.splitlines() + ['', endTag]
    return ['# ' + line for line in headerLines]


def formatCComment(header):
    prologue = ['/* ' + beginTag, ' *']
    epilogue = [' *', ' * ' + endTag + ' */']
    headerLines = [' * ' + line for line in header.splitlines()]
    return prologue + headerLines + epilogue


sourceTypes = {
    '.py' : formatPythonComment,
    '.cpp': formatCComment,
    '.h'  : formatCComment,
    '.c'  : formatCComment }


def getFormatter(filename):
    for k, v in sourceTypes.iteritems():
        if filename.endswith(k):
            return v
    return None


def writeLines(lines, filename):
    tmp_handle, tmp_path = tempfile.mkstemp()
    tmp_file = os.fdopen(tmp_handle, 'w')
    for line in lines:
        print >> tmp_file, line
    del tmp_file
        
    os.remove(filename)
    os.rename(tmp_path, filename)


def updateCopyright(header, source):
    lines = open(source).read().splitlines()

    formatter = getFormatter(source)
    if not formatter:
        print source + ': Unknown extension, skipping.'
        return
    headerLines = formatter(header)


    # Find location of header in source.
    startLine = None
    endLine   = None
    for i, line in enumerate(lines):
        if startLine is None:
            if beginTag in line:
                startLine = i
        elif endLine is None:
            if endTag in line:
                endLine = i + 1

    if startLine is None or endLine is None:
        # Insert header at top.
        print source + ": Inserting header."
        if len(lines) > 0 and lines[0].startswith('#!'):
            lines = lines[:1] + headerLines + lines[1:]
        else:
            lines = headerLines + lines
    else:
        # Replace existing header.
        print source + ": Replacing header."
        lines[startLine:endLine] = headerLines

    writeLines(lines, source)


def usage(argv):
    print """\
Usage: [python] %s [Options] HeaderTemplate [Sources]

Options:
    -h, --help      Show this help text.
""" % argv[0]
    return 1


def main(argv=sys.argv):
    # Parse options.
    program = os.path.basename(argv[0])
    try:
        options, args = getopt.getopt(argv[1:], '', ['help'])
    except getopt.GetoptError:
        print program + ': Invalid Option'
        print
        return usage(argv)

    if len(args) < 1:
        print program + ': HeaderTemplate filename not specified'
        print
        return usage(argv)

    HeaderTemplate = open(args[0]).read()
    Sources = args[1:]
    if len(Sources) < 1:
        print program + ': No sources specified'
        print
        return usage(argv)
    
    for s in Sources:
        updateCopyright(HeaderTemplate, s)

if __name__ == '__main__':
    sys.exit(main() or 0)
