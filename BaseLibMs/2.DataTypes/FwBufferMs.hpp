/***********************************************************************\
*																								*
*								B u f f e r   H a n d l e r							*
*																								*
\***********************************************************************/
#ifndef BUFFER_HANDLER_H
#define BUFFER_HANDLER_H
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"





	/***********************************************************************\
	*																								*
	*										Include files										*
	*																								*
	\***********************************************************************/
	#include	HDR_FW_BASE_TYPES
	#include	HDR_FW_RESULT
	#include HDR_FW_STRING





	/***********************************************************************\
	*																								*
	*										Definitions											*
	*																								*
	\***********************************************************************/
	#define	UNKNOWN							-0x01





	/***********************************************************************\
	*																								*
	*											Class												*
	*																								*
	\***********************************************************************/

	class CFwBuffer//: protected CMicString
	{
		public:	FW_RESULT	Clear(void);

		//	Class.
		public:				CFwBuffer();
		public:	virtual	~CFwBuffer();

		//	Buffer title.
		private:	STRING	my_title;
		public:	FW_RESULT	Title(STRING new_title);
		public:	STRING	Title(void);

		//	Buffer user.
		private:	FW_INT	my_user;
		public:	FW_RESULT	User(FW_INT user);
		public:	FW_INT	User(void);
		public:	STRING	UserGet(bool Hex);


		//	Buffer block size.
		private:	FW_INT	my_block_size;
		public:	FW_RESULT	BlockSize(FW_INT block_size);
		public:	FW_INT	BlockSize(void);
		public:	STRING	BlockSizeGet(bool Hex);


		//	Buffer size methods.
		private:	FW_INT	my_length;				//	the message length.
		public:	FW_INT	Length(void);			//	Get the message length.
		public:	bool		Length(FW_INT	leng);	//	Check new buffer space.
		public:	STRING	LengthGet(bool hex);

		//	Buffer pointer.
		private:	FW_INT	my_pointer;
		public:	bool		Pointer(FW_INT pointer);
		public:	FW_INT	Pointer(void);
		public:	bool		Complete(void);
		public:	STRING	PointerGet(bool	hex);

		//	Buffer size methods.
		private:	FW_INT	my_bottom;				//	the message length.
		public:	FW_INT	Bottom(void);			//	Get the message length.
		public:	bool		Bottom(FW_INT leng);	//	Allocate new buffer space.
		public:	STRING	BottomGet(bool Hex);


		//	Properties string.
		public:	STRING	Properties(bool Hex);
		public:	bool		Properties(STRING string);


		//	Buffer contents methods.
		private:	unsigned char*			my_pBuffer;			//	all port data is a characters array.
		public:	const unsigned char*	Buffer(void);		//	Get a pointer to the array buffer.
		public:	FW_UCHAR					Buffer(FW_INT index);
		public:	bool						Allocate(FW_INT leng);	//	Allocate new buffer space.
		public:	bool						Buffer(const unsigned char* pArr,FW_INT leng);
		public:	bool						Buffer(LPVOID pArr,FW_INT leng);

		public:	bool						BufferLet(STRING string);
		public:	STRING					BufferGet();

		public:	bool						BufferAdd(const unsigned char* new_buffer,FW_INT new_length);
		public:	bool						BufferAdd(CFwBuffer* pBuffer);
		public:	bool						BufferSet(const unsigned char new_byte,FW_INT new_index);
		public:	bool						BufferSet(const unsigned char* new_buffer,FW_INT new_length, FW_INT strt_frm);
		public:	void						BufferClear(void);


		//	List methods.
		public:	bool						IsEmpty(void);
		public:	unsigned char			Head(void);
		public:	unsigned char			HeadGet(void);
		public:	bool						HeadRemove(FW_INT size);
		public:	FW_INT					Serach(unsigned char byte);
		public:	unsigned char			End(void);

		//	Operators.
		public:	bool						operator ==	(const CFwBuffer* pBuff);	// compare this message contents with another message contents.
		public:	CFwBuffer*				operator =	(const CFwBuffer* pBuff);
		public:	CFwBuffer*				operator += (const CFwBuffer* pBuff);
		public:	unsigned char&			operator [] (FW_INT Index);

		//	String conversion of the buffer contents.
		public:	STRING					BufferText(bool	Hex = false);
		public:	bool						BufferText(STRING	array);
		public:	bool						DescriptionLet(STRING description);
		public:	STRING					DescriptionGet(bool hex);
	};
#endif // BUFFER_HANDLER_H.
