import wx

class NamedPanel(wx.Panel):
    """
    A wx.Panel subclass that has a border and a visible name.
    Here's how it's used:
    
      namedPanel = NamedPanel(frame, 'My name goes here')
      aButton    = wx.Button(namedPanel, -1, 'aButton')
      namedPanel.setup()

    I hope to figure out how to avoid the need to call setup()
    explicitly.
    
    Author: Robb Shecter (robb@acm.org)
    """

    def __init__(self, parent, name='No Name'):
        "Instantiate a new NamedPanel with the given name."
        wx.Panel.__init__(self, parent, -1)
        group      = wx.StaticBox(self, -1, name)
        if "__WXMAC__" in wx.PlatformInfo:
            self.box   = wx.StaticBoxSizer(group)
        else:
            self.box   = wx.StaticBoxSizer(group, wx.VERTICAL)

        self.isSetup = 0

    def setup(self):
        "Prepare the UI. Required before the panel is shown."
        self.__setChildPanel(self.GetChildren()[1])

    def __setChildPanel(self, aPanel):
        "Specify the panel to display inside the named border"
        if self.isSetup:
            raise 'NamedPanel.__setChildPanel() was called twice'
        self.isSetup = 1
        if "__WXMAC__" in wx.PlatformInfo:
            self.box.Add(aPanel, 1, 4)
        else:
            self.box.Add(aPanel, 1, wx.EXPAND|wx.ALL, 4)

        self.SetAutoLayout(True)
        self.SetSizer(self.box)
        self.box.Fit(self)
        self.box.SetSizeHints(self)

app = wx.PySimpleApp()
frame = wx.Frame(None, -1, 'NamedPanel Test', size=(300,300))

namedPanel = NamedPanel(frame, 'My name goes here')
aButton    = wx.Button(namedPanel, -1, 'aButton')
namedPanel.setup()

frame.Show(1)
app.MainLoop()