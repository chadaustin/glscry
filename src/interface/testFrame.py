#Boa:Frame:wxFrame1

from wxPython.wx import *
import os, time
import Gnuplot, Gnuplot.PlotItems, Gnuplot.funcutils

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

[wxID_WXFRAME1MENU3ITEMS0, wxID_WXFRAME1MENU3ITEMS1, 
] = map(lambda _init_coll_menu3_Items: wxNewId(), range(2))

[wxID_WXFRAME1MENU1ITEMS0, wxID_WXFRAME1MENU1ITEMS1, wxID_WXFRAME1MENU1ITEMS2, 
] = map(lambda _init_coll_menu1_Items: wxNewId(), range(3))

[wxID_WXFRAME1MENU2ITEMS0, wxID_WXFRAME1MENU2ITEMS1, 
] = map(lambda _init_coll_menu2_Items: wxNewId(), range(2))

[wxID_WXFRAME1MENU4ITEMS0] = map(lambda _init_coll_menu4_Items: wxNewId(), range(1))

class wxFrame1(wxFrame):
    def _init_coll_menu3_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU3ITEMS0, item='Items0',
              kind=wxITEM_NORMAL)
        parent.Append(helpString='', id=wxID_WXFRAME1MENU3ITEMS1, item='Items1',
              kind=wxITEM_NORMAL)

    def _init_coll_menu2_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU2ITEMS0, item='Items0',
              kind=wxITEM_NORMAL)
        parent.Append(helpString='', id=wxID_WXFRAME1MENU2ITEMS1, item='Items1',
              kind=wxITEM_NORMAL)

    def _init_coll_menu1_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS0, item='Items0',
              kind=wxITEM_NORMAL)
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS1, item='Items1',
              kind=wxITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS2, item='Items2',
              kind=wxITEM_NORMAL)

    def _init_coll_menu4_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU4ITEMS0, item='Items0',
              kind=wxITEM_NORMAL)

    def _init_coll_menuBar1_Menus(self, parent):
        # generated method, don't edit

        parent.Append(menu=self.menu1, title='Menus0')
        parent.Append(menu=self.menu2, title='Menus1')
        parent.Append(menu=self.menu3, title='Menus2')
        parent.Append(menu=self.menu4, title='Menus3')

    def _init_coll_notebook1_Pages(self, parent):
        # generated method, don't edit

        parent.AddPage(imageId=-1, page=self.panel3, select=True,
              text='GLGraph')
        parent.AddPage(imageId=-1, page=self.panel4, select=False,
              text='GLScry')
              
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
        # generated method, don't edit
        self.menuBar1 = wxMenuBar()

        self.menu1 = wxMenu(title='')

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
              pos=wxPoint(15, 3), size=wxSize(1120, 821),
              style=wxDEFAULT_FRAME_STYLE, title='wxFrame1')
        self._init_utils()
        self.SetClientSize(wxSize(1112, 787))
        self.SetMenuBar(self.menuBar1)

        self.panel1 = wxPanel(id=wxID_WXFRAME1PANEL1, name='panel1',
              parent=self, pos=wxPoint(0, 0), size=wxSize(256, 768),
              style=wxTAB_TRAVERSAL)

        self.panel2 = wxPanel(id=wxID_WXFRAME1PANEL2, name='panel2',
              parent=self, pos=wxPoint(256, 0), size=wxSize(856, 768),
              style=wxTAB_TRAVERSAL)

        self.staticBitmap1 = wxStaticBitmap(bitmap=wxBitmap(u'C:/python23/blank.png',
              wxBITMAP_TYPE_PNG), id=wxID_WXFRAME1STATICBITMAP1,
              name='staticBitmap1', parent=self.panel2, pos=wxPoint(40, 38),
              size=wxSize(852, 764), style=0)
        self.staticBitmap1.SetAutoLayout(True)
        self.staticBitmap1.Center(wxBOTH)
        EVT_LEFT_DCLICK(self.staticBitmap1, self.OnBitmapDblClick)
        
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
        
    def __init__(self, parent):
        self._init_ctrls(parent)

    # Build the tree from the chosen directory
    def BuildFolder(self, event):
        dlg = wxDirDialog(self)
        try:
            if dlg.ShowModal() == wxID_OK:
                dir = dlg.GetPath()
                self.browse_txt.Clear()
                self.browse_txt.WriteText(dir)
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
    
    # Graph button events  
    def OnGraphButton(self, event):
        self.have_graphed = 1
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
        size = len(selected)
        count = 0;
        path = range(size)
        # Combine selected files into one list
        while count < size:
            path[count] = self.treeCtrl1.GetPyData(selected[count])
            count = count + 1
        # Set up the graph and plot data
        self.GetXtics(path, g)
        self.SetGraphLabel(path, g)
        self.GraphData(path, g)
        time.sleep(.7)
        img = wxBitmap(r"temp.png", wxBITMAP_TYPE_PNG)
        resizedimg = img
        toobig = false
        height = img.GetHeight()
        width = img.GetWidth()
        if width > 852:
            resizedimg.SetWidth(852)
            toobig = true
        if height > 764:
            resizedimg.SetHeight(764)
            toobig = true
        if toobig == true:
            self.staticBitmap1.SetBitmap(resizedimg)
        else:
            self.staticBitmap1.SetBitmap(img)
    # Get xtics for the graph
    def GetXtics(self, path, graph):
        numfiles = len(path)
        file = range(numfiles)
        filecount = 0
        # make a list of xtics in each file
        combinedtics = range(numfiles)
        while filecount < numfiles:
            file[filecount] = eval(open(path[filecount]).read())
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
        sortedtics = range(0)
        filecount = 0
        while filecount < numfiles:
            size = len(combinedtics[filecount])
            count = 0
            while count < size:
                # add xtic to sortedtics if it is not already there
                if self.data_style.GetSelection() != 3:
                    xtic = int(combinedtics[filecount][count])
                else:
                    xtic = combinedtics[filecount][count]
                if xtic not in sortedtics:
                    sortedtics.append(xtic)
                count = count + 1
            filecount = filecount + 1
        # now sort sortedtics and set the xtics
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
            file[filecount] = eval(open(path[filecount]).read())
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
    def GraphData(self, path, graph):
        numfiles = len(path)
        file = range(numfiles)
        filecount = 0
        while filecount < numfiles:
            file[filecount] = eval(open(path[filecount]).read())
            filecount = filecount + 1
        choice = self.data_type.GetSelection()
        if choice == -1:
            choice = 0
        filecount = 0
        count = 0
        resultcount = 0
        numresults = len(file[0]['Test']['GraphLines'])
        plotcom = "plot "
        while filecount < numfiles:
            while resultcount < numresults:
                title = file[filecount]['Test']['GraphLines'][resultcount]['Title']
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
                while count < size:
                    name =file[filecount]['Test']['GraphLines'][resultcount]['ResultSet'][count]['Name']
                    result =file[filecount]['Test']['GraphLines'][resultcount]['ResultSet'][count]['Results'][choice]['Value']
                    # graph it
                    graph("%s %f" % (count, result))
                    count = count + 1
                graph("e\n")
                time.sleep(0.1)
                count = 0
                resultcount = resultcount + 1
            resultcount = 0
            filecount = filecount + 1
        graph("exit")
        graph("exit")
    
    # Double click event for static bitmap 1
    # Open a new window and view image at full size    
    def OnBitmapDblClick(self, event):
        img = wxBitmap("temp.png", wxBITMAP_TYPE_PNG)
        height = img.GetHeight()
        width = img.GetWidth()
        self.wxExpFrame1 = wxFrame(self, id=wxID_WXEXPFRAME1, name='',
            pos=wxPoint(175, 144), size=wxSize(768, 530),
            style=wxDEFAULT_FRAME_STYLE, title="Generated Image")
        self.scrolledWindow1 =wxScrolledWindow(id=wxID_WXMINIFRAME1SCROLLEDWINDOW1,
            name='scrolledWindow1', parent=self.wxExpFrame1, pos=wxPoint(0, 0),
            size=wxSize(width, height), style=wxHSCROLL | wxVSCROLL)
             
        self.fullBitmap1 = wxStaticBitmap(bitmap=wxBitmap(".\\temp.png",
            wxBITMAP_TYPE_PNG), id=wxID_WXFULLBITMAP,
            name='fullbitmap1', parent=self.scrolledWindow1, pos=wxPoint(0, 0),
            size=wxSize(width, height), style=0)
        
        self.scrolledWindow1.SetScrollbars(20, 20, (width/20) + .5, (height/20) + .9, noRefresh = FALSE)         
        
        self.wxExpFrame1.Show()
    