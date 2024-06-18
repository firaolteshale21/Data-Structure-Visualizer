#include "HomePage.h"
#include "MainFrame.h"
#include "Stack_Array.h"
#include "Stack_Linked_List.h"
#include "Queue_Linked_List.h"
#include "Array_Visualizer.h"
#include "Linked_List.h" 
#include "Queue_Array.h" 
#include <wx/wx.h>

enum {
    Stack_Array_ID = 2,
    Stack_LinkedList_ID = 3,
    Queue_LinkedList_ID = 4,
    Array_Visualizer_ID = 5,
    Linked_List_ID = 6,
    Queue_Array_ID = 7 
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(Stack_Array_ID, MainFrame::OnStackArrayButtonClick)
EVT_BUTTON(Stack_LinkedList_ID, MainFrame::OnStackLinkedListButtonClick)
EVT_BUTTON(Queue_LinkedList_ID, MainFrame::OnQueuesLinkedListButtonClick)
EVT_BUTTON(Array_Visualizer_ID, MainFrame::OnArrayButtonClick)
EVT_BUTTON(Linked_List_ID, MainFrame::OnLinkedListButtonClick) 
EVT_BUTTON(Queue_Array_ID, MainFrame::OnQueuesArrayButtonClick)
EVT_CLOSE(MainFrame::OnClose)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 500)) {
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);

    wxButton* stackArrayButton = new wxButton(panel, Stack_Array_ID, "Stack Array: Implementation", wxDefaultPosition, wxSize(-1, 50));
    wxButton* stackLinkedListButton = new wxButton(panel, Stack_LinkedList_ID, "Stack Linked List Implementation", wxDefaultPosition, wxSize(-1, 50));
    wxButton* queuesArrayButton = new wxButton(panel, Queue_Array_ID, "Queues: Array Implementation", wxDefaultPosition, wxSize(-1, 50));
    wxButton* queuesLinkedListButton = new wxButton(panel, Queue_LinkedList_ID, "Queues: Linked List Implementation", wxDefaultPosition, wxSize(-1, 50));
    wxButton* arrayButton = new wxButton(panel, Array_Visualizer_ID, "Array Visualization", wxDefaultPosition, wxSize(-1, 50));
    wxButton* linkedListButton = new wxButton(panel, Linked_List_ID, "Linked List Visualization", wxDefaultPosition, wxSize(-1, 50)); // Update ID

    wxFont buttonFont = stackArrayButton->GetFont();
    buttonFont.SetPointSize(buttonFont.GetPointSize() + 6);
    buttonFont.SetWeight(wxFONTWEIGHT_BOLD);

    stackArrayButton->SetFont(buttonFont);
    stackLinkedListButton->SetFont(buttonFont);
    queuesArrayButton->SetFont(buttonFont);
    queuesLinkedListButton->SetFont(buttonFont);
    arrayButton->SetFont(buttonFont);
    linkedListButton->SetFont(buttonFont);

    // Adjust button positions
    verticalSizer->Add(stackArrayButton, 0, wxALIGN_CENTER | wxTOP, 20);
    verticalSizer->Add(stackLinkedListButton, 0, wxALIGN_CENTER | wxTOP, 20);
    verticalSizer->Add(queuesArrayButton, 0, wxALIGN_CENTER | wxTOP, 20);
    verticalSizer->Add(queuesLinkedListButton, 0, wxALIGN_CENTER | wxTOP, 20);
    verticalSizer->Add(arrayButton, 0, wxALIGN_CENTER | wxTOP, 20);
    verticalSizer->Add(linkedListButton, 0, wxALIGN_CENTER | wxTOP, 20);

    panel->SetSizerAndFit(verticalSizer);
    this->Centre();
    CreateStatusBar();
    SetStatusText("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tDeveloped By Firaol Teshale");
}



void MainFrame::OnStackArrayButtonClick(wxCommandEvent& event) {
    Stack_Array* stackArrayWindow = new Stack_Array(this, wxID_ANY, "Stack Using Array Implementation");
    stackArrayWindow->Show(true);
    this->Hide();
}

void MainFrame::OnStackLinkedListButtonClick(wxCommandEvent& event) {
    Stack_Linked_List* stackLinkedListWindow = new Stack_Linked_List(this, wxID_ANY, "Stack Using Linked List Implementation");
    stackLinkedListWindow->Show(true);
    this->Hide();
}

void MainFrame::OnQueuesLinkedListButtonClick(wxCommandEvent& event) {
    Queue_Linked_List* queueLinkedListWindow = new Queue_Linked_List(this, wxID_ANY, "Queue Using Linked List Implementation");
    queueLinkedListWindow->Show(true);
    this->Hide();
}

void MainFrame::OnArrayButtonClick(wxCommandEvent& event) {
    Array_Visualizer* arrayVisualizerWindow = new Array_Visualizer(this, wxID_ANY, "Array Visualization");
    arrayVisualizerWindow->Show(true);
    this->Hide();
}

void MainFrame::OnLinkedListButtonClick(wxCommandEvent& event) {
    Linked_List* linkedListWindow = new Linked_List(this, wxID_ANY, "Linked List Visualization");
    linkedListWindow->Show(true);
    this->Hide();
}

void MainFrame::OnQueuesArrayButtonClick(wxCommandEvent& event) {
    Queue_Array* queueArrayWindow = new Queue_Array(this, wxID_ANY, "Queue Using Array Implementation");
    queueArrayWindow->Show(true);
    this->Hide();
}

void MainFrame::OnClose(wxCloseEvent& event) {
    wxMessageDialog dialog(this, "Are you sure you want to close the window?", "Confirm Exit", wxYES_NO | wxICON_QUESTION);
    int response = dialog.ShowModal();
    if (response == wxID_YES) {
        wxTheApp->Exit();
        Destroy();
           
    }
    else {
        event.Veto();
    }
}
