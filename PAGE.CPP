//
//	page.cpp
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
Page::Page() 
{
	// Setup defaults.
	m_pParser = NULL;
}

// Destructor.
Page::~Page()
{
}

// Save a color value.
void Page::SaveColor( ClsStdioFile *pFile, LPPARSER pParser, LPCTSTR pszDesc, DWORD dwFlag, int nIndex )
{
	if ( pParser->crColors[ nIndex ] == CLR_DEFAULT )
		pFile->PrintF( "%s*\n", pszDesc );
	else
	{
		pFile->PrintF( pszDesc );
		pFile->PrintF( ( pParser->dwColorFlags & dwFlag ) ? _T( "*\n" ) : _T( "%ld,%ld,%ld\n" ), GetRValue( pParser->crColors[ nIndex ] ), 
													 GetGValue( pParser->crColors[ nIndex ] ), 													 
													 GetBValue( pParser->crColors[ nIndex ] ));
	}
}

// Re-act on an edit control event.
void Page::HandleEditControl( UINT nNotifyCode, UINT nCtrlID, LPTSTR *pStrPtr, BOOL bChange /* = TRUE */ )
{
	// Was the focus lost?
	if ( nNotifyCode == EN_KILLFOCUS )
	{
		// Get the contents of the control.
		LPTSTR pszText = CopyEditContents( nCtrlID );
		if ( pszText )
		{
			// Release current contents.
			if ( *pStrPtr ) ::FreePooled( pParserPool, *pStrPtr );

			// Check if it has valid contents.
			for ( size_t i = 0; i <= _tcslen( pszText ); i++ )
			{
				// If we read the end it were all blanks.
				if ( pszText[ i ] == _T( '\0' ))
				{
					// Free the memory.
					::FreePooled( pParserPool, pszText );

					// Clear edit control contents.
					::SetWindowText( GetDlgItemHandle( nCtrlID ), _T( "" ));

					// Clear the pointer.
					*pStrPtr = NULL;
					return;
				}

				// Is it a white space?
				if ( ! _istspace( pszText[ i ] )) break;
			}

			// Setup new contents.
			*pStrPtr = pszText;
		}
		else
			// Error...
			MessageBox( ClsString( MAKEINTRESOURCE( IDS_NO_MEMORY )), ClsGetApp()->GetAppTitle(), MB_ICONERROR | MB_OK );
	}
	else if ( bChange == TRUE && nNotifyCode == EN_CHANGE && ( ::GetFocus() == GetDlgItemHandle( nCtrlID )))
		// Changed...
		if ( m_pParser ) pSettings->Changed( m_pParser );
}
	
// Copy the contents of an edit control.
LPTSTR Page::CopyEditContents( UINT nCtrlID )
{
	// Get the edit control.
	HWND hEdit = GetDlgItemHandle( nCtrlID );

	// First we see how many bytes we need for the new buffer.
	int nLen = ::GetWindowTextLength( hEdit );
	
	// Allocate buffer.
	LPTSTR pszBuffer = ( LPTSTR )::AllocPooled( pParserPool, nLen + 1 );
	if ( pszBuffer )
	{
		// Get contents.
		::GetWindowText( hEdit, pszBuffer, nLen + 1 );
		return pszBuffer;
	}
	return NULL;
}