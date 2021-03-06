#undef new
#ifndef _BCC_H_
#define _BCC_H_
//
//	bcc.h 
//
//	(C) Copyright 1999-2002 by Jan van den Baard
//	    All Rights Reserved.
//
//	Brainchild configurator definitions.
//
#include <classes/all.h>
#include <shlwapi.h>
#include <cpl.h>

#include "resource.h"
#include "defs.h"  

// Keywords are converted into
// the following format in the
// keywords.cpp module..
typedef struct tagKeyword
{
	struct tagKeyword	*lpNext;
	struct tagKeyword	*lpPrev;
	COLORREF		 crColor;
	COLORREF		 crBgColor;
	LPARRAY			 lpaKeywords;
} KEYWORDS, FAR *LPKEYWORDS;

typedef struct tagKeyList
{
	LPKEYWORDS		lpFirst;
	LPKEYWORDS		lpEndMark;
	LPKEYWORDS		lpLast;
} KEYLIST, FAR *LPKEYLIST;

#include "list.h"
#include "page.h"
#include "toolbar.h"
#include "treeview.h"
#include "colorlist.h"
#include "optiontree.h"
#include "block.h"
#include "classname.h"
#include "keywords.h"
#include "kwedit.h"
#include "keyrec.h"
#include "hardcoded.h"
#include "insertedit.h"
#include "run.h"
#include "about.h"
#include "printer.h"
#include "general.h"
#include "datetime.h"
#include "files.h"
#include "syntax.h"
#include "indent.h"
#include "keyboard.h"
#include "comments.h"
#include "markers.h"
#include "main.h"
#include "nosettings.h"

// CPL version information.
#define BCC_VERSION	2
#define BCC_REVISION	6

// global data.
extern POOL		pParserPool;
extern PARSERLIST	plParsers;
extern SettingsDialog  *pSettings;

#endif