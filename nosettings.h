//
//	nosettings.h
//
//	(C) Copyright 2005 by Jan van den Baard.
//	    All Rights Reserved.
//
//	Settings directory chooser dialog.
//

// Settings directory chooser dialog class.
class NoSettings : public ClsDialog
{
	_NO_COPY( NoSettings );
public:
	// Construction/destruction.
	NoSettings();
	virtual ~NoSettings();
	
	// Implementation.
	BOOL SelectSettingsDirectory( ClsWindow& Parent );
	
protected:
	// Overidables.
	virtual LRESULT OnInitDialog( LPPROPSHEETPAGE pPsp );
	virtual LRESULT OnCommand( UINT nNotifyCode, UINT nCtrlID, HWND hWndCtrl );

	// Data.
	ClsDirBrowser	m_Browser;
};