#include "appgui.hxx"
#include "popen2.hxx"
#include "system.hxx"
#include "wx/clipbrd.h"
#include <iostream>

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : G_MainDialog(parent, id, title, pos, size, style), hst(std::string(getenv("HOME")) + "/.config/wxclip.hist")
{
   for (const auto &i : hst.GetCommandsList())
   {
      command->Append(i);
   };
   LoadClipboard();
}

void MainFrame::LoadClipboard()
{
   if (wxTheClipboard->Open())
   {
      if (wxTheClipboard->IsSupported(wxDF_UNICODETEXT))
      {
         wxTextDataObject data;
         wxTheClipboard->GetData(data);
         clipContent->Clear();
         clipContent->SetValue(data.GetText());
      }
      wxTheClipboard->Close();
   }
}

void MainFrame::ClickOnAccept(wxCommandEvent &event)
{
   if (command->IsTextEmpty())
      return;
   auto cmd = command->GetValue().ToStdString();
   // std::cerr << cmd << std::endl;

   PopenStrFilter filter(cmd);
   filter.Run(clipContent->GetValue().ToStdString());
   auto buff = filter.Read();

   Popen xclipCmd("xclip -i -selection clipboard", "w");
   xclipCmd.write(buff);

   hst.AppendCmd(GetCommand());

   event.Skip();
}

void MainFrame::OnClipboardChange(wxClipboardEvent & /* event */)
{
   std::cerr << "Clipboard change" << std::endl;
   LoadClipboard();
}

// clang-format off

wxBEGIN_EVENT_TABLE(MainFrame, wxDialog)
   EVT_CLIPBOARD_CHANGED(MainFrame::OnClipboardChange)
   EVT_BUTTON(wxID_OK, MainFrame::ClickOnAccept)
wxEND_EVENT_TABLE()

    // clang-format on