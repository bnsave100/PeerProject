/*
 * This is a part of the BugTrap package.
 * Copyright (c) 2005-2009 IntelleSoft.
 * All rights reserved.
 *
 * Description: About dialog.
 * Author: Maksim Pyatkovskiy.
 */

#include "StdAfx.h"
#include "Resource.h"
#include "AboutDlg.h"
#include "BugTrapUI.h"
#include "BugTrapUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
 * @addtogroup BugTrapUI BugTrap Graphical User Interface
 * @{
 */

/// E-mail hyper-link control.
static CHyperLink g_hlURL;

/**
 * @brief WM_COMMAND handler of About dialog.
 * @param hwnd - window handle.
 * @param id - control ID.
 * @param hwndCtl - control handle.
 * @param codeNotify - notification code.
 */
static void AboutDlg_OnCommand(HWND hwnd, int id, HWND /*hwndCtl*/, UINT /*codeNotify*/) {
    /* codeNotify; hwndCtl; */
    switch (id) {
    case IDOK:
    case IDCANCEL:
        EndDialog(hwnd, FALSE);
        break;
    }
}

/**
 * @brief WM_INITDIALOG handler of About dialog.
 * @param hwnd - window handle.
 * @param hwndFocus - system-defined focus window.
 * @param lParam - user-defined parameter.
 * @return true to setup focus to system-defined control.
 */
static BOOL AboutDlg_OnInitDialog(HWND hwnd, HWND /*hwndFocus*/, LPARAM /*lParam*/) {
    /* lParam; hwndFocus; */
    CenterWindow(hwnd, GetParent(hwnd));
    HWND hwndCtl = GetDlgItem(hwnd, IDCANCEL);
    SetFocus(hwndCtl);
    hwndCtl = GetDlgItem(hwnd, IDC_URL);
    TCHAR szLinkURL[MAX_PATH];
    GetWindowText(hwndCtl, szLinkURL, countof(szLinkURL));
    g_hlURL.SetLinkURL(szLinkURL);
    g_hlURL.Attach(hwndCtl);
    return FALSE;
}

/**
 * @brief WM_DESTROY handler of About dialog.
 * @param hwnd - window handle.
 */
static void AboutDlg_OnDestroy(HWND /*hwnd*/) {
    /* hwnd; */
    g_hlURL.Detach();
}

/**
 * @brief Dialog procedure of About dialog.
 * @param hwndDlg - window handle.
 * @param uMsg - message identifier.
 * @param wParam - 1st message parameter.
 * @param lParam - 2nd message parameter.
 * @return message result.
 */
INT_PTR CALLBACK AboutDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        HANDLE_MSG(hwndDlg, WM_INITDIALOG, AboutDlg_OnInitDialog);
        HANDLE_MSG(hwndDlg, WM_COMMAND, AboutDlg_OnCommand);
        HANDLE_MSG(hwndDlg, WM_DESTROY, AboutDlg_OnDestroy);
    default:
        return FALSE;
    }
}

/** @} */
