#include <fstream>						// needed for std::ifstream and std::ofstream
#include <iostream>						// needed to handle standard input and output
#include <wx/app.h>						// defines wxDECLARE_APP macro, which isn't really required here, but is used
#include <wx/wx.h>						// needed for all wxWidgets applications
#include <wx/filepicker.h>			// needed for our wxFilePickerCtrls
#include <wx/xrc/xmlres.h>			// needed for our XML resources

// define the wxDELETE macro for pointers, if not using smart pointers
#define wxDELETE(p) if((p) != NULL) { delete p; p = NULL; }

// define the CopyApp class, which inherits publicly from wxApp
class CopyApp : public wxApp
{
// define the public section of the CopyApp class
public:
	// declare the OnInit function (essentially the main())
	virtual bool OnInit();
	// declare the OnExit function (how the application closes)
	virtual int OnExit();
	
	// declare the getters and setters for private variables
	std::string GetSourceFile();
	void SetSourceFile(const std::string&);
	std::string GetDestinationFile();
	void SetDestinationFile(const std::string&);
	
	// declare the function that actually does the copying
	bool CopyFile(const std::string&, const std::string&);
	
	// declare the event-handling functions
	void OnCopyEntered(wxCommandEvent&);
	void OnCancel(wxCommandEvent&);
	void OnOK(wxCommandEvent&);
	
	// declare the public variables
	wxFrame* win;					// the main window
	wxIcon mainIcon;				// the icon for the main window
	
// define the private section of the CopyApp class
private:
	// declare the private variables
	std::string sourceFile;			// the std::string representation of the source file path
	std::string destinationFile;	// the std::string representation of the destination file path
};

// invoke wxWidgets' magic to create a getter for the app instance
wxDECLARE_APP(CopyApp);
