//
//	comments.cpp
//
//	(C) Copyright 2000-2002 by Jan van den Baard.
//	    All Rights Reserved.
//

#include "bcc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Constructor.
CommentsPage::CommentsPage() 
{
	// Setup icon.
	m_nIcon = IDI_COMMENTS;
}

// Destructor.
CommentsPage::~CommentsPage()
{
}

// Refresh page contents.
void CommentsPage::RefreshData( LPPARSER pParser )
{
	_ASSERT_VALID( pParser );

	// Save parser.
	m_pParser = pParser;

	// Setup edit controls.
	m_Init.SetWindowText( pParser->pszCommentInit );
	m_Term.SetWindowText( pParser->pszCommentTerm );
	m_Single.SetWindowText( pParser->pszCommentSingle );
}

// Save page/parser contents.
BOOL CommentsPage::SavePage( ClsStdioFile *pFile, LPPARSER pParser )
{
	try
	{
		// Save strings.
		if ( pParser->pszCommentInit   && *pParser->pszCommentInit   ) pFile->PrintF( _T( "CommentInit=%s\n" ), pParser->pszCommentInit );
		if ( pParser->pszCommentTerm   && *pParser->pszCommentTerm   ) pFile->PrintF( _T( "CommentTerm=%s\n" ), pParser->pszCommentTerm );
		if ( pParser->pszCommentSingle && *pParser->pszCommentSingle ) pFile->PrintF( _T( "CommentSingle=%s\n" ), pParser->pszCommentSingle );

	}
	catch ( ClsException& e )
	{
		// Error...
		UNREFERENCED_PARAMETER( e );
		return FALSE;
	}
	return TRUE;
}

// WM_COMMAND handler.
LRESULT CommentsPage::OnCommand( UINT nNotifyCode, UINT nCtrlID, HWND hWndCtrl )
{
	// What's the message.
	switch ( nCtrlID )
	{
		case	IDC_COMMENT_INIT:
			// Change string.
			HandleEditControl( nNotifyCode, nCtrlID, &m_pParser->pszCommentInit );
			break;

		case	IDC_COMMENT_TERM:
			// Change string.
			HandleEditControl( nNotifyCode, nCtrlID, &m_pParser->pszCommentTerm );
			break;

		case	IDC_COMMENT_SINGLE:
			// Change string.
			HandleEditControl( nNotifyCode, nCtrlID, &m_pParser->pszCommentSingle );
			break;
	}				
	// Pass to the base class.
	return Page::OnCommand( nNotifyCode, nCtrlID, hWndCtrl );
}

// WM_INITDIALOG handler.
LRESULT CommentsPage::OnInitDialog( PROPSHEETPAGE * pPropSheetPage )
{
	// Setup static controls.
	m_STCom.Attach( GetDlgItemHandle( IDC_ST_COMMENTS ));

	// And the edit control.
	m_Init.Attach( GetDlgItemHandle( IDC_COMMENT_INIT ));
	m_Term.Attach( GetDlgItemHandle( IDC_COMMENT_TERM ));
	m_Single.Attach( GetDlgItemHandle( IDC_COMMENT_SINGLE ));

	// Call the base-class.
	return Page::OnInitDialog( pPropSheetPage );
}