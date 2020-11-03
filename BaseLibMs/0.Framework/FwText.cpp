#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"
/********************************************************************\
*																							*
*							S t r i n g   H a n d l e r							*
*																							*
\********************************************************************/





/********************************************************************\
*																							*
*										Include Files									*
*																							*
\********************************************************************/
#include <algorithm>
#include	HDR_FW_DEBUGGING
#include	HDR_FW_TEXT_STR





/********************************************************************\
'																							'
'									CONTAINERS											'
'																							'
\********************************************************************/
ENUM_NAMES_CREATE(STR_TAG, STR_TAG_NAMES);





#ifdef	__cplusplus_cli
#elif	__cplusplus
#else
	FW_RESULT StrSet(CHAR_ARR_REF(str), CHAR_ARR_REF(set))
	{
		RES_DECLR(result);
		if(strlen(set) < STR_SIZE_MAX){
			RES_CHECK(result, str == strcpy(str, set));
		}
		else{
			RES_FAILE(result);
		}

		RES_RETURN(result);
	}
#endif

//	Get a string containing a Double Word value.
STRING	NumToStr(long long num, bool Hex)
{
	STR_DECLR(tmp);
	STR_DECLR(Description);

	if(num<0x00){
		STR_SET(Description, "-");
		num *= (-1);
	}
	else{
		STR_CLEAR(Description);
	}

	STR_CLEAR(tmp);
	if(Hex)
	{
		STR_TO_HEX(tmp, num);		//	hex format.
	}
	else{
		STR_TO_DEC(tmp ,num);		//	Decimal format.
	}
	STR_ADD(Description,tmp);	//	Hex prefix.

	STR_RETURN(Description);
}

//----------------------------------------------------------
//	Convert a number written in a string in to an integer.
unsigned long	GetNum(STRING str_num)
{
	FW_INT	index = 0x00,  tmp = 0x00;
	FW_INT	length = str_num.length();	//	set end if string as current border.
	bool	Hex = false,  Neg = false;
	FW_INT	Val = 0x00;						//	new number value.

	if(STR_FIND(str_num, STR_HEX))		//	Search for hex number.
		Hex = true;							//	Hex number is found.

	while(index < length)
	{												//	run threw new number digits.
		tmp = str_num[index];				//	get digit.
		index++;									//	move to next byte.

		if(tmp == '-'){						//	Negative number support.
			Neg = true;
		}

		if(Hex){
			if((tmp>='0') && (tmp<='9') ){					//	legal digit is found.
				tmp -= '0';											//	Convert from ASCII to digit.
				Val *= 0x10;
				Val += tmp;											//	increase value.
			}
			if((tmp>='A') && (tmp<='F')){
				tmp = tmp - 'A' + 10;
				Val *= 0x10;
				Val += tmp;											//	increase value.
			}
			if((tmp>='a') && (tmp<='f')){
				tmp = tmp - 'a' + 10;
				Val *= 0x10;
				Val += tmp;											//	increase value.
			}
		}
		else{
			if( (tmp>='0') && (tmp<='9') ){					//	legal digit is found.
				tmp -= '0';
				Val *= 10;
				Val += tmp;											//	increase value.
			}
		}
	}

	if(true == Neg){						//	Negative number support.				
		Val *= (-1);
	}

	return(Val);
}


//----------------------------------------------------------'
//	Get a record from a string according to the separatot tag.
//	<record1><tag><record2><tag>...
//	The last Item in a string with no end marker will also returned.
STRING	GetTextRecord(STRING page, unsigned char tag, int index)
{
	FW_INT	border_curr = 0x00;	//	Current segment border.
	FW_INT	border_next = 0x00;	//	Next segment border.
	STR_DECLR(replay);				//	Replay string.

	FW_INT	cntr = 0x00;
	do	{
		border_curr = border_next;
		border_next = STR_FIND_INDEX(page, TAG_STR_END, border_curr);		// search end of String.
		if(STR_NOT_FOUND == border_next){
			border_next = STR_LEN(page);		// search End of String.
		}

		if(border_next >= border_curr){
			border_next++;							//	step over tag.
		}else	{
			border_next = STR_NOT_FOUND;		//	Record not found;
			break;
		}
		cntr++;
	}while(cntr <= index);

	if(border_next > 0x00)
	{
		border_next--;																	//	Remove the end mark and return contents only.
//		STR_SET(my_item, STR_SUBSTR(page, border_curr, (border_next-border_curr)));	//	Set as active item.
//		STR_SET(replay, my_item);																//	return the item.
		STR_SET(replay, STR_SUBSTR(page, border_curr, (border_next-border_curr)));
	}
	STR_RETURN(replay);
}














/********************************************************************\
*																							*
*											Class											*
*																							*
\********************************************************************/

FW_RESULT	CMicString::Init(void)
{
	RES_DECLR(result);

	//STR_INIT(my_item);
	//STR_INIT(my_page);
	//STR_INIT(my_segment);
	//STR_INIT(my_formation);
	//STR_INIT(my_description);

	RES_RETURN(result);
}
FW_RESULT	CMicString::Clear(void)
{
	RES_DECLR_INIT(result,Init());
	RES_RETURN(result);
}

CMicString::CMicString()
{
	RES_ALERT(Init());
}

//CMicString::CMicString(STRING description)
//{
//	RES_ALERT(Init());
//	RES_ALERT(DescriptionLet(description));
//}

CMicString::~CMicString()
{
}










/********************************************************************\
*																							*
*										Conversion										*
*																							*
\********************************************************************/
//	Check if the string is a number.
bool	CMicString::IsNum(STRING num_str)
{
	bool		hex		= false;
	bool		is_hex	= true;
	FW_INT	counter	= 0x00;
	char		Char		= NULL;
	FW_INT	Length	=	0x00;

	Length = STR_LEN(num_str);
	for(counter = 0; counter < Length; counter++)
	{
		if(true == is_hex)
		{														//	result still true.
			Char = STR_PBUFF(num_str)[counter];
			if(Char != '-')
			{													//	Ignore negative signe
				if((false == hex) && ((Char == 'x') || (Char == 'X')))
				{												//	Check Hex header
					if((counter > 1) && (STR_PBUFF(num_str)[counter-1] == '0')){
						hex = true;							//	Hex number validation.
					}
					else{
						is_hex = false;					//	Not prefix must be error.
					}
				}	//	end of check hex header
				else{
					if(true == hex)
					{											//	Check Hex number
						if((Char < 'a') || (Char > 'f'))
						{										//	Not low characters.
							if((Char < 'A') || (Char > 'F'))
							{									//	Not High characters.
								if((Char < '0')||(Char > '9')){	//	Not digit.
                              is_hex = false;	//	Must be error.
								}
							}
						}
					}
					else
					{											//	Check decimal number
						if((Char < '0')||(Char > '9')){	//	Not digit.
							is_hex = false;				//	Must be error.
						}
					}
				}
			}	//	end of ignore -
		}	//	end of result still true
		else{
			break;
		}
	}	//Next counter
	return(is_hex);
}	//End Function

//--------------------------------------------------------------------------
//	Get a string containing a Byte value.
STRING	CMicString::GetNum(unsigned char num, bool Hex)
{
	STR_DECLR(tmp);
	STR_DECLR(Description);

	STR_CLEAR(tmp);
	if(Hex)
	{
		STR_TO_HEX(tmp,num);		//	hex format.
		STR_ADD(Description,"0x");
		STR_ADD(Description,tmp);	//	Hex prefix.
	}
	else{
		STR_TO_DEC(tmp, num);		//	Decimal format.
		STR_ADD(Description,tmp);
	}
	STR_RETURN(Description);
}

//	Get a string containing a Word value.
STRING	CMicString::GetNum(FW_INT num, bool Hex)
{
	STR_DECLR(tmp);
	STR_DECLR(Description);

	if(Hex)
	{
		if(num < 0x00){
			STR_ADD(Description, STR_MINUS);
			num *= (-1);
		}
//		else{
//			STR_ADD(Description,"0x");
//		}
		STR_TO_HEX(tmp ,num);		//	hex format.
		//tmp.MakeUpper();
	}
	else{
		if(num < 0x00){
			Description += "-" + tmp;	//	Hex prefix.
			num *= (-1);
		}
		else{
			Description += tmp;
		}
		STR_TO_DEC(tmp, num);		//	Decimal format.
	}
	STR_ADD(Description,tmp);		//	Hex prefix.

	STR_RETURN(Description);
}

//	Get a string containing a Double Word value.
STRING	CMicString::GetNum(FW_LONG num, bool Hex)
{
	STR_DECLR(tmp);
	STR_DECLR(Description);

	if(num<0x00){
		STR_SET(Description, STR_MINUS);
		num *= (-1);
	}
	else{
		STR_CLEAR(Description);
	}

	STR_CLEAR(tmp);
	if(Hex)
	{
		STR_TO_HEX(tmp, num);		//	hex format.
	}
	else{
		STR_TO_DEC(tmp ,num);		//	Decimal format.
	}
	STR_ADD(Description,tmp);	//	Hex prefix.

	STR_RETURN(Description);
}
//----------------------------------------------------------
//	Convert a number written in a string in to an integer.
FW_LONG	CMicString::GetNum(STRING str_num)
{
	FW_INT	index = 0x00,  tmp = 0x00;
	FW_INT	length = STR_LEN(str_num);	//	set end if string as current border.
	bool	Hex = false,  Neg = false;
	FW_INT	Val = 0x00;						//	new number value.

	if(STR_NOT_FOUND != STR_FIND(str_num, STR_HEX))		//	Search for hex number.
		Hex = true;								//	Hex number is found.

	if(STR_FIND_INDEX(str_num, "[",index) > STR_NOT_FOUND){	//	Number closure is found.
		index = STR_FIND(str_num, "[");								//	ignore prceeding text.
	}

	while(index < length)
	{												//	run threw new number digits.
		tmp = str_num[index];				//	get digit.
		index++;									//	move to next byte.

		if(tmp == '-'){						//	Negative number support.
			Neg = true;
		}

		if(Hex){
			if((tmp>='0') && (tmp<='9') ){					//	legal digit is found.
				tmp -= '0';											//	Convert from ASCII to digit.
				Val *= 0x10;
				Val += tmp;											//	increase value.
			}
			if((tmp>='A') && (tmp<='F')){
				tmp = tmp - 'A' + 10;
				Val *= 0x10;
				Val += tmp;											//	increase value.
			}
			if((tmp>='a') && (tmp<='f')){
				tmp = tmp - 'a' + 10;
				Val *= 0x10;
				Val += tmp;											//	increase value.
			}
		}
		else{
			if( (tmp>='0') && (tmp<='9') ){					//	legal digit is found.
				tmp -= '0';
				Val *= 10;
				Val += tmp;											//	increase value.
			}
		}
	}

	if(true == Neg){						//	Negative number support.				
		Val *= (-1);
	}

	return(Val);
}


//----------------------------------------------------------
//	Get NUMBER from an ARRAY string.
//	Get the string contains data items written in texte mode "1,2,3.." or "0x01,0x02,..."
//	seperated using '>',',' or ';' or ':' or '.' seperators.
//	The string with no end marker will also pe processed. 
FW_INT	CMicString::GetNum(STRING	page, STRING sep, FW_INT at_index=0x00)
{
	STR_DECLR_INIT(item, GetTextItem(page, sep, at_index));
	RETURN(GetNum(item));
}

FW_INT	CMicString::GetNum(STRING	page, FW_INT at_index)
{
	FW_INT		num_count = -0x01, Val = -0x01;
	FW_INT		index = 0x00, index1=0x00, lst_index = 0x00, tmp = 0x00;
	bool		continu = true, Hex = false, Neg = false;

	while(continu)
	{
		//	Get the index of the next seperator.
		index = STR_FIND_INDEX(page, TAG_LNK_END, lst_index);				//	search link seperator marker.

		index1 = STR_FIND_INDEX(page, TAG_ITM_END, lst_index);			//	search item seperator marker.
		if((index == STR_NOT_FOUND) || ((index1 != STR_NOT_FOUND) && (index1 < index))){	//	Link Not found or item seperator befor link.
			index = index1;													//	Keep Item.
		}

		index1 = STR_FIND_INDEX(page, TAG_PAG_END, lst_index);	//	search number seperator marker.
		if((index == STR_NOT_FOUND) || ((index1 != STR_NOT_FOUND) && (index1<index))){	//	Link Not found or item seperator befor link.
			index = index1;													//	Keep Item.
		}

		index1 = STR_FIND_INDEX(page, TAG_PAG_END, lst_index);	//	search array seperator marker.
		if((index == STR_NOT_FOUND) || ((index1 != STR_NOT_FOUND) && (index1<index))){	//	Link Not found or item seperator befor link.
			index = index1;													//	Keep Item.
		}

		index1 = STR_FIND_INDEX(page, TAG_SEG_END, lst_index);	//	search segment seperator marker.
		if((index == STR_NOT_FOUND) || ((index1 != STR_NOT_FOUND) && (index1<index))){	//	Link Not found or item seperator befor link.
			index = index1;													//	Keep Item.
		}

		index1 = STR_FIND_INDEX(page, TAG_FRM_END, lst_index);	//	search end of data marker.
		if((index == STR_NOT_FOUND) || ((index1 != STR_NOT_FOUND) && (index1<index))){	//	Link Not found or item seperator befor link.
			index = index1;													//	Keep Item.
		}

		if(index == STR_NOT_FOUND)										//	End of current number not found
		{
			continu = false;												//	set as last number.
			index = STR_LEN(page);										//	set end if string as current border.
		}

		Val = 0x00;															//	new number value.
		if(index > lst_index)
		{											//	new number is found.
			num_count ++;													//	Increase index.
			Neg = false;													//	Not negative until minus is found.

			Hex = false;

			if(	(STR_FIND_INDEX(page, "0x", lst_index) > STR_NOT_FOUND)	&&		//	Start searching from last index.
					((FW_INT)STR_FIND_INDEX(page, "0x", lst_index) < index)				)		//	if found chak it is befor the end of this number.
				Hex = true;																			//	Hex number is found.

			if(	(STR_FIND_INDEX(page, "[", lst_index) > STR_NOT_FOUND)	&&		//	Start searching from last index.
					((FW_INT)STR_FIND_INDEX(page, "[", lst_index) < index)				)		//	if found chak it is befor the end of this number.
				lst_index = STR_FIND_INDEX(page, "[", lst_index);						//	Number closure is found.

			while( lst_index < index)
			{							//	run threw new number digits.
				tmp = page[lst_index];							//	get digit.
				lst_index++;										//	move to next byte.

				if(tmp == '-'){									//	Negative number support.
					Neg = true;
				}

				if(Hex){
					if((tmp>='0') && (tmp<='9') ){	//	legal digit is found.
						tmp -= '0';							//	Convert from ASCII to digit.
						Val *= 0x10;
						Val += tmp;							//	increase value.
					}
					if((tmp>='A') && (tmp<='F')){
						tmp = tmp - 'A' + 10;
						Val *= 0x10;
						Val += tmp;							//	increase value.
					}
					if((tmp>='a') && (tmp<='f')){
						tmp = tmp - 'a' + 10;
						Val *= 0x10;
						Val += tmp;							//	increase value.
					}

				}
				else{
					if( (tmp>='0') && (tmp<='9') ){	//	legal digit is found.
						tmp -= '0';
						Val *= 10;
						Val += tmp;							//	increase value.
					}
				}
			}
			if(num_count == at_index){					//	the request number is found.
				continu = false;												//	set as last number.
				break;
			}
		}
		lst_index++;
	}

	if(Neg == true){						//	Negative number support.				
		Val *= (-1);
	}

	if(num_count < at_index){												//	requested number is out of range. 
		Val = -0x01;
	}

	return(Val);
}

//	Set the new string as current string
//	and returnd the requested index.
//FW_INT	CMicString::GetNum(FW_INT at_index=0x00)
//{
//	return(GetNum(my_page, at_index));
//}
STRING	CMicString::GetArr(FW_CHAR* pArr, FW_LONG length, bool hex)
{
	STR_DECLR(str_arr);
	for (FW_INT i = 0; i < length; i++)
	{
		unsigned char num =  pArr[i];
		if(i > 0x00) STR_ADD(str_arr, TAG_ITM_END);
		STR_ADD(str_arr, CMicString::GetNum((FW_INT)num, hex));
	}
	STR_RETURN(str_arr);
}





/********************************************************************\
*																							*
*									Substring Find										*
*																							*
\********************************************************************/
bool	CMicString::FindRight(STRING search_str, STRING sub_str)
{
	bool found = false;

	FW_INT search_len = STR_LEN(search_str);
	FW_INT sub_str_len = STR_LEN(sub_str);
	if(search_len >= sub_str_len){
		found = (STR_NOT_FOUND != STR_FIND_INDEX(search_str, sub_str, (search_len - sub_str_len)));
	}
	RETURN(found);
}





/********************************************************************\
*																							*
*											Tokens										*
*																							*
\********************************************************************/
//	Find the string starting after the start token.
STRING	CMicString::TokenRightGet(STRING search_str, STRING tkstart)
{
	FW_INT	ptoken	= -0x01;
	FW_INT	pstart	= 0x00;
	STR_DECLR(Ext);

	do{
		ptoken = STR_FIND_INDEX(search_str, tkstart, pstart);	//	Search for next ".".
		if(ptoken >= 0x00){								//	occurance is found
			pstart = ptoken;								//	keep pointer.
			pstart += STR_LEN(tkstart);	
		}
	}while(ptoken >= 0x00);

	//	Pass over the searched character.
	if((pstart >=0) && (pstart < (FW_INT)STR_LEN(search_str))) {
		STR_SET(Ext, STR_SUBSTR(search_str, pstart, STR_LEN(search_str) - pstart));
	}

	STR_RETURN(Ext);
}

//	Find the string starting after the "tkstart" token and ends before "tkend".
STRING	CMicString::TokenRangeGet(STRING search_str, STRING tkstart, STRING tkend)
{
	FW_INT		ptoken		= 0x00;
	FW_INT		range_start	= 0x00;
	FW_INT		range_end	= 0x00;
	STR_DECLR(Range);

	ptoken = STR_FIND_INDEX(search_str, tkstart, range_start);	//	Search for next ".".
	if(ptoken >= 0x00)
	{																//	occurrence is found.
		range_start = ptoken;								//	keep pointer.
		range_start += STR_LEN(tkstart);					//	Pass over the searched token.

		ptoken = range_end = range_start;
		ptoken = STR_FIND_INDEX(search_str, tkend, ptoken);	//	Search for next ".".
		if(ptoken > 0x00)	{
			range_end = ptoken;									//	keep pointer.
		}
	}
	if(range_end == range_start){
		if(STR_LEN(search_str) > (range_end + STR_LEN(tkend))){	//	Not empty range "()"
			range_end  = STR_LEN(search_str);			//	Till end if terminator not found.
		}
	}

	if((range_start >=0) && (range_start < range_end)) {
		STR_SET(Range, STR_SUBSTR(search_str, range_start,range_end - range_start));
	}
	STR_RETURN(Range);
}

STRING	CMicString::TokenRangeRmv(STRING search_str, STRING tkstart, STRING tkend)
{
	FW_INT		ptoken		= 0x00;
	FW_INT		range_start	= 0x00;
	FW_INT		range_end	= 0x00;
	STR_DECLR(NoRange);


	ptoken = 0x00;
	ptoken = STR_FIND_INDEX(search_str, tkstart, ptoken);	//	Search for next ".".
	if(ptoken >= 0x00){												//	occurance is found.
		range_start = ptoken;										//	keep pointer.
		ptoken += STR_LEN(tkstart);							//	Pass over the searched token.

		range_end = ptoken;
		ptoken = STR_FIND_INDEX(search_str, tkend, range_end);//	Search for next ".".
		if(ptoken > 0x00)	{
			range_end = ptoken;									//	keep pointer.
			range_end += STR_LEN(tkstart);					//	Pass over the searched token.
		}
	}

	if(range_start >=0){
		STR_SET(NoRange, STR_LEFT(search_str, range_start));
	}
	if(range_end < (FW_INT)STR_LEN(search_str)){
		STR_ADD(NoRange, STR_SUBSTR(search_str, range_end, STR_LEN(search_str) - range_start));
	}

	STR_RETURN(NoRange);
}

//	Find the string from start till the last appearance of the "tkend" token.
//	If the token is not found the whole string is returned.
STRING	CMicString::TokenLeftGet(STRING search_str, STRING tkend)
{
	FW_INT		ptoken	= 0x00;
	FW_INT		pend		= 0x00;
	STR_DECLR(Prefix);

	ASSERT(STR_LEN(tkend) != 0x00);
	do{
		ptoken = STR_FIND_INDEX(search_str, tkend, ptoken);	//	Search for next ".".
		if(ptoken >= 0x00){								//	token is found...
			pend = ptoken;									//	keep pointer.
			ptoken += STR_LEN(tkend);
		}
	}while(ptoken >= 0x00);
	
	if(0x00 == pend){
		pend = STR_LEN(search_str);
	}

	//	Pass over the searched character.
	if((pend >=0) && (pend <= (FW_INT)STR_LEN(search_str))) {
		STR_SET(Prefix, STR_SUBSTR(search_str, 0x00, pend));		//	The string from start till token.
	}
	STR_RETURN(Prefix);
}










/********************************************************************\
*																							*
*							T e x t   c o n t a i n e r s							*
*																							*
\********************************************************************/

//	Count the number of item appearances in the string.
FW_INT	CMicString::GetTextCount(STRING string, STRING item)
{
	FW_INT	count = 0x00;
	FW_INT	index = 0x00;

	while(index++>-1){
		index = STR_FIND_INDEX(string, item, index);	//	search number separator marker.
		count++;											//	increase counter.
	}
	count--;												//	remove not found item count.
	return(count);
}

//	the index of the next byte after count appearances of item in the string.
FW_INT	CMicString::GetTextIndex(STRING string, STRING item, FW_INT count)
{
	FW_INT	index = 0x00;

	while((index>-1) && (count>0x00)){
		index = STR_FIND_INDEX(string, item , index++);		//	search number separator marker.
		count--;
	}
	return(index);
}

//----------------------------------------------------------
//	Get Text item from Text string.
//	Items are separated by spaces " ".
//	The last Item in a string with no end marker will also returned. 
STRING	CMicString::GetTextItem(STRING page, STRING sep, FW_INT index)
{
	FW_INT	border_curr = 0x00;	//	Current segment border.
	FW_INT	border_next = 0x00;	//	Next segment border.
	STR_DECLR(replay);			//	Replay string.

	FW_INT	cntr = 0x00;
	do	{
		border_curr = border_next;
		border_next = STR_FIND_INDEX(page, sep, border_curr);		// search end of Item.
		if(STR_NOT_FOUND == border_next){
			border_next = STR_LEN(page);				// search End of String.
		}
		if(border_next >= border_curr)
			border_next++;									//	step over ","
		else
		{
			border_next = STR_NOT_FOUND;				//	Segment not found;
			break;
		}
		cntr++;
	}while(cntr <= index);

	if(STR_NOT_FOUND != border_next)
	{
		border_next--;																	//	Remove the end mark and return contents only.
		STR_DECLR_INIT(item, STR_SUBSTR(page, border_curr, (border_next-border_curr)));	//	Set as active item.
		replay = item;																//	return the item.
	}
	STR_RETURN(replay);
}

//----------------------------------------------------------
//	Get Text string from Text buffer
//	 *	Strings are seperated by new line.
//	The last Item in a string with no end marker will also returned.
STRING	CMicString::GetTextItem(STRING page, FW_INT index)
{
	FW_INT	border_curr = 0x00;	//	Current segment border.
	FW_INT	border_next = 0x00;	//	Next segment border.
	STR_DECLR(replay);			//	Replay string.

	FW_INT	cntr = 0x00;
	do	{
		border_curr = border_next;
		border_next = STR_FIND_INDEX(page, TAG_TXT_END, border_curr);		// search end of Item.
		if(border_next < 0x00){
			border_next = STR_FIND_INDEX(page, TAG_STR_END, border_curr);		// search end of Formation.
			if(border_next == STR_NOT_FOUND){
				border_next = STR_LEN(page);					// search End of String.
			}
		}

		if(border_next >= border_curr)
			border_next++;							//	step over ","
		else
		{
			border_next = -0x01;					//	Segment not found;
			break;
		}
		cntr++;
	}while(cntr<=index);

	if(border_next > 0x00)
	{
		border_next--;																	//	Remove the end mark and return contents only.
		STR_DECLR_INIT(item, STR_SUBSTR(page, border_curr, (border_next-border_curr)));	//	Set as active item.
		replay = item;																//	return the item.
	}
	STR_RETURN(replay);
}


//----------------------------------------------------------'
//	Get a record from a string according to the separatot tag.
//	<record1><tag><record2><tag>...
STRING	CMicString::TextRangeGet(STRING string, unsigned char tag_start, unsigned char tag_end, FW_INT index)
{
	STR_DECLR(replay);							//	Replay string.
	FW_INT	border_start = 0x00;					//	Current segment border.
	FW_INT	border_end = STR_LEN(string);		//	Initialise to string size.


	FW_INT	cntr = 0x00;
	do
	{	//	Search for start of list.
		cntr	++;											//	Next closure.
		border_start = STR_FIND_INDEX(string, tag_start,border_start) + 1;	// search for starting tag "(".
		if(border_start < 0x00){											//	end tag not found.
			border_start = STR_LEN(string);							// search End of String.
		}
	}while(cntr <= index);

	if(border_start >= 0x01)
	{
		cntr = 0x00;
		STR_SET(replay, STR_SUBSTR(string, border_start,border_end - border_start));	//	Keep the remaining string.	

		do
		{	//	Search for start of list.
			cntr	++;											//	Next closure.
			border_end -= 1;									//	Overlap the tag.
			border_end = STR_RFIND(replay, tag_end);	// search end of tag ")".

			if(border_end > 0x00){							//	end tag not found.
				STR_SET(replay,STR_SUBSTR(replay, 0,border_end));		//	
			}
			else{
				STR_CLEAR(replay);							// search Start of String.
			}
		}while(cntr <= index);

	}
	else{
		STR_CLEAR(replay);
	}
	STR_RETURN(replay);
}

STRING	CMicString::TextRangeRmv(STRING string, unsigned char tag_start, unsigned char tag_end, FW_INT index)
{
	STR_DECLR(enclosed);
	STR_DECLR(tmp);

	STR_SET(enclosed,TextRangeGet(string, tag_start, tag_end, index));
	
	STR_ADD_CHAR(tmp, tag_start);		//"("
	STR_ADD(tmp, enclosed);		//"(..."
	STR_ADD_CHAR(tmp, tag_end);		//"(...)"
	STR_SET(enclosed, tmp);

	STR_SET(tmp, STR_LEFT(string, STR_FIND(string, tmp)));
	if((STR_LEN(tmp) + STR_LEN(enclosed)) < STR_LEN(string))
	{
		STR_ADD(tmp, STR_RIGHT(string, STR_LEN(tmp) + STR_LEN(enclosed)));
	}
	STR_RETURN(tmp);
}









/********************************************************************\
*																							*
*										Border Search									*
*																							*
\********************************************************************/

//------------------------------------------------------------------------------------------
//	Get the tag border dis clouding text string marked by '#' tag.
FW_INT	CMicString::BorderFind(STRING description, STRING tag, FW_INT from)
{
	FW_INT	border_text = 0x00;
	FW_INT	border_new	= 0x00;

	border_text = from;
	border_new = STR_FIND_INDEX(description, tag, from);				// search End of formation end.
	if(border_new < 0x00){
		border_new = STR_LEN(description);
	}

	while((border_text>=0x00) && (border_text<border_new))				//	New text end found befor formation end.
	{
		border_text = STR_FIND_INDEX(description, TAG_STR_END, border_text);		// search beginning of text at the end of last search.
		if((border_text>=0x00) && (border_text<border_new))				//	New text start found befor formation end. 
		{
			border_text++;																//	Overlap text mark.
			border_text = STR_FIND_INDEX(description, TAG_STR_END, border_text);	// search text End.
			if(border_text < 0x00){													//	if not found - the rest of the string is text.
				border_text = STR_LEN(description);							// search End of formation string.
			}
			else{
				border_text++;															//	Overlap text mark.
			}
			if(border_text>border_new){											//	search new formation end after end of text.
				border_new = STR_FIND_INDEX(description, tag, border_text);	// search End of formation end.
				if(border_new < 0x00){
					border_new = STR_LEN(description);
				}
			}
		}
	}
	return(border_new);
}

//-------------------------------------------------------------------
//	Search the string from index till
//	the top most level of of the tags hierarchy.
FW_INT	CMicString::BorderFind(STRING description, STR_TAG tag, FW_INT from)
{
	STR_DECLR(border);
	FW_INT	indx_curr = from;
	FW_INT	indx_tag = 0x00;

	STR_SET(border, ENUM_NAME(STR_TAG, tag));						//	Set tag string.
	indx_curr = BorderFind(description, border ,from);		//	search the tag.

	tag = (STR_TAG)(tag - 1);											//	Next Tag.
	while(ENUM_UNDEF(STR_TAG) < tag)									//	While not last tag.
	{
		STR_SET(border, ENUM_NAME(STR_TAG, tag));					//	Set new tag string.
		indx_tag = BorderFind(description, border, from);	//	Get border of new tag.
		if((indx_tag > from) && (indx_tag < indx_curr)){		//	new tag before searched tag.
			indx_curr = indx_tag;										//	keep new border.
		}
		tag = (STR_TAG)(tag - 1);										//	Next tag.
	}
	return(indx_curr);
}

SRange	CMicString::RangeFind(STRING description, STR_TAG tag, FW_INT index)
{
	SRange	range = {0};
	FW_INT	cntr = 0x00;														//	number of ranges to pass.

	do	{
		range.from = range.to;												//	Keep current border.
		range.to = BorderFind(description, tag, range.from);		//	Get next borer.
		if(range.to >= range.from){										//	If new border found.
			range.to += STR_LEN(ENUM_NAME(STR_TAG, tag));			//	step over border.
		}
		else	{										//	Border not found;
			break;									//	Stop searching.
		}
		cntr++;
	}while(cntr <= index);						//	Last position not reached.

	if(range.to > range.from){
		range.to--;									//	Stop before the border.
	}
	range.length = range.to - range.from;	//	calculate the length.
	
	RETURN(range);
}
STRING	CMicString::RangeGet(STRING description, STR_TAG tag, FW_INT index)
{
	STR_DECLR(replay);

	SRange range = RangeFind(description, tag, index);
	if(range.length > 0x00){
		STR_SET(replay, STR_SUBSTR(description, range.from, range.length));
	}
	STR_RETURN(replay);
}

STRING	CMicString::RangeRemove(STRING& pDescription, STR_TAG tag, FW_INT index)
{
	STR_DECLR(replay);
	
	SRange range = RangeFind(pDescription, tag, index);
	if(range.length > 0x00){
		STR_SET(replay, STR_SUBSTR(pDescription, range.from, range.length));	//	Leep item string.

		if(range.from > 0x00){											//	Not the first range.
			range.from -= STR_LEN(ENUM_NAME(STR_TAG, tag));		//	Delet its border.
		}
		else	if(range.to < (FW_INT)STR_LEN(pDescription)){			//	First range but not only range in the string.
			range.to += STR_LEN(ENUM_NAME(STR_TAG, tag));		//	Delete its border; making the nex item to be first.
		}

		range.length = range.to - range.from;						//	Re calculate the borders length.
		STR_DELETE(pDescription, range.from, range.length);			//	Remove the range.
	}
	STR_RETURN(replay);
}









/********************************************************************\
*																							*
*											Item											*
*																							*
\********************************************************************/
//----------------------------------------------------------
//	Get LINK string from a string.
//	Get the string from a string containing links.
//	 *	a link is any string ending with '>'
//	The last Item in a string with no end marker will also returned. 
STRING	CMicString::GetLink(STRING chain,FW_INT index)
{
	FW_INT	border_curr = 0x00;			//	Current segment border.
	FW_INT	border_next = 0x00;			//	Next segment border.

	STR_DECLR(replay);					//	Replay string.

	FW_INT	cntr = 0x00;
//	my_item =	chain;

	do	{
		border_curr = border_next;
		border_next = BorderFind(chain, STR_TAG_LNK, border_curr);

		if(border_next<0x00){
			border_next = STR_LEN(chain);
		}
		if(border_next >= border_curr)
			border_next++;							//	step over ">"
		else
		{
			border_next = -0x01;					//	Link not found;
			break;
		}
		cntr++;
	}while(cntr <= index);

	if(border_next > 0x00)
	{
		border_next--;																//	Remove the end mark and return contents only.
		STR_SET(replay, STR_SUBSTR(chain, border_curr,(border_next-border_curr)));	//	Set as active item.
	}

	STR_RETURN(replay);
}












/********************************************************************\
*																							*
*											Page											*
*																							*
\********************************************************************/

//FW_RESULT	CMicString::LetPage(STRING	page)
//{
//	RES_DECLR(result);
//
//	my_page = page;
//	RES_CHECK(result,my_page == page);
//
//	RES_RETURN(result);
//}
//STRING	CMicString::GetPage(void)
//{
//	STR_RETURN(my_page);
//}

//----------------------------------------------
//	Get PAGE string.
//	 * The rturned page becomes the working array for reading data.
//	 * pages are seperated by ";"
//	 * Empty string is returned in case of error "".
FW_RESULT	CMicString::AddItem(STRING& page, STRING item)
{
	RES_DECLR(result);

	if(STR_NOT_EMPTY(page)){
		STR_ADD(page, TAG_ITM_END);
	}
	STR_ADD(page, item);

	RES_RETURN(result);
}
//----------------------------------------------------------
//	Get ITEM string from PAGE string.
//	Get the string contains items is written in texte.
//	 *	Item can be a number in "1,2,3.." or "0x01,0x02,..." or a general string
//	 *	Items are seperated using '>' or ';' or ':' or '.' seperators.
//	The last Item in a string with no end marker will also returned. 
STRING	CMicString::GetItem(STRING	page, FW_INT index)
{
	FW_INT	border_curr = 0x00;	//	Current segment border.
	FW_INT	border_next = 0x00;	//	Next item border.
	STR_DECLR(replay);			//	Replay string.

	FW_INT	cntr = 0x00;
	do	{
		border_curr = border_next;
		border_next = BorderFind(page, STR_TAG_ITM, border_curr);

		if(border_next<0x00){
			border_next = STR_LEN(page);
		}
		if(border_next >= border_curr)
			border_next++;							//	step over ","
		else
		{
			border_next = -0x01;					//	Segment not found;
			break;
		}
		cntr++;
	}while(cntr<=index);

	if(border_next > 0x00){
		border_next--;																	//	Remove the end mark and return contents only.
		STR_SET(replay, STR_SUBSTR(page, border_curr,(border_next-border_curr)));	//	Set as active item.
	}

	STR_RETURN(replay);
}
//	Set the new string as current page.
//	and returnd the requested item.
//STRING	CMicString::GetItem(STRING	page, FW_INT index=0x00)
//{
//	my_page = page;
//	STR_RETURN(GetItem(index));
//}









/********************************************************************\
*											Page											*
\********************************************************************/

//FW_RESULT	CMicString::LetSegment(STRING	segment)
//{
//	RES_DECLR(result);
//
//	my_segment = segment;
//	RES_CHECK(result,my_segment == segment);
//
//	RES_RETURN(result);
//}
//STRING	CMicString::GetSegment(void)
//{
//	STR_RETURN(my_segment);
//}

//----------------------------------------------
//	Get SEGMENT string from FORMATION string.
//	 * The rturned segment becomes the working segment
//		for reading data.
//	 * Segments are seperated by ":"
//	 * Empty string is returned in case of error "".
FW_RESULT	CMicString::AddPage(STRING&	segment, STRING page)
{
	RES_DECLR(result);

	if(STR_NOT_EMPTY(segment)){
		STR_ADD(segment, TAG_PAG_END);
	}
	STR_ADD(segment, page);

	RES_RETURN(result);
}

STRING	CMicString::GetPage(STRING	segment, FW_INT index)
{
	FW_INT	border_curr = 0x00;	//	Current segment border.
	FW_INT	border_next = 0x00;	//	Next segment border.
	STR_DECLR(replay);			//	Replay string.

	FW_INT cntr=0x00;
	do{
		border_curr = border_next;
		border_next = BorderFind(segment, STR_TAG_PAG, border_curr);

		if(border_next<0x00){
			border_next = STR_LEN(segment);
		}
		if(border_next >= border_curr)
			border_next++;							//	step over ";"
		else
		{
			border_next = -0x01;					//	End of page not found;
			break;									//	No need to continue search.
		}

		cntr++;
	}while(cntr<=index);

	if(border_next > 0x00)
	{
		border_next--;																	//	Remove the end mark and return contents only.
//		STR_SET(my_page, STR_SUBSTR(my_segment, border_curr, (border_next-border_curr)));	//	Set as active array.
//		STR_SET(replay, my_page);													//	return the array.
		STR_SET(replay, STR_SUBSTR(segment, border_curr, (border_next-border_curr)));		//	return the array.
	}
	STR_RETURN(replay);
}
STRING	CMicString::PageRemove(STRING& pDescription, FW_INT index)
{
	STR_DECLR(replay);
	STR_SET(replay, RangeRemove(pDescription, STR_TAG_PAG, index));
	STR_RETURN(replay);
}

//	Set the new string as current segment.
//	Get a string containing the segment page.
//STRING	CMicString::GetPage(STRING segment, FW_INT index)
//{
//	STR_DECLR(replay);			//	Replay string.
//
//	my_segment = segment;		//	Set the new string as current formation string.
//	STR_SET(replay,GetPage(index));	//	Get the segment inside the formation string.
//
//	STR_RETURN(replay);
//}









/********************************************************************\
*										Segment											*
\********************************************************************/

STRING	CMicString::GetSegment(STRING	formation, FW_INT index)
{
	FW_INT	border_curr = 0x00;	//	Current segment border.
	FW_INT	border_next = 0x00;	//	Next segment border.
	STR_DECLR(replay);			//	Replay string.

	FW_INT cntr = 0x00;
	do{
		//	Message Title					"title:"
		border_curr = border_next;

		border_next	=	BorderFind(formation, STR_TAG_SEG, border_curr);

		if(border_next<0x00){
			border_next = STR_LEN(formation);
		}
		if(border_next >= border_curr)
			border_next++;							//	step over ":"
		else
		{
			border_next = -0x01;					//	Segment not found;
			break;
		}
		cntr++;
	}while(cntr<=index);

	if(border_next > 0x00)
	{
		border_next--;																	//	Remove the end mark and return contents only.
		//STR_SET(my_segment, STR_SUBSTR(my_formation, border_curr,(border_next-border_curr)));
		//GetPage(my_segment, 0x00);
		//STR_SET(replay, my_segment);
		STR_SET(replay, STR_SUBSTR(formation, border_curr,(border_next-border_curr)));
	}

	STR_RETURN(replay);
}
//	Set the new string as current formation.
//	Get a string containing the segment.
//STRING	CMicString::GetSegment(STRING	str_formation, FW_INT index)
//{
//	STR_DECLR(replay);						//	Replay string.
//
//	my_formation = str_formation;			//	Set the new string as current formation string.
//	STR_SET(replay,GetSegment(index));	//	Get the segment inside the formation string.
//
//	STR_RETURN(replay);
//}









/********************************************************************\
*											Formation									*
\********************************************************************/

//-------------------------------
//FW_RESULT	CMicString::FormationLet(STRING	formation)
//{
//	RES_DECLR(result);
//
//	my_formation = formation;
//	RES_CHECK(result,my_formation == formation);
//
//	RES_RETURN(result);
//}
//	Add formation string.
STRING	CMicString::FormationAdd(STRING& description, STRING	formation)
{
	STR_ADD(formation,TAG_FRM_END);
	STR_ADD(formation, "\n");
	STR_ADD(formation, "\r");
	STR_ADD(description, formation);

	STR_RETURN(description);
}

STRING	CMicString::FormationGet(STRING description, FW_INT index)
{
	FW_INT	border_curr = 0x00;	//	Current segment border.
	FW_INT	border_next = 0x00;	//	Next segment border.
	FW_INT	border_text = 0x00;

	STR_DECLR(replay);			//	Replay string.

//	STR_SET(my_description,description);
	STR_REMOVE(description, '\r');
	STR_REMOVE(description, '\n');

	FW_INT cntr = 0x00;
	do{
		//	Message Title					"title:"
		border_curr = border_next;
		border_next = BorderFind(description,TAG_FRM_END,border_next);

		if(border_next < 0x00){											//	New border not found.
			border_next = STR_LEN(description);				// search End of formation string.
		}
		if(border_next >= border_curr)
		{
			border_next++;							//	step over "."
		}
		else
		{
			border_next = -0x01;					//	Segment not found;
			break;
		}
		if(border_next <= border_curr)
		{
			border_next = -0x01;					//	Segment not found;
			break;
		}

		cntr++;
	}while(cntr<=index);

	if(border_next > 0x00)
	{
		border_next--;																	//	Remove the end mark and return contents only.
		//STR_SET(my_formation, STR_SUBSTR(my_description, border_curr, (border_next-border_curr)));
		//GetSegment(my_formation,0x00);
		//STR_SET(replay,my_formation);
		STR_SET(replay, STR_SUBSTR(description, border_curr, (border_next-border_curr)));
	}

	STR_RETURN(replay);

}
STRING	CMicString::FormationRemove(STRING& pDescription, FW_INT index)
{
	STR_DECLR(replay);
	STR_SET(replay, RangeRemove(pDescription, STR_TAG_FRM, index));
	STR_RETURN(replay);
}









/********************************************************************\
*										Parameters										*
\********************************************************************/

//	Return a string within the borders of (...).
STRING	CMicString::ParametersGet(STRING	description)
{
	STR_RETURN(TokenRangeGet(description, TAG_PRM_OPEN, TAG_PRM_CLOSE));
}
//	Returns a string with out the taile "(...)".
STRING	CMicString::ParametersRemove(STRING& description)
{
	STR_RETURN(TokenRangeRmv(description, TAG_PRM_OPEN, TAG_PRM_CLOSE));
}









/********************************************************************\
*											Text											*
\********************************************************************/

//	Return a string within the borders of #...#.
STRING	CMicString::TextGet(STRING	description)
{
	STR_RETURN(TokenRangeGet(description, TAG_STR_END, TAG_STR_END));
}
//	Returns a string with out the taile "#..#".
STRING	CMicString::TextRemove(STRING& description)
{
	STR_RETURN(TokenRangeRmv(description, TAG_STR_END, TAG_STR_END));
}









/********************************************************************\
*									Description											*
\********************************************************************/

//FW_RESULT	CMicString::DescriptionLet(STRING	description)
//{
//	RES_DECLR(result);
//
//	STR_SET(my_description, description);
//	RES_CHECK(result, STR_NOT_EMPTY(my_description));
//	RES_CHECK(result, STR_CMP(my_description, description));
//
//	RES_RETURN(result);
//}
//STRING	CMicString::DescriptionGet(void)
//{
//	STR_RETURN(my_description);
//}





