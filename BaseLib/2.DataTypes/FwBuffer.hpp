/***********************************************************************\
*																								*
*								B u f f e r   H a n d l e r							*
*																								*
\***********************************************************************/
#ifndef FW_BUFFER_HPP
#define FW_BUFFER_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





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

	class CFwBuffer
	{
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
		private:	int		my_block_size;
		public:	FW_RESULT	BlockSize(int block_size);
		public:	int		BlockSize(void);
		public:	STRING	BlockSizeGet(bool Hex);

		//	Buffer size methods.
		private:	FW_INT	my_length;				//	the message length.
		public:	FW_INT	Length(void);			//	Get the message length.
		public:	bool		Length(FW_INT	leng);	//	Check new buffer space.
		public:	STRING	LengthGet(bool hex);


		//	Buffer pointer.
		private:	FW_INT	my_pointer;
		public:	FW_INT	Pointer(void);
		public:	bool		Pointer(FW_INT pointer);
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
		private:	char*			my_pBuffer;			//	all port data is a characters array.
		public:	const char*	Buffer(void);		//	Get a pointer to the array buffer.
		public:	char			Buffer(int index);
		public:	FW_RESULT		Allocate(int leng);	//	Allocate new buffer space.
		public:	FW_RESULT		Buffer(const char* pArr,int leng);
		public:	FW_RESULT		Buffer(void* pArr,int leng);

		public:	FW_RESULT		BufferLet(STRING string);
		public:	STRING		BufferGet();

		public:	FW_RESULT		BufferAdd(const char* new_buffer,int new_length);
		public:	FW_RESULT		BufferAdd(CFwBuffer* pBuffer);
		public:	FW_RESULT		BufferSet(const char new_byte,int new_index);
		public:	FW_RESULT		BufferSet(const char* new_buffer,int new_length, int strt_frm);
		public:	FW_RESULT		BufferClear(void);


		//	List methods.
		public:	bool			IsEmpty(void);
		public:	char			Head(void);
		public:	char			HeadGet(void);
		public:	FW_RESULT		HeadRemove(int size);
		public:	int			Serach(char byte);
		public:	char			End(void);

		//	Operators.
		public:	bool			operator ==	(const CFwBuffer* pBuff);	// compare this message contents with another message contents.
		public:	CFwBuffer*	operator =	(const CFwBuffer* pBuff);
		public:	CFwBuffer*	operator += (const CFwBuffer* pBuff);
		public:	char&			operator [] (int Index);

		//	String conversion of the buffer contents.
		public:	STRING		BufferText(bool	Hex = false);
		public:	bool			BufferText(STRING	array);
		public:	bool			DescriptionLet(STRING description);
		public:	STRING		DescriptionGet(bool hex);
	};

#endif // FW_BUFFER_HPP
