from wxPython.wx import *
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
        
        
        
class Form1(wxPanel):
    def __init__(self, parent, id):
        wxPanel.__init__(self, parent, -1)
        self.quote = wxStaticText(self, -1, "Your quote :",wxPoint(20, 30))

        # A multiline TextCtrl
        self.logger = wxTextCtrl(self,5, "",wxPoint(300,20), wxSize(200,300),wxTE_MULTILINE | wxTE_READONLY)

        # A button
        self.button =wxButton(self, 10, "Save", wxPoint(200, 300))
        EVT_BUTTON(self, 10, self.OnClick)

        # the edit control - one line version.
        self.lblname = wxStaticText(self, -1, "Your name :",wxPoint(20,60))
        self.editname = wxTextCtrl(self, 20, "Enter here your name", wxPoint(150, 60), wxSize(150, -1))
        EVT_TEXT(self, 20, self.EvtText)
        EVT_CHAR(self.editname, self.EvtChar)

        # the combobox Control
        self.sampleList = ['friends', 'advetising', 'Websearch', 'yellowpages']
        self.lblhear = wxStaticText(self,-1,"How did you hear from us ?",wxPoint(20, 90))
        self.edithear=wxComboBox(self, 30, "", wxPoint(150, 90), wxSize(95, -1),
                   self.sampleList, wxCB_DROPDOWN)
        EVT_COMBOBOX(self, 30, self.EvtComboBox)
        EVT_TEXT(self, 30, self.EvtText)
        # Checkbox
        self.insure = wxCheckBox(self, 40, "Do you want Insured Shipment ?",wxPoint(20,180))
        EVT_CHECKBOX(self, 40,   self.EvtCheckBox)
        # Radio Boxes
        self.radioList = ['blue', 'red', 'yellow', 'orange', 'green', 'purple',
                      'navy blue', 'black', 'gray']

        rb = wxRadioBox(self, 50, "What color would you like ?", wxPoint(20, 210), wxDefaultSize,
                        self.radioList, 3, wxRA_SPECIFY_COLS)
        EVT_RADIOBOX(self, 50, self.EvtRadioBox)
    def EvtRadioBox(self, event):
        self.logger.AppendText('EvtRadioBox: %d\n' % event.GetInt())
    def EvtComboBox(self, event):
        self.logger.AppendText('EvtComboBox: %s\n' % event.GetString())
    def OnClick(self,event):
        self.logger.AppendText(" Click on object with Id %d\n" %event.GetId())
    def EvtText(self, event):
        self.logger.AppendText('EvtText: %s\n' % event.GetString())
    def EvtChar(self, event):
        self.logger.AppendText('EvtChar: %d\n' % event.GetKeyCode())
        event.Skip()
    def EvtCheckBox(self, event):
        self.logger.AppendText('EvtCheckBox: %d\n' % event.Checked())

class Form2(wxPanel):
    def __init__(self, parent, id):
        wxPanel.__init__(self, parent, -1)
        self.sampleList = ['friends', 'advetising', 'Websearch', 'yellowpages']
        self.radioList = ['blue', 'red', 'yellow', 'orange', 'green', 'purple',
                      'navy blue', 'black', 'gray']
        gs = wxFlexGridSizer(5,2,5,5)
        gs.Add(wxStaticText(self, -1, "Your name :"),0,wxEXPAND)
        self.editname=wxTextCtrl(self, 20, "Enter here your name")
        gs.Add(self.editname,0,wxEXPAND)
        EVT_TEXT(self, 20, self.EvtText)
        EVT_CHAR(self.editname, self.EvtChar)
        gs.Add(wxStaticText(self,-1,"How did you hear from us ?"),0,wxEXPAND)
        gs.Add(wxComboBox(self, 30, "", wxPoint(-1,-1),wxSize(-1,-1), self.sampleList, wxCB_DROPDOWN),0,wxEXPAND)
        EVT_COMBOBOX(self, 30, self.EvtComboBox)
        EVT_TEXT(self, 30, self.EvtText)
        gs.Add((60, 20), 0, wxEXPAND)
        gs.Add(wxCheckBox(self, 40, "Do you want Insured Shipment ?"),0,wxEXPAND)
        EVT_CHECKBOX(self, 40,   self.EvtCheckBox)
        gs.Add((60, 20), 0, wxEXPAND)
        gs.Add(wxRadioBox(self, 50, "What color would you like ?", wxPoint(-1,-1),wxDefaultSize,
                        self.radioList, 3, wxRA_SPECIFY_COLS),0,wxEXPAND)
        EVT_RADIOBOX(self, 50, self.EvtRadioBox)
        gs.Add((60, 20), 0, wxEXPAND)
        gs.Add(wxButton(self, 10, "Save"),0,wxALIGN_CENTER)
        EVT_BUTTON(self, 10, self.OnClick)
        # gs.AddGrowableRow(0)
        boxh = wxBoxSizer(wxHORIZONTAL)
        boxh.Add(gs,0,wxEXPAND)

        self.logger=wxTextCtrl(self,5, "",wxPoint(-1,-1),wxSize(-1,-1),wxTE_MULTILINE | wxTE_READONLY)
        boxh.Add( self.logger
                  ,1,wxEXPAND)

        self.sizer = boxh
        self.sizer.Fit(self)
        self.SetAutoLayout(true)
        self.SetSizer(self.sizer)
    def EvtRadioBox(self, event):
        self.logger.AppendText('EvtRadioBox: %d\n' % event.GetInt())
    def EvtComboBox(self, event):
        self.logger.AppendText('EvtComboBox: %s\n' % event.GetString())
    def OnClick(self,event):
        self.logger.AppendText(" Click on object with Id %d\n" %event.GetId())
    def EvtText(self, event):
        self.logger.AppendText('EvtText: %s\n' % event.GetString())
    def EvtChar(self, event):
        self.logger.AppendText('EvtChar: %d\n' % event.GetKeyCode())
        event.Skip()
    def EvtCheckBox(self, event):
        self.logger.AppendText('EvtCheckBox: %d\n' % event.Checked())




app = wxPySimpleApp()
frame = MainWindow(None, -1, "work_in_progress")

nb = wxNotebook(frame,-1)
form1=Form1(nb, -1)
form2=Form2(nb,-1)
nb.AddPage(form1, "Absolute Positionning")
nb.AddPage(form2, "Sizers")

frame.Show(1)
app.MainLoop()