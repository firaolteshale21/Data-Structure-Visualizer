#include "Stack_Array.h"
#include <wx/msgdlg.h>
#include <wx/textctrl.h>
#include <wx/grid.h>

wxBEGIN_EVENT_TABLE(Stack_Array, wxFrame)
// Event table entries can go here if needed
wxEND_EVENT_TABLE()

Stack_Array::Stack_Array(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxFrame(parent, id, title), userInputText(nullptr), stackGrid(nullptr), poppedValueText(nullptr), topIndexText(nullptr), topIndex(-1) // Initialize member variables
{
    // Initialize your window here

    wxPanel* panel = new wxPanel(this);

    // Create the "Clear Stack" button
    wxButton* clearButton = new wxButton(panel, wxID_ANY, wxT("Clear Stack"));
    // Create the control text
    wxStaticText* controlText = new wxStaticText(panel, wxID_ANY, "Enter Value:");

    // Create the text control
    userInputText = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER); // Assign to member variable

    // Create the "Push" button
    wxButton* pushButton = new wxButton(panel, wxID_ANY, wxT("Push"));

    // Create the "Pop" button
    wxButton* popButton = new wxButton(panel, wxID_ANY, wxT("Pop"));

    // Create a horizontal sizer for control text and input field
    wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer->Add(controlText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    controlSizer->Add(userInputText, 1, wxALIGN_CENTER_VERTICAL, 0);

    // Create a horizontal sizer for buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(pushButton, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    buttonSizer->Add(popButton, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    buttonSizer->Add(clearButton, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    // Create a vertical sizer to hold the text, control sizer, button sizer, and grid
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add text to the main sizer (consider increasing its font size if needed)
    wxStaticText* text = new wxStaticText(panel, wxID_ANY, "Stack Implementation Using Array");

    // Set the font size of the text
    wxFont textFont = text->GetFont();
    textFont.SetPointSize(20);  // Adjust the font size as needed
    text->SetFont(textFont);

    mainSizer->Add(text, 0, wxALL | wxCENTER, 10);

    // Add the control sizer to the main sizer
    mainSizer->Add(controlSizer, 0, wxALIGN_CENTER | wxALL, 10);

    // Add the button sizer to the main sizer
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    // Create the grid to represent the stack
    stackGrid = new wxGrid(panel, wxID_ANY); // Assign to member variable
    stackGrid->CreateGrid(10, 1); // Create a grid with 10 rows and 1 column
    stackGrid->EnableEditing(false); // Disable editing
    for (int i = 0; i < 10; i++) {
        std::string label = std::to_string(9 - i); // Labels from 0 at the bottom to 9 at the top
        stackGrid->SetRowLabelValue(i, label.c_str());
    }
    stackGrid->SetColLabelValue(0, "Elements");

    mainSizer->Add(stackGrid, 0, wxALIGN_CENTER | wxALL, 10);

    // Create a static text control to display the top index and align it to the center
    topIndexText = new wxStaticText(panel, wxID_ANY, "Top: NULL", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont topFont = topIndexText->GetFont();
    topFont.SetPointSize(topFont.GetPointSize() * 2); // Increase the font size by a factor of 2
    topIndexText->SetFont(topFont);
    mainSizer->Add(topIndexText, 0, wxALIGN_CENTER | wxALL, 10);

    // Create a static text control to display the popped value and align it to the center
    poppedValueText = new wxStaticText(panel, wxID_ANY, "Popped Value: ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont font = poppedValueText->GetFont();
    font.SetPointSize(font.GetPointSize() * 2); // Increase the font size by a factor of 2
    poppedValueText->SetFont(font);
    mainSizer->Add(poppedValueText, 0, wxALIGN_CENTER | wxALL, 10);

    panel->SetSizerAndFit(mainSizer);

    // Set the size and center the window
    this->SetSize(1280, 720);
    this->Centre();

    // Bind the clearButton event to a handler function
    clearButton->Bind(wxEVT_BUTTON, &Stack_Array::OnClearButtonClick, this);

    // Bind the pushButton event to a handler function
    pushButton->Bind(wxEVT_BUTTON, &Stack_Array::OnPushButtonClick, this);

    // Bind the popButton event to a handler function
    popButton->Bind(wxEVT_BUTTON, &Stack_Array::OnPopButtonClick, this);

    // Bind the close event to handle window close action
    this->Bind(wxEVT_CLOSE_WINDOW, &Stack_Array::OnClose, this);

    // Bind the text enter event to handle text input
    userInputText->Bind(wxEVT_TEXT_ENTER, &Stack_Array::OnTextEnter, this);
}

void Stack_Array::OnClearButtonClick(wxCommandEvent& event) {
    // Clear all cells in the grid
    for (int row = 0; row < stackGrid->GetNumberRows(); ++row) {
        stackGrid->SetCellValue(row, 0, "");
    }

    // Optionally reset the first cell to an initial state
    stackGrid->SetCellValue(0, 0, " ");

    // Update the top index
    topIndex = -1;
    topIndexText->SetLabel("Top: NULL");

    wxMessageBox("Stack Cleared Successfully");
}

void Stack_Array::OnClose(wxCloseEvent& event) {
    wxWindow* parent = GetParent();
    parent->Show();
    Destroy();
}

void Stack_Array::OnTextEnter(wxCommandEvent& event) {
    // Retrieve the input value from the text box
    wxString inputValue = userInputText->GetValue();

    // Check if the input value is an integer
    long intValue;
    if (inputValue.ToLong(&intValue)) {
        // Input value is an integer
        wxMessageBox(wxString::Format("Integer value entered: %ld", intValue));
        // Store the integer value for later use
        // You can use the variable intValue here
    }
    else {
        // Input value is a string
        wxMessageBox(wxString::Format("String value entered: %s", inputValue));
        // Store the string value for later use
        // You can use the variable inputValue here
    }
}

void Stack_Array::OnPushButtonClick(wxCommandEvent& event) {
    // Retrieve the input value from the text box
    wxString inputValue = userInputText->GetValue();

    // Check if the input value is an integer
    long intValue;
    if (inputValue.ToLong(&intValue)) {
        // Ensure the stack is not full
        if (topIndex < 9) {
            // Increment the top index
            topIndex++;

            // Place the new value at the position indicated by topIndex
            stackGrid->SetCellValue(9 - topIndex, 0, inputValue);  // Insert from bottom (row 9) upwards

            // Update the top index text
            topIndexText->SetLabel(wxString::Format("Top: %d", topIndex));
        }
        else {
            wxMessageBox("Stack overflow! Cannot push more elements.", "Error", wxOK | wxICON_ERROR);
        }
    }
    else {
        // Input value is not an integer, show an error message
        wxMessageBox("Please enter a valid integer value.");
    }
}

void Stack_Array::OnPopButtonClick(wxCommandEvent& event) {
    if (topIndex >= 0) {
        // Get the value from the top of the stack
        wxString poppedValue = stackGrid->GetCellValue(9 - topIndex, 0);  // Pop from the current top index

        // Clear the value at the position indicated by topIndex
        stackGrid->SetCellValue(9 - topIndex, 0, "");

        // Decrement the top index
        topIndex--;

        // Update the top index text
        topIndexText->SetLabel(topIndex >= 0 ? wxString::Format("Top: %d", topIndex) : "Top: NULL");

        // Update the static text to display the popped value
        poppedValueText->SetLabel(wxString::Format("Popped Value: %s", poppedValue));
    }
    else {
        wxMessageBox("Stack underflow! Cannot pop any elements.", "Error", wxOK | wxICON_ERROR);
    }
}
