#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    void OnStackArrayButtonClick(wxCommandEvent& event);
    void OnStackLinkedListButtonClick(wxCommandEvent& event);
    void OnQueuesLinkedListButtonClick(wxCommandEvent& event);
    void OnArrayButtonClick(wxCommandEvent& event);
    void OnLinkedListButtonClick(wxCommandEvent& event);
    void OnQueuesArrayButtonClick(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);


    wxDECLARE_EVENT_TABLE();
};

#endif // MAINFRAME_H
