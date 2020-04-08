﻿//
// Datagrams.h
//
// This file is part of PeerProject (peerproject.org) � 2008-2015
// Portions copyright Shareaza Development Team, 2002-2008.
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

#define DATAGRAM_HASH_SIZE	32
#define DATAGRAM_HASH_MASK	31

#define SGP_TAG_1			"SGP"
#define SGP_TAG_2			"GND"
#define SGP_DEFLATE			0x01
#define SGP_ACKNOWLEDGE		0x02

#pragma pack(push,1)

typedef struct {
    CHAR	szTag[3];
    BYTE	nFlags;
    WORD	nSequence;
    BYTE	nPart;
    BYTE	nCount;
} SGP_HEADER;

#pragma pack(pop)

typedef struct {
    DWORD	nTotal;
    DWORD	tLast;
    DWORD	nMeasure;
    DWORD	pHistory[24];
    DWORD	pTimes[24];
    DWORD	nPosition;
    DWORD	tLastAdd;
    DWORD	tLastSlot;
} UDPBandwidthMeter;

class CBuffer;
class CDatagramIn;
class CDatagramOut;
class CPacket;


class CDatagrams {
public:
    CDatagrams();
    ~CDatagrams();

public:
    DWORD			m_nInBandwidth;
    DWORD			m_nInFrags;
    DWORD			m_nInPackets;
    DWORD			m_nOutBandwidth;
    DWORD			m_nOutFrags;
    DWORD			m_nOutPackets;

protected:
    SOCKET			m_hSocket;
    WORD			m_nSequence;
    BOOL			m_bStable;
    DWORD			m_tLastWrite;

    UDPBandwidthMeter	m_mInput;
    UDPBandwidthMeter	m_mOutput;

    DWORD			m_nBufferBuffer;	// Number of output buffers (Settings.Gnutella2.UdpBuffers)
    CBuffer		*m_pBufferBuffer;	// Output buffers
    CBuffer		*m_pBufferFree;		// List of free output buffers
    DWORD			m_nBufferFree;		// Number of free output buffer items in list

    DWORD			m_nInputBuffer;
    CDatagramIn	*m_pInputBuffer;
    CDatagramIn	*m_pInputFree;
    CDatagramIn	*m_pInputFirst;
    CDatagramIn	*m_pInputLast;
    CDatagramIn	*m_pInputHash[ DATAGRAM_HASH_SIZE ];

    DWORD			m_nOutputBuffer;
    CDatagramOut	*m_pOutputBuffer;
    CDatagramOut	*m_pOutputFree;
    CDatagramOut	*m_pOutputFirst;
    CDatagramOut	*m_pOutputLast;
    CDatagramOut	*m_pOutputHash[ DATAGRAM_HASH_SIZE ];

private:
    // Buffer for current incoming UDP packet. It's global since
    // CDatagrams processes one packet at once only. Maximum UDP size 64KB.
    BYTE		m_pReadBuffer[ 65536 ];

public:
    BOOL	Listen();
    void	Disconnect();

    // True if the socket is valid, false if closed
    inline BOOL IsValid() const {
        return ( m_hSocket != INVALID_SOCKET );
    }

    // Avoid using this function directly, use !Network.IsFirewalled(CHECK_UDP) instead
    inline BOOL IsStable() const {
        return IsValid() && m_bStable;
    }

    inline void SetStable(BOOL bStable = TRUE) {
        m_bStable = bStable;
    }

    BOOL	Send(const IN_ADDR *pAddress, WORD nPort, CPacket *pPacket, BOOL bRelease = TRUE, LPVOID pToken = NULL, BOOL bAck = TRUE);
    BOOL	Send(const SOCKADDR_IN *pHost, CPacket *pPacket, BOOL bRelease = TRUE, LPVOID pToken = NULL, BOOL bAck = TRUE);
    void	PurgeToken(LPVOID pToken);
    void	OnRun();

protected:
    BOOL	TryRead();
    BOOL	TryWrite();
    void	Measure();
    void	ManageOutput();
    void	Remove(CDatagramOut *pDG);
    void	Remove(CDatagramIn *pDG, BOOL bReclaimOnly = FALSE);
    void	ManagePartials();

    BOOL	OnDatagram(const SOCKADDR_IN *pHost, const BYTE *pBuffer, DWORD nLength);
    BOOL	OnReceiveSGP(const SOCKADDR_IN *pHost, const SGP_HEADER *pHeader, DWORD nLength);
    BOOL	OnAcknowledgeSGP(const SOCKADDR_IN *pHost, const SGP_HEADER *pHeader, DWORD nLength);
};

extern CDatagrams Datagrams;
