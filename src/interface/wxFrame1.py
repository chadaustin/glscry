#Boa:Frame:wxFrame1

from wxPython.wx import *
import os


def create(parent):
    return wxFrame1(parent)

[wxID_WXFRAME1, wxID_WXFRAME1BROWSE_BUTTON, wxID_WXFRAME1GRAPH_BUTTON, 
 wxID_WXFRAME1NOTEBOOK1, wxID_WXFRAME1PANEL1, wxID_WXFRAME1PANEL2, 
 wxID_WXFRAME1TEXTCTRL1, wxID_WXFRAME1TREECTRL1, wxID_WXFRAME1WINDOW1, 
] = map(lambda _init_ctrls: wxNewId(), range(9))

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
              text=u'Pages0')
        parent.AddPage(imageId=-1, page=self.panel2, select=False,
              text='Pages1')

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
              pos=wxPoint(-4, -4), size=wxSize(1032, 746),
              style=wxDEFAULT_FRAME_STYLE, title='work_in_progress')
        self._init_utils()
        self.SetClientSize(wxSize(1024, 712))
        self.SetMenuBar(self.menuBar1)

        self.notebook1 = wxNotebook(id=wxID_WXFRAME1NOTEBOOK1, name='notebook1',
              parent=self, pos=wxPoint(0, 0), size=wxSize(248, 692), style=0)

        self.window1 = wxWindow(id=wxID_WXFRAME1WINDOW1, name='window1',
              parent=self, pos=wxPoint(248, 0), size=wxSize(776, 692), style=0)

        self.panel1 = wxPanel(id=wxID_WXFRAME1PANEL1, name='panel1',
              parent=self.notebook1, pos=wxPoint(0, 0), size=wxSize(240, 666),
              style=wxTAB_TRAVERSAL)

        self.panel2 = wxPanel(id=wxID_WXFRAME1PANEL2, name='panel2',
              parent=self.notebook1, pos=wxPoint(0, 0), size=wxSize(240, 666),
              style=wxTAB_TRAVERSAL)

        self.textCtrl1 = wxTextCtrl(id=wxID_WXFRAME1TEXTCTRL1, name='textCtrl1',
              parent=self.panel1, pos=wxPoint(8, 16), size=wxSize(144, 21),
              style=0, value=u'C:\\')

        self.browse_button = wxButton(id=wxID_WXFRAME1BROWSE_BUTTON,
              label=u'Browse', name=u'browse_button', parent=self.panel1,
              pos=wxPoint(160, 16), size=wxSize(75, 23), style=0)
        EVT_BUTTON(self.browse_button, wxID_WXFRAME1BROWSE_BUTTON,
              self.OnBrowse_buttonButton)

        self.treeCtrl1 = wxTreeCtrl(id=wxID_WXFRAME1TREECTRL1, name='treeCtrl1',
              parent=self.panel1, pos=wxPoint(8, 56), size=wxSize(216, 536),
              style=wxTR_HAS_BUTTONS)

        self.graph_button = wxButton(id=wxID_WXFRAME1GRAPH_BUTTON,
              label=u'Graph', name=u'graph_button', parent=self.panel1,
              pos=wxPoint(160, 608), size=wxSize(75, 31), style=0)

        self._init_coll_notebook1_Pages(self.notebook1)

    def __init__(self, parent,filename='work_in_progress'):
        self.dirname=""
        self._init_ctrls(parent)

    def OnMenu1Items0Menu(self, event):
        event.Skip()

    def OnMenu4Items1Menu(self, event):
        event.Skip()
    
    def OnMenu4Items0Menu(self, event):
        d= wxMessageDialog( self, "work_in_progress \n"
                            "V. 2.16.05"," About work_in_progress", wxOK | wxICON_INFORMATION)  # Create a message dialog box
        d.ShowModal() # Shows it
        d.Destroy() # finally destroy it when finished.    

    def OnMenu1Id_saveMenu(self, event):
        f=open(os.path.join(self.dirname,self.filename),"w")
        f.write(self.control.GetValue())
        f.close()
    def OnMenu1Id_saveasMenu(self, event):
        self.dirname=os.getcwd()
        dlg = wxFileDialog(self, "Choose a file", self.dirname, " ","*.*", wxSAVE)
        if dlg.ShowModal() == wxID_OK:
            self.filename=dlg.GetFilename()
            self.dirname=dlg.GetDirectory()
            self.OnSave(e)
        dlg.Destroy()    
    def OnMenu1Id_exitMenu(self, event):
        self.Close(true)

    def OnBrowse_buttonButton(self, event):
        dlg = wxDirDialog(self, "Choose a directory:",
                      style=wxDD_DEFAULT_STYLE|wxDD_NEW_DIR_BUTTON)
        if dlg.ShowModal() == wxID_OK:
            self.textCtrl1.Clear()
            self.textCtrl1.WriteText(dlg.GetPath())
        dlg.Destroy()
    #tree ctrl functions
    
    def OnRightClick(self, event):
        pt = event.GetPosition();
        item, flags = self.treeCtrl1.HitTest(pt)
        self.log.WriteText("OnRightClick: %s, %s, %s\n" %
                           (self.treeCtrl1.GetItemText(item), type(item), item.__class__))
        self.treeCtrl1.SelectItem(item)


    def OnRightUp(self, event):
        pt = event.GetPosition();
        item, flags = self.treeCtrl1.HitTest(pt)
        self.log.WriteText("OnRightUp: %s (manually starting label edit)\n"
                           % self.treeCtrl1.GetItemText(item))
        self.treeCtrl1.EditLabel(item)



    def OnBeginEdit(self, event):
        self.log.WriteText("OnBeginEdit\n")
        # show how to prevent edit...
        if self.treeCtrl1.GetItemText(event.GetItem()) == "The Root Item":
            wxBell()
            self.log.WriteText("You can't edit this one...\n")

            # Lets just see what's visible of its children
            cookie = 0
            root = event.GetItem()
            (child, cookie) = self.treeCtrl1.GetFirstChild(root, cookie)
            while child.IsOk():
                self.log.WriteText("Child [%s] visible = %d" %
                                   (self.treeCtrl1.GetItemText(child),
                                    self.treeCtrl1.IsVisible(child)))
                (child, cookie) = self.treeCtrl1.GetNextChild(root, cookie)

            event.Veto()


    def OnEndEdit(self, event):
        self.log.WriteText("OnEndEdit\n")
        # show how to reject edit, we'll not allow any digits
        for x in event.GetLabel():
            if x in string.digits:
                self.log.WriteText("You can't enter digits...\n")
                event.Veto()
                return


    def OnLeftDClick(self, event):
        pt = event.GetPosition();
        item, flags = self.treeCtrl1.HitTest(pt)
        self.log.WriteText("OnLeftDClick: %s\n" % self.treeCtrl1.GetItemText(item))
        parent = self.treeCtrl1.GetItemParent(item)
        self.treeCtrl1.SortChildren(parent)
        event.Skip()


    def OnSize(self, event):
        w,h = self.GetClientSizeTuple()
        self.treeCtrl1.SetDimensions(0, 0, w, h)


    def OnItemExpanded(self, event):
        item = event.GetItem()
        self.log.WriteText("OnItemExpanded: %s\n" % self.treeCtrl1.GetItemText(item))

    def OnItemCollapsed(self, event):
        item = event.GetItem()
        self.log.WriteText("OnItemCollapsed: %s\n" % self.treeCtrl1.GetItemText(item))

    def OnSelChanged(self, event):
        self.item = event.GetItem()
        self.log.WriteText("OnSelChanged: %s\n" % self.treeCtrl1.GetItemText(self.item))
        if wxPlatform == '__WXMSW__':
            self.log.WriteText("BoundingRect: %s\n" %
                               self.treeCtrl1.GetBoundingRect(self.item, True))
        #items = self.tree.GetSelections()
        #print map(self.tree.GetItemText, items)
        event.Skip()


    def OnActivate(self, event):
        self.log.WriteText("OnActivate: %s\n" % self.treeCtrl1.GetItemText(self.item))     
