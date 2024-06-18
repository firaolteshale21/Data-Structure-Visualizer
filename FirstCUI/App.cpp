#include "App.h"
#include "HomePage.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    HomePage* homePage = new HomePage("Home Page - Data Structure Visualizer");
    // Get the screen size
    int screenWidth, screenHeight;
    wxDisplaySize(&screenWidth, &screenHeight);

    // Set the window size to 80% of the screen size
    int windowWidth = static_cast<int>(screenWidth * 0.8);
    int windowHeight = static_cast<int>(screenHeight * 0.9);

    // Set the window position to be centered on the screen
    int windowPosX = (screenWidth - windowWidth) / 2;
    int windowPosY = (screenHeight - windowHeight) / 2;

    // Set the window size and position
    homePage->SetSize(windowPosX, windowPosY, windowWidth, windowHeight);
    // Load and set the custom icon if needed
    // wxIcon icon;
    // icon.LoadFile("path_to_your_icon.ico", wxBITMAP_TYPE_ICO);
    // homePage->SetIcon(icon);

    homePage->Show();

    return true;
}
