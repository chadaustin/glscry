#!/usr/bin/env python
#Boa:App:BoaApp

import wx
import os
import GLAnalyzeMain

modules ={u'GLAnalyzeMain': [1, 'Main frame of Application', u'GLAnalyzeMain.py']}

class BoaApp(wx.App):
    def OnInit(self):
        wx.InitAllImageHandlers()
        self.main = GLAnalyzeMain.create(None)
        self.main.Show()
        self.SetTopWindow(self.main)
        GLAnalyzeMain.wxFrame1.InitConfig(self.main)
        return True

def main():
    application = BoaApp(0)
    application.MainLoop()

if __name__ == '__main__':
    main()
    
if os.path.exists("temp.png"):
    os.remove("temp.png")
if os.path.exists("full.png"):
    os.remove("full.png")
if os.path.exists("temp.gnu"):
    os.remove("temp.gnu")