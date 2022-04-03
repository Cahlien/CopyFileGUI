#ifndef MAIN_APPLICATION_H
	#define MAIN_APPLICATION_H
	
	#include <chrono>
	#include <thread>
	#include <wx/app.h>
	#include <wx/filepicker.h>

	#include "guimanager.h"
	#include "copier.h"

	class CopyApp : public wxApp
	{
	public:
		virtual bool OnInit();
		virtual int OnExit();
		
		GUIManager* GetGUIManager();
		
		void OnCopyEntered(wxCommandEvent&);
		void OnCancel(wxCommandEvent&);
		void OnOK(wxCommandEvent&);
		
		void RegisterCopier();
		void DeregisterCopier();
		
		int CopyFile();

	private:
		GUIManager guiManager;
		int copiers;
	};
#endif
