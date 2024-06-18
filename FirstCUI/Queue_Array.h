#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

#include <wx/wx.h>
#include <vector>
#include <wx/grid.h>

class Queue_Array : public wxFrame {
public:
    Queue_Array(wxWindow* parent, wxWindowID id, const wxString& title);

private:
    void OnClose(wxCloseEvent& event);
    void OnEnqueueButtonClick(wxCommandEvent& event);
    void OnDequeueButtonClick(wxCommandEvent& event);
    void OnClearQueueButtonClick(wxCommandEvent& event);
    void UpdateQueueDisplay();

    wxTextCtrl* userInputText;
    wxStaticText* dequeuedValueText;
    wxStaticText* frontText;
    wxStaticText* rearText;
    wxGrid* queueGrid;
    std::vector<int> queue;
    int front;
    int rear;

    wxDECLARE_EVENT_TABLE();
};

#endif // QUEUE_ARRAY_H
