/********************************************************************\
*																							*
*										Time Handler									*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





/********************************************************************\
*																							*
*										Include Files									*
*																							*
\********************************************************************/
//#include	"mmsystem.h"
#include	HDR_FW_TIMER_MS





/********************************************************************\
*																							*
*											Class											*
*																							*
\********************************************************************/
CMicTimerMs::CMicTimerMs()
{
	my_start		= 0x00;
	my_current	= 0x00;
	my_delta		= 0x00;
	
	pParent		= 0x00;
}

CMicTimerMs::CMicTimerMs(LPVOID ptr)
:	my_start(0x00)
,	my_current(0x00)
,	my_delta(0x00)
,	pParent(ptr)
{
	return;
}

CMicTimerMs::~CMicTimerMs()
{
}





/********************************************************************\
*																							*
*										Period											*
*																							*
\********************************************************************/

//	Initialize the period timer.
FW_RESULT	CMicTimerMs::SetPeriod(double delta)
{
	RES_DECLR(result);

	my_delta		= delta;

	GetSystemTime(&StartTime);
	my_start	=	StartTime.wHour;
	my_start	*=	60;
	my_start	+=	StartTime.wMinute;
	my_start	*=	60;
	my_start	+=	StartTime.wSecond;
	my_start	*=	1000;
	my_start	+=	StartTime.wMilliseconds;
	
	RES_RETURN(result);
}

//	Check if still in period.
bool	CMicTimerMs::InPeriod(void)
{
	SYSTEMTIME		CurrentTime = {0};

	GetSystemTime(&CurrentTime);
	my_current	=	CurrentTime.wHour;
	my_current	*=	60;
	my_current	+=	CurrentTime.wMinute;
	my_current	*=	60;
	my_current	+=	CurrentTime.wSecond;
	my_current	*=	1000;
	my_current	+=	CurrentTime.wMilliseconds;

	return(my_delta > (my_current - my_start));
}










/********************************************************************\
*																							*
*										Interval											*
*																							*
\********************************************************************/
LPVOID CMicTimerMs::GetParent()
{
	return(pParent);
}


