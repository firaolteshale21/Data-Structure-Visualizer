#include "Queue_Array.h"
#include <wx/grid.h>

wxBEGIN_EVENT_TABLE(Queue_Array, wxFrame)
EVT_BUTTON(wxID_ANY, Queue_Array::OnEnqueueButtonClick)
EVT_BUTTON(wxID_ANY, Queue_Array::OnDequeueButtonClick)
EVT_BUTTON(wxID_ANY, Queue_Array::OnClearQueueButtonClick)
EVT_CLOSE(Queue_Array::OnClose)
wxEND_EVENT_TABLE()

Queue_Array::Queue_Array(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxFrame(parent, id, title), userInputText(nullptr), dequeuedValueText(nullptr), frontText(nullptr), rearText(nullptr), queueGrid(nullptr), front(-1), rear(-1) {

    wxPanel* panel = new wxPanel(this);

    // Create the text control for user input
    wxStaticText* controlText = new wxStaticText(panel, wxID_ANY, "Enter Value:");
    userInputText = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    // Create buttons
    wxButton* enqueueButton = new wxButton(panel, wxID_ANY, wxT("Enqueue"));
    wxButton* dequeueButton = new wxButton(panel, wxID_ANY, wxT("Dequeue"));
    wxButton* clearQueueButton = new wxButton(panel, wxID_ANY, wxT("Clear Queue"));

    // Create the static text to display the dequeued value
    dequeuedValueText = new wxStaticText(panel, wxID_ANY, "Dequeued Value: ");

    // Create the static text to display the front and rear
    frontText = new wxStaticText(panel, wxID_ANY, "Front: -");
    rearText = new wxStaticText(panel, wxID_ANY, "Rear: -");

    // Create a grid to display the queue
    queueGrid = new wxGrid(panel, wxID_ANY);
    queueGrid->CreateGrid(10, 1);
    queueGrid->EnableEditing(false);

    for (int i = 0; i < 10; ++i) {
        queueGrid->SetRowLabelValue(i, wxString::Format("%d", i));
    }

    queueGrid->SetColLabelValue(0, "Queue");

    // Layout sizers
    wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer->Add(controlText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    controlSizer->Add(userInputText, 1, wxALIGN_CENTER_VERTICAL);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(enqueueButton, 0, wxALL, 5);
    buttonSizer->Add(dequeueButton, 0, wxALL, 5);
    buttonSizer->Add(clearQueueButton, 0, wxALL, 5);

    wxBoxSizer* frontRearSizer = new wxBoxSizer(wxHORIZONTAL);
    frontRearSizer->Add(frontText, 0, wxALL, 5);
    frontRearSizer->Add(rearText, 0, wxALL, 5);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(controlSizer, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(frontRearSizer, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(queueGrid, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(dequeuedValueText, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizerAndFit(mainSizer);
    this->SetSize(800, 600);
    this->Centre();

    // Bind button events
    enqueueButton->Bind(wxEVT_BUTTON, &Queue_Array::OnEnqueueButtonClick, this);
    dequeueButton->Bind(wxEVT_BUTTON, &Queue_Array::OnDequeueButtonClick, this);
    clearQueueButton->Bind(wxEVT_BUTTON, &Queue_Array::OnClearQueueButtonClick, this);
}

void Queue_Array::OnEnqueueButtonClick(wxCommandEvent& event) {
    wxString inputValue = userInputText->GetValue();
    long intValue;
    if (inputValue.ToLong(&intValue)) {
        queue.push_back(intValue);
        rear = queue.size() - 1;
        if (front == -1) {
            front = 0;
        }
        UpdateQueueDisplay();
    }
    else {
        wxMessageBox("Please enter a valid integer value.");
    }
}

void Queue_Array::OnDequeueButtonClick(wxCommandEvent& event) {
    if (!queue.empty()) {
        int dequeuedValue = queue.front();
        dequeuedValueText->SetLabel(wxString::Format("Dequeued Value: %d", dequeuedValue));
        queue.erase(queue.begin());
        if (queue.empty()) {
            front = rear = -1;
        }
        else {
            rear = queue.size() - 1;
        }
        UpdateQueueDisplay();
    }
    else {
        wxMessageBox("Queue is empty.");
    }
}

void Queue_Array::OnClearQueueButtonClick(wxCommandEvent& event) {
    queue.clear();
    front = rear = -1;
    UpdateQueueDisplay();
    dequeuedValueText->SetLabel("Dequeued Value: ");
}

void Queue_Array::UpdateQueueDisplay() {
    for (int i = 0; i < 10; ++i) {
        if (i < queue.size()) {
            queueGrid->SetCellValue(i, 0, wxString::Format("%d", queue[i]));
        }
        else {
            queueGrid->SetCellValue(i, 0, "");
        }
    }
    frontText->SetLabel(wxString::Format("Front: %d", front));
    rearText->SetLabel(wxString::Format("Rear: %d", rear));
}
void Queue_Array::OnClose(wxCloseEvent& event) {
    wxWindow* parent = GetParent();
    parent->Show();
    Destroy();
}