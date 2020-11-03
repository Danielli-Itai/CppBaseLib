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
#include <time.h>
//#include	"mmsystem.h"
#include	HDR_FW_BASE_TYPES
#include	HDR_MIC_TIME





/********************************************************************\
*																							*
*										Functions										*
*																							*
\********************************************************************/
STRING DateTimeToString(CTime time)
{
	STR_RETURN(time.Format(DATE_TIME_FORMAT));
}

CTime DateTimeToTime(STRING sTime)
{
	CTime time;
	RES_DECLR(result);
	COleDateTime oletime;
	RES_CHECK(result, oletime.ParseDateTime(STR_PBUFF(sTime)));
	if (RES_TRUE(result))
	{
		SYSTEMTIME sysTime;
		RES_CHECK(result, oletime.GetAsSystemTime(sysTime));
		if (RES_TRUE(result))
		{
			time = CTime(sysTime);
		}
	}
	return time;
}





/********************************************************************\
*																							*
*											Class											*
*																							*
\********************************************************************/

CMicTime::CMicTime()
{
	my_Time	= 0x00;
	my_Duration	= 0x00;
}
CMicTime::CMicTime(STRING time)
{
	RES_ALERT(TimeSet(time));
}
CMicTime::~CMicTime()
{
}





/********************************************************************\
*																							*
*										Period											*
*																							*
\********************************************************************/

//	Initialize the period timer.
FW_RESULT	CMicTime::SetPeriod(double delta)
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
//bool	CMicTime::InPeriod(void)
//{
//	SYSTEMTIME		CurrentTime = {0};
//
//	GetSystemTime(&CurrentTime);
//	my_current	=	CurrentTime.wHour;
//	my_current	*=	60;
//	my_current	+=	CurrentTime.wMinute;
//	my_current	*=	60;
//	my_current	+=	CurrentTime.wSecond;
//	my_current	*=	1000;
//	my_current	+=	CurrentTime.wMilliseconds;
//
//	return(my_delta > (my_current - my_start));
//}




/********************************************************************\
*																							*
*										Interval											*
*																							*
\********************************************************************/

FW_RESULT CMicTime::IntervalTime(int Hou, int Min, int Sec)
{
	RES_DECLR(result);

	RES_CHECK(result,(Hou >= 0x00) && (Hou <= 23));
	RES_CHECK(result,(Min >= 0x00) && (Min <= 59));
	RES_CHECK(result,(Sec >= 0x00) && (Sec <= 59));

	CTimeSpan tmpTimeSpan( 0, Hou, Min, Sec );
	TimeInterval = tmpTimeSpan;

	RES_RETURN(result);
}


bool CMicTime::IntervalFlagChck()
{
	bool in_interval = true;
	
	TimeCurrent = CTime::GetCurrentTime();
	TimeDelta = TimeCurrent - TimeLast;
	
	if(TimeDelta>TimeInterval){
		in_interval  = true;
	}
	else{
		in_interval  = false;
	}

	return(in_interval);
}

FW_RESULT CMicTime::IntervalTimeInit()
{
	TimeLast = CTime::GetCurrentTime();
	return(TRUE);
}






/********************************************************************\
*																							*
*											Time											*
*																							*
\********************************************************************/

CTime CMicTime::Time()
{
	RETURN(my_Time);
}

void CMicTime::TimeClear()
{
	my_Time	= 0x00;
}

STRING CMicTime::TimeGet(void)
{
	STR_RETURN(my_Time.Format(DATE_TIME_FORMAT));
}

FW_RESULT CMicTime::TimeUpdate()
{
	my_Time = CTime::GetCurrentTime();
	RES_RETURN(my_Time != 0x00);
}

FW_RESULT CMicTime::TimeSet(CTime sTime)
{
	my_Time = sTime;
	RES_RETURN(my_Time != 0x00);
}

FW_RESULT CMicTime::TimeSet(STRING sTime)
{
	RES_DECLR(result);

	int wDay = 0x00, wMonth = 0x00, wYear = 0x00, wHour =0x00, wMinute = 0x00, wSecond = 0x00;
	sscanf_s(STR_PBUFF(sTime), DATE_TIME_PARSING, &wDay, &wMonth, &wYear, &wHour, &wMinute, &wSecond);

	if((0x00!=wDay) || (0x00!=wMonth)||(0x00!=wYear)||(0x00!=wHour)||(0x00!=wMinute)||(0x00!=wSecond)) 
	{
		RES_CHECK(result, ((wDay >= 1)		&& (wDay		<= 31)));
		RES_CHECK(result, ((wMonth >= 1)		&& (wMonth	<= 12)));
		RES_CHECK(result, ((wYear >= 1900)	&& (wYear	< 3000)));

		RES_CHECK(result, ((wHour >= 0x00)	&& (wHour < 24)));
		RES_CHECK(result, ((wMinute >= 0x00) && (wMinute < 60)));
		RES_CHECK(result, ((wSecond >= 0x00) && (wSecond < 60)));
	}
	SYSTEMTIME	StartTime = {   wYear, wMonth, 0, wDay, wHour, wMinute, wSecond, 0x00 /*wMilliseconds*/	};
	my_Time = StartTime;

	RES_RETURN(result);
}

STRING CMicTime::TimeCurrGet(void)
{
	CTime	TimeCurrent = CTime::GetCurrentTime();
	STR_RETURN(TimeCurrent.Format(DATE_TIME_FORMAT));
}

bool CMicTime::TimeCheck(void)
{
	CTime	TimeCurrent = CTime::GetCurrentTime();
	STR_RETURN(my_Time < TimeCurrent);
}

CTimeSpan CMicTime::TimePassed(void)
{
	CTimeSpan	TimeSpan =  CTime::GetCurrentTime() - my_Time;
	RETURN(TimeSpan);
}

STRING	CMicTime::TimePassedGet(void)
{
	CTimeSpan	TimeSpan =  TimePassed();
	STR_RETURN(TimeSpan.Format(PERIOD_FORMATTING));
}


STRING CMicTime::TimeEndGet()
{
	CTime	TimeEnd =  my_Time;
	TimeEnd += my_Duration;
	STR_RETURN(TimeEnd.Format(DATE_TIME_FORMAT));
}










/********************************************************************\
*																							*
*										Period											*
*																							*
\********************************************************************/
CTimeSpan	CMicTime::Duration()
{
	RETURN(my_Duration);
}

FW_RESULT	CMicTime::Duration(CTimeSpan	duration)
{
	RES_DECLR(result);

	my_Duration = duration;
	RES_CHECK(result, my_Duration.GetTimeSpan() != 0x00);

	RES_RETURN(result);
}

//	Initialize the period timer.
FW_RESULT	CMicTime::Duration(int days, int Hou, int Min, int Sec)
{
	RES_DECLR(result);

	RES_CHECK(result,(days >= 0x00) && (days <= FW_UINT_MAX));
	RES_CHECK(result,(Hou >= 0x00) && (Hou < 24));
	RES_CHECK(result,(Min >= 0x00) && (Min < 60));
	RES_CHECK(result,(Sec >= 0x00) && (Sec < 60));

	CTimeSpan tmpTimeSpan(days, Hou, Min, Sec );
	my_Duration = tmpTimeSpan;

	RES_RETURN(result);
}


FW_RESULT	CMicTime::Duration(STRING duration)
{
	RES_DECLR(result);

	int wDays=0x00, wHour =0x00, wMinute = 0x00, wSecond = 0x00;
	sscanf_s(STR_PBUFF(duration), PERIOD_PARSING, &wDays, &wHour, &wMinute, &wSecond);
	RES_CHECK(result,Duration(wDays, wHour, wMinute, wSecond));

	RES_RETURN(result);
}

FW_RESULT	CMicTime::DurationAdd(STRING duration)
{
	RES_DECLR(result);

	CTimeSpan  current = my_Duration;

	RES_CHECK(result,Duration(duration));
	my_Duration = my_Duration + current;

	RES_RETURN(result);
}

STRING 	CMicTime::DurationGet()
{
	STR_DECLR(duration);
	int days= (int)my_Duration.GetDays();
	int hrs = my_Duration.GetHours();
	int min = my_Duration.GetMinutes();
	int sec = my_Duration.GetSeconds();
	STR_FORMAT(duration, PERIOD_FORMATTING, (days, hrs, min, sec));
	STR_RETURN(duration);
}

//	Check if still in period.
bool	CMicTime::InPeriod(void)
{
	CTime	TimeCurrent = CTime::GetCurrentTime();
	CTimeSpan TimeDelta = TimeCurrent - my_Time;
	return(TimeDelta < my_Duration);
}

void	CMicTime::DurationCear()
{
	my_Duration = 0x00;
}






void CMicTime::Clear(void)
{
	my_Time = 0x00;
	my_Duration = 0x00;
}





STRING	CMicTime::TimeGet(MIC_TIME time)
{
	STR_RETURN(time.Format(DATE_TIME_FORMAT));
}


