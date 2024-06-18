#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <wx/wx.h>
#include <wx/grid.h>

class Stack_Array : public wxFrame
{
public:
    Stack_Array(wxWindow* parent, wxWindowID id, const wxString& title);

private:
    void OnClearButtonClick(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnTextEnter(wxCommandEvent& event); // Declaration of the OnTextEnter event handler
    void OnPushButtonClick(wxCommandEvent& event); // Declaration of the OnPushButtonClick event handler
    void OnPopButtonClick(wxCommandEvent& event);  // Declaration of the OnPopButtonClick event handler

    wxStaticText* topIndexText;
    int topIndex;  // To keep track of the top index of the stack

    wxTextCtrl* userInputText; // Member variable for the text control
    wxGrid* stackGrid;         // Member variable for the grid control
    wxStaticText* poppedValueText; // Member variable to display the popped value

    wxDECLARE_EVENT_TABLE();
};

#endif // STACK_ARRAY_H
