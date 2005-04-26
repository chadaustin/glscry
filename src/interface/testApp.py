#!/usr/bin/env python
#Boa:App:BoaApp

from wxPython.wx import *
import os
import testFrame

modules ={u'testFrame': [1, 'Main frame of Application', u'testFrame.py']}

class BoaApp(wxApp):
    def OnInit(self):
        wxInitAllImageHandlers()
        self.main = testFrame.create(None)
        self.main.Show()
        self.SetTopWindow(self.main)
        return True
         
def main():
    application = BoaApp(0)
    application.MainLoop()

if __name__ == '__main__':
    main()

os.remove("temp.png")