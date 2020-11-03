#ifndef CONFIG_H
#define CONFIG_H





	#ifndef SIMULATION
		#define	SIMULATION
	#endif // !SIMULATION










	 /***********************************************************************\
	 *																								*
	 *									A p p l i c a t i o n s								*
	 *																								*
	 \***********************************************************************/
	#ifndef	FW_RES_ENABLED
		 #define	FW_RES_ENABLED
	#endif
	#ifndef FW_LOG
		#define	FW_LOG
	#endif // !FW_LOG
	#ifndef FW_THREADS
		//#define	FW_THREADS
	#endif // !FW_LOG




	#ifdef _MSC_VER
		#define	VS_BUILD
		//#define	snprintf		_snprintf
		//#define	__attribute__
		#define	aligned
	#endif

	#ifndef TIXML_USE_STL
		#define	TIXML_USE_STL
	#endif // !TIXML_USE_STL

	#ifndef DINI_API
		#define DINI_API
	#endif  /*DINI_API*/

	#ifndef WIN_WDM
		#define	WIN_WDM
	#endif // !WIN_WDM

	#ifndef _CRT_SECURE_NO_WARNINGS
		#define	_CRT_SECURE_NO_WARNINGS
	#endif // !_CRT_SECURE_NO_WARNINGS

	#ifndef SUPPORT_ALL
		#define	SUPPORT_ALL
	#endif // !SUPPORT_ALL

	#ifndef PCIEDIRECT
		#define	PCIEDIRECT
	#endif // !PCIEDIRECT

	#ifndef EMU_STANDALONE_LIBRARY
		// #define EMU_STANDALONE_LIBRARY
	#endif

	#ifndef SYSTENC_AS_SLAVE
		//#define	SYSTENC_AS_SLAVE
	#endif // !SYSTENC_AS_SLAVE
#endif // _FW_CONFIG_H
