// begins with an include guard
#ifndef _GUI_MANAGER_H_
	#define _GUI_MANAGER_H_ 1

	// include basic wxWidgets header for access to the wxFrame and wxIcon types
	#include <wx/wx.h>

	// class declaration of GUIManager class
	class GUIManager
	{
		// public section of class
		public:
			// default constructor
			GUIManager();
			// destructor
			~GUIManager();
			
			// getter for main window
			wxFrame* GetMainWindow();
			// setter for main window
			void SetMainWindow(wxFrame*);
			// getter for main window's icon
			wxIcon* GetMainWindowIcon();
			// setter for main window's icon
			void SetMainWindowIcon(wxIcon);
			
			// function to close the gui manager
			int Close();

		// private section of class
		private:
			// wxFrame pointer variable for main window
			wxFrame* mainWindow;
			// wxIcon pointer variable for main window's icon
			wxIcon* mainWindowIcon;

	};
#endif
