from wxPython.wx import *
import os
ID_ABOUT=101
ID_OPEN=102
ID_SAVE=103
ID_SAVEAS=104
ID_EXIT=110

class MainWindow(wxFrame):
    def __init__(self,parent,id,filename='work_in_progress'):
        
        self.filename=filename
        self.dirname=""
        wxFrame.__init__(self,parent,-4, "%s" % self.filename, size = (800,600),
                                     style=wxDEFAULT_FRAME_STYLE|wxNO_FULL_REPAINT_ON_RESIZE)
        self.control = wxTextCtrl(self, 1, style=wxTE_MULTILINE)
        self.CreateStatusBar() # A Statusbar in the bottom of the window
        # Setting up the menu.
        filemenu= wxMenu()
        filemenu.Append(ID_OPEN,"&Open"," Open a new file ")
        filemenu.Append(ID_SAVE,"&Save"," Save the current file")
        filemenu.Append(ID_SAVEAS,"Save &As"," Save the file under a different name")
        filemenu.AppendSeparator()
        filemenu.Append(ID_EXIT,"E&xit"," Terminate the program")
        # Setting up the Help menu.
        helpmenu = wxMenu()
        helpmenu.AppendSeparator()
        helpmenu.Append(ID_ABOUT, "&About"," Information about this program")
        # Creating the menubar.
        menuBar = wxMenuBar()
        menuBar.Append(filemenu,"&File") # Adding the "filemenu" to the MenuBar
        menuBar.Append(helpmenu, "&Help") #Adding the "helpmenu" to the MenuBar
        self.SetMenuBar(menuBar)  # Adding the MenuBar to the Frame content.
        EVT_MENU(self, ID_ABOUT, self.OnAbout) # attach the menu-event ID_ABOUT to the method self.OnAbout
        EVT_MENU(self, ID_EXIT, self.OnExit)   # attach the menu-event ID_EXIT to the method self.OnExit
        EVT_MENU(self, ID_OPEN, self.OnOpen)
        EVT_MENU(self, ID_SAVE, self.OnSave)
        EVT_MENU(self, ID_SAVEAS, self.OnSaveAs)
                       
        self.Show(1)
        #sizers
        self.sz3 = wx.BoxSizer(wx.HORIZONTAL) 
        self.w4 = wx.Window(self,-1,wx.Point(3,3),wx.Size(20,250))
        self.w6 = wx.Window(self,-1,wx.Point(274,73),wx.Size(20,20))
        self.wxnb7 = wx.Notebook(self.w4,-1,wx.Point(0,0),wx.Size(20,20))
        self.sz3.Add(self.w4,0,wx.TOP|wx.LEFT|wx.BOTTOM|wx.RIGHT|wx.ALIGN_TOP|wx.FIXED_MINSIZE,3)
        self.sz3.Add(self.w6,0,wx.TOP|wx.LEFT|wx.BOTTOM|wx.RIGHT|wx.FIXED_MINSIZE,3)
        self.SetSizer(self.sz3);self.SetAutoLayout(1);self.Layout();
        self.Refresh()
        self.Show(1)

    def OnAbout(self,e):
        d= wxMessageDialog( self, " \twork_in_progress \n"
                            " \tV. 1.25.05"," About work_in_progress", wxOK)  # Create a message dialog box
        d.ShowModal() # Shows it
        d.Destroy() # finally destroy it when finished.
    def OnExit(self,e):
        self.Close(true)  # Close the frame.
    def OnSave(self,e):
        """ Save the current file """
        f=open(os.path.join(self.dirname,self.filename),"w")
        f.write(self.control.GetValue())
        f.close()
    def OnOpen(self,e):
        """ Open a file"""
        dlg = wxFileDialog(self, "Choose a file", self.dirname, "", "*.*", wxOPEN)
        if dlg.ShowModal() == wxID_OK:
            self.filename=dlg.GetFilename()
            self.dirname=dlg.GetDirectory()
        f=open(os.path.join(self.dirname,self.filename),'r')
        self.control.SetValue(f.read())
        f.close()
        dlg.Destroy()
    def OnSaveAs(self,e):
        """ Save as """
        dlg = wxFileDialog(self, "Choose a file", self.dirname, self.filename,"*.*", wxSAVE)
        if dlg.ShowModal() == wxID_OK:
            self.filename=dlg.GetFilename()
            self.dirname=dlg.GetDirectory()
            self.OnSave(e)
        dlg.Destroy()

class LeftPanel(wxPanel):
    def __init__(self, parent):
        wxPanel.__init__(self, parent)
        self.SetBackgroundColour(wx.NamedColour("MEDIUM ORCHID"))

app = wxPySimpleApp()
frame = MainWindow(None, -1, "work_in_progress")
LeftPanel(frame, -1)
frame.Show(1)
app.MainLoop()