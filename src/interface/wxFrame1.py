#Boa:Frame:wxFrame1

from wxPython.wx import *

def create(parent):
    return wxFrame1(parent)

[wxID_WXFRAME1, wxID_WXFRAME1BROWSE_BUTTON, wxID_WXFRAME1GRAPH_BUTTON, 
 wxID_WXFRAME1NOTEBOOK1, wxID_WXFRAME1PANEL1, wxID_WXFRAME1PANEL2, 
 wxID_WXFRAME1TEXTCTRL1, wxID_WXFRAME1TREECTRL1, wxID_WXFRAME1WINDOW1, 
] = map(lambda _init_ctrls: wxNewId(), range(9))

[wxID_WXFRAME1MENU1ITEMS0, wxID_WXFRAME1MENU1ITEMS1, wxID_WXFRAME1MENU1ITEMS2, 
 wxID_WXFRAME1MENU1ITEMS3, wxID_WXFRAME1MENU1ITEMS4, 
] = map(lambda _init_coll_menu1_Items: wxNewId(), range(5))

[wxID_WXFRAME1MENU4ITEMS0, wxID_WXFRAME1MENU4ITEMS1, 
] = map(lambda _init_coll_menu4_Items: wxNewId(), range(2))

[wxID_WXFRAME1MENU2ITEMS0] = map(lambda _init_coll_menu2_Items: wxNewId(), range(1))

[wxID_WXFRAME1MENU3ITEMS0] = map(lambda _init_coll_menu3_Items: wxNewId(), range(1))

class wxFrame1(wxFrame):
    def _init_coll_menu3_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU3ITEMS0,
              item=u'Properties', kind=wxITEM_NORMAL)

    def _init_coll_menu2_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU2ITEMS0, item='Items0',
              kind=wxITEM_NORMAL)

    def _init_coll_menu1_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS0, item=u'New',
              kind=wxITEM_NORMAL)
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS1, item=u'Open',
              kind=wxITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS2, item=u'Save',
              kind=wxITEM_NORMAL)
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS3,
              item=u'Save As', kind=wxITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU1ITEMS4, item=u'Exit',
              kind=wxITEM_NORMAL)
        EVT_MENU(self, wxID_WXFRAME1MENU1ITEMS0, self.OnMenu1Items0Menu)

    def _init_coll_menu4_Items(self, parent):
        # generated method, don't edit

        parent.Append(helpString=u'', id=wxID_WXFRAME1MENU4ITEMS0,
              item=u'About', kind=wxITEM_NORMAL)
        parent.AppendSeparator()
        parent.Append(helpString='', id=wxID_WXFRAME1MENU4ITEMS1, item=u'Help',
              kind=wxITEM_NORMAL)
        EVT_MENU(self, wxID_WXFRAME1MENU4ITEMS1, self.OnMenu4Items1Menu)

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
              pos=wxPoint(-4, -4), size=wxSize(1032, 746),
              style=wxDEFAULT_FRAME_STYLE, title='wxFrame1')
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

        self.treeCtrl1 = wxTreeCtrl(id=wxID_WXFRAME1TREECTRL1, name='treeCtrl1',
              parent=self.panel1, pos=wxPoint(8, 56), size=wxSize(216, 536),
              style=wxTR_HAS_BUTTONS)

        self.graph_button = wxButton(id=wxID_WXFRAME1GRAPH_BUTTON,
              label=u'Graph', name=u'graph_button', parent=self.panel1,
              pos=wxPoint(160, 608), size=wxSize(75, 31), style=0)

        self._init_coll_notebook1_Pages(self.notebook1)

    def __init__(self, parent):
        self._init_ctrls(parent)

    def OnMenu1Items0Menu(self, event):
        event.Skip()

    def OnMenu4Items1Menu(self, event):
        event.Skip()
