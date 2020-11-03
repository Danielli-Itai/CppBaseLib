#ifndef FW_POINTERS_MS_HPP
#define	FW_POINTERS_MS_HPP
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"




	/***********************************************************************\
	*																								*
	*									Include Files										*
	*																								*
	\***********************************************************************/
	//#include	HDR_STDAFX
	#include	HDR_FW_RESULT





	/***********************************************************************\
	*																								*
	*										Pointers												*
	*																								*
	\***********************************************************************/
	//	Creation.
	#ifndef NULL
		#define NULL    0
	#endif

	#define	PTR_NULL							NULL
	//	Creation.
	#define	PTR_INIT(PTR)					PTR = NULL
	#define	PTR_DECLR(CLASS,PTR)			CLASS* PTR = NULL
	#define	PTR_PARAM(CLASS,PTR)			CLASS* PTR
	#define	PTR_MEMBER(CLASS,PTR)		CLASS* PTR;
	#define	PTR_MEMBER_INIT(PTR)			PTR(PTR_NULL)

	#define	PTR_DECLR_INIT(CLASS,PTR,INIT)		\
				CLASS* PTR = INIT						\
				/*PTR_DECLR_INIT*/

	#ifdef __cplusplus
		 #define	PTR_CREATE(CLASS,PTR)				\
					ASSERT(NULL == PTR);					\
					PTR = new CLASS();					\
					/*PTR_CREATE*/
		 #define	PTR_CREATE_ARR(CLASS,PTR, SIZE)	\
					ASSERT(NULL == PTR);					\
					PTR = new CLASS[SIZE];				\
					/*PTR_CREATE*/
		 #define	PTR_DECLR_NEW_ARR(CLASS,PTR, SIZE)	\
					CLASS* PTR = new CLASS[SIZE];			\
					/*PTR_CREATE*/

		 #define	PTR_CREATE_INIT(CLASS,PTR,INIT)	\
					ASSERT(NULL == PTR);					\
					PTR = new CLASS(INIT);				\
					/*PTR_CREATE_INIT*/

		 #define	PTR_DECLR_NEW(CLASS,PTR)			\
					CLASS* PTR = new CLASS();			\
					/*PTR_DECLR_NEW*/

		 #define	PTR_INIT_NEW(CLASS, PTR)			\
					PTR_INIT(PTR);							\
					PTR_CREATE(CLASS,PTR)				\
					/*PTR_INIT_NEW*/

		 #define	PTR_DECLR_NEW_INIT(CLASS,PTR,INIT)	\
					CLASS* PTR = new CLASS(INIT);			\
					/*PTR_DECLR_NEW_INIT*/

			#define	PTR_MOVE(PTR,SRC)					\
					ASSERT(NULL == PTR);					\
					PTR = SRC;								\
					PTR_CLR(SRC);							\
					/*PTR_MOVE*/

			#define	PTR_SET(PTR,VAL)					\
					ASSERT(NULL == PTR);					\
					PTR = VAL;								\
					/*PTR_SET*/

			#define	PTR_RESET(PTR,VAL)				\
					PTR = VAL;								\
					/*PTR_RESET*/

			#define	PTR_CLR(PTR)						\
					PTR = NULL;								\
					/*PTR_CLR*/

			#define	PTR_SET_NEW(CLASS,PTR)			\
						 ASSERT(NULL == PTR);			\
						 PTR = new CLASS();				\
						 /*PTR_SET_NEW*/

			#define	PTR_SET_NEW_INIT(CLASS,PTR,INIT)	\
						 ASSERT(NULL == PTR);				\
						 PTR = new CLASS(INIT);				\
						 /*PTR_SET_NEW*/
			
			#define	PTR_IS_NULL(PTR)				(NULL == PTR)
			#define	PTR_NOT_NULL(PTR)				(NULL != (PTR))
	#endif // __cplusplus

	#define	ENUM_PTR_ARR_INIT(ENUM, ARR)												\
	for(int ENUM##count =0x00; ENUM##count < ENUM##_COUNT; ENUM##count++){	\
		PTR_INIT(ARR[ENUM##count]);														\
	}																								\
	/*ENUM_PTR_ARR_INIT*/

	#define	ENUM_PTR_ARR_DESTROY(ENUM, ARR)											\
	for(int ENUM##count =0x00; ENUM##count < ENUM##_COUNT; ENUM##count++){	\
		if(PTR_NOT_NULL(ARR[ENUM##count])){												\
				PTR_DESTROY(ARR[ENUM##count]);												\
		}																							\
	}																								\
	/*ENUM_PTR_ARR_DESTROY*/







	/*C creation function*/

	/*C++ creation template*/
	template <class CLASS>
	bool	FW_New(CLASS** pointer)
	{
		RES_DECLR(result);

		if(NULL == (*pointer))
		{
			(*pointer) = new CLASS;
			if(NULL == (*pointer)){
				RES_FAILE(result);
			}
		}
		else{
			RES_FAILE(result);
		}
		RES_RETURN(result);
	}




	/*C destruction function*/
	#ifdef __cplusplus
		/*C++ destruction template*/
		template <class P_REF>
		bool	FW_Delete(P_REF** pointer)
		{
			RES_DECLR(result);

			if(NULL != (*pointer))
			{
				delete (*pointer);
				(*pointer) = NULL;
			}
			else{
				RES_FAILE(result);
			}
			RES_RETURN(result);
		}

		//	Destruction.
		#define PTR_DESTROY(PTR)	\
			FW_Delete(&(PTR));		\
			/*PTR_DESTROY*/
		#define	PTR_DESTROY_ARR(PTR)	\
				delete[] PTR;				\
				PTR_INIT(PTR)				\
				/*PTR_DESTROY_ARR*/

		template <class P_ARR>
		FW_RESULT	PtrArrPush(P_ARR* pArray[], int size, P_ARR* &pData)
		{
			RES_DECLR(result);

			if(size > 0x01)//	In case queue size is grater than 1.
			{					//	 first item will need to be pushed.
				for(int i = size -1; i>0x00; i--)
				{	//	All elements from end to second.
					if(PTR_NOT_NULL(pArray[i])){			//	Destroy current.
						PTR_DESTROY(pArray[i]);
					}
					PTR_MOVE(pArray[i], pArray[i-1]);	//	Push previous to current.
				}
			}
			else{	//	Other ways it it is also the last.
				if(PTR_NOT_NULL(pArray[0x00])){			//	and will be destroyed.
					PTR_DESTROY(pArray[0x00]);				//	Destroy first item.
				}
			}
			PTR_CREATE(P_ARR, pArray[0x00]);			//	Create new object.
			(*pArray[0x00]) = (*pData);				//	Pass all contents.

			RES_RETURN(result);
		};


		template <class P_ARR>
		FW_RESULT	PtrArrPop(P_ARR* pArray[], int size, P_ARR* &pData)
		{
			RES_DECLR(result);

			if(PTR_NOT_NULL(pData)){				//	Destroy current.
				PTR_DESTROY(pData);
			}
			PTR_CREATE(P_ARR, pData);				//	Create new object.
			(*pData) = (*pArray[0x00]);				//	Pass all contents.

			PTR_DESTROY(pArray[0]);					//	Push previous to current.
			for(int i = 0x00; i<size-1; i++)
			{	//	All elements from end to second.
				PTR_MOVE(pArray[i], pArray[i+1]);	//	Push previous to current.
			}
			PTR_INIT(pArray[size - 1]);

			RES_RETURN(result);
		}
	#endif // __cplusplus


	#define PTR_OBJ_RETURN(PTR)				\
		RES_ALERT(PTR_NOT_NULL(PTR));		\
		RETURN(*PTR);						\
		/*PTR_OBJ_RETURN*/

	#define PTR_RETURN(PTR)					\
		RETURN(PTR);						\
		/*PTR_RETURN*/

#endif // !FW_POINTERS_MS_HPP
