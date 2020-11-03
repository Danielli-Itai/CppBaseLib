/*******************************************************************************
* lrtimer.cpp                                                                  *
*                                                                              *
* Written by Max Gurdziel 2005 under GNU General Public License                *
* contact me: max[at]remoteSOS[dot]com                                         *
*                                                                              *
* LRTimer is a low resolution timer class with own timing thread. It allows    *
*  an external callback function to be supplied that will be called in         *
*  pre-defined time intervals. The smallest timer interval you can use is 1ms. *
*                                                                              *
*  See header file for more info, usage information and example                *
*                                                                              *
*                                                                              *
*                                                                              *
* Permission to use, copy, modify, and distribute this software and its        *
* documentation under the terms of the GNU General Public License is hereby    *
* granted. No representations are made about the suitability of this software  *
* for any purpose. It is provided "as is" without express or implied warranty. *
* See http://www.gnu.org/copyleft/gpl.html for more details.                   *
*                                                                              *
* All I ask is that if you use LRTimer in your project you retain the          *
* copyright notice. If you have any comments and suggestions please email me   *
* max[at]remoteSOS[dot]com                                                     *
*                                                                              *
*******************************************************************************/
#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/Includes.h"





/********************************************************************\
*																							*
*									Include Files										*
*																							*
\********************************************************************/
#include HDR_FW_LRTIMER





//#define _WIN32_WINNT 0x0500


LRTimer::LRTimer():
	m_dwInterval(1000),
	m_bRunning(FALSE),
	m_bExitThred(TRUE),
  	m_pCallback(NULL),
	m_pv(NULL),
    m_hTimerThread(0) {}

LRTimer::~LRTimer()
{
}

VOID CALLBACK LRTimer::TimerAPCProc(LPVOID pVoid, DWORD dw1, DWORD dw2) 
{

	if (NULL != m_pCallback) 
	{
		(*m_pCallback)(m_pv, dw1, dw2);              // call custom callback function
	} 
	else 
	{
		printf("\nNo callback function set");
	}
}


DWORD WINAPI LRTimer::timerThread() 
{
	HANDLE          hTimer;
	BOOL            bSuccess;
	LARGE_INTEGER   liDueTime;
	TCHAR           szError[255];

	m_bExitThred = FALSE;

	if ( hTimer = CreateWaitableTimer(
		NULL,                   // Default security attributes
		FALSE,                  // Create auto-reset timer
		"LRTimer" ) )           // Name of waitable timer


		liDueTime.QuadPart=-(LONGLONG)m_dwInterval * _SECOND;

	bSuccess = SetWaitableTimer(
		hTimer,                            // Handle to the timer object
		&liDueTime, 						 // When timer will become signaled first time
		m_dwInterval,                      // Periodic timer interval
		TimerAPCProcAdapter,               // Completion routine
		this,                              // Argument to the completion routine
		FALSE );                           // Do not restore a suspended system


	if (bSuccess) 
	{
		while (m_bRunning)
			SleepEx(1, TRUE);
		CancelWaitableTimer(hTimer);
	} 
	else 
	{
		wsprintf( szError, "SetWaitableTimer failed with Error %d.", GetLastError() );
		MessageBox( NULL, szError, "Error", MB_ICONEXCLAMATION );
		m_bExitThred = TRUE;
		return 1;
	}
	CloseHandle(hTimer);
	m_bExitThred = TRUE;
	return 0;
}


VOID LRTimer::start()
{
	m_bRunning = TRUE;
	if (m_hTimerThread != 0)
	{
		stop();
	}
	m_hTimerThread = CreateThread(NULL, 0, timerThreadAdapter, this ,0,&m_iID);
	if (m_hTimerThread == NULL) 
	{
		printf( "\nCreateThread failed (%d)", GetLastError() );
		return;
	}
}

VOID LRTimer::start(DWORD _interval_ms) 
{
  setInterval(_interval_ms);
  start();
}

VOID LRTimer::stop() 
{
	m_bRunning = FALSE;
	Sleep(500);
	CloseHandle(m_hTimerThread);
	m_hTimerThread = 0;
}

VOID LRTimer::setInterval(DWORD _interval_ms)
{
	m_dwInterval = _interval_ms;
}

DWORD LRTimer::getInterval()
{
	return m_dwInterval;
}

VOID LRTimer::setCallbackFunction(VOID (*_pCallback)(PVOID,DWORD,DWORD), PVOID pv) 
{
	m_pCallback = _pCallback;
	m_pv = pv;
}

BOOL LRTimer::isRunning() 
{
  return m_bRunning;
}
