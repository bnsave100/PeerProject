﻿//
// UploadFiles.h
//
// This file is part of PeerProject (peerproject.org) � 2008-2014
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

class CUploadFile;
class CUploadTransfer;


class CUploadFiles {
public:
    CUploadFiles();
    virtual ~CUploadFiles();

protected:
    CList< CUploadFile * >	m_pList;

public:
    void			Clear();
    CUploadFile	*GetFile(CUploadTransfer *pUpload, const Hashes::Sha1Hash &oSHA1, LPCTSTR pszName, LPCTSTR pszPath, QWORD nSize);
    void			Remove(CUploadTransfer *pTransfer);
    void			MoveToHead(CUploadTransfer *pTransfer);
    void			MoveToTail(CUploadTransfer *pTransfer);

    // List Access
public:
    inline POSITION GetIterator() const {
        return m_pList.GetHeadPosition();
    }

    inline CUploadFile *GetNext(POSITION &pos) const {
        return m_pList.GetNext( pos );
    }

    inline INT_PTR GetCount() const {
        return m_pList.GetCount();
    }

    inline BOOL Check(CUploadFile *pFile) const {
        return m_pList.Find( pFile ) != NULL;
    }
};

extern CUploadFiles UploadFiles;
