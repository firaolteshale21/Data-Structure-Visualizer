#ifndef ARRAY_VISUALIZER_H
#define ARRAY_VISUALIZER_H

#include <wx/wx.h>
#include <vector>

class Array_Visualizer : public wxFrame {
public:
    Array_Visualizer(wxWindow* parent, wxWindowID id, const wxString& title);

private:
    void OnClose(wxCloseEvent& event);
    void OnInsertButtonClick(wxCommandEvent& event);
    void OnDeleteButtonClick(wxCommandEvent& event);
    void UpdateArrayVisualization();

    wxPanel* panel;
    wxTextCtrl* inputBox;
    wxBoxSizer* arraySizer;
    wxBoxSizer* indexSizer;
    wxStaticText* arrayBoxes[15];
    int arrayData[15];
    int currentIndex;

    wxDECLARE_EVENT_TABLE();
};

#endif // ARRAY_VISUALIZER_H
