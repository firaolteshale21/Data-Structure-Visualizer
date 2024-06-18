#ifndef QUEUE_LINKED_LIST_H
#define QUEUE_LINKED_LIST_H

#include <wx/wx.h>
#include <wx/grid.h>

class Queue_Linked_List : public wxFrame
{
public:
    Queue_Linked_List(wxWindow* parent, wxWindowID id, const wxString& title);

private:
    void OnEnqueueButtonClick(wxCommandEvent& event);
    void OnDequeueButtonClick(wxCommandEvent& event);
    void OnClearButtonClick(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

    wxTextCtrl* userInputText;
    wxStaticText* frontLabelValue;
    wxStaticText* rearLabelValue;
    wxStaticText* dequeuedValueLabel;
    wxGrid* nodes[6];
    int frontNode;
    int rearNode;
    int enqueueValueFront = 400;
    int dequeueValues = 400;

    wxDECLARE_EVENT_TABLE();
};

#endif // QUEUE_LINKED_LIST_H
