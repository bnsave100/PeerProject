//
// PageComment.h
//
// This file is part of PeerProject Torrent Wizard (peerproject.org) � 2008,2012-2014
// Portions Copyright Shareaza Development Team, 2007.
//
// PeerProject Torrent Wizard is free software; you can redistribute it
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or later version (at your option).
//
// Torrent Wizard is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 3.0
// along with PeerProject; if not, write to Free Software Foundation, Inc.
// 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA  (www.fsf.org)
//

#pragma once

#include "WizardSheet.h"


class CCommentPage : public CWizardPage {
    DECLARE_DYNCREATE(CCommentPage)

    // Construction
public:
    CCommentPage();
    //virtual ~CCommentPage();

    enum { IDD = IDD_COMMENT_PAGE };

    // Dialog Data
public:
    CString	m_sComment;
    //	CString	m_sSource;
    BOOL	m_bPrivate;

    // Operations
protected:
    void SaveComments();

    // Overrides
protected:
    virtual BOOL OnInitDialog();
    virtual void OnReset();
    virtual BOOL OnSetActive();
    virtual LRESULT OnWizardBack();
    virtual LRESULT OnWizardNext();

    virtual void DoDataExchange(CDataExchange *pDX);

    // Implementation
protected:
    afx_msg void OnXButtonDown(UINT nFlags, UINT nButton, CPoint point);

    DECLARE_MESSAGE_MAP()
};
