#ifndef GUI_MANAGER_H
	#define GUI_MANAGER_H

	#include <wx/wx.h>
	#include <wx/xrc/xmlres.h>
	
	class GUIManager
	{
		public:
			GUIManager();
			~GUIManager();
			
			wxFrame* GetMainWindow();
			void SetMainWindow(const std::string&);
			
			wxIcon* GetMainWindowIcon();
			void SetMainWindowIcon(const std::string&);
			
			void ShowMainWindow(const bool&);
			void DisplayErrorDialog(const std::string&);
			
			int Close();

		private:
			wxFrame* mainWindow;
			wxIcon* mainWindowIcon;

	};
#endif
