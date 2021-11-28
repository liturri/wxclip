#pragma once

#include "cmd_history.hxx"
#include "wxgui.hxx"
#include <wx/clipbrd.h>

class MainFrame : public G_MainDialog
{
protected:
   CommandHistory hst;

public:
   MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos = wxDefaultPosition,
             const wxSize &size = wxDefaultSize, long style = /* wxDEFAULT_FRAME_STYLE */ 0);

   void OnClipboardChange(wxClipboardEvent &event);

   void LoadClipboard();

   void ClickOnAccept(wxCommandEvent &event);

   const std::string GetCommand() const
   {
      return command->GetValue().ToStdString();
   };

   wxDECLARE_EVENT_TABLE();
};