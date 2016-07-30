//
//	comments.h
//
//	(C) Copyright 2000-2006 by Jan van den Baard.
//	    All Rights Reserved.
//
//	Comments page.
//

// Comments page class.
class CommentsPage : public Page
{
	_NO_COPY( CommentsPage );
public:
	// Construction/destruction.
	CommentsPage();
	virtual ~CommentsPage();

	// Overidables.
	virtual void RefreshData( LPPARSER pParser );
	virtual BOOL SavePage( ClsStdioFile *pFile, LPPARSER pParser );

protected:
	// Overidables.
	virtual LRESULT OnInitDialog( LPPROPSHEETPAGE pPsp );
	virtual LRESULT OnCommand( UINT nNotifyCode, UINT nCtrlID, HWND hWndCtrl );

	// Data.
	ClsInfoControl		m_STCom;
	ClsEdit			m_Init, m_Term, m_Single;
};