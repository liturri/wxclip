#include "appgui.hxx"
#include "actions.hxx"
#include "popen2.hxx"
#include "str2.hxx"
#include "system.hxx"
#include "wx/clipbrd.h"
#include <iostream>
#include <wx/msgdlg.h>

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
   std::string result;
   auto cmd = command->GetValue().ToStdString();
   auto clipStr = clipContent->GetValue().ToStdString();
   // std::cerr << cmd << std::endl;

   if (starts_with(cmd, "!"))
   {
      BangActions b;
      try
      {
         result = b.BangChain(cmd.substr(1), clipStr);
      }
      catch (const std::out_of_range err)
      {
         wxMessageBox(err.what(), "Error!");
         return;
      }
   }
   else
   {
      PopenStrFilter filter(cmd);
      filter.Run(clipStr);
      result = filter.Read();
   }
   Popen xclipCmd("xclip -i -selection clipboard", "w");
   xclipCmd.write(result);

   hst.AppendCmd(GetCommand());

   event.Skip();
}

void MainFrame::ClickOnHelp(wxCommandEvent &event)
{
   BangActions b;
   std::string buff;
   buff = "Comandos ! (bang) ej: !sort|lower\nLista de comandos internos:\n\n";
   buff += b.Help();
   wxMessageBox(buff, "Help");
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
   EVT_BUTTON(wxID_HELP, MainFrame::ClickOnHelp)
wxEND_EVENT_TABLE()

    // clang-format on