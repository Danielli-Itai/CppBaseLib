#ifndef FW_STRING_CLI_HPP
#define	FW_STRING_CLI_HPP

	#ifdef	__cplusplus_cli
		//#define		STRING							string
		//#define		STR_EMPTY							""

		#define	STRING_MNG			String
		#define	STRING_PRM			STRING_MNG^
		#define	STRING_REF			STRING_MNG^%

		#define	STR_SET_MNG(STR,SET)	STR = gcnew STRING_MNG(SET);
	#endif	/*!__cplusplus_cli*/

#endif