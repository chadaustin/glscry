#Boa:Frame:wxFrame1
#GLAnalyze created by Alex Allen

from wxPython.wx import *
import os, time
import Gnuplot, Gnuplot.PlotItems, Gnuplot.funcutils
import string
import sys
from glob import glob
import getopt
import socket

def create(parent):
    return wxFrame1(parent)

[wxID_WXFRAME1, wxID_WXFRAME1BROWSE_BUTTON, wxID_WXFRAME1BROWSE_TXT, 
 wxID_WXFRAME1DATA_STYLE, wxID_WXFRAME1DATA_STYLE_TXT, wxID_WXFRAME1DATA_TYPE, 
 wxID_WXFRAME1DATA_TYPE_TXT, wxID_WXFRAME1GRAPH_BUTTON, 
 wxID_WXFRAME1NOTEBOOK1, wxID_WXFRAME1PANEL1, wxID_WXFRAME1PANEL2, 
 wxID_WXFRAME1PANEL3, wxID_WXFRAME1PANEL4, wxID_WXFRAME1STATICBITMAP1, 
 wxID_WXFRAME1TREECTRL1, wxID_WXEXPFRAME1, wxID_WXMINIFRAME1SCROLLEDWINDOW1,
 wxID_WXFULLBITMAP,
] = map(lambda _init_ctrls: wxNewId(), range(18))

[wxID_WXFRAME1MENU1ITEMS0, wxID_WXFRAME1MENU1ITEMS1, wxID_WXFRAME1MENU1ITEMS2, 
] = map(lambda _init_coll_menu1_Items: wxNewId(), range(3))

[wxID_WXFRAME1MENU2ITEMS0,
] = map(lambda _init_coll_menu2_Items: wxNewId(), range(1))

class wxFrame1(wxFrame):

    def _init_coll_menu2_Items(self, parent):         

        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU2ITEMS0, item='About',
              kind=wxITEM_NORMAL)
        EVT_MENU(self, wxID_WXFRAME1MENU2ITEMS0, self.OnAbout)

    def _init_coll_menu1_Items(self, parent):
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS0, item='Open',
              kind=wxITEM_NORMAL)
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS1, item='Save Image',
              kind=wxITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS2, item='Exit',
              kind=wxITEM_NORMAL)
        EVT_MENU(self, wxID_WXFRAME1MENU1ITEMS0, self.OnOpen)
        EVT_MENU(self, wxID_WXFRAME1MENU1ITEMS1, self.OnSave)
        EVT_MENU(self, wxID_WXFRAME1MENU1ITEMS2, self.OnExit)

    def _init_coll_menuBar1_Menus(self, parent):         

        parent.Append(menu=self.menu1, title='File')
        parent.Append(menu=self.menu2, title='Help')
        # to be added later if needed
        #parent.Append(menu=self.menu3, title='Menus2')
        #parent.Append(menu=self.menu4, title='Menus3')

    def _init_coll_notebook1_Pages(self, parent):

        parent.AddPage(imageId=-1, page=self.panel3, select=True,
              text='Graph')
        parent.AddPage(imageId=-1, page=self.panel4, select=False,
              text='GLScry')
    def _init_glscry_panel(self, parent):
        glsizer = wxFlexGridSizer(14, 2, 2, 2)
        self.checkBoxes = []
        blank = wxStaticText(self.panel4, -1, " ")
        checkAll = wxButton(self.panel4, -1, "Select All")
        EVT_BUTTON(checkAll, -1, self.SelectAll)
        run = wxButton(self.panel4, -1, "Run Tests")
        EVT_BUTTON(run, -1, self.RunGLScry)
        # create each test's individual checkbox
        batchCheck = wxCheckBox(self.panel4, -1, "Batch Sizes")
        self.checkBoxes.append(batchCheck)
        fillCheck = wxCheckBox(self.panel4, -1, "Fill Rate")
        self.checkBoxes.append(fillCheck)
        hierzCheck = wxCheckBox(self.panel4, -1, "Hierz")
        self.checkBoxes.append(hierzCheck)
        lightsCheck = wxCheckBox(self.panel4, -1, "Lights")
        self.checkBoxes.append(lightsCheck)
        pixelCheck = wxCheckBox(self.panel4, -1, "Pixel Transfer")
        self.checkBoxes.append(pixelCheck)
        primCheck = wxCheckBox(self.panel4, -1, "Prim Type")
        self.checkBoxes.append(primCheck)
        stateCheck = wxCheckBox(self.panel4, -1, "State Change")
        self.checkBoxes.append(stateCheck)
        texmemCheck = wxCheckBox(self.panel4, -1, "Tex Memory")
        self.checkBoxes.append(texmemCheck)
        texupCheck = wxCheckBox(self.panel4, -1, "Tex Upload")
        self.checkBoxes.append(texupCheck)
        vboCheck = wxCheckBox(self.panel4, -1, "VBO")
        self.checkBoxes.append(vboCheck)
        vertexCheck = wxCheckBox(self.panel4, -1, "Vertex Cache")
        self.checkBoxes.append(vertexCheck)
        vformatsCheck = wxCheckBox(self.panel4, -1, "VFormats")
        self.checkBoxes.append(vformatsCheck)
        for i in range(0, 12):
            glsizer.Add(self.checkBoxes[i], 0, wxALIGN_LEFT)
            glsizer.Add(blank, 0, wxALIGN_LEFT)
        glsizer.Add(checkAll, 0, wxALIGN_LEFT)
        glsizer.Add(run, 0, wxALIGN_LEFT)
        parent.SetSizer(glsizer)
        parent.SetAutoLayout(True)
        parent.Layout()
    def _init_data_type(self, parent):
        parent.Append("VertexRate")
        parent.Append("PrimitiveRate")
        parent.Append("FillRate")
        parent.Append("BatchRate")
    
    def _init_data_style(self, parent):
        parent.Append("Lines")
        parent.Append("Points")
        parent.Append("LinesPoints")
        parent.Append("Boxes")
                    
    def _init_utils(self):
         
        self.menuBar1 = wxMenuBar()
        self.menu1 = wxMenu(title='')
        self.menu2 = wxMenu(title='')

        self._init_coll_menuBar1_Menus(self.menuBar1)
        self._init_coll_menu1_Items(self.menu1)
        self._init_coll_menu2_Items(self.menu2)

    def _init_ctrls(self, prnt):
         
        self.curImg = wxBitmap("blank.png", wxBITMAP_TYPE_PNG)
        self.curImgPath = "blank.png"
        wxFrame.__init__(self, id=wxID_WXFRAME1, name='', parent=prnt,
              pos=wxPoint(15, 3), size=wxSize(1120, 821),
              style=wxDEFAULT_FRAME_STYLE, title='GLAnalyze')
        self._init_utils()
        self.SetClientSize(wxSize(1112, 787))
        self.SetMenuBar(self.menuBar1)

        self.panel1 = wxPanel(id=wxID_WXFRAME1PANEL1, name='panel1',
              parent=self, pos=wxPoint(0, 0), size=wxSize(256, 768),
              style=wxTAB_TRAVERSAL)

        self.panel2 = wxPanel(id=wxID_WXFRAME1PANEL2, name='panel2',
              parent=self, pos=wxPoint(256, 0), size=wxSize(856, 768),
              style=wxTAB_TRAVERSAL)
        # panel sizers
        box = wxBoxSizer(wxHORIZONTAL)
        box.Add(self.panel1, 0, wxEXPAND)
        box.Add(self.panel2, 1, wxEXPAND)
        self.SetAutoLayout(True)
        self.SetSizer(box)
        self.Layout()
        # end panel sizers
        # bitmap resizers
        self.staticBitmap1 = wxStaticBitmap(bitmap=wxBitmap('blank.png',
              wxBITMAP_TYPE_PNG), id=wxID_WXFRAME1STATICBITMAP1,
              name='staticBitmap1', parent=self.panel2, pos=wxPoint(40, 38),
              size=wxSize(852, 764), style=0)
        self.staticBitmap1.SetAutoLayout(True)
        self.staticBitmap1.Center(wxBOTH)
        self.box2 = wxBoxSizer(wxHORIZONTAL)
        self.box2.Add(self.staticBitmap1, 2, wxEXPAND)
        self.panel2.SetAutoLayout(True)
        self.panel2.SetSizer(self.box2)
        self.panel2.Layout()
        # end bitmap resizer
        EVT_LEFT_DCLICK(self.staticBitmap1, self.OnBitmapDblClick)
        # notebook layout sizers
        self.notebook1 = wxNotebook(id=wxID_WXFRAME1NOTEBOOK1, name='notebook1',
              parent=self.panel1, pos=wxPoint(8, 56), size=wxSize(248, 704),
              style=0)

        self.panel3 = wxPanel(id=wxID_WXFRAME1PANEL3, name='panel3',
              parent=self.notebook1, pos=wxPoint(0, 0), size=wxSize(240, 678),
              style=wxTAB_TRAVERSAL)
    
        self.panel4 = wxPanel(id=wxID_WXFRAME1PANEL4, name='panel4',
              parent=self.notebook1, pos=wxPoint(0, 0), size=wxSize(240, 678),
              style=wxTAB_TRAVERSAL)

        self.treeCtrl1 = wxTreeCtrl(id=wxID_WXFRAME1TREECTRL1, name='treeCtrl1',
              parent=self.panel3, pos=wxPoint(16, 80), size=wxSize(200, 536),
              style=wxTR_HAS_BUTTONS | wxTR_MULTIPLE)

        self.graph_button = wxButton(id=wxID_WXFRAME1GRAPH_BUTTON,
              label='Graph', name='graph_button', parent=self.panel3,
              pos=wxPoint(144, 624), size=wxSize(75, 31), style=0)
        EVT_BUTTON(self.graph_button, wxID_WXFRAME1GRAPH_BUTTON,
              self.OnGraphButton)
              
        self.data_style = wxChoice(choices=[], id=wxID_WXFRAME1DATA_STYLE,
              name='data_style', parent=self.panel3, pos=wxPoint(88, 48),
              size=wxSize(125, 21), style=0)

        self.data_style_txt = wxStaticText(id=wxID_WXFRAME1DATA_STYLE_TXT,
              label='Data Style:', name='data_style_txt', parent=self.panel3,
              pos=wxPoint(16, 48), size=wxSize(65, 16), style=0)
        self.data_style_txt.SetFont(wxFont(10, wxSWISS, wxNORMAL, wxNORMAL,
              False, 'Arial'))

        self.data_type = wxChoice(choices=[], id=wxID_WXFRAME1DATA_TYPE,
              name='data_type', parent=self.panel3, pos=wxPoint(88, 16),
              size=wxSize(125, 21), style=0)

        self.data_type_txt = wxStaticText(id=wxID_WXFRAME1DATA_TYPE_TXT,
              label='Data Type:', name='data_type_txt', parent=self.panel3,
              pos=wxPoint(16, 16), size=wxSize(63, 16), style=0)
        self.data_type_txt.SetFont(wxFont(10, wxSWISS, wxNORMAL, wxNORMAL,
              False, 'Arial'))

        self.browse_txt = wxTextCtrl(id=wxID_WXFRAME1BROWSE_TXT,
              name='browse_txt', parent=self.panel1, pos=wxPoint(8, 16),
              size=wxSize(152, 21), style=0, value='Select a directory...')

        self.browse_button = wxButton(id=wxID_WXFRAME1BROWSE_BUTTON,
              label='Browse', name='browse_button', parent=self.panel1,
              pos=wxPoint(168, 16), size=wxSize(75, 23), style=0)
        EVT_BUTTON(self.browse_button, wxID_WXFRAME1BROWSE_BUTTON,
              self.BuildFolder)
        self._init_coll_notebook1_Pages(self.notebook1)
        self._init_data_type(self.data_type)
        self._init_data_style(self.data_style)
        self._init_glscry_panel(self.panel4)              
        
    def __init__(self, parent):
        self._init_ctrls(parent)
    
    # menu items
    # About
    def OnAbout(self, event):
        d= wxMessageDialog( self, "GLAnalyze developed by Alex Allen in collaboration with Dr. Dirk Reiners and Chad Austin.\n"
                            "Designed to work with GLScry developed by Chad Austin and Dr. Dirk Reiners. \n" "version 0.1 ", "About GLAnalyze", wxOK | wxICON_INFORMATION)
                            # Create a message dialog box
        d.ShowModal() # Shows it
        d.Destroy() # finally destroy it when finished
        
    # Open file dialog
    def OnOpen(self, event):
        dlg = wxFileDialog(self, "Choose a file", os.getcwd(), "", "*.png", wxOPEN)
        if dlg.ShowModal() == wxID_OK:
            # This returns a Python list of files that were selected.
            self.curImgPath = dlg.GetPath()
            self.curImg = wxBitmap(self.curImgPath, wxBITMAP_TYPE_PNG)
            self.staticBitmap1.SetBitmap(self.curImg)
            self.Layout()
            self.box2.RecalcSizes()            
        dlg.Destroy()
    # Save file dialog
    def OnSave(self, event):
        dlg = wxFileDialog(self, "Choose a file", self.browse_txt.GetValue() , "", "*.png", wxSAVE)
        dlg.SetFilterIndex(2)
        if dlg.ShowModal() == wxID_OK:
            path = dlg.GetPath()
            self.curImg.SaveFile( path, wxBITMAP_TYPE_PNG ) 
        dlg.Destroy()
    
    # Exit
    def OnExit(self, event):
        self.Close(true)  # Close the frame.

    # Build the tree from the chosen directory
    def BuildFolder(self, event):
        print os.curdir
        dlg = wxDirDialog(self, "Select a directory", os.getcwd())
        try:
            if dlg.ShowModal() == wxID_OK:
                dir = dlg.GetPath()
                self.browse_txt.Clear()
                self.browse_txt.WriteText(dir)
                self.root = ""
                self.treeCtrl1.DeleteAllItems()
                self.StartTestBuild(dir)
                self.treeCtrl1.Expand(self.root)
                
        finally:
            dlg.Destroy()

     
    # Build tree by test 
    def StartTestBuild(self, dir):
        rootname = os.path.split(dir)
        self.root = self.treeCtrl1.AddRoot(rootname[1])
        self.rootdir = dir
        self.treeCtrl1.DeleteAllItems()
        self.treeCtrl1.AddRoot("Data")
        self.testlist = self.treeCtrl1.AppendItem(self.treeCtrl1.GetRootItem(), "Test List")
        self.dirlist = self.treeCtrl1.AppendItem(self.treeCtrl1.GetRootItem(), "Directory List")
        self.testlisting = []
        self.testpath = []
        self.machinelisting = []
        self.machinepath = []
        self.GetTestInfo(self.dirlist, dir)
        self.BuildTree()
        
    def GetTestInfo(self, parent, dir):
        dirlisting = os.listdir(dir)
        for listing in dirlisting:
            pathinquestion = os.path.join(dir, listing)
            if os.path.isfile(pathinquestion):
                # build tree by test
                filename = os.path.split(pathinquestion)
                extension = filename[1].split(".")
                extension = extension[1]
                test = filename[1]
                test = test.rstrip(extension)
                test = test.rstrip(".")
                # build a list of tests and thier paths
                if extension == "testresult":
                    self.testlisting.insert(len(self.testlisting), test)
                    self.testpath.insert(len(self.testpath), pathinquestion)
                    # build directory tree
                    child = self.treeCtrl1.AppendItem(parent, listing)
                    childdata = self.treeCtrl1.GetItemData(child)
                    childdata.path = pathinquestion
                    self.treeCtrl1.SetPyData(child, pathinquestion)  
            elif os.path.isdir(pathinquestion):
                newparent = self.treeCtrl1.AppendItem(parent, listing)
                newdir = os.path.join(dir, listing)
                self.GetTestInfo(newparent, newdir)
                
    def BuildTree(self):
        addedtests = []
        curtest = 0
        while curtest < len(self.testlisting):
            # first get first test from list, then add it as parent in tree
            if self.testlisting[curtest] not in addedtests:
                newitem = self.treeCtrl1.AppendItem(self.testlist, self.testlisting[curtest])
                addedtests.insert(len(addedtests), self.testlisting[curtest])
                # then search list for test of the same name, adding its machine name
                count = 0
                while count < len(self.testlisting):
                    if self.testlisting[count] == self.testlisting[curtest]:
                        host = self.GetHost(self.testpath[count])
                        titleList = self.GetTitleList(self.testpath[count])
                        child = self.treeCtrl1.AppendItem(newitem, host)
                        self.treeCtrl1.SetPyData(child, self.testpath[count])
                        # add test titles under the host 
                        titleCount = 0
                        while titleCount < len(titleList):
                            title = self.treeCtrl1.AppendItem(child, titleList[titleCount])
                            self.treeCtrl1.SetPyData(title, self.testpath[count])
                            titleCount = titleCount + 1
                    count = count + 1
            curtest = curtest + 1              
        self.treeCtrl1.Expand(self.treeCtrl1.GetRootItem())
        
        
    # Build tree by test helper functions
    def GetHost(self, path):
        file = eval(open(path, "rU").read())
        host = file['System']['Host']
        return host
    def GetTitleList(self, path):
        file = eval(open(path, "rU").read())
        titleLen = len(file['Test']['GraphLines'])
        titleList = []
        count = 0
        while count < titleLen:
            title = file['Test']['GraphLines'][count]['Title']
            titleList.insert(count, title)
            count = count + 1
        return titleList
    
    # Graph button events  
    def OnGraphButton(self, event):
        #-#------open a new gnuplot session-----#-#
        g = Gnuplot.Gnuplot(debug=1)
        g("set yrange [0:*]")
        g("set terminal png")
        g("set size 2,2")
        g('set output "temp.png"')
        datastyle = "lines"
        if self.data_style.GetSelection() != -1:
            datastyle = self.data_style.GetStringSelection()
            datastyle = datastyle.lower()
        datacom = "set data style " + datastyle
        g(datacom)
        #-#------get datafile------#-#
        selected = self.treeCtrl1.GetSelections()
        # first check if there is a file selected             
        size = len(selected)
        count = 0;
        path = range(size)
        text = range(size)
        # Combine selected files into one list
        while count < size:
            path[count] = self.treeCtrl1.GetPyData(selected[count])
            text[count] = self.treeCtrl1.GetItemText(selected[count])
            count = count + 1
        # Set up the graph and plot data
        sortedtics = range(0)
        self.GetXtics(path, g, sortedtics)
        self.SetGraphLabel(path, g)
        self.GraphData(path, g, sortedtics, text)
        time.sleep(.7)
        self.curImg = wxBitmap(r"temp.png", wxBITMAP_TYPE_PNG)
        self.curImgPath = r"temp.png"
        self.staticBitmap1.SetBitmap(self.curImg)
        self.Layout()
        self.box2.RecalcSizes()
    # Get xtics for the graph
    def GetXtics(self, path, graph, sortedtics):
        numfiles = len(path)
        file = range(numfiles)
        filecount = 0
        # make a list of xtics in each file
        combinedtics = range(numfiles)
        while filecount < numfiles:
            try:
                file[filecount] = eval(open(path[filecount], "rU").read())
            except:
                print "\nERROR: Please select a valid test.\n"
                d= wxMessageDialog( self, "Please select a valid test.", "Error", wxOK | wxICON_ERROR)
                d.ShowModal() 
                d.Destroy() 
                break
            size = len(file[filecount]['Test']['GraphLines'][0]['ResultSet'])
            xtics = range(size)
            # set xtics from file
            count = 0
            while count < size:
                xtics[count] = file[filecount]['Test']['GraphLines'][0]['ResultSet'][count]['Name']
                count = count + 1
            combinedtics[filecount] = xtics
            filecount = filecount + 1
        # append each value of xtics in combined xtics to sortedtics
        filecount = 0
        while filecount < numfiles:
            size = len(combinedtics[filecount])
            count = 0
            while count < size:
                # add xtic to sortedtics if it is not already there
                if self.data_style.GetSelection() != 3:
                    try:
                        xtic = int(combinedtics[filecount][count])
                    except:
                        print "\nERROR: Cannot graph data. Try a different data style.\n"
                        d= wxMessageDialog( self, "Cannot graph data. Try a different data style.", "Error", wxOK | wxICON_ERROR)
                        d.ShowModal() 
                        d.Destroy()
                        break
                else:
                    xtic = combinedtics[filecount][count]
                if xtic not in sortedtics:
                    sortedtics.append(xtic)
                count = count + 1
            filecount = filecount + 1
        # now sort sortedtics and set the xtics if you are not graphing with boxes
        if self.data_style.GetSelection() != 3:
            sortedtics.sort()
        count = 0
        size = len(sortedtics)
        xcom = "set xtics ("
        while count < size:
            xcom = xcom + "\"" + "%s" % (sortedtics[count])
            xcom = xcom + "\" "
            xcom = xcom + " " + "%s" % (count)
            if count < size - 1:
                xcom = xcom + ", "
            count = count + 1
        xcom = xcom + ")"
        graph(xcom)
    # Set up the graph                
    def SetGraphLabel(self, path, graph):
        choice = self.data_type.GetSelection()
        if choice == -1:
            choice = 0
        # check title of each file, and set a multi-line title if they differ
        numfiles = len(path)
        file = range(numfiles)
        filecount = 0
        ylabels = range(0)
        titles = range(0)
        newlbl = ""
        newtitle = ""
        while filecount < numfiles:
            file[filecount] = eval(open(path[filecount], "rU").read())
            y = file[filecount]['Test']['GraphLines'][0]['ResultSet'][0]['Results'][choice]['Units']
            if y not in ylabels:
                ylabels.append(y)
            # get the title
            version = file[filecount]['GLScry Version']
            host = file[filecount]['System']['Host']
            vendor = file[filecount]['System']['OpenGL Vendor']
            renderer = file[filecount]['System']['OpenGL Renderer']
            glversion = file[filecount]['System']['OpenGL Version']
            Gtitle = version + " :: " + host + " :: " + vendor + " :: " + renderer +" :: " + glversion
            if Gtitle not in titles:
                titles.append(Gtitle)
            filecount = filecount + 1
        # assemble the label from ylabels
        count = 0
        size = len(ylabels)
        while count < size:
            newlbl = newlbl + ylabels[count]
            if count < size - 1:
                newlbl = newlbl + ", "
            count = count + 1
        graph.ylabel(newlbl)
        # set the title
        size = len(titles)
        count = 0
        while count < size:
            newtitle = newtitle + titles[count]
            if count < size - 1:
                newtitle = newtitle + r'\n'
            count = count + 1
        graph.title(newtitle)
    
    # Graph the data            
    def GraphData(self, path, graph, sortedtics, text):
        numfiles = len(path)
        file = range(numfiles)
        filecount = 0
        while filecount < numfiles:
            file[filecount] = eval(open(path[filecount], "rU").read())
            filecount = filecount + 1
        choice = self.data_type.GetSelection()
        if choice == -1:
            choice = 0
        filecount = 0
        count = 0
        resultcount = 0
        alltitles = range(0)
        plotcom = "plot "
        while filecount < numfiles:
            if self.IsTitle(file[filecount], text[filecount]):
                resultcount = self.GetResultCount(file[filecount], text[filecount])
                numresults = resultcount + 1
            else:
                numresults = len(file[filecount]['Test']['GraphLines'])
            while resultcount < numresults:
                title = file[filecount]['Test']['GraphLines'][resultcount]['Title']
                host = file[filecount]['System']['Host']
                title = title + "(" + host + ")"
                if filecount == 0:
                    plotcom = plotcom + "'-' title '%s'" % (title)
                    if resultcount < numresults - 1:
                        plotcom = plotcom + ","
                else:
                    plotcom = plotcom + ",'-' title '%s'" % (title)
                resultcount = resultcount + 1
            resultcount = 0
            filecount = filecount + 1
        graph(plotcom)
        resultcount = 0
        filecount = 0
        while filecount < numfiles:
            size = len(file[filecount]['Test']['GraphLines'][0]['ResultSet'])
            while resultcount < numresults:
                if self.IsTitle(file[filecount], text[filecount]):
                    resultcount = self.GetResultCount(file[filecount], text[filecount])
                    numresults = resultcount + 1
                else:
                    numresults = len(file[filecount]['Test']['GraphLines'])
                while count < size:
                    name =file[filecount]['Test']['GraphLines'][resultcount]['ResultSet'][count]['Name']
                    result =file[filecount]['Test']['GraphLines'][resultcount]['ResultSet'][count]['Results'][choice]['Value']
                    # get the index of name in sortedtics
                    index = self.GetIndex(name, sortedtics)
                    # graph it
                    graph("%s %f" % (index, result))
                    count = count + 1
                graph("e\n")
                time.sleep(0.1)
                count = 0
                resultcount = resultcount + 1
            resultcount = 0
            filecount = filecount + 1
        graph("exit")
        graph("exit")
    # if count == numresults, then text is not a title, if count < numresults, then
    # the resultset to graph will file['Test']['GraphLines'][count]
    def GetResultCount(self, file, text):
        numresults = len(file['Test']['GraphLines'])
        count = 0
        while count < numresults:
            if file['Test']['GraphLines'][count]['Title'] == text:
                return count
            count = count + 1
        return count
    def IsTitle(self, file, text):
        numresults = len(file['Test']['GraphLines'])
        count = 0
        while count < numresults:
            if file['Test']['GraphLines'][count]['Title'] == text:
                return True
            count = count + 1
        return False
    # search through sorted tics to find value and return its index
    def GetIndex(self, value, sortedtics):
        # get the size of sorted tics
        ticsize = len(sortedtics)
        count = 0
        while count < ticsize:
            if self.data_style.GetSelection() != 3:
                value = int(value)
                curval = int(sortedtics[count])
            else:
                curval = sortedtics[count]
            if curval == value:
                index = count
                return index
            count = count + 1
    # Double click event for static bitmap 1
    # Open a new window and view image at full size    
    def OnBitmapDblClick(self, event):
        img = self.curImg
        height = img.GetHeight()
        width = img.GetWidth()
        self.wxExpFrame1 = wxFrame(self, id=wxID_WXEXPFRAME1, name='',
            pos=wxPoint(175, 144), size=wxSize(768, 530),
            style=wxDEFAULT_FRAME_STYLE, title="Generated Image")
        self.scrolledWindow1 =wxScrolledWindow(id=wxID_WXMINIFRAME1SCROLLEDWINDOW1,
            name='scrolledWindow1', parent=self.wxExpFrame1, pos=wxPoint(0, 0),
            size=wxSize(width, height), style=wxHSCROLL | wxVSCROLL)
             
        self.fullBitmap1 = wxStaticBitmap(bitmap=wxBitmap(self.curImgPath,
            wxBITMAP_TYPE_PNG), id=wxID_WXFULLBITMAP,
            name='fullbitmap1', parent=self.scrolledWindow1, pos=wxPoint(0, 0),
            size=wxSize(width, height), style=0)
        
        self.scrolledWindow1.SetScrollbars(20, 20, (width/20) + .5, (height/20) + .9, noRefresh = FALSE)         
        
        self.wxExpFrame1.Show()
    # Start GLScry functions
    #!/usr/bin/env python
    # [Begin Copyright Header]
    # 
    # GLScry - OpenGL Performance Analysis Tool
    # Copyright (C) 2004-2005  Iowa State University
    # 
    # This software is licensed under the terms of the GNU Lesser Public
    # License, version 2.1, as published by the Free Software Foundation.
    # See the file COPYRIGHT.txt for details.
    # 
    # Authors:
    #   Chad Austin <aegisk@iastate.edu>
    #   Dirk Reiners <dreiners@iastate.edu>
    # 
    # [End Copyright Header]
    def SelectAll(self, event):
        for i in range(0,12):
            self.checkBoxes[i].SetValue(True)
    def GetSelected(self):
        selected = []
        for i in range(0,12):
            if self.checkBoxes[i].IsChecked():
                selected.append(i)
            i = i + 1
        return selected
    def CreateTestList(self, selected):
        tests = []
        for i in range(0, len(selected)):
            if selected[i] == 0:
                tests.append("batchsizes")
            if selected[i] == 1:
                tests.append("fillrate")
            if selected[i] == 2:
                tests.append("hierz")
            if selected[i] == 3:
                tests.append("lights")
            if selected[i] == 4:
                tests.append("pixeltransfer")
            if selected[i] == 5:
                tests.append("primtype")
            if selected[i] == 6:
                tests.append("statechange")
            if selected[i] == 7:
                tests.append("texmem")
            if selected[i] == 8:
                tests.append("texupload")
            if selected[i] == 9:
                tests.append("vbo")
            if selected[i] == 10:
                tests.append("vertexcache")
            if selected[i] == 11:
                tests.append("vformats")
            i = i + 1
        return tests
    def AssignPath(self, tests, scriptDir):
        paths = []
        for i in range(len(tests)):
            path = os.path.join(scriptDir, tests[i])
            path = path + ".py"
            paths.append(path)
        return paths
    def RunGLScry(self, event):
        selected = self.GetSelected()
        tests = self.CreateTestList(selected)
        cwd = os.getcwd()
        scriptDir = os.path.join(cwd, 'test')
        moduleDir = os.path.join(cwd, 'lib')
        sys.path.append(moduleDir)
        # Get test list.
        if tests:
            names = tests
            tests = self.AssignPath(tests, scriptDir)
        if not tests:
            print "\nERROR: No tests selected."
            d= wxMessageDialog( self, "No tests selected. Please select a test or click 'Select All' to run all tests.", "Error", wxOK | wxICON_ERROR)
            d.ShowModal() 
            d.Destroy()
            event.Skip()
            
        
        # Create data directory if it does not exist and switch to it so
        # the tests output their files there.
        
        hostname = socket.gethostname()
        datadir = os.path.join(cwd, 'data', hostname)
        try:
            os.makedirs(datadir)
        except OSError:
            pass
        os.chdir(datadir)

        print 'Data directory:', datadir

        print '\nQueuing tests for execution:'
        for t in names:
            print "  " + t
    
        for t in tests:
            print
            print "Running test script '%s'" % t
            exec open(t) in {}