#include "Queue_Linked_List.h"
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(Queue_Linked_List, wxFrame)
EVT_CLOSE(Queue_Linked_List::OnClose)
wxEND_EVENT_TABLE()

Queue_Linked_List::Queue_Linked_List(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxFrame(parent, id, title), userInputText(nullptr), frontNode(0), rearNode(0)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create a horizontal sizer for the input and buttons
    wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create the "Enter Value" static text
    wxStaticText* controlText = new wxStaticText(panel, wxID_ANY, "Enter Value:");
    controlSizer->Add(controlText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 0);

    // Create the text control for input
    userInputText = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    controlSizer->Add(userInputText, 0, wxALIGN_CENTER_VERTICAL, 0);

    // Create the "Enqueue" button
    wxButton* enqueueButton = new wxButton(panel, wxID_ANY, wxT("Enqueue"));
    controlSizer->Add(enqueueButton, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 15);

    // Create the "Dequeue" button
    wxButton* dequeueButton = new wxButton(panel, wxID_ANY, wxT("Dequeue"));
    controlSizer->Add(dequeueButton, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 15);

    // Create the "Clear Queue" button
    wxButton* clearButton = new wxButton(panel, wxID_ANY, wxT("Clear Queue"));
    controlSizer->Add(clearButton, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 15);

    // Add the control sizer to the main sizer
    mainSizer->Add(controlSizer, 0, wxALIGN_CENTER | wxTOP, 15);

    // Create a horizontal sizer for the nodes and labels
    wxBoxSizer* nodeSizer = new wxBoxSizer(wxHORIZONTAL);

    // Function to create a node
    auto createNode = [&](wxPanel* parent, int value, int id) -> wxGrid* {
        wxGrid* node = new wxGrid(parent, id, wxDefaultPosition, wxSize(100, 50));
        node->CreateGrid(1, 1);
        node->EnableEditing(false);
        node->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTER);
        node->SetRowLabelValue(0, wxString::Format("%d", value));
        node->SetColLabelValue(0, "");
        return node;
        };

    // Create and add nodes and labels
    for (int i = 0; i < 6; ++i) {
        int labelValue = 400 + i;
        int gridValue = labelValue + 1;

        wxBoxSizer* nodeContainer = new wxBoxSizer(wxVERTICAL);
        wxStaticText* label = new wxStaticText(panel, wxID_ANY, wxString::Format("%d", labelValue), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        wxGrid* node = createNode(panel, gridValue, wxID_HIGHEST + i + 1); // Create nodes with unique IDs
        nodes[i] = node; // Store the node pointer in the array

        nodeContainer->Add(label, 0, wxALIGN_CENTER | wxBOTTOM, 5);
        nodeContainer->Add(node, 0, wxALIGN_CENTER | wxALL, 5);
        nodeSizer->Add(nodeContainer, 0, wxALIGN_CENTER | wxALL, 5);
        node->SetColLabelSize(15);
        node->SetRowLabelSize(34);

        if (i < 5) {
            wxStaticText* arrow = new wxStaticText(panel, wxID_ANY, "-------->", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
            nodeSizer->Add(arrow, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
        }
        else {
            node->SetRowLabelValue(0, "NULL");
        }
    }

    // Add the node sizer to the main sizer
    mainSizer->Add(nodeSizer, 0, wxALIGN_CENTER | wxTOP, 20);

    // Create a horizontal sizer for the "Front" and "Rear" labels and empty boxes
    wxBoxSizer* queueSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create an empty static box to represent the queue's front
    wxStaticBox* frontBox = new wxStaticBox(panel, wxID_ANY, "");
    wxStaticBoxSizer* frontBoxSizer = new wxStaticBoxSizer(frontBox, wxVERTICAL);
    frontLabelValue = new wxStaticText(panel, wxID_ANY, wxT("NULL"));
    frontBoxSizer->Add(frontLabelValue, 0, wxALIGN_CENTER);

    // Create an empty static box to represent the queue's rear
    wxStaticBox* rearBox = new wxStaticBox(panel, wxID_ANY, "");
    wxStaticBoxSizer* rearBoxSizer = new wxStaticBoxSizer(rearBox, wxVERTICAL);
    rearLabelValue = new wxStaticText(panel, wxID_ANY, wxT("NULL"));
    rearBoxSizer->Add(rearLabelValue, 0, wxALIGN_CENTER);

    // Create the "Front" label
    wxStaticText* frontLabel = new wxStaticText(panel, wxID_ANY, "Front");
    wxStaticText* rearLabel = new wxStaticText(panel, wxID_ANY, "Rear");
    queueSizer->Add(frontLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    queueSizer->Add(frontBoxSizer, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);
    queueSizer->Add(rearLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    queueSizer->Add(rearBoxSizer, 0, wxALIGN_CENTER_VERTICAL);

    wxFont newFont = frontLabel->GetFont();
    newFont.SetPointSize(newFont.GetPointSize() + 5);
    frontLabel->SetFont(newFont);
    rearLabel->SetFont(newFont);

    // Add the "Front" and "Rear" sizer to the main sizer
    mainSizer->Add(queueSizer, 0, wxALIGN_CENTER | wxTOP, 30);

    // Create a sizer for the dequeued value
    wxBoxSizer* dequeuedValueSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* dequeuedValueText = new wxStaticText(panel, wxID_ANY, "Dequeued Value = ");
    wxFont font = dequeuedValueText->GetFont();
    font.SetPointSize(font.GetPointSize() + 5); // Increase font size by 2 points
    dequeuedValueText->SetFont(font);
    dequeuedValueLabel = new wxStaticText(panel, wxID_ANY, wxT(""));
    dequeuedValueSizer->Add(dequeuedValueText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    dequeuedValueSizer->Add(dequeuedValueLabel, 0, wxALIGN_CENTER_VERTICAL);

    // Add the dequeued value sizer to the main sizer
    mainSizer->Add(dequeuedValueSizer, 0, wxALIGN_CENTER | wxTOP, 15);

    panel->SetSizerAndFit(mainSizer);
    this->SetSize(1280, 720);
    this->Centre();

    // Bind events to their handlers
    enqueueButton->Bind(wxEVT_BUTTON, &Queue_Linked_List::OnEnqueueButtonClick, this);
    dequeueButton->Bind(wxEVT_BUTTON, &Queue_Linked_List::OnDequeueButtonClick, this);
    clearButton->Bind(wxEVT_BUTTON, &Queue_Linked_List::OnClearButtonClick, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &Queue_Linked_List::OnClose, this);
}

void Queue_Linked_List::OnEnqueueButtonClick(wxCommandEvent& event) {
    wxString inputValue = userInputText->GetValue();
    if (inputValue.IsEmpty()) {
        wxMessageBox("Please enter a value to enqueue.", "Error", wxICON_ERROR);
        return;
    }

    if (rearNode >= 6) {
        wxMessageBox("Queue is full.\nPlease CLEAR THE QUEUE and TRY AGAIN.", "Error", wxICON_ERROR);
        return;
    }

    nodes[rearNode]->SetCellValue(0, 0, inputValue);
    rearNode++;

    if (frontNode == 0) {
        frontLabelValue->SetLabel("400");
    }
    
    rearLabelValue->SetLabel(wxString::Format("%d", enqueueValueFront++));

    userInputText->Clear();
}

void Queue_Linked_List::OnDequeueButtonClick(wxCommandEvent& event) {
    if (frontNode == rearNode) {
        wxMessageBox("Queue is empty.", "Error", wxICON_ERROR);
        return;
    }

    wxString dequeuedValue = nodes[frontNode]->GetCellValue(0, 0);
    dequeuedValueLabel->SetLabel(dequeuedValue);

    // Clearing the cell value at the frontNode position
    nodes[frontNode]->SetCellValue(0, 0, wxEmptyString);

    // Moving the frontNode position to the next cell
    frontNode++;

    // Updating the "Front" label value
    frontLabelValue->SetLabel(wxString::Format("%d", frontNode + 400));

    // Checking if the queue became empty
    if (frontNode == rearNode) {
        frontLabelValue->SetLabel("NULL");
        rearLabelValue->SetLabel("NULL");
    }
}


void Queue_Linked_List::OnClearButtonClick(wxCommandEvent& event) {
    for (int i = 0; i < rearNode; i++) {
        nodes[i]->SetCellValue(0, 0, wxEmptyString);
    }
    enqueueValueFront = 400;
    frontNode = 0;
    rearNode = 0;
    frontLabelValue->SetLabel("NULL");
    rearLabelValue->SetLabel("NULL");
    dequeuedValueLabel->SetLabel(wxEmptyString);

}

void Queue_Linked_List::OnClose(wxCloseEvent& event) {
    wxWindow* parent = GetParent();
    parent->Show();
    Destroy();
}