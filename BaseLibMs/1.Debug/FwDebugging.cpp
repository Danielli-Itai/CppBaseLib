/********************************************************************\
*																							*
*										Debugginh										*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





/********************************************************************\
*																							*
*										Include Files									*
*																							*
\********************************************************************/
#include	HDR_FW_STRING
#include	HDR_FW_DEBUGGING





/***********************************************************************\
*																								*
*										D e b u g g i n g									*
*																								*
\***********************************************************************/
STRING	GetLinePath(STRING file, STRING func, int line)
{
//          std::ostringstream stringStream;
//          stringStream << file << ": " << func << "() " <<  line << "";
//		STR_DECLR(line_path);
//	 STR_FORMAT(line_path.c_str(),("%s: %s() %d ", file, func, line));
//		  STR_RETURN(stringStream.str());
  	STR_DECLR(line_path);
	STR_ADD(line_path, file + ": ");
	STR_ADD(line_path, func + " ");
	STR_TO_DEC(line_path, line);
	STR_RETURN(line_path);
}


ENUM_DECLR(DEBUG_LEVEL, AppDebugLevel);
bool	DebugChk(DEBUG_LEVEL level)
{
      return(AppDebugLevel < level);
}







