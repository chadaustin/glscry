#Boa:Frame:wxFrame1
#GLAnalyze created by Alex Allen

import wx
import os, time, shutil
import Gnuplot, Gnuplot.PlotItems, Gnuplot.funcutils
import string
import sys
from glob import glob
from decimal import *
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
 wxID_WXFULLBITMAP,wxID_WXFRAME1MENU1ITEMS3,
] = [wx.NewId() for _init_ctrls in range(19)]

[wxID_WXFRAME1MENU1ITEMS0, wxID_WXFRAME1MENU1ITEMS1, wxID_WXFRAME1MENU1ITEMS2,
] = [wx.NewId() for _init_coll_menu1_Items in range(3)]

[wxID_WXFRAME1MENU2ITEMS0,
] = [wx.NewId() for _init_coll_menu2_Items in range(1)]

def WriteToInfoBox(string):
    infoBox.WriteText(string)
    
class wxFrame1(wx.Frame):

    def _init_coll_menu2_Items(self, parent):

        parent.AppendSeparator()
        parent.Append(help='', id=wxID_WXFRAME1MENU2ITEMS0, text='About', kind=wx.ITEM_NORMAL)
        self.Bind(wx.EVT_MENU, self.OnAbout, id=wxID_WXFRAME1MENU2ITEMS0)

    def _init_coll_menu1_Items(self, parent):
        parent.Append(help='', id=wxID_WXFRAME1MENU1ITEMS0, text='Open', kind=wx.ITEM_NORMAL)
        parent.Append(help='', id=wxID_WXFRAME1MENU1ITEMS1, text='Save Image', kind=wx.ITEM_NORMAL)
        parent.Append(help='', id=wxID_WXFRAME1MENU1ITEMS3, text='Save Gnuplot File', kind=wx.ITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(help='', id=wxID_WXFRAME1MENU1ITEMS2, text='Exit', kind=wx.ITEM_NORMAL)
        self.Bind(wx.EVT_MENU, self.OnOpen, id=wxID_WXFRAME1MENU1ITEMS0)
        self.Bind(wx.EVT_MENU, self.OnSave, id=wxID_WXFRAME1MENU1ITEMS1)
        self.Bind(wx.EVT_MENU, self.OnExit, id=wxID_WXFRAME1MENU1ITEMS2)
        self.Bind(wx.EVT_MENU, self.OnGnuSave, id=wxID_WXFRAME1MENU1ITEMS3)

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
        boxsizer = wx.BoxSizer(wx.VERTICAL)
        glsizer = wx.FlexGridSizer(16, 2, 2, 2)
        boxsizer.Add(glsizer)
        self.checkBoxes = []
        checkAll = wx.Button(self.panel4, -1, "Select All")
        wx.EVT_BUTTON(checkAll, -1, self.SelectAll)
        run = wx.Button(self.panel4, -1, "Run Tests")
        wx.EVT_BUTTON(run, -1, self.RunGLScry)
        # create each test's individual checkbox
        batchCheck = wx.CheckBox(self.panel4, -1, "Batch Sizes")
        self.checkBoxes.append(batchCheck)
        fillCheck = wx.CheckBox(self.panel4, -1, "Fill Rate")
        self.checkBoxes.append(fillCheck)
        hierzCheck = wx.CheckBox(self.panel4, -1, "Hierz")
        self.checkBoxes.append(hierzCheck)
        lightsCheck = wx.CheckBox(self.panel4, -1, "Lights")
        self.checkBoxes.append(lightsCheck)
        pixelCheck = wx.CheckBox(self.panel4, -1, "Pixel Transfer")
        self.checkBoxes.append(pixelCheck)
        primCheck = wx.CheckBox(self.panel4, -1, "Prim Type")
        self.checkBoxes.append(primCheck)
        stateCheck = wx.CheckBox(self.panel4, -1, "State Change")
        self.checkBoxes.append(stateCheck)
        texmemCheck = wx.CheckBox(self.panel4, -1, "Tex Memory")
        self.checkBoxes.append(texmemCheck)
        texupCheck = wx.CheckBox(self.panel4, -1, "Tex Upload")
        self.checkBoxes.append(texupCheck)
        vboCheck = wx.CheckBox(self.panel4, -1, "VBO")
        self.checkBoxes.append(vboCheck)
        vertexCheck = wx.CheckBox(self.panel4, -1, "Vertex Cache")
        self.checkBoxes.append(vertexCheck)
        vformatsCheck = wx.CheckBox(self.panel4, -1, "VFormats")
        self.checkBoxes.append(vformatsCheck)
        glsizer.Add(wx.StaticText(self.panel4, -1, "Tests:"), 0, wx.ALIGN_LEFT)
        glsizer.Add(wx.StaticText(self.panel4, -1, " "), 0, wx.ALIGN_LEFT)
        for i in range(0, 12):
            glsizer.Add(self.checkBoxes[i], 0, wx.ALIGN_LEFT)
            glsizer.Add(wx.StaticText(self.panel4, -1, " "), 0, wx.ALIGN_LEFT)
        glsizer.Add(checkAll, 0, wx.ALIGN_LEFT)
        glsizer.Add(run, 0, wx.ALIGN_LEFT)
        # text control for displaying GLScry information
        global infoBox
        infoBox = wx.TextCtrl(self.panel4, -1, "", size = (235, 200), style = wx.TE_MULTILINE | wx.TE_READONLY | wx.HSCROLL)
        boxsizer.Add(wx.StaticText(self.panel4, -1, " "), 0, wx.ALIGN_LEFT)
        boxsizer.Add(wx.StaticText(self.panel4, -1, "Log:"), 0, wx.ALIGN_LEFT)
        boxsizer.Add(infoBox, wx.ALIGN_CENTER)
        boxsizer.Add(wx.StaticText(self.panel4, -1, " "), 0, wx.ALIGN_LEFT)
        parent.SetSizer(boxsizer)
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

        self.menuBar1 = wx.MenuBar()
        self.menu1 = wx.Menu(title='')
        self.menu2 = wx.Menu(title='')

        self._init_coll_menuBar1_Menus(self.menuBar1)
        self._init_coll_menu1_Items(self.menu1)
        self._init_coll_menu2_Items(self.menu2)

    def _init_ctrls(self, prnt):

        self.curImg = wx.Bitmap("blank.png", wx.BITMAP_TYPE_PNG)
        self.curImgPath = "blank.png"
        wx.Frame.__init__(self, id=wxID_WXFRAME1, name='', parent=prnt,
              pos= wx.Point(15, 3), size= wx.Size(1120, 821),
              style=wx.DEFAULT_FRAME_STYLE, title='GLAnalyze')
        self._init_utils()
        self.SetClientSize(wx.Size(1112, 787))
        self.SetMenuBar(self.menuBar1)

        self.panel1 = wx.Panel(id=wxID_WXFRAME1PANEL1, name='panel1',
              parent=self, pos= wx.Point(0, 0), size= wx.Size(256, 768),
              style=wx.TAB_TRAVERSAL)

        self.panel2 = wx.Panel(id=wxID_WXFRAME1PANEL2, name='panel2',
              parent=self, pos= wx.Point(256, 0), size= wx.Size(856, 768),
              style=wx.TAB_TRAVERSAL)
        # panel sizers
        self.box = wx.BoxSizer(wx.HORIZONTAL)
        self.box.Add(self.panel1, 0, wx.EXPAND)
        self.box.Add(self.panel2, 2, wx.EXPAND)
        self.SetAutoLayout(True)
        self.SetSizer(self.box)
        
        # end panel sizers
        # bitmap resizers
        self.curImg = wx.Bitmap(r"blank.png", wx.BITMAP_TYPE_PNG)
        self.curImgPath = "blank.png"
        self.fullImg = self.curImg
        self.fullImgPath = self.curImgPath
        self.ImageResize()
        self.staticBitmap1 = wx.StaticBitmap(bitmap= self.curImg, id=wxID_WXFRAME1STATICBITMAP1,
              name='staticBitmap1', parent=self.panel2, pos= wx.Point(40, 38), style=0)
        self.staticBitmap1.SetAutoLayout(True)
        self.staticBitmap1.Center(wx.BOTH)
        self.staticBitmap1.SetBitmap(self.curImg)
        self.box2 = wx.BoxSizer(wx.HORIZONTAL)
        self.box2.Add(self.staticBitmap1, 2, wx.EXPAND)
        self.panel2.SetSizer(self.box2)
        # end bitmap resizer
        self.staticBitmap1.Bind(wx.EVT_LEFT_DCLICK, self.OnBitmapDblClick)
        # notebook layout sizers
        self.notebook1 = wx.Notebook(id=wxID_WXFRAME1NOTEBOOK1, name='notebook1',
              parent=self.panel1, pos= wx.Point(8, 56), size= wx.Size(248, 704),
              style=0)

        self.panel3 = wx.Panel(id=wxID_WXFRAME1PANEL3, name='panel3',
              parent=self.notebook1, pos= wx.Point(0, 0), size= wx.Size(240, 678),
              style=wx.TAB_TRAVERSAL)

        self.panel4 = wx.Panel(id=wxID_WXFRAME1PANEL4, name='panel4',
              parent=self.notebook1, pos= wx.Point(0, 0), size= wx.Size(240, 678),
              style=wx.TAB_TRAVERSAL)

        self.treeCtrl1 = wx.TreeCtrl(id=wxID_WXFRAME1TREECTRL1, name='treeCtrl1',
              parent=self.panel3, pos= wx.Point(16, 80), size= wx.Size(200, 536),
              style=wx.TR_HAS_BUTTONS | wx.TR_MULTIPLE)

        self.graph_button = wx.Button(id=wxID_WXFRAME1GRAPH_BUTTON,
              label='Graph', name='graph_button', parent=self.panel3,
              pos= wx.Point(144, 624), size= wx.Size(75, 31), style=0)
        self.graph_button.Bind(wx.EVT_BUTTON, self.OnGraphButton, id=wxID_WXFRAME1GRAPH_BUTTON)

        self.data_style=wx.Choice(choices=[], id=wxID_WXFRAME1DATA_STYLE,
              name='data_style', parent=self.panel3, pos= wx.Point(88, 48),
              size= wx.Size(125, 21), style=0)

        self.data_style_txt = wx.StaticText(id=wxID_WXFRAME1DATA_STYLE_TXT,
              label='Data Style:', name='data_style_txt', parent=self.panel3,
              pos= wx.Point(16, 48), size= wx.Size(65, 16), style=0)
        self.data_style_txt.SetFont(wx.Font(10,wx.SWISS,wx.NORMAL,wx.NORMAL,
              False, 'Arial'))

        self.data_type = wx.Choice(choices=[], id=wxID_WXFRAME1DATA_TYPE,
              name='data_type', parent=self.panel3, pos= wx.Point(88, 16),
              size= wx.Size(125, 21), style=0)

        self.data_type_txt = wx.StaticText(id=wxID_WXFRAME1DATA_TYPE_TXT,
              label='Data Type:', name='data_type_txt', parent=self.panel3,
              pos= wx.Point(16, 16), size= wx.Size(63, 16), style=0)
        self.data_type_txt.SetFont(wx.Font(10,wx.SWISS,wx.NORMAL,wx.NORMAL,
              False, 'Arial'))

        self.browse_txt = wx.TextCtrl(id=wxID_WXFRAME1BROWSE_TXT,
              name='browse_txt', parent=self.panel1, pos= wx.Point(8, 16),
              size= wx.Size(152, 21), style=0, value='Select a directory...')

        self.browse_button = wx.Button(id=wxID_WXFRAME1BROWSE_BUTTON,
              label='Browse', name='browse_button', parent=self.panel1,
              pos= wx.Point(168, 16), size= wx.Size(75, 23), style=0)
        self.browse_button.Bind(wx.EVT_BUTTON, self.BuildFolder, id=wxID_WXFRAME1BROWSE_BUTTON)
        
        # window resize and maximize events
        wx.EVT_MAXIMIZE(self, self.OnSize)
        wx.EVT_SIZE(self, self.OnSize)
        wx.EVT_IDLE(self, self.OnIdle)
        
        self._init_coll_notebook1_Pages(self.notebook1)
        self._init_data_type(self.data_type)
        self._init_data_style(self.data_style)
        self._init_glscry_panel(self.panel4)

    def __init__(self, parent):
        self._init_ctrls(parent)
        
    # tree build gauge
    def GaugeBox(self, max):
        self.mini= wx.MiniFrame( self, -1, "Tree Build Progress", size =(250, 50), style = wx.STAY_ON_TOP | wx.CAPTION)
        self.mini.Center()
        self.mini.Show() # Shows it
        self.buildGague = wx.Gauge(self.mini, -1, max, wx.DefaultPosition, (250, 25), wx.GA_HORIZONTAL)
        
    # image buffer
    def InitBuffer(self):
        # initialize the bitmap used for buffering the display
        size = self.GetClientSize()
        self.buffer = wx.EmptyBitmap(size.width, size.height)
        dc = wx.BufferedDC(None, self.buffer)
        dc.SetBackground(wx.Brush(self.GetBackgroundColour()))
        dc.Clear()
        self.reInitBuffer = False
        
    def ImageResize(self):
        self.curImg = self.curImg.ConvertToImage()
        wSize = self.panel2.GetSizeTuple()
        self.curImg.Rescale(wSize[0] -6, wSize[1] -1)
        self.curImg = self.curImg.ConvertToBitmap()
        self.Refresh()
        
    def OnSize(self, event):
        self.ImageResize()
        self.Layout()
        self.reInitBuffer = True
    
    def OnIdle(self, event):
        if self.reInitBuffer:
            self.InitBuffer()
            self.ImageResize()
            self.Refresh(False)
                   
    # menu items
    # About
    def OnAbout(self, event):
        d= wx.MessageDialog( self, "GLAnalyze developed by Alex Allen in collaboration with Dr. Dirk Reiners and Chad Austin.\n"
                            "Designed to work with GLScry developed by Chad Austin and Dr. Dirk Reiners. \n" "version 0.1 ", "About GLAnalyze", wx.OK | wx.ICON_INFORMATION)
                            # Create a message dialog box
        d.ShowModal() # Shows it
        d.Destroy() # finally destroy it when finished

    # Open file dialog
    def OnOpen(self, event):
        dlg = wx.FileDialog(self, "Choose a file", os.getcwd(), "", "*.png", wx.OPEN)
        if dlg.ShowModal() == wx.ID_OK:
            # This returns a Python list of files that were selected.
            self.curImgPath = dlg.GetPath()
            self.curImg = wx.Bitmap(self.curImgPath, wx.BITMAP_TYPE_PNG)
            self.fullImg = self.curImg
            self.fullImgPath = self.curImgPath
            self.ImageResize()
            self.staticBitmap1.SetBitmap(self.curImg)
        dlg.Destroy()
    # Save file dialog
    def OnSave(self, event):
        dlg = wx.FileDialog(self, "Choose a file", self.browse_txt.GetValue() , "", "*.png", wx.SAVE)
        dlg.SetFilterIndex(2)
        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPath()
            if os.path.exists("full.png"):
                self.fullImg.SaveFile(path, wx.BITMAP_TYPE_PNG)
            else:
                if os.path.exists("temp.png"):
                    self.curImg.SaveFile(path, wx.BITMAP_TYPE_PNG)
                else:
                    d= wx.MessageDialog( self, "Please generate an image first.", "No Image to Save", wx.OK | wx.ICON_ERROR)
                            # Create a message dialog box
                    d.ShowModal() # Shows it
                    d.Destroy() # finally destroy it when finished
                
        dlg.Destroy()
    
    def OnGnuSave(self, event):
        dlg = wx.FileDialog(self, "Choose a file", self.browse_txt.GetValue() , "", "*.gnu", wx.SAVE)
        dlg.SetFilterIndex(2)
        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPath()
            if os.path.exists(r"temp.gnu"):
                shutil.copy(r"temp.gnu",path)
            else:
                d= wx.MessageDialog(self, "Please generate a graph first.", "No Graph to Save", wx.OK | wx.ICON_ERROR)
                            # Create a message dialog box
                d.ShowModal() # Shows it
                d.Destroy() # finally destroy it when finished
        dlg.Destroy()

    # Exit
    def OnExit(self, event):
        self.Close(True)  # Close the frame.

    # Build the tree from the chosen directory
    def BuildFolder(self, event):
        dlg = wx.DirDialog(self, "Select a directory", os.getcwd())
        try:
            if dlg.ShowModal() == wx.ID_OK:
                dir = dlg.GetPath()
                self.browse_txt.Clear()
                self.browse_txt.WriteText(dir)
                self.root = ""
                self.treeCtrl1.DeleteAllItems()
                self.StartTestBuild(dir)
                self.treeCtrl1.Expand(self.root)

        finally:
            dlg.Destroy()


    # Build tree functions
    def StartTestBuild(self, dir):
        rootname = os.path.split(dir)
        self.root = self.treeCtrl1.AddRoot(rootname[1])
        self.rootdir = dir
        self.treeCtrl1.DeleteAllItems()
        self.treeCtrl1.AddRoot("Data")
        self.testlist = self.treeCtrl1.AppendItem(self.treeCtrl1.GetRootItem(), "Test List")
        self.byHost = self.treeCtrl1.AppendItem(self.testlist, "By Host")
        self.byTitle = self.treeCtrl1.AppendItem(self.testlist, "By Title")
        self.dirlist = self.treeCtrl1.AppendItem(self.treeCtrl1.GetRootItem(), "Directory List")
        self.testlisting = []
        self.testpath = []
        self.machinelisting = []
        self.machinepath = []
        self.GetTestInfo(self.dirlist, dir)
        self.BuildTree()
        self.mini.Destroy()

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
        addedtitles = []
        addedhosts = []
        curtest = 0
        self.GaugeBox(len(self.testlisting))
        while curtest < len(self.testlisting):
            self.buildGague.SetValue(curtest)
            # first get first test from list, then add it as parent in tree
            if self.testlisting[curtest] not in addedtests:
                newhost = self.treeCtrl1.AppendItem(self.byHost, self.testlisting[curtest])
                hostbytitle = self.treeCtrl1.AppendItem(self.byTitle, self.testlisting[curtest])
                addedtests.insert(len(addedtests), self.testlisting[curtest])
                # then search list for test of the same name, adding its machine name
                count = 0
                while count < len(self.testlisting):
                    if self.testlisting[count] == self.testlisting[curtest]:
                        addedtitle = []
                        host = self.GetHost(self.testpath[count])
                        titleList = self.GetTitleList(self.testpath[count])
                        hostchild = self.treeCtrl1.AppendItem(newhost, host)
                        self.treeCtrl1.SetPyData(hostchild, self.testpath[count])
                        # add test titles under the host and under test for byTest
                        titleCount = 0
                        while titleCount < len(titleList):
                            toadd = titleList[titleCount] + " " + self.testlisting[curtest]
                            if toadd not in addedtitles:
                                self.treeCtrl1.AppendItem(hostbytitle, titleList[titleCount])
                                addedtitles.insert(len(addedtitle), toadd)                
                            title = self.treeCtrl1.AppendItem(hostchild, titleList[titleCount])
                            self.treeCtrl1.SetPyData(title, self.testpath[count])
                            titleCount = titleCount + 1   
                    count = count + 1
            # first build a list of byTitle's children, and then iter that list
            # if the test is the same as the tree node, then add its host to its children
            for i in self.iterchildren(self.treeCtrl1, self.byTitle):
                if self.testlisting[curtest] == self.treeCtrl1.GetItemText(i):
                    for x in self.iterchildren(self.treeCtrl1, i):
                        toadd = self.treeCtrl1.AppendItem(x, self.GetHost(self.testpath[curtest]))
                        self.treeCtrl1.SetPyData(toadd, self.testpath[curtest])
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
    def HasTitle(self, path, tiq):
        file = eval(open(path, "rU").read())
        titleLen = len(file['Test']['GraphLines'])
        count = 0
        while count < titleLen:
            title = file['Test']['GraphLines'][count]['Title']
            if tiq == title:
                return True
            count = count + 1
        return False
    def iterchildren(self, treectrl, node):
        cid, citem = treectrl.GetFirstChild(node)
        while cid.IsOk(): 
            yield cid
            cid, citem = treectrl.GetNextChild(node, citem)
    # Graph button events
    def OnGraphButton(self, event):
        temp = "temp.gnu"
        self.plot = open(temp, 'w')
        #-#------open a new gnuplot session-----#-#
        g = Gnuplot.Gnuplot(debug=1)
        w, h = self.CalcImageSize()
        g("set yrange [0:*]")
        print >> self.plot, "set yrange [0:*]"
        g("set terminal png")
        print >> self.plot, "set terminal png"
        g("set size %s,%f" %(w,h))
        print >> self.plot, "set size %s,%f" %(w,h)
        g('set output "temp.png"')
        print >> self.plot, "set output 'plot.png'"
        datastyle = "lines"
        if self.data_style.GetSelection() != -1:
            datastyle = self.data_style.GetStringSelection()
            datastyle = datastyle.lower()
        self.datacom = "set data style " + datastyle
        g(self.datacom)
        print >> self.plot, self.datacom
        #-#------get datafile------#-#
        selected = self.treeCtrl1.GetSelections()
        # first check if there is a file selected
        size = len(selected)
        count = 0;
        self.path = range(size)
        self.text = range(size)
        self.parents = range(size)
        # Combine selected files into one list
        while count < size:
            self.path[count] = self.treeCtrl1.GetPyData(selected[count])
            self.text[count] = self.treeCtrl1.GetItemText(selected[count])
            self.parents[count] = self.treeCtrl1.GetItemText(self.treeCtrl1.GetItemParent(selected[count]))
            count = count + 1
        # Set up the graph and plot data
        sortedtics = range(0)
        self.GetXtics(self.path, g, sortedtics, True)
        self.SetGraphLabel(self.path, g, True)
        self.GraphData(self.path, g, sortedtics, self.text, self.parents, True)
        self.plot.close()
        time.sleep(0.5)
        mtry = 0
        while mtry < 5:
            if os.stat(r"temp.png")[6] > 0:
                self.curImg = wx.Bitmap(r"temp.png", wx.BITMAP_TYPE_PNG)
                self.curImgPath = r"temp.png"
                self.ImageResize()
                self.staticBitmap1.SetBitmap(self.curImg)
                break
            time.sleep(0.1)
            mtry = mtry + 1
    # calculate gnuplot image output size for current size of window
    def CalcImageSize(self):
        # get current size of the window
        width, height = self.panel2.GetSizeTuple()
        width = float(width)
        height = float(height)
        # the calculate the size setting for gnuplot
        rwidth = width / 640;
        rwidth = round(rwidth, 1)
        rheight = height / 480;
        rheight = round(rheight, 1)
        getcontext().rounding = 'ROUND_DOWN'
        if rwidth * 640 > width:
            rwidth = rwidth - 0.1            
        if rheight * 480 > height:
            rheight = rheight - 0.1
        return rwidth, rheight
    # Get xtics for the graph
    def GetXtics(self, path, graph, sortedtics, tofile):
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
                d= wx.MessageDialog( self, "Please select a valid test.", "Error", wx.OK | wx.ICON_ERROR)
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
                        d= wx.MessageDialog( self, "Cannot graph data. Try a different data style.", "Error", wx.OK | wx.ICON_ERROR)
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
        if tofile is True:
            print >> self.plot, xcom
    # Set up the graph
    def SetGraphLabel(self, path, graph, tofile):
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
        if tofile is True:
            print >> self.plot, "set ylabel '%s'" %(newlbl)
        # set the title
        size = len(titles)
        count = 0
        while count < size:
            newtitle = newtitle + titles[count]
            if count < size - 1:
                newtitle = newtitle + r'\n'
            count = count + 1
        graph.title(newtitle)
        if tofile is True:
            print >> self.plot, "set title '%s'" %(newtitle)

    # Graph the data
    def GraphData(self, path, graph, sortedtics, text, parents, tofile):
        longtitle = self.UseLong(path)
        numfiles = len(path)
        file = range(numfiles)
        shortTitles = []
        longTitles = []
        newtitle = []
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
            if self.IsTitle(file[filecount], text[filecount], parents[filecount]):
                resultcount = self.GetResultCount(file[filecount], text[filecount], parents[filecount])
                numresults = resultcount + 1
            else:
                numresults = len(file[filecount]['Test']['GraphLines'])
            while resultcount < numresults:
                if longtitle:
                    title = file[filecount]['Test']['GraphLines'][resultcount]['Title']
                    host = file[filecount]['System']['Host']
                    renderer = file[filecount]['System']['OpenGL Renderer']
                    title = title + " :: " + host + " :: " + renderer
                else:
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
        if tofile is True:
            print >> self.plot, plotcom
        resultcount = 0
        filecount = 0
        while filecount < numfiles:
            size = len(file[filecount]['Test']['GraphLines'][0]['ResultSet'])
            while resultcount < numresults:
                if self.IsTitle(file[filecount], text[filecount], parents[filecount]):
                    resultcount = self.GetResultCount(file[filecount], text[filecount], parents[filecount])
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
                    if tofile is True:
                        print >> self.plot, "%s %f" % (index, result)
                    count = count + 1
                graph("e\n")
                graph("e\n")
                if tofile is True:
                    print >> self.plot, "e\n"
                time.sleep(0.1)
                count = 0
                resultcount = resultcount + 1
            resultcount = 0
            filecount = filecount + 1
        graph("exit")
        graph("exit")
    # helper function to browse through selected tests and compare their titles,
    # if they are the same the function will return true and a longer name will be used
    def UseLong(self, path):
        file = []
        titles = []
        filecount = 0
        while filecount < len(path):
            file.insert(len(file), eval(open(path[filecount], "rU").read()))
            filecount = filecount + 1
        filecount = 0
        while filecount < len(file):
            title = file[filecount]['Test']['GraphLines'][0]['Title']
            if title not in titles:
                titles.insert(len(titles), title)
            else:
                return True
            filecount = filecount + 1
        return False
    
    # if count == numresults, then text is not a title, if count < numresults, then
    # the resultset to graph will file['Test']['GraphLines'][count]
    def GetResultCount(self, file, text, parents):
        numresults = len(file['Test']['GraphLines'])
        count = 0
        while count < numresults:
            if file['Test']['GraphLines'][count]['Title'] == text or file['Test']['GraphLines'][count]['Title'] == parents:
                return count
            count = count + 1
        return count
    def IsTitle(self, file, text, parents):
        numresults = len(file['Test']['GraphLines'])
        count = 0
        while count < numresults:
            if file['Test']['GraphLines'][count]['Title'] == text or file['Test']['GraphLines'][count]['Title'] == parents:
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
        g = Gnuplot.Gnuplot(debug=1)
        g("set yrange [0:*]")
        g("set terminal png")
        g("set size 2,2")
        g('set output "full.png"')
        g(self.datacom)
        sortedtics = []
        self.GetXtics(self.path, g, sortedtics, False)
        self.SetGraphLabel(self.path, g, False)
        self.GraphData(self.path, g, sortedtics, self.text, self.parents, False)
        time.sleep(0.5)
        mtry = 0
        while mtry < 8:
            if os.stat(r"full.png")[6] > 0:
                self.fullImg = wx.Bitmap(r"full.png", wx.BITMAP_TYPE_PNG)
                self.fullImgPath = r"full.png"
                break
            time.sleep(0.1)
            mtry = mtry + 1        
        img = self.fullImg
        height = img.GetHeight()
        width = img.GetWidth()
        self.wxExpFrame1 = wx.Frame(self, id=wxID_WXEXPFRAME1, name='',
            pos= wx.Point(175, 144), size= wx.Size(768, 530),
            style=wx.DEFAULT_FRAME_STYLE, title="Generated Image")
        self.scrolledWindow1 = wx.ScrolledWindow(id=wxID_WXMINIFRAME1SCROLLEDWINDOW1,
            name='scrolledWindow1', parent=self.wxExpFrame1, pos= wx.Point(0, 0),
            size= wx.Size(width, height), style=wx.HSCROLL | wx.VSCROLL)

        self.fullBitmap1 = wx.StaticBitmap(bitmap= self.fullImg, id=wxID_WXFULLBITMAP,
            name='fullbitmap1', parent=self.scrolledWindow1, pos= wx.Point(0, 0),
            size= wx.Size(width, height), style=0)

        self.scrolledWindow1.SetScrollbars(20, 20, (width/20) + .5, (height/20) + .9, noRefresh = False)

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
            d= wx.MessageDialog( self, "No tests selected. Please select a test or click 'Select All' to run all tests.", "Error", wx.OK | wx.ICON_ERROR)
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
    
        infoBox.WriteText('Data directory: %s' % (datadir))

        infoBox.WriteText('\nQueuing tests for execution:')
        for t in names:
            infoBox.WriteText("\n  %s" % t)

        for t in tests:
            infoBox.WriteText("\n")
            infoBox.WriteText("Running test script '%s'" % t)
            exec open(t) in {}
