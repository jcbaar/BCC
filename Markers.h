//
//	markers.h
//
//	(C) Copyright 2000-2006 by Jan van den Baard.
//	    All Rights Reserved.
//
//	Markers page.
//

// Markers page class.
class MarkersPage : public Page
{
	_NO_COPY( MarkersPage );
public:
	// Construction/destruction.
	MarkersPage();
	virtual ~MarkersPage();

	// Overidables.
	virtual void RefreshData( LPPARSER pParser );
	virtual BOOL SavePage( ClsStdioFile *pFile, LPPARSER pParser );

protected:
	// Overidables.
	virtual LRESULT OnInitDialog( LPPROPSHEETPAGE pPsp );
	virtual LRESULT OnCommand( UINT nNotifyCode, UINT nCtrlID, HWND hWndCtrl );

	// Data.
	ClsInfoControl	m_STHead, m_STHead2, m_STHead3;
	ClsComboBox	m_Marker;
	ClsColorPicker	m_FgColor, m_BkColor, m_BkColorBM, m_BkColorCL;
	ClsCheckBox	m_Highlight;
};