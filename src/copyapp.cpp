#include "copyapp.h"


wxIMPLEMENT_APP(CopyApp);


bool CopyApp::OnInit()
{
	wxXmlResource::Get()->Load("../../../src/include/gui.xrc");
	
	guiManager.SetMainWindow("mainWindow");
	guiManager.SetMainWindowIcon("../../../src/include/Icon16.png");
	guiManager.ShowMainWindow(true);
	
	XRCCTRL(*(guiManager.GetMainWindow()), "copyButton", wxButton)->Bind(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CopyApp::OnCopyEntered), this, XRCID("copyButton"));
	XRCCTRL(*(guiManager.GetMainWindow()), "wxID_OK", wxButton)->Bind(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CopyApp::OnOK), this, XRCID("wxID_OK"));
	XRCCTRL(*(guiManager.GetMainWindow()), "wxID_CANCEL", wxButton)->Bind(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CopyApp::OnCancel), this, XRCID("wxID_CANCEL"));
	
	copiers = 0;
	
	return true;
}


int CopyApp::OnExit()
{
	guiManager.Close();

	exit(0);
}


void CopyApp::OnCopyEntered(wxCommandEvent& event)
{
	CopyFile();
}


void CopyApp::OnCancel(wxCommandEvent& event)
{
	OnExit();
}


void CopyApp::OnOK(wxCommandEvent& event)
{
	if(!CopyFile())
	{
		guiManager.GetMainWindow()->Show(false);
		
		while(copiers > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		
		OnExit();		
	}
}


GUIManager* CopyApp::GetGUIManager()
{
	return &guiManager;
}


void CopyApp::RegisterCopier()
{
	++copiers;
}


void CopyApp::DeregisterCopier()
{
	--copiers;
}

int CopyApp::CopyFile()
{
	int result = 1;
	
	Copier copier{};
	
	std::string source{XRCCTRL(*(guiManager.GetMainWindow()), "sourceEntry", wxFilePickerCtrl)->GetPath().ToStdString()};	
	std::string destination{XRCCTRL(*(guiManager.GetMainWindow()), "destinationEntry", wxFilePickerCtrl)->GetPath().ToStdString()};

	if(source.length() == 0 && destination.length() == 0)
	{
		guiManager.DisplayErrorDialog("Please provide source file and destination location");
	}
	else if(source.length() == 0)
	{
		guiManager.DisplayErrorDialog("Please provide source file");
	}
	else if(destination.length() == 0)
	{
		guiManager.DisplayErrorDialog("Please provide destination location");
	}
	else
	{
		copier.SetSource(source);
		copier.SetDestination(destination);
	
		std::thread copy_thread(&Copier::CreateCopy, copier);
		copy_thread.detach();

		result = 0;
	}

	return result;
}
