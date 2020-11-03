/********************************************************************\
*																							*
*										Memory Manager									*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"




/********************************************************************\
*																							*
*										Include files									*
*																							*
\********************************************************************/
#include	HDR_FW_POINTERS
#include	HDR_FW_MEMNGR





CMemAlloc::CMemAlloc(STRING file, int line, void* pObject)
{
	my_file = file;
	my_line = line;
	my_pObject = pObject;
	return;
}


CMemManager::CMemManager()
{
	for(int i= 0x00; i<ALLOC_TBL_SIZE; i++){
		PTR_INIT(alloc_table[i]); 
	}
	return;
}

FW_RESULT	CMemManager::CMemAdd(STRING file, int line, void* pObject)
{
	RES_DECLR(result);

	RES_FAILE(result)
	for(int i= 0x00;(false == result)&&(i<ALLOC_TBL_SIZE); i++){
		if(PTR_IS_NULL(alloc_table[i])){
			PTR_SET(alloc_table[i],new CMemAlloc(file, line, (void*)pObject));
			RES_SUCCESS(result);
		}
	}
	RES_RETURN(result);
}

FW_RESULT	CMemManager::CMemClear(STRING file, int line, void* pObject)
{
	RES_DECLR(result);
	for(int i= 0x00; i<ALLOC_TBL_SIZE; i++){
		if(alloc_table[i] == pObject){
			PTR_INIT(alloc_table[i]);
			RES_SUCCESS(result);
		}
	}
	RES_RETURN(result);
}
CMemManager::~CMemManager()
{
	RES_DECLR(result);

	for(int i= 0x00; i<ALLOC_TBL_SIZE; i++){
		if(PTR_NOT_NULL(alloc_table[i])){
			RES_FAILE(result);
		}
	}
	//RES_ALERT(result);
}











	/***********************************************************************\
	*																								*
	*										Object managment									*
	*																								*
	\***********************************************************************/
CMemManager	MemManager;

bool	FW_Malloc(void** pointer, int size)
{
	bool	result = true;

	if(NULL == (*pointer))	{
		(*pointer) = malloc(size);
		if(NULL == (*pointer)){
			RES_FAILE(result);
		}
		else{
			if(NULL == memset((*pointer),0,size)){
				RES_FAILE(result);
			}
		}
	}
	else{
		result = false;
	}
	return(result);
}

bool	FW_Free(void** pointer)
{
	bool	result = true;
	if(NULL != (*pointer))	{
		delete (*pointer);
		(*pointer) = NULL;
	}
	else{
		result = false;
	}
	return(result);
}




