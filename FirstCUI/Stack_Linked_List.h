#ifndef STACK_LINKED_LIST_H
#define STACK_LINKED_LIST_H

#include <wx/wx.h>
#include <wx/grid.h>

class Stack_Linked_List : public wxFrame {
public:
    Stack_Linked_List(wxWindow* parent, wxWindowID id, const wxString& title);

private:
    void OnClose(wxCloseEvent& event);
    void OnPushButtonClick(wxCommandEvent& event);
    void OnPopButtonClick(wxCommandEvent& event);
    void OnClearButtonClick(wxCommandEvent& event);

    wxTextCtrl* userInputText;
    int currentNode;
    wxGrid* nodes[6]; // Array to hold grid pointers
    wxStaticText* topLabelValue; // Label to show the top value
    wxStaticText* poppedValueLabel; // Label to show the popped value

    wxDECLARE_EVENT_TABLE();
};

#endif // STACK_LINKED_LIST_H
