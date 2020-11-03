/***********************************************************************\
*																								*
*										Xml Types											*
*																								*
\***********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"





/***********************************************************************\
*																								*
*									Header files											*
*																								*
\***********************************************************************/
#include	HDR_FW_XML_TYPES









ENUM_NAMES_CREATE(XML_PROP, XML_PROP_NAMES);
ENUM_NAMES_CREATE(XML_DATA, XML_DATA_NAMES);






STRING	XmlPropGet(XML_PROP prop, STRING str)
{
	STR_DECLR(prop_str);

	STR_ADD(prop_str, ENUM_NAME(XML_PROP, prop));
	STR_ADD(prop_str, str);
	STR_ADD(prop_str, XML_PROP_END);


	STR_RETURN(prop_str);
}
STRING	XmlPropGet(XML_PROP prop, long num)
{
	STR_DECLR(prop_str);

	STR_DECLR(tmp_str);
	STR_ADD(tmp_str,NumToStr(num,false));

	STR_ADD(prop_str, XmlPropGet(prop, tmp_str));


	STR_RETURN(prop_str);
}

STRING	XmlPropData(XML_DATA data, STRING str)
{
	STR_DECLR(tmp_str);

	STR_ADD(tmp_str, XmlPropGet(XML_PROP_TYPE, ENUM_NAME(XML_DATA, data)));

	STR_ADD(tmp_str, STR_SPACE);
	STR_ADD(tmp_str, XmlPropGet(XML_PROP_VALUE, str));

	STR_RETURN(tmp_str);
}

STRING	XmlPropData(XML_DATA data, long num)
{
	STR_DECLR(prop_str);

	STR_ADD(prop_str, XmlPropGet(XML_PROP_TYPE, ENUM_NAME(XML_DATA, data)));

	STR_ADD(prop_str, STR_SPACE);
	STR_DECLR(tmp_str);
	STR_ADD(tmp_str, NumToStr(num,false));
	STR_ADD(prop_str,	XmlPropGet(XML_PROP_VALUE, tmp_str));
	STR_RETURN(prop_str);
}
