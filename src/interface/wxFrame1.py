#Frame:wxFrame1

from wxPython.wx import *
from wxPython.gizmos import *

def create(parent):
    return wxFrame1(parent)

[wxID_WXFRAME1, wxID_WXFRAME1BUTTON1, wxID_WXFRAME1NOTEBOOK1, 
 wxID_WXFRAME1PANEL1, wxID_WXFRAME1PANEL2, wxID_WXFRAME1PANEL3, 
 wxID_WXFRAME1TREELISTCTRL1, 
] = map(lambda _init_ctrls: wxNewId(), range(7))

class wxFrame1(wxFrame):
    def _init_coll_menuBar1_Menus(self, parent):
        # menu bar setup

        parent.Append(menu=wxMenu(), title='Menus0')
        parent.Append(menu=wxMenu(), title='Menus1')
        parent.Append(menu=wxMenu(), title='Menus2')
        parent.Append(menu=wxMenu(), title='Menus3')

    def _init_coll_notebook1_Pages(self, parent):
        # notebook setup

        parent.AddPage(imageId=-1, page=self.panel1, select=True, text='Pages0')
        parent.AddPage(imageId=-1, page=self.panel2, select=False,
              text='Pages1')

    def _init_utils(self):
        # add menu bar
        self.menuBar1 = wxMenuBar()

        self._init_coll_menuBar1_Menus(self.menuBar1)

    def _init_sizers(self):
        # sizer setup
        self.boxSizer1 = wxBoxSizer(wxHORIZONTAL)
        self.boxSizer1.Add = (self.notebook1, 0, wxEXPAND)
        self.boxSizer1.Add = (self.panel3, 1, wxEXPAND)
    def _init_ctrls(self, prnt):
        wxFrame.__init__(self, id=wxID_WXFRAME1, name='', parent=prnt,
              pos=wxPoint(-4, -4), size=wxSize(800, 600),
              style=wxDEFAULT_FRAME_STYLE, title='wxFrame1')
        self._init_utils()
        self.SetClientSize(wxSize(800, 600))
        self.SetMenuBar(self.menuBar1)

        self.notebook1 = wxNotebook(id=wxID_WXFRAME1NOTEBOOK1, name='notebook1',
              parent=self, pos=wxPoint(0, 0), size=wxSize(288, 600), style=0)

        self.panel1 = wxPanel(id=wxID_WXFRAME1PANEL1, name='panel1',
              parent=self.notebook1, pos=wxPoint(0, 0), size=wxSize(280, 600),
              style=wxTAB_TRAVERSAL)

        self.panel2 = wxPanel(id=wxID_WXFRAME1PANEL2, name='panel2',
              parent=self.notebook1, pos=wxPoint(0, 0), size=wxSize(280, 600),
              style=wxTAB_TRAVERSAL)

        self.panel3 = wxPanel(id=wxID_WXFRAME1PANEL3, name='panel3',
              parent=self, pos=wxPoint(288, 0), size=wxSize(520, 600),
              style=wxTAB_TRAVERSAL)

        self.treeListCtrl1 = wxTreeListCtrl(id=wxID_WXFRAME1TREELISTCTRL1,
              name='treeListCtrl1', parent=self.panel1, pos=wxPoint(8, 8),
              size=wxSize(256, 475), style=wxTR_HAS_BUTTONS)

        self.button1 = wxButton(id=wxID_WXFRAME1BUTTON1, label='Graph',
              name='button1', parent=self.panel1, pos=wxPoint(200, 500),
              size=wxSize(65, 25), style=0)

        self._init_coll_notebook1_Pages(self.notebook1)

        self._init_sizers()

    def __init__(self, parent):
        self._init_ctrls(parent)
