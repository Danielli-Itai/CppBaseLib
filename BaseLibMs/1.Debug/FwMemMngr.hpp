#ifndef FW_MEMNGR_HPP
#define	FW_MEMNGR_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





	/**********************************************************************\
	*																								*
	*										Include Files										*
	*																								*
	\**********************************************************************/
	#include	HDR_FW_RESULT
	#include	HDR_FW_STRING





	/********************************************************************\
	*																							*
	*										Memory Manager									*
	*																							*
	\********************************************************************/
	#define	ALLOC_TBL_SIZE		1000
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

#endif // !FW_MEMNGR_HPP
