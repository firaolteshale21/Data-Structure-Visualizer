#include "HomePage.h"
#include "MainFrame.h"

enum {
    Start_Button_ID = 1
};

wxBEGIN_EVENT_TABLE(HomePage, wxFrame)
EVT_BUTTON(Start_Button_ID, HomePage::OnStartButtonClick)
wxEND_EVENT_TABLE()

HomePage::HomePage(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);

    // Create a static text with the required information
    wxStaticText* headerText = new wxStaticText(panel, wxID_ANY, "Data Structure Visualizer\n\nDeveloped by\n\nFiraol Teshale", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont headerFont = headerText->GetFont();
    headerFont.SetPointSize(headerFont.GetPointSize() + 25);
    headerFont.SetWeight(wxFONTWEIGHT_BOLD);
    headerFont.SetFamily(wxFONTFAMILY_ROMAN);
    headerText->SetFont(headerFont);

    // Create the start button
    wxButton* startButton = new wxButton(panel, Start_Button_ID, "Click here to continue", wxDefaultPosition, wxSize(-1, 65));
    wxFont buttonFont = startButton->GetFont();
    buttonFont.SetPointSize(buttonFont.GetPointSize() + 9.5);
    buttonFont.SetWeight(wxFONTWEIGHT_BOLD);
    buttonFont.SetFamily(wxFONTFAMILY_ROMAN);
    startButton->SetFont(buttonFont);

    // Add the text and button to the sizer
    verticalSizer->Add(headerText, 0, wxALIGN_CENTER | wxTOP, 50);
    verticalSizer->Add(startButton, 0, wxALIGN_CENTER | wxTOP, 70);

    panel->SetSizerAndFit(verticalSizer);
    this->Centre();
    CreateStatusBar();
    SetStatusText("Welcome to the Data Structure Visualizer");
}

void HomePage::OnStartButtonClick(wxCommandEvent& event) {
    // Get the size and position of the current HomePage window
    wxRect windowRect = GetRect();

    MainFrame* mainFrame = new MainFrame("Data Structure Visualizer");
    mainFrame->SetSize(windowRect.GetPosition().x, windowRect.GetPosition().y, windowRect.GetSize().GetWidth(), windowRect.GetSize().GetHeight()); // Set MainFrame to the same size and position as HomePage
    mainFrame->Show(true);
    this->Hide();
}
