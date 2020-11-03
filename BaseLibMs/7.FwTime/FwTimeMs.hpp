/********************************************************************\
*																							*
*										Time Handler									*
*																							*
\********************************************************************/
#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/********************************************************************\
	*																							*
	*										Include Files									*
	*																							*
	\********************************************************************/
	//#include	HDR_STDAFX
	#include	HDR_FW_RESULT
	#include	HDR_FW_STRING





	/********************************************************************\
	*																							*
	*										Definitions										*
	*																							*
	\********************************************************************/
	#define	MIC_TIME					CTime
	#define	MIC_DURATION			CTimeSpan

	#define	DATE_TIME_FORMAT		_T("%d/%m/%Y %H:%M:%S")
	#define	DATE_TIME_PARSING		_T("%d/%d/%d %d:%d:%d")
	#define	PERIOD_PARSING			_T("%d %d:%d:%d")
	#define	PERIOD_FORMATTING		_T("%d %d:%d:%d")




	/********************************************************************\
	*																							*
	*										Functions										*
	*																							*
	\********************************************************************/
	STRING	DateTimeToString(CTime time);
	CTime		DateTimeToTime(STRING sTime);





	/********************************************************************\
	*																							*
	*										Class												*
	*																							*
	\********************************************************************/
	#define	DURATION		CTimeSpan
	class CMicTime
	{
		public:				CMicTime();
		public:				CMicTime(STRING time);
		public:	virtual	~CMicTime();

		public:	double		my_start;
		public:	double		my_current;
		public:	double		my_delta;
		public:	SYSTEMTIME	StartTime;

		public:	FW_RESULT		SetPeriod(double delta);
	//	public:	FW_RESULT		InPeriod(void);

		private:	CTime			TimeCurrent;
		private:	CTime			TimeLast;
		private:	CTimeSpan	TimeDelta; 
		private:	CTimeSpan	TimeInterval;
		public:	FW_RESULT		IntervalTime(int Hou, int Min, int Sec);
		public:	FW_RESULT		IntervalTimeInit(void);
		public:	bool			IntervalFlagChck(void);

		private:	CTime			my_Time; 	
		public:	CTime			Time();
		public:	void			TimeClear();
		public:	STRING		TimeGet(void);
		public:	FW_RESULT		TimeUpdate();

		public:	FW_RESULT		TimeSet(CTime sTime);
		public:	FW_RESULT		TimeSet(STRING sTime);
		public:	FW_RESULT		TimeCheck(void);
		public:	CTimeSpan	TimePassed(void);
		public:	STRING		TimePassedGet(void);
		public:	STRING		TimeEndGet();


		private:	CTimeSpan	my_Duration;
		public:	CTimeSpan	Duration();
		public:	FW_RESULT		Duration(CTimeSpan duration);
		public:	FW_RESULT		Duration(int days, int Hou, int Min, int Sec);
		public:	FW_RESULT		Duration(STRING per);
		public:	FW_RESULT		DurationAdd(STRING per);
		public:	STRING 		DurationGet();
		public:	FW_RESULT		InPeriod(void);
		public:	void			DurationCear();

		public:	void			Clear(void);

		public:	static	STRING	TimeGet(MIC_TIME time);
		public:	static	STRING	TimeCurrGet(void);
	};
#endif // TIME_HANDLER_H

