﻿//
// DlgSettingsManager.h
//
// This file is part of PeerProject (peerproject.org) � 2008-2010
// Portions copyright Shareaza Development Team, 2002-2007.
//
// PeerProject is free software. You may redistribute and/or modify it
// under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation (fsf.org);
// version 3 or later at your option. (AGPLv3)
//
// PeerProject is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Affero General Public License 3.0 for details:
// (http://www.gnu.org/licenses/agpl.html)
//

#pragma once

#include "WndSettingsSheet.h"


class CSettingsManagerDlg : public CSettingsSheet {
    DECLARE_DYNAMIC(CSettingsManagerDlg)

public:
    CSettingsManagerDlg(CWnd *pParent = NULL);

public:
    INT_PTR	DoModal(LPCTSTR pszWindow = NULL);

    static BOOL Run(LPCTSTR pszWindow = NULL);
    static void OnSkinChange(BOOL bSet);
    static CSettingsManagerDlg *m_pThis;

protected:
    void		AddPage(CSettingsPage *pPage);
    void		AddGroup(CSettingsPage *pPage);

protected:
    virtual void DoDataExchange(CDataExchange *pDX);

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnApply();

    DECLARE_MESSAGE_MAP()
};
