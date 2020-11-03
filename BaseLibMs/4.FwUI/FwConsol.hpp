#ifndef FW_CONSOLE_HPP
#define	FW_CONSOLE_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"
	/**************************************************************************\
	*																									*
	*										Include Files											*
	*																									*
	\**************************************************************************/
	#include <conio.h>
	#include <iostream>     // std::cout
	#include <sstream>      // std::stringstream





	/**************************************************************************\
	*																									*
	*										Definitions												*
	*																									*
	\**************************************************************************/
	#define	CONSOL_ROWS_COUNT	40

	#define	CONSOL_OUT(CONT, MSG){	\
		std::stringstream CONT;			\
		CONT <<  std::endl << MSG;		\
		printf(CONT.str().c_str());}	\
		/*CONSOL_OUT*/

	#define	CONSOL_OUT_HEX(CONT, MSG){	\
		std::stringstream CONT;				\
		CONT << std::hex << MSG;			\
		printf(CONT.str().c_str());}		\
		/*CONSOL_OUT*/

	#define	CONSOL_CLEAR				\
		system("cls");						\
		/*CONSOL_CLEAR*/
#endif // !FW_CONSOLE_HPP




