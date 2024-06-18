#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <wx/wx.h>

class HomePage : public wxFrame {
public:
    HomePage(const wxString& title);

private:
    void OnStartButtonClick(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // HOMEPAGE_H
