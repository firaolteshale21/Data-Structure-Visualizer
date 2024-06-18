#include "Array_Visualizer.h"

wxBEGIN_EVENT_TABLE(Array_Visualizer, wxFrame)
EVT_CLOSE(Array_Visualizer::OnClose)
EVT_BUTTON(1001, Array_Visualizer::OnInsertButtonClick)
EVT_BUTTON(1002, Array_Visualizer::OnDeleteButtonClick)
wxEND_EVENT_TABLE()

Array_Visualizer::Array_Visualizer(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxFrame(parent, id, title, wxDefaultPosition, wxSize(1000, 800)), currentIndex(0) {
    panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Input and buttons
    wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
    inputBox = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 30));
    wxButton* insertButton = new wxButton(panel, 1001, "Insert", wxDefaultPosition, wxSize(70, 30));
    wxButton* deleteButton = new wxButton(panel, 1002, "Delete", wxDefaultPosition, wxSize(70, 30));

    controlSizer->Add(inputBox, 0, wxALL, 5);
    controlSizer->Add(insertButton, 0, wxALL, 5);
    controlSizer->Add(deleteButton, 0, wxALL, 5);

    mainSizer->Add(controlSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);

    // Array visualization
    arraySizer = new wxBoxSizer(wxHORIZONTAL);
    indexSizer = new wxBoxSizer(wxHORIZONTAL);

    for (int i = 0; i < 15; ++i) {
        arrayData[i] = 0; // Initialize the array with default values
        wxStaticText* arrayBox = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxSize(50, 50), wxALIGN_CENTER | wxBORDER_SIMPLE);
        wxFont font = arrayBox->GetFont();
        font.SetPointSize(12);
        arrayBox->SetFont(font);
        arrayBoxes[i] = arrayBox;
        arraySizer->Add(arrayBox, 0, wxALL, 5);

        wxStaticText* indexBox = new wxStaticText(panel, wxID_ANY, wxString::Format("%d", i), wxDefaultPosition, wxSize(50, 20), wxALIGN_CENTER);
        indexSizer->Add(indexBox, 0, wxALL, 5);
    }

    mainSizer->Add(arraySizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    mainSizer->Add(indexSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);

    panel->SetSizerAndFit(mainSizer);
    this->Centre();
}

void Array_Visualizer::OnClose(wxCloseEvent& event) {
    wxWindow* parent = GetParent();
    parent->Show();
    Destroy();
}

void Array_Visualizer::OnInsertButtonClick(wxCommandEvent& event) {
    wxString valueStr = inputBox->GetValue();
    long value;
    if (valueStr.ToLong(&value)) {
        if (currentIndex < 15) {
            arrayData[currentIndex] = static_cast<int>(value);
            arrayBoxes[currentIndex]->SetLabel(valueStr);
            currentIndex++;
        }
        else {
            wxMessageBox("Array is full", "Error", wxOK | wxICON_ERROR);
        }
    }
}

void Array_Visualizer::OnDeleteButtonClick(wxCommandEvent& event) {
    if (currentIndex > 0) {
        currentIndex--;
        arrayData[currentIndex] = 0;
        arrayBoxes[currentIndex]->SetLabel("");
    }
    else {
        wxMessageBox("Array is empty", "Error", wxOK | wxICON_ERROR);
    }
}