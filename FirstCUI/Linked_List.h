#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <wx/wx.h>
#include <vector>

class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

class Linked_List : public wxFrame {
public:
    Linked_List(wxWindow* parent, wxWindowID id, const wxString& title);
    ~Linked_List();

private:
    wxPanel* panel;
    wxBoxSizer* sizer;
    wxBoxSizer* buttonSizer;
    wxBoxSizer* inputSizer;
    wxButton* insertButton;
    wxButton* deleteButton;
    wxButton* clearButton;
    wxStaticText* text;
    wxTextCtrl* dataInput;
    wxTextCtrl* positionInput;

    Node* head;

    void OnInsertButtonClick(wxCommandEvent& event);
    void OnDeleteButtonClick(wxCommandEvent& event);
    void OnClearButtonClick(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

    void InsertNode(int value, int position);
    void DeleteNode();
    void ClearList();
    void DrawLinkedList();

    wxDECLARE_EVENT_TABLE();
};

#endif // LINKED_LIST_H
