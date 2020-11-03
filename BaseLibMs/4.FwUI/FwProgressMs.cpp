/**************************************************************************\
*																									*
*										Progress Callback										*
*																									*
\**************************************************************************/
#include "../../../0.Framework/BaseLibMs/0.Config/Config.h"
#include "../../../0.Framework/BaseLibMs/0.Config/Includes.h"





	/**************************************************************************\
	*																									*
	*										Include Files											*
	*																									*
	\**************************************************************************/
	#include	<list>
	#include	HDR_FW_DEBUGGING
	#include HDR_FW_PROGRESS





	/***********************************************************************\
	*																								*
	*										Progress Callback									*
	*																								*
	\***********************************************************************/
	PTR_DECLR(ProgressCb, pProgressCb);

	FW_RESULT ProgressCbClr(ProgressCb pCb)
	{
		PTR_CLR(pProgressCb);
		RES_RETURN(RES_OK);
	}

	FW_RESULT ProgressCbSet(ProgressCb pCb)
	{
		RES_DECLR(result);

		RES_CHECK(result, PTR_IS_NULL(pProgressCb));
		if(RES_TRUE(result)){
			PTR_SET(pProgressCb, pCb);
		}
		RES_RETURN(result);
	}

	FW_RESULT ProgressCbCall(STRING message, int val, int max)
	{
		RES_DECLR(result);

		RES_CHECK(result, PTR_NOT_NULL(pProgressCb));
		if(RES_TRUE(result)){
			RES_CHECK(result, (*pProgressCb)(message,val, max));
		}

		RES_RETURN(result);
	}

