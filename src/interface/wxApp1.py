#!/usr/bin/env python
#Boa:App:BoaApp

from wxPython.wx import *

import wxFrame1

modules ={'wxFrame1': [1, 'Main frame of Application', 'none://wxFrame1.py']}

class BoaApp(wxApp):
    def OnInit(self):
        wxInitAllImageHandlers()
        self.main = wxFrame1.create(None)
        self.main.Show()
        self.SetTopWindow(self.main)
        return True

def main():
    application = BoaApp(0)
    application.MainLoop()

if __name__ == '__main__':
    main()
