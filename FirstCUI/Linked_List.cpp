#include "Linked_List.h"

wxBEGIN_EVENT_TABLE(Linked_List, wxFrame)
EVT_BUTTON(1001, Linked_List::OnInsertButtonClick)
EVT_BUTTON(1002, Linked_List::OnDeleteButtonClick)
EVT_BUTTON(1003, Linked_List::OnClearButtonClick)
EVT_CLOSE(Linked_List::OnClose)
wxEND_EVENT_TABLE()

Linked_List::Linked_List(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxFrame(parent, id, title, wxDefaultPosition, wxSize(1000, 800)), head(nullptr) {
    panel = new wxPanel(this);
    sizer = new wxBoxSizer(wxVERTICAL);
    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer = new wxBoxSizer(wxHORIZONTAL);

    dataInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, -1));
    positionInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, -1));
    insertButton = new wxButton(panel, 1001, "Insert", wxDefaultPosition, wxDefaultSize);
    deleteButton = new wxButton(panel, 1002, "Delete", wxDefaultPosition, wxDefaultSize);
    clearButton = new wxButton(panel, 1003, "Clear Node", wxDefaultPosition, wxDefaultSize);

    inputSizer->Add(new wxStaticText(panel, wxID_ANY, "Data: "), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    inputSizer->Add(dataInput, 1, wxALL | wxEXPAND, 5);
    inputSizer->Add(new wxStaticText(panel, wxID_ANY, "Position: "), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    inputSizer->Add(positionInput, 1, wxALL | wxEXPAND, 5);

    buttonSizer->Add(insertButton, 1, wxEXPAND | wxALL, 5);
    buttonSizer->Add(deleteButton, 1, wxEXPAND | wxALL, 5);
    buttonSizer->Add(clearButton, 1, wxEXPAND | wxALL, 5);

    text = new wxStaticText(panel, wxID_ANY, "Singly Linked List Visualization", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont font = text->GetFont();
    font.SetPointSize(18); // Increase the font size to 18 points
    text->SetFont(font);

    sizer->Add(inputSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    sizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    sizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    sizer->AddStretchSpacer(1); // To push the panel to the top and leave space for drawing

    panel->SetSizer(sizer);
    this->Centre();
}

Linked_List::~Linked_List() {
    ClearList();
}

void Linked_List::OnInsertButtonClick(wxCommandEvent& event) {
    long data, position;
    if (dataInput->GetValue().ToLong(&data) && positionInput->GetValue().ToLong(&position)) {
        InsertNode(data, position); // Insert the value at the specified position
        DrawLinkedList();
    }
    else {
        wxMessageBox("Please enter valid integers for data and position.", "Invalid Input", wxOK | wxICON_ERROR);
    }
}

void Linked_List::OnDeleteButtonClick(wxCommandEvent& event) {
    DeleteNode();
    DrawLinkedList();
}

void Linked_List::OnClearButtonClick(wxCommandEvent& event) {
    ClearList();
    DrawLinkedList();
}

void Linked_List::OnClose(wxCloseEvent& event) {
    GetParent()->Show();
    Destroy();
}

void Linked_List::InsertNode(int value, int position) {
    Node* newNode = new Node(value);

    if (position <= 0 || head == nullptr) {
        // Insert at the beginning if position is 0 or negative, or if the list is empty
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* temp = head;
        int currentPosition = 0;

        // Traverse to the position just before the desired position
        while (temp->next != nullptr && currentPosition < position - 1) {
            temp = temp->next;
            currentPosition++;
        }

        // Insert the new node
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void Linked_List::DeleteNode() {
    if (head == nullptr) return;

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

void Linked_List::ClearList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Linked_List::DrawLinkedList() {
    wxClientDC dc(panel);
    dc.Clear();

    Node* current = head;
    int x = 50;
    int y = 150;
    int width = 100;
    int height = 50;
    int gap = 20;

    if (head != nullptr) {
        // Draw head pointer
        dc.DrawText("Head", x - 50, y + height / 2 - 10);
        dc.DrawLine(x - 20, y + height / 2, x, y + height / 2);
    }

    while (current != nullptr) {
        // Draw the node
        dc.DrawRectangle(x, y, width, height);
        dc.DrawText(wxString::Format("%d", current->data), x + width / 2 - 10, y + height / 2 - 10);

        if (current->next != nullptr) {
            // Draw the arrow
            dc.DrawLine(x + width, y + height / 2, x + width + gap, y + height / 2);
            dc.DrawLine(x + width + gap - 5, y + height / 2 - 5, x + width + gap, y + height / 2);
            dc.DrawLine(x + width + gap - 5, y + height / 2 + 5, x + width + gap, y + height / 2);
        }
        else {
            // Draw tail pointer
            dc.DrawText("Tail", x + width + gap + 10, y + height / 2 - 10);
            dc.DrawLine(x + width, y + height / 2, x + width + gap, y + height / 2);
        }

        x += width + gap;
        current = current->next;
    }
}
