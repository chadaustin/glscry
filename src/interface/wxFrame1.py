#Boa:Frame:wxFrame1

from wxPython.wx import *
import os
import Gnuplot, Gnuplot.PlotItems, Gnuplot.funcutils

def create(parent):
    return wxFrame1(parent)

[wxID_WXFRAME1, wxID_WXFRAME1BATCHSIZES, wxID_WXFRAME1BROWSE_BUTTON, 
 wxID_WXFRAME1CHOICE1, wxID_WXFRAME1EXAMPLE, wxID_WXFRAME1GRAPH_BUTTON, 
 wxID_WXFRAME1HIERZ, wxID_WXFRAME1LIGHTS, wxID_WXFRAME1NOTEBOOK1, 
 wxID_WXFRAME1PANEL1, wxID_WXFRAME1PANEL2, wxID_WXFRAME1PIXELTRANSFER, 
 wxID_WXFRAME1STATICBITMAP1, wxID_WXFRAME1STATICTEXT1, wxID_WXFRAME1TEXMEM, 
 wxID_WXFRAME1TEXTCTRL1, wxID_WXFRAME1TREECTRL1, wxID_WXFRAME1WINDOW1, 
] = map(lambda _init_ctrls: wxNewId(), range(18))

[wxID_WXFRAME1MENU1ID_EXIT, wxID_WXFRAME1MENU1ID_NEW, 
 wxID_WXFRAME1MENU1ID_OPEN, wxID_WXFRAME1MENU1ID_SAVE, 
 wxID_WXFRAME1MENU1ID_SAVEAS, 
] = map(lambda _init_coll_menu1_Items: wxNewId(), range(5))

[wxID_WXFRAME1MENU4ID_ABOUT, wxID_WXFRAME1MENU4ID_HELP, 
] = map(lambda _init_coll_menu4_Items: wxNewId(), range(2))

[wxID_WXFRAME1MENU2ITEMS0] = map(lambda _init_coll_menu2_Items: wxNewId(), range(1))

[wxID_WXFRAME1MENU3ID_PROP] = map(lambda _init_coll_menu3_Items: wxNewId(), range(1))

class wxFrame1(wxFrame):
    
    def _init_coll_menu3_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU3ID_PROP,
              item=u'Properties', kind=wxITEM_NORMAL)

    def _init_coll_menu2_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU2ITEMS0, item='Items0',
              kind=wxITEM_NORMAL)

    def _init_coll_menu1_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ID_NEW, item=u'New',
              kind=wxITEM_NORMAL)
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ID_OPEN, item=u'Open',
              kind=wxITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ID_SAVE, item=u'Save',
              kind=wxITEM_NORMAL)
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ID_SAVEAS,
              item=u'Save As', kind=wxITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ID_EXIT, item=u'Exit',
              kind=wxITEM_NORMAL)
        EVT_MENU(self, wxID_WXFRAME1MENU1ID_NEW, self.OnMenu1Items0Menu)
        EVT_MENU(self, wxID_WXFRAME1MENU1ID_SAVE, self.OnMenu1Id_saveMenu)
        EVT_MENU(self, wxID_WXFRAME1MENU1ID_SAVEAS, self.OnMenu1Id_saveasMenu)
        EVT_MENU(self, wxID_WXFRAME1MENU1ID_EXIT, self.OnMenu1Id_exitMenu)

    def _init_coll_menu4_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString=u'', id=wxID_WXFRAME1MENU4ID_ABOUT,
              item=u'About', kind=wxITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU4ID_HELP, item=u'Help',
              kind=wxITEM_NORMAL)
        EVT_MENU(self, wxID_WXFRAME1MENU4ID_HELP, self.OnMenu4Items1Menu)
        EVT_MENU(self, wxID_WXFRAME1MENU4ID_ABOUT, self.OnMenu4Items0Menu)

    def _init_coll_menuBar1_Menus(self, parent):
        # generated method, don't edit

        parent.Append(menu=self.menu1, title=u'File')
        parent.Append(menu=self.menu2, title=u'Edit')
        parent.Append(menu=self.menu3, title=u'Options')
        parent.Append(menu=self.menu4, title=u'Help')

    def _init_coll_notebook1_Pages(self, parent):
        # generated method, don't edit

        parent.AddPage(imageId=-1, page=self.panel1, select=True,
              text=u'Analyze')
        parent.AddPage(imageId=-1, page=self.panel2, select=False,
              text='GLScry')
              
    def _init_choiceBox(self, parent):
        parent.Append("VertexRate")
        parent.Append("PrimitiveRate")
        parent.Append("FillRate")
        parent.Append("BatchRate")
    
    def _init_utils(self):
        # generated method, don't edit
        self.menuBar1 = wxMenuBar()

        self.menu1 = wxMenu(title=u'')

        self.menu2 = wxMenu(title='')

        self.menu3 = wxMenu(title='')

        self.menu4 = wxMenu(title='')

        self._init_coll_menuBar1_Menus(self.menuBar1)
        self._init_coll_menu1_Items(self.menu1)
        self._init_coll_menu2_Items(self.menu2)
        self._init_coll_menu3_Items(self.menu3)
        self._init_coll_menu4_Items(self.menu4)

    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wxFrame.__init__(self, id=wxID_WXFRAME1, name='', parent=prnt,
              pos=wxPoint(112, 70), size=wxSize(1032, 746),
              style=wxDEFAULT_FRAME_STYLE, title='work_in_progress')
        self._init_utils()
        self.SetClientSize(wxSize(1024, 712))
        self.SetMenuBar(self.menuBar1)

        self.notebook1 = wxNotebook(id=wxID_WXFRAME1NOTEBOOK1, name='notebook1',
              parent=self, pos=wxPoint(0, 0), size=wxSize(248, 692), style=0)

        self.window1 = wxScrolledWindow(id=wxID_WXFRAME1WINDOW1, name='window1',
              parent=self, pos=wxPoint(248, 0), size=wxSize(776, 692), style=0)

        self.panel1 = wxPanel(id=wxID_WXFRAME1PANEL1, name='Analyze',
              parent=self.notebook1, pos=wxPoint(0, 0), size=wxSize(240, 666),
              style=wxTAB_TRAVERSAL)

        self.panel2 = wxPanel(id=wxID_WXFRAME1PANEL2, name='GLScry',
              parent=self.notebook1, pos=wxPoint(0, 0), size=wxSize(240, 666),
              style=wxTAB_TRAVERSAL)

        self.textCtrl1 = wxTextCtrl(id=wxID_WXFRAME1TEXTCTRL1, name='textCtrl1',
              parent=self.panel1, pos=wxPoint(8, 48), size=wxSize(144, 21),
              style=0, value=u'Please select a directory')

        self.browse_button = wxButton(id=wxID_WXFRAME1BROWSE_BUTTON,
              label=u'Browse', name=u'browse_button', parent=self.panel1,
              pos=wxPoint(160, 48), size=wxSize(75, 23), style=0)
        EVT_BUTTON(self.browse_button, wxID_WXFRAME1BROWSE_BUTTON,
              self.BuildFolder)

        self.treeCtrl1 = wxTreeCtrl(id=wxID_WXFRAME1TREECTRL1, name='treeCtrl1',
              parent=self.panel1, pos=wxPoint(8, 80), size=wxSize(216, 536),
              style=wxTR_HAS_BUTTONS | wxTR_MULTIPLE)

        self.graph_button = wxButton(id=wxID_WXFRAME1GRAPH_BUTTON,
              label=u'Graph', name=u'graph_button', parent=self.panel1,
              pos=wxPoint(160, 624), size=wxSize(75, 31), style=0)
        EVT_BUTTON(self.graph_button, wxID_WXFRAME1GRAPH_BUTTON,
              self.OnGraphButton)

        self.staticBitmap1 = wxStaticBitmap(bitmap=wxBitmap('blank.png',
              wxBITMAP_TYPE_PNG), id=wxID_WXFRAME1STATICBITMAP1,
              name='staticBitmap1', parent=self.window1, pos=wxPoint(0, 0),
              size=wxSize(775, 692), style=0)
        self.staticBitmap1.SetAutoLayout(True)
        self.staticBitmap1.Center(wxBOTH)
        EVT_LEFT_DCLICK(self.staticBitmap1, self.OnBitmapDblClick)

        self.batchsizes = wxCheckBox(id=wxID_WXFRAME1BATCHSIZES,
              label='Batch Sizes', name='batchsizes', parent=self.panel2,
              pos=wxPoint(64, 88), size=wxSize(83, 23), style=0)

        self.example = wxCheckBox(id=wxID_WXFRAME1EXAMPLE, label='Example',
              name='example', parent=self.panel2, pos=wxPoint(64, 108),
              size=wxSize(83, 23), style=0)

        self.hierz = wxCheckBox(id=wxID_WXFRAME1HIERZ, label='Hierz',
              name='hierz', parent=self.panel2, pos=wxPoint(64, 128),
              size=wxSize(83, 23), style=0)

        self.lights = wxCheckBox(id=wxID_WXFRAME1LIGHTS, label='Lights',
              name='lights', parent=self.panel2, pos=wxPoint(64, 148),
              size=wxSize(83, 23), style=0)

        self.pixeltransfer = wxCheckBox(id=wxID_WXFRAME1PIXELTRANSFER,
              label='Pixel Transfer', name='pixeltransfer', parent=self.panel2,
              pos=wxPoint(64, 168), size=wxSize(83, 23), style=0)

        self.texmem = wxCheckBox(id=wxID_WXFRAME1TEXMEM, label='Texmem',
              name='texmem', parent=self.panel2, pos=wxPoint(64, 188),
              size=wxSize(83, 23), style=0)
        
        self.choice1 = wxChoice(choices=[], id=wxID_WXFRAME1CHOICE1,
              name='choice1', parent=self.panel1, pos=wxPoint(128, 16),
              size=wxSize(109, 21), style=0)

        self.staticText1 = wxStaticText(id=wxID_WXFRAME1STATICTEXT1,
              label=u'First choose a data type:', name='staticText1',
              parent=self.panel1, pos=wxPoint(8, 16), size=wxSize(116, 16),
              style=0)
              
        self._init_choiceBox(self.choice1)
        self._init_coll_notebook1_Pages(self.notebook1)
        
    def __init__(self, parent,filename='work_in_progress'):
        self.dirname=""
        self._init_ctrls(parent)

    def OnMenu1Items0Menu(self, event):
        event.Skip()

    def OnMenu4Items1Menu(self, event):
        event.Skip()
    
    def OnMenu4Items0Menu(self, event):
        #-#------About Dialog Box------#-#
        d= wxMessageDialog( self, "work_in_progress \n"
                            "V. 2.16.05"," About work_in_progress", wxOK | wxICON_INFORMATION)  # Create a message dialog box
        d.ShowModal() # Shows it
        d.Destroy() # finally destroy it when finished.    

    def OnMenu1Id_saveMenu(self, event):
        #-#------Save------#-#
        f=open(os.path.join(self.dirname,self.filename),"w")
        f.write(self.control.GetValue())
        f.close()
    def OnMenu1Id_saveasMenu(self, event):
        #-#------Save As------#-#
        self.dirname=os.getcwd()
        dlg = wxFileDialog(self, "Choose a file", self.dirname, " ","*.*", wxSAVE)
        if dlg.ShowModal() == wxID_OK:
            self.filename=dlg.GetFilename()
            self.dirname=dlg.GetDirectory()
            self.OnSave()
        dlg.Destroy()    
    def OnMenu1Id_exitMenu(self, event):
        event.Skip()
        event.Skip()
        
        #-#------Exit------#-#
        self.Close(true)
    
    def OnGraphButton(self, event):
        #-#------open a new gnuplot session-----#-#
        g = Gnuplot.Gnuplot(debug=1)
        #-#------get datafile------#-#
        selected = self.treeCtrl1.GetSelections()
        size = len(selected)
        count = 0;
        while count < size:
            path = self.treeCtrl1.GetPyData(selected[count])
            count = count + 1
            self.SetGraphLabel(path, g)
            self.GraphData(path, g)           
    def SaveAndDisplay(self, event):
        #-#------Graph Button Event------#-#
        selected = self.treeCtrl1.GetSelection()
        path = self.treeCtrl1.GetPyData(selected)
        
        img = wxBitmap(path, wxBITMAP_TYPE_PNG)
        #-#------Resize Image for Window------#-#
        resizedimg = img
        toobig = false
        height = img.GetHeight()
        width = img.GetWidth()
        if width > 774:
            resizedimg.SetWidth(774)
            toobig = true
        if height > 691:
            resizedimg.SetHeight(691)
            toobig = true
        if toobig == true:
            self.staticBitmap1.SetBitmap(resizedimg)
        else:
            self.staticBitmap1.SetBitmap(img)
    def OnBitmapDblClick(self, event):
    #-#------On Double Click of StaticBitmap1, Open a new scrolled window
    #to view image at full size------#-#    
         selected = self.treeCtrl1.GetSelection()
         nm = self.treeCtrl1.GetItemText(selected)
         path = self.treeCtrl1.GetPyData(selected)
         img = wxBitmap(path, wxBITMAP_TYPE_PNG)
         height = img.GetHeight()
         width = img.GetWidth()
                 
         self.wxExpFrame1 = wxFrame(self, id=wxID_WXMINIFRAME1, name='',
              pos=wxPoint(175, 144), size=wxSize(768, 530),
              style=wxDEFAULT_FRAME_STYLE, title=nm)
         self.scrolledWindow1 = wxScrolledWindow(id=wxID_WXMINIFRAME1SCROLLEDWINDOW1,
              name='scrolledWindow1', parent=self.wxExpFrame1, pos=wxPoint(0, 0),
              size=wxSize(width, height), style=wxHSCROLL | wxVSCROLL)
         self.scrolledWindow1.SetScrollbars(30, 30, width, height, 0, 0, noRefresh = FALSE)              
         
         self.fullBitmap1 = wxStaticBitmap(bitmap=wxBitmap(path,
              wxBITMAP_TYPE_PNG), id=wxID_WXFULLBITMAP,
              name='fullbitmap1', parent=self.scrolledWindow1, pos=wxPoint(0, 0),
              size=wxSize(width, height), style=0)
         self.wxExpFrame1.Show()
                
        
    #-#------Tree Functions------#-#
                  
    def BuildFolder(self, event):
        #-#------Build a tree according to root directory------#-#
        dlg = wxDirDialog(self)
        try:
            if dlg.ShowModal() == wxID_OK:
                dir = dlg.GetPath()
                self.textCtrl1.Clear()
                self.textCtrl1.WriteText(dir)
                self.root = ""
                self.treeCtrl1.DeleteAllItems()
                self.StartBuildFromDir(dir)
                self.treeCtrl1.Expand(self.root)
                
        finally:
            dlg.Destroy()

    def StartBuildFromDir(self, dir):
        rootname = os.path.split(dir)
        self.root = self.treeCtrl1.AddRoot(rootname[1])
        self.rootdir = dir
        self.BuildChildrenFromDir(self.root, dir)

    def BuildChildrenFromDir(self, parent, dir):
        dirlisting = os.listdir(dir)
        for listing in dirlisting:
            pathinquestion = os.path.join(dir, listing)
            if os.path.isfile(pathinquestion):
                extension = os.path.splitext(pathinquestion)
                extension = extension[1]
                if extension == ".testresult":
                    child = self.treeCtrl1.AppendItem(parent, listing)
                    childdata = self.treeCtrl1.GetItemData(child)
                    childdata.path = pathinquestion
                    self.treeCtrl1.SetPyData(child, pathinquestion)            
                    
                    
            elif os.path.isdir(pathinquestion):
                newparent = self.treeCtrl1.AppendItem(parent, listing)
                newdir = os.path.join(dir, listing)
                self.BuildChildrenFromDir(newparent, newdir)
                  
    def SetGraphLabel(self, path, graph):
        choice = self.choice1.GetSelection()
        if choice == -1:
            choice = 0
        # load info from .testresult file
        file = eval(open(path).read())
        # set x-label
        X = file['Test']['XUnits']
        graph.xlabel(X)
        # set y-label
        Y = file['Test']['GraphLines'][0]['ResultSet'][0]['Results'][choice]['Units']
        graph.ylabel(Y)
        # set the title
        version = file['GLScry Version']
        host = file['System']['Host']
        vendor = file['System']['OpenGL Vendor']
        renderer = file['System']['OpenGL Renderer']
        glversion = file['System']['OpenGL Version']
        Gtitle = version + " :: " + host + " :: " + vendor + " :: " + renderer + " :: " + glversion
        graph.title(Gtitle)
        
    def GraphData(self, path, graph):
        file = eval(open(path).read())
        choice = self.choice1.GetSelection()
        if choice == -1:
            choice = 0
        size = len(file['Test']['GraphLines'][0]['ResultSet'])
        count = 0
        graph("plot '-' title 'test'\n")
        while count < size:
            name = file['Test']['GraphLines'][0]['ResultSet'][count]['Name']
            result = file['Test']['GraphLines'][0]['ResultSet'][count]['Results'][choice]['Value']
            # graph it
            print name
            print result
            graph("%s %f\n" % (name, result))
            count = count + 1
        graph("e\n")
        raw_input("press return to continue...\n")
        #graph.reset()


