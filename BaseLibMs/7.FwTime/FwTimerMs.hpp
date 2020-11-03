/********************************************************************\
*																							*
*										Time Handler									*
*																							*
\********************************************************************/
#ifndef MIC_TIMER_MS_H
#define MIC_TIMER_MS_H
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/********************************************************************\
	*																							*
	*										Include Files									*
	*																							*
	\********************************************************************/
	#include	HDR_MIC_TIME




	/********************************************************************\
	*																							*
	*										Class												*
	*																							*
	\********************************************************************/

	class CMicTimerMs
	{  
		public:				CMicTimerMs();
		public:				CMicTimerMs(LPVOID ptr);
		public:	virtual	~CMicTimerMs();
	
		public:	double		my_start;
		public:	double		my_current;
		public:	double		my_delta;
		public:	SYSTEMTIME	StartTime;

		public:	FW_RESULT		SetPeriod(double delta);
		public:	FW_RESULT		InPeriod(void);

		private:	LPVOID		pParent;
		public:	LPVOID		GetParent(void);
	};
#endif // TIME_HANDLER_H
