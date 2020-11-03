#ifndef MEM_MNGR_MS_HPP
#define	MEM_MNGR_MS_HPP
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/**********************************************************************\
	*																								*
	*										Include Files										*
	*																								*
	\**********************************************************************/
	#include	HDR_FW_RESULT
	#include	HDR_FW_STRING





	bool	FW_Malloc(void** pointer, int size);
	bool	FW_Free(void** pointer);





	/********************************************************************\
	*																							*
	*										Defenitions										*
	*																							*
	\********************************************************************/
	#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif

	#define	ALLOC_TBL_SIZE		1000

	#define	MMNGR_DCLR				\
		CMemManager*	pMemManager	\
		/*MMNGR_DCLR*/

	#define	MMNGR_CONSTRUCT				\
		pMemManager = new CMemManager()	\
		/*MMNGR_CONSTRUCT*/

	#define	MMNGR_ADD(P_OBJECT)									\
		pMemManager->CMemAdd(__FILE__, __LINE__, P_OBJECT)	\
		/*MMNGR_ADD*/

	#define	MMNGR_CLEAR(P_OBJECT)									\
		pMemManager->CMemClear(__FILE__, __LINE__, P_OBJECT)	\
		/*MMNGR_ADD*/

	#define	MMNGR_DISTRUCT	\
		delete pMemManager	\
		/*MMNGR_DISTRUCT*/





	/********************************************************************\
	*																							*
	*										Memory Manager									*
	*																							*
	\********************************************************************/

	class	CMemAlloc
	{
		STRING	my_file;
		int		my_line;
		void*		my_pObject;

		public:	CMemAlloc(STRING file, int line, void* pObject);
	};

	class	CMemManager
	{
		CMemAlloc*	alloc_table[ALLOC_TBL_SIZE];
		public:	CMemManager();
		public:	virtual ~CMemManager();
		public:	FW_RESULT	CMemAdd(STRING file, int line, void* pObject);
		public:	FW_RESULT	CMemClear(STRING file, int line, void* pObject);
	};





#endif // !MEM_MNGR_MS_HPP
