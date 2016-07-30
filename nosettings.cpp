//
//	NoSettings.cpp
//
//	(C) Copyright 2005 by Jan van den Baard.
//	    All Rights Reserved.
//

#include "bcc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Construction.
NoSettings::NoSettings()
{
}

// Destruction.
NoSettings::~NoSettings()
{
}

LRESULT NoSettings::OnInitDialog( LPPROPSHEETPAGE pPsp )
{
	// Setup browser control.
	m_Browser.Attach( GetDlgItemHandle( IDC_BROWSE ));
	return TRUE;
}

LRESULT NoSettings::OnCommand( UINT nNotifyCode, UINT nCtrlID, HWND hWndCtrl )
{
	// What's up.
	switch ( nCtrlID )
	{
		case	IDC_OK:
		{
			// Is anything selected?
			ClsString strPath, strErr;
			BOOL bEndDialog = FALSE;
			m_Browser.GetWindowText( strPath );
			if ( strPath.GetStringLength())
			{
				// Make sure it really is a directory.
				if ( ::PathFileExists( strPath ) && ( ::GetFileAttributes( strPath ) & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY )
				{
					// Create the key.
					ClsRegKey reg;
					if ( reg.CreateKey( HKEY_LOCAL_MACHINE, _T( "Software\\BCDLL\\CurrentVersion" )) == ERROR_SUCCESS )
					{
						// Add the string value relecting the settings directory.
						if ( reg.SetValue( strPath, _T( "Settings" )) == ERROR_SUCCESS )
						{
							// Create the "Defaults" directory.
							if ( strPath[ strPath.GetStringLength() - 1 ] != _T( '\\' ))
								strPath += _T( '\\' );
							ClsString strDir = strPath + _T( "Defaults" );

							// Create the defaults directory.
							if ( ::CreateDirectory( strDir, NULL ) == TRUE )
							{
								// Create the user directory.
								TCHAR szUser[ MAX_PATH ];
								DWORD dwLen = MAX_PATH;

								// Obtain user name and create it's directory.
								if ( ::GetUserName( szUser, &dwLen ))
								{
									strDir = strPath + szUser;
									if ( ::CreateDirectory( strDir, NULL ) == TRUE )
									{
										EndDialog( TRUE );
										return 0;
									}
									else
									{
										strErr = ClsString( MAKEINTRESOURCE( IDS_CREATEDIR ));
										bEndDialog = TRUE;
									}
								}
								else
								{
									strErr = ClsString( MAKEINTRESOURCE( IDS_CREATEDIR ));
									bEndDialog = TRUE;
								}
							}
							else
							{
								strErr = ClsString( MAKEINTRESOURCE( IDS_CREATEDIR ));
								bEndDialog = TRUE;
							}
						}
						else
						{
							strErr = ClsString( MAKEINTRESOURCE( IDS_NOREGISTRY ));
							bEndDialog = TRUE;
						}
					}
					else
					{
						strErr = ClsString( MAKEINTRESOURCE( IDS_NOREGISTRY ));
						bEndDialog = TRUE;
					}
				}
				else
					strErr = ClsString( MAKEINTRESOURCE( IDS_NODIRECTORY ));
			}
			else
				strErr = ClsString( MAKEINTRESOURCE( IDS_ENTERDIRECTORY ));

			MessageBox( strErr, ClsGetApp()->GetAppTitle(), MB_ICONERROR | MB_OK );
			if ( bEndDialog ) EndDialog( FALSE );
			return 0;
		}

		case	IDC_CANCEL:
			EndDialog( FALSE );
			return 0;
	}

	// Pass onto the base class.
	return ClsDialog::OnCommand( nNotifyCode, nCtrlID, hWndCtrl );
}

// Open the block editor.
BOOL NoSettings::SelectSettingsDirectory( ClsWindow& Parent )
{
	// Open the dialog.
	return DoModal( Parent, IDD_NOSETTINGS );
}
