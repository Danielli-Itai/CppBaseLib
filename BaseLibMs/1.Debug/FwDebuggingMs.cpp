#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"



/***********************************************************************\
*																								*
*											Include Files									*
*																								*
\***********************************************************************/
#include	HDR_FW_DEBUGGING





/***********************************************************************\
*																								*
*										D e b u g g i n g									*
*																								*
\***********************************************************************/

STRING	GetLinePath(STRING file, STRING func, int line)
{
	STR_DECLR(line_path);
	STR_FORMAT(line_path, "%s: %s() %d ", (file, func , line));
	STR_RETURN(line_path);
}

ENUM_DECLR(DEBUG_LEVEL, AppDebugLevel);
bool	DebugChk(DEBUG_LEVEL level)
{
	return(AppDebugLevel < level);
}

