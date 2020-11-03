#ifndef DATA_TYPES_H
#define	DATA_TYPES_H
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





	/**********************************************************************\
	*																								*
	*										Containers											*
	*																								*
	\**********************************************************************/

	#define	UTYPE_INIT(VAR)		VAR.val = 0x00

	#define	FW_CHAR	char
	#define	FW_UCHAR	unsigned char
	#ifdef	__cplusplus
		typedef struct _SCharBmp
		{
			FW_UCHAR	b0:1;
			FW_UCHAR	b1:1;
			FW_UCHAR	b2:1;
			FW_UCHAR	b3:1;
			FW_UCHAR	b4:1;
			FW_UCHAR	b5:1;
			FW_UCHAR	b6:1;
			FW_UCHAR	b7:1;
		}SCharBmp;


		typedef union _UCharBmp{
			SCharBmp	s;
			FW_CHAR	val;
			FW_UCHAR	uval;
		 }UCharBmp;
		#define		FW_UCHAR_MAX		0xFF
	#endif

	 #define	FW_INT	int
	 #define	FW_UINT	unsigned int
	 typedef union _Uint
	 {
		  FW_INT		val;
		  FW_UINT	uval;
		  FW_UCHAR	chr[2];
	 }UInt;
	 #define	FW_UINT_INIT(VAR)			VAR = 0x00
	 #define	FW_UINT_MAX	0xFFFF
	 #define	UINT_DECR(VAL)				\
		  if(VAL.val > 0x00){				\
				VAL.val--;						\
		  }										\
	 /*UINT_DECR*/

	 #define	UINT_ADD(VAR,VAL)								\
		  if(((FW_ULONG)VAR.val + VAL.val) < UINT_MAX){	\
				VAR.val += VAL.val;								\
		  }															\
		  else{														\
				VAR.val = UINT_MAX;								\
		  }															\
		  /*UINT_ADD*/

	 #define	UINT_SUB(VAR,VAL)		\
		  if(VAR.val > VAL.val){		\
				VAR.val -= VAL.val;		\
		  }									\
		  else{								\
				VAR.val = 0x00;			\
		  }									\
		  /*UINT_SUB*/


	 #define	FW_ULONG_MAX	_UI32_MAX/*0xFFFFFFFF*/
	 #define	FW_LONG			signed long
	 #define	FW_ULONG			unsigned long
	 typedef union _ULong
	 {
		  FW_ULONG val;
		  UInt		uint[2];
		  FW_UCHAR	chr[4];
	 }ULong;
	 #define	ULONG_ADD(VAR,VAL)									\
				ASSERT(((FW_ULONG)VAR.val + VAL.val) < ULONG_MAX);	\
				VAR.val += VAL.val;										\
				/*ULONG_ADD*/

#ifdef	_MSC_VER
	#define	FW_ULONG64_MAX	0xFFFFFFFFFFFFFFFF
	#define	FW_LONG64		signed long long
	#define	FW_ULONG64		unsigned long long
	typedef union _ULong64
	{
		FW_ULONG64	val;
		ULong			lng[2];
		UInt			uint[4];
		FW_UCHAR		chr[8];
	}ULong64;
	#define	FW_ULONG64_ADD(VAR,VAL)										\
			ASSERT(((FW_ULONG)VAR.val + VAL.val) < ULONG64_MAX);	\
			VAR.val += VAL.val;												\
			/*ULONG_ADD*/
#endif

	#define	FW_INC(VAL,MAX)				if(VAL<MAX)		(VAL)++
	#define	FW_DEC(VAL)						if(VAL>0x00)	(VAL)--

	#define	TIME_BIN							unsigned int
	#define	ULONG_ARR_REF(DATA)			FW_ULONG	DATA[]
	#define	ULONG_ARR_PRM(DATA)			const FW_ULONG	DATA[]






	/***********************************************************************\
	*																								*
	*										s t r i n g											*
	*																								*
	\***********************************************************************/
	#define	CHAR_ARR_REF(ARR)					char ARR[]
	#define	CHAR_ARR_PRM(ARR)					const char ARR[]





	/***********************************************************************\
	*																								*
	*										B i t s												*
	*																								*
	\***********************************************************************/
	#define	INT_BIT(INDX)	((int)1<<INDX)

	#define	BIT_SET(NAME, INDEX)			\
					NAME |= (0x01<<INDEX)	\
					/*BITS_SET*/

	#define	BIT_CLR(NAME, INDEX)			\
					NAME &= (~(0x01<<INDEX))\
					/*BIT_CLR*/

	#define	BIT_CHK(NAME, INDEX)			\
					(0x00 != (NAME & (0x01<<INDEX)))	\
					/*BIT_CHK*/


	#define	BITS_SET(NAME, BITS)			\
					NAME |= BITS				\
					/*BITS_SET*/

	#define	BITS_CLR(NAME, BITS)			\
					NAME &= (~BITS)			\
					/*BITS_CLR*/





	/***********************************************************************\
	*																								*
	*											F l a g s 										*
	*																								*
	\***********************************************************************/
	#define FLAGS_TYPE	long

	#define	FLAG_NEW(FLAG)				\
			FLAGS_TYPE FLAG:1				\
			/*FLAG_NEW*/

	#define	FLAGS_TYPE_DEF(TYPE,FLAGS)	\
			struct	S##TYPE					\
			{										\
					FLAGS						\
			};									\
			union	U##TYPE					\
			{										\
					struct	S##TYPE	s;		\
					FLAGS_TYPE		all;	\
			}										\
			/*FLAGS_TYPE_DEF*/
	#define	FLAGS_DECLARE(TYPE,NAME)	\
			U##TYPE	NAME						\
			/*FLAGS_CREATE*/
	#define	FLAGS_CREATE(TYPE,NAME)		\
			U##TYPE	NAME ={0}				\
			/*FLAGS_CREATE*/
	#define 	FLAGS_INIT(NAME)			\
					NAME.all = 0x00			\
			/*FLAGS_CLEAR*/
	#define	FLAGS_COMP(NAME1,NAME2)			\
					(NAME1.all == NAME2.all)	\
			/*FLAGS_COMP*/
	#define	FLAGS_ALL(NAME)				\
			NAME.all							\
			/*FLAGS_ALL*/
	#define 	FLAGS_SET(NAME,VAL)		\
			NAME.all = VAL					\
			/*FLAGS_CLEAR*/
	#define 	FLAGS_CHK(NAME)			\
			(NAME.all != 0x0)				\
			/*FLAGS_CHK*/

	#define	FLAG_DECLR(FLAG)				\
			bool FLAG = false;				\
			/*FLAG_DECLR*/
	#define 	FLAG_ON(NAME,FLAG)		\
			NAME.s.FLAG = 0x01				\
			/*FLAG_SET*/
	#define 	FLAG_OFF(NAME,FLAG)		\
			NAME.s.FLAG = 0x00				\
			/*FLAG_SET*/
	#define 	FLAG_SET(NAME,FLAG,STATE)	\
			NAME.s.FLAG = STATE					\
			/*FLAG_SET*/

	#define 	FLAG_CHK(NAME,FLAG)			\
			(NAME.s.FLAG != 0x0)				\
			/*FLAG_SET*/
	#define 	FLAG_CHK_NOT(NAME,FLAG)		\
			(NAME.s.FLAG == 0x0)				\
			/*FLAG_SET*/
	#define	FLAG_COMP(NAME1,NAME2,FLAG)	\
			(NAME1.s.FLAG == NAME2.s.FLAG)	\
			/*FLAGS_COMP*/
	#define	FLAG_NOT_COMP(NAME1,NAME2,FLAG)	\
			(NAME1.s.FLAG != NAME2.s.FLAG)		\
			/*FLAGS_COMP*/
	#define	FLAG_EQU(NAME1,NAME2,FLAG)		\
			(NAME1.s.FLAG = NAME2.s.FLAG)	\
			/*FLAGS_COMP*/
	#define FLAG_TOGGLE(NAME,FLAG)			\
			if(FLAG_CHK(NAME,FLAG))			\
					FLAG_OFF(NAME,FLAG);		\
			else										\
					FLAG_ON(NAME,FLAG);		\
			/*	FLAG_TOGGLE	*/
	#define	FLAG_RETURN(FLAG)					\
			return(FLAG)						\
			/*FLAG_RETURN*/

#endif // !DATA_TYPES_H
