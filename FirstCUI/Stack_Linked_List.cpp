#include "Stack_Linked_List.h"
#include <wx/msgdlg.h>
#include <wx/grid.h>

wxBEGIN_EVENT_TABLE(Stack_Linked_List, wxFrame)
EVT_CLOSE(Stack_Linked_List::OnClose)
wxEND_EVENT_TABLE()

Stack_Linked_List::Stack_Linked_List(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxFrame(parent, id, title), userInputText(nullptr), currentNode(0)
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

    // Create the "Push" button
    wxButton* pushButton = new wxButton(panel, wxID_ANY, wxT("Push"));
    controlSizer->Add(pushButton, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 15);

    // Create the "Pop" button
    wxButton* popButton = new wxButton(panel, wxID_ANY, wxT("Pop"));
    controlSizer->Add(popButton, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 15);

    // Create the "Clear" button
    wxButton* clearButton = new wxButton(panel, wxID_ANY, wxT("Clear"));
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
        int labelValue = 200 + i;
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

    // Create a horizontal sizer for the "Top" label and empty box
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create an empty static box to represent the stack's top
    wxStaticBox* topBox = new wxStaticBox(panel, wxID_ANY, "");
    wxStaticBoxSizer* topBoxSizer = new wxStaticBoxSizer(topBox, wxVERTICAL);
    topLabelValue = new wxStaticText(panel, wxID_ANY, wxT("NULL"));
    topBoxSizer->Add(topLabelValue, 0, wxALIGN_CENTER);

    // Create the "Top" label
    wxStaticText* topLabel = new wxStaticText(panel, wxID_ANY, "Top");
    topSizer->Add(topLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    topSizer->Add(topBoxSizer, 0, wxALIGN_CENTER_VERTICAL);
    wxFont newFont = topLabel->GetFont();
    newFont.SetPointSize(newFont.GetPointSize() + 5);
    topLabel->SetFont(newFont);

    // Add the "Top" sizer to the main sizer
    mainSizer->Add(topSizer, 0, wxALIGN_CENTER | wxTOP, 30);

    // Create a sizer for the popped value
    wxBoxSizer* poppedValueSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* poppedValueText = new wxStaticText(panel, wxID_ANY, "Popped Value = ");
    wxFont font = poppedValueText->GetFont();
    font.SetPointSize(font.GetPointSize() + 5); // Increase font size by 2 points
    poppedValueText->SetFont(font);
    poppedValueLabel = new wxStaticText(panel, wxID_ANY, wxT(""));
    poppedValueSizer->Add(poppedValueText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    poppedValueSizer->Add(poppedValueLabel, 0, wxALIGN_CENTER_VERTICAL);

    // Add the popped value sizer to the main sizer
    mainSizer->Add(poppedValueSizer, 0, wxALIGN_CENTER | wxTOP, 15);

    panel->SetSizerAndFit(mainSizer);
    this->SetSize(1280, 720);
    this->Centre();

    // Bind events to their handlers
    pushButton->Bind(wxEVT_BUTTON, &Stack_Linked_List::OnPushButtonClick, this);
    popButton->Bind(wxEVT_BUTTON, &Stack_Linked_List::OnPopButtonClick, this);
    clearButton->Bind(wxEVT_BUTTON, &Stack_Linked_List::OnClearButtonClick, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &Stack_Linked_List::OnClose, this);
}

void Stack_Linked_List::OnPushButtonClick(wxCommandEvent& event) {
    // Get the value from the text control
    wxString valueStr = userInputText->GetValue();
    long value;
    if (!valueStr.ToLong(&value)) {
        wxMessageBox("Invalid input! Please enter an integer value.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Check if there's space in the stack
    if (currentNode < 6) {
        // Shift all nodes to the right
        for (int i = currentNode; i > 0; --i) {
            nodes[i]->SetCellValue(0, 0, nodes[i - 1]->GetCellValue(0, 0));
        }

        // Set the value in the first node
        nodes[0]->SetCellValue(0, 0, wxString::Format("%ld", value));

        // Update the top label value
        topLabelValue->SetLabel("200");

        // Move to the next node
        currentNode++;
    }
    else {
        wxMessageBox("No more nodes available!", "Error", wxOK | wxICON_ERROR);
    }
}

void Stack_Linked_List::OnPopButtonClick(wxCommandEvent& event) {
    if (currentNode == 0) {
        wxMessageBox("Stack is empty!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Get the value from the top node
    wxString poppedValue = nodes[0]->GetCellValue(0, 0);
    poppedValueLabel->SetLabel(poppedValue);

    // Shift all nodes to the left
    for (int i = 0; i < currentNode - 1; ++i) {
        nodes[i]->SetCellValue(0, 0, nodes[i + 1]->GetCellValue(0, 0));
    }

    // Clear the value in the last node
    nodes[currentNode - 1]->SetCellValue(0, 0, "");

    // Decrement currentNode
    currentNode--;

    // Update the top label value
    if (currentNode > 0) {
        topLabelValue->SetLabel("200");
    }
    else {
        topLabelValue->SetLabel("NULL");
    }
}

void Stack_Linked_List::OnClearButtonClick(wxCommandEvent& event) {
    for (int i = 0; i < 6; ++i) {
        nodes[i]->ClearGrid();
    }
    currentNode = 0;
    topLabelValue->SetLabel("NULL");
    poppedValueLabel->SetLabel("");
    wxMessageBox("Stack is Cleared Successfully!", "Stack Clear", wxOK | wxICON_INFORMATION);
}

void Stack_Linked_List::OnClose(wxCloseEvent& event) {
    wxWindow* parent = GetParent();
    parent->Show();
    Destroy();
}
