//
//	markers.cpp
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
MarkersPage::MarkersPage() 
{
	// Setup icon.
	m_nIcon = IDI_MARKERS;
}

// Destructor.
MarkersPage::~MarkersPage()
{
}

// Refresh page contents.
void MarkersPage::RefreshData( LPPARSER pParser )
{
	_ASSERT_VALID( pParser );

	// Save parser.
	m_pParser = pParser;

	// Setup the default line marker color.
	ClsColor color( pParser->crColors[ CARR_BACKGROUND ] );
	color.DarkenColor( 0.10, 0.10, 0.10 );

	// Setup the color selection.
	m_FgColor.Color() = pParser->crColors[ CARR_MARKER_FG_1 + m_Marker.GetCurSel() ];
	m_FgColor.RedrawWindow();
	m_BkColor.Color() = pParser->crColors[ CARR_MARKER_1 + m_Marker.GetCurSel() ];
	m_BkColor.RedrawWindow();
	m_BkColorBM.Color() = pParser->crColors[ CARR_BOOKMARK ];
	m_BkColorBM.RedrawWindow();
	m_BkColorCL.DefaultColor() = color;
	m_BkColorCL.Color() = pParser->crColors[ CARR_LINE_HIGHLIGHT ];
	m_BkColorCL.RedrawWindow();

	// Setup the checkboxes.
	m_Highlight.SetCheck( m_pParser->bHighlightCurrentLine ? BST_CHECKED : BST_UNCHECKED );
}

// Save page/parser contents.
BOOL MarkersPage::SavePage( ClsStdioFile *pFile, LPPARSER pParser )
{
	try
	{
		// Write colors comment.
		pFile->PrintF( ClsString( MAKEINTRESOURCE( IDS_COMMENT_MARKERS )));

		// Save the colors.
		SaveColor( pFile, pParser, _T( "Marker1RGB="),			CF_DEFAULT_MARKER_1, CARR_MARKER_1 );
		SaveColor( pFile, pParser, _T( "Marker2RGB="),			CF_DEFAULT_MARKER_2, CARR_MARKER_2 );
		SaveColor( pFile, pParser, _T( "Marker3RGB="),			CF_DEFAULT_MARKER_3, CARR_MARKER_3 );
		SaveColor( pFile, pParser, _T( "Marker4RGB="),			CF_DEFAULT_MARKER_4, CARR_MARKER_4 );
		SaveColor( pFile, pParser, _T( "Marker5RGB="),			CF_DEFAULT_MARKER_5, CARR_MARKER_5 );
		SaveColor( pFile, pParser, _T( "Marker1FgRGB="),		CF_DEFAULT_MARKER_FG_1, CARR_MARKER_FG_1 );
		SaveColor( pFile, pParser, _T( "Marker2FgRGB="),		CF_DEFAULT_MARKER_FG_2, CARR_MARKER_FG_2 );
		SaveColor( pFile, pParser, _T( "Marker3FgRGB="),		CF_DEFAULT_MARKER_FG_3, CARR_MARKER_FG_3 );
		SaveColor( pFile, pParser, _T( "Marker4FgRGB="),		CF_DEFAULT_MARKER_FG_4, CARR_MARKER_FG_4 );
		SaveColor( pFile, pParser, _T( "Marker5FgRGB="),		CF_DEFAULT_MARKER_FG_5, CARR_MARKER_FG_5 );
		SaveColor( pFile, pParser, _T( "BookmarkRGB=" ),		CF_DEFAULT_BOOKMARK, CARR_BOOKMARK );
		SaveColor( pFile, pParser, _T( "LineHighlightRGB="),		CF_DEFAULT_LINE_HIGHLIGHT, CARR_LINE_HIGHLIGHT );

		// Flags.
		pFile->PrintF( _T( "HighlightLine=%lc\n" ),	    pParser->bHighlightCurrentLine ? _T( 'Y' ) : _T( 'N' ));
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
LRESULT MarkersPage::OnCommand( UINT nNotifyCode, UINT nCtrlID, HWND hWndCtrl )
{
	// What's the message.
	switch ( nCtrlID )
	{
		case	IDC_HIGHLIGHT:
			// Store the checked state.
			m_pParser->bHighlightCurrentLine = ( BOOL )( m_Highlight.GetCheck() == BST_CHECKED );
			pSettings->Changed( m_pParser );
			break;

		case	IDC_MARKER:
			// Setup the color selection.
			if ( nNotifyCode == CBN_SELCHANGE )
			{
				m_FgColor.Color() = m_pParser->crColors[ CARR_MARKER_FG_1 + m_Marker.GetCurSel() ];
				m_FgColor.RedrawWindow();
				m_BkColor.Color() = m_pParser->crColors[ CARR_MARKER_1 + m_Marker.GetCurSel() ];
				m_BkColor.RedrawWindow();
				return 0;
			}
			break;

		case	IDC_FGCOLOR:
			// Save the color.
			if ( nNotifyCode == COLPN_COLORCHANGED )
			{
				m_pParser->crColors[ CARR_MARKER_FG_1 + m_Marker.GetCurSel() ] = m_FgColor.Color();
				pSettings->Changed( m_pParser );
			}
			return 0;

		case	IDC_BGCOLOR:
			// Save the color.
			if ( nNotifyCode == COLPN_COLORCHANGED )
			{
				m_pParser->crColors[ CARR_MARKER_1 + m_Marker.GetCurSel() ] = m_BkColor.Color();
				pSettings->Changed( m_pParser );
			}
			return 0;

		case	IDC_BGCOLOR_BM:
			// Save the color.
			if ( nNotifyCode == COLPN_COLORCHANGED )
			{
				m_pParser->crColors[ CARR_BOOKMARK ] = m_BkColorBM.Color();

				// Default?
				if ( m_BkColorBM.Color() == CLR_DEFAULT )
				{
					// Setup default.
					m_pParser->dwColorFlags |= CF_DEFAULT_BOOKMARK;
				}
				else
				{
					// Setup the color.
					m_pParser->dwColorFlags &= ~CF_DEFAULT_BOOKMARK;
				}
				pSettings->Changed( m_pParser );
			}
			return 0;

		case	IDC_BGCOLOR_CL:
			// Save the color.
			if ( nNotifyCode == COLPN_COLORCHANGED )
			{
				m_pParser->crColors[ CARR_LINE_HIGHLIGHT ] = m_BkColorCL.Color();
				
				// Default?
				if ( m_BkColorBM.Color() == CLR_DEFAULT )
				{
					// Setup default.
					m_pParser->dwColorFlags |= CF_DEFAULT_LINE_HIGHLIGHT;
				}
				else
				{
					// Setup the color.
					m_pParser->dwColorFlags &= ~CF_DEFAULT_LINE_HIGHLIGHT;
				}
				pSettings->Changed( m_pParser );
			}
			return 0;
		default:
			break;
	}				
	// Pass to the base class.
	return Page::OnCommand( nNotifyCode, nCtrlID, hWndCtrl );
}

// WM_INITDIALOG handler.
LRESULT MarkersPage::OnInitDialog( PROPSHEETPAGE * pPropSheetPage )
{
	// Attach controls.
	m_STHead.Attach( GetDlgItemHandle( IDC_MN_HEADER ));
	m_STHead2.Attach( GetDlgItemHandle( IDC_MN_HEADER2 ));
	m_STHead3.Attach( GetDlgItemHandle( IDC_MN_HEADER3 ));
	m_Marker.Attach( GetDlgItemHandle( IDC_MARKER ));
	m_FgColor.Attach( GetDlgItemHandle( IDC_FGCOLOR ));
	m_BkColor.Attach( GetDlgItemHandle( IDC_BGCOLOR ));
	m_BkColorBM.Attach( GetDlgItemHandle( IDC_BGCOLOR_BM ));
	m_BkColorCL.Attach( GetDlgItemHandle( IDC_BGCOLOR_CL ));

	// Setup the Checkboxes.
	m_Highlight.Attach( GetDlgItemHandle( IDC_HIGHLIGHT ));

	// Setup the color pickers.
	m_FgColor.DefaultString() = ClsString( MAKEINTRESOURCE( IDS_TRANSPARENT ));
	m_BkColor.DefaultString() = _T( "" );
	m_BkColorBM.DefaultString() = ClsString( MAKEINTRESOURCE( IDS_DEFAULT ));
	m_BkColorCL.DefaultString() = ClsString( MAKEINTRESOURCE( IDS_DEFAULT ));
	m_BkColorBM.DefaultColor() = RGB( 0, 255, 255 );
	m_FgColor.ShowToolTip();
	m_BkColor.ShowToolTip();
	m_BkColorBM.ShowToolTip();
	m_BkColorCL.ShowToolTip();
	m_FgColor.DropDownArrow() = TRUE;
	m_BkColor.DropDownArrow() = TRUE;
	m_BkColorBM.DropDownArrow() = TRUE;
	m_BkColorCL.DropDownArrow() = TRUE;
	if ( ! ThemingAPI.IsThemingEnabled())
	{
		m_FgColor.SetHotTrack( FALSE );
		m_BkColor.SetHotTrack( FALSE );
		m_BkColorBM.SetHotTrack( FALSE );
		m_BkColorCL.SetHotTrack( FALSE );
	}

	// Add combobox selections.
	m_Marker.AddString( _T( "1" ));
	m_Marker.AddString( _T( "2" ));
	m_Marker.AddString( _T( "3" ));
	m_Marker.AddString( _T( "4" ));
	m_Marker.AddString( _T( "5" ));

	// Preselect the first entry.
	m_Marker.SetCurSel( 0 );

	// Call the base-class.
	return Page::OnInitDialog( pPropSheetPage );
}