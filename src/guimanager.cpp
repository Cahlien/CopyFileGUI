#include "guimanager.h"


GUIManager::GUIManager()
{
	wxXmlResource::Get()->InitAllHandlers();
}


GUIManager::~GUIManager()
{
	mainWindow->Destroy();
	Close();
}


wxFrame* GUIManager::GetMainWindow()
{
	return mainWindow;
}


void GUIManager::SetMainWindow(const std::string& win)
{
	
	mainWindow = wxXmlResource::Get()->LoadFrame(NULL, win);
}


wxIcon* GUIManager::GetMainWindowIcon()
{
	return mainWindowIcon;
}


void GUIManager::SetMainWindowIcon(const std::string& filepath)
{
	
	mainWindowIcon = new wxIcon(filepath, wxBITMAP_TYPE_ANY);
	mainWindow->SetIcon(*mainWindowIcon);
}


void GUIManager::ShowMainWindow(const bool& visibility)
{
	wxTheApp->SetTopWindow(mainWindow);
	mainWindow->Show(visibility);
}


void GUIManager::DisplayErrorDialog(const std::string& errorMessage)
{
	wxMessageDialog* error = new wxMessageDialog(NULL, errorMessage, wxT("Error"), wxOK);
	error->ShowModal();
	wxDELETE(error);
}


int GUIManager::Close()
{
	mainWindow->Close(TRUE);
	return 0;
}
