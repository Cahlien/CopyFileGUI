#ifndef _MAIN_APPLICATION_H_
	#define _MAIN_APPLICATION_H_ 1
	
	#include <chrono>
	#include <thread>
	#include <wx/app.h>						// defines wxDECLARE_APP macro, which isn't really required here, but is used
	#include <wx/wx.h>						// needed for all wxWidgets applications
	#include <wx/filepicker.h>			// needed for our wxFilePickerCtrls
	#include <wx/xrc/xmlres.h>			// needed for our XML resources

	#include "guimanager.h"
	#include "copier.h"
	
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
		
		// declare getter for gui manager
		GUIManager* GetGUIManager();
		
		// declare the event-handling functions
		void OnCopyEntered(wxCommandEvent&);
		void OnCancel(wxCommandEvent&);
		void OnOK(wxCommandEvent&);
		
	// define the private section of the CopyApp class
	private:
		// declare the private variable for the GUIManager
		GUIManager guiManager;
	};

	// invoke wxWidgets' magic to create a getter for the app instance
	wxDECLARE_APP(CopyApp);
#endif
