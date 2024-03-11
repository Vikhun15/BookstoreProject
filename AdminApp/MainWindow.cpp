#define __WXMSW__
#define WXUSINGDLL

#include <wx/wx.h>
#include <wx/gdicmn.h>
#include <wx/frame.h>
#include <wx/wxprec.h>

class App : public wxApp {
public:
	bool OnInit(){
		wxFrame* window = new wxFrame(NULL, wxID_ANY, "Hello", wxDefaultPosition, wxSize(600, 400));
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText* text = new wxStaticText(window, wxID_ANY, "Well done!", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
		text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
		sizer->Add(text, 1, wxALIGN_CENTER);

		window->SetSizer(sizer);

		window->Show();
		return true;
	}
};

wxIMPLEMENT_APP(App);