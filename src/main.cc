// -*- C++ -*-
//
// generated by wxGlade 1.0.3 on Fri Nov 26 10:54:29 2021
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

// This is an automatically generated file.
// Manual changes will be overwritten without warning!

#include "appgui.hxx"
#include "cmd_history.hxx"
#include <wx/image.h>
#include <wx/wx.h>

class wxClipApp : public wxApp
{
public:
   bool OnInit() override;
};

IMPLEMENT_APP(wxClipApp)

bool wxClipApp::OnInit()
{
   wxInitAllImageHandlers();
   auto *mainDialog = new MainFrame(NULL, wxID_ANY, wxEmptyString);
   SetTopWindow(mainDialog);
   auto exitDialogValue = mainDialog->ShowModal();

   return false;
}
