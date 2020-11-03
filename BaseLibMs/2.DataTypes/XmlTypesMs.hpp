/***********************************************************************\
*																								*
*				Assembly types.h: .														*
*																								*
\***********************************************************************/
#ifndef	XML_TYPES_H
#define	XML_TYPES_H
	#include "../../../0.Framework/BaseLibMs/0.Config/ConfigMs.h"
	#include "../../../0.Framework/BaseLibMs/0.Config/IncludesMs.h"






/***********************************************************************\
*																								*
*									Include Files.											*
*																								*
\***********************************************************************/
//#include	HDR_ASSEMBLY_TYPES
#include	HDR_FW_ENUMS







	/***********************************************************************\
	*																								*
	*								Configuration types.										*
	*																								*
	\***********************************************************************/

	#define	XML_NOD_BEGIN			_T("<")
	#define	XML_NOD_END				_T(">")
	#define	XML_NOD_FINISH			_T("/>")
	#define	XML_PROP_END			_T("\"")
	#define	XML_TAG_BEGIN			_T("</")
	#define	XML_TAG_END				_T(">")

	#define MODULE_TYPE_STR			_T("Module")
	#define CONTROLLER_TYPE_STR	_T("Controller")

	#define	PROP_NAME				_T("name=\"")



	#define XML_DATA_FIELDS	\
			PROP_EXPTION		\
		,	PROP_COM_PORT		\
		,	PROP_TEMP_C			\
		,	PROP_POS_STPS		\
		,	PROP_POS_STRT		\
		,	PROP_POS_HOME		\
		,	PROP_POS_END		\
		,	PROP_MOV_SPEED		\
		,	PROP_STATE			\
		,	PROP_STATE_TIME	\
		,	PROP_STATUS			\
		,	PROP_STATUS_TIME	\
		,	PROP_RLU_SAMPL		\
		,	PROP_RLU_MESUR		\
		,	PROP_PULSES			\
		,	PROP_PROC_STEP		\
		,	PROP_PROC_STATE	\
		,	PROP_PROC_EVENT	\
		,	PROP_VERSION		\
		,	PROP_SCHD_STEP		\
		,	PROP_SIZE			\
		,	PROP_CONTNTS		\
		,	PROP_CONT_ALRT		\
		,	PROP_TIME			\
		,	PROP_TIME_STRT		\
		,	PROP_TIME_ALRT		\
		,	PROP_TIME_END		\
		,	PROP_FILL_EXPR		\
		,	PROP_PREP_EXPR		\
		,	PROP_READY_EXPR	\
		,	PROP_TCP_IP			\
		,	PROP_TCP_PORT		\
		/*XML_DATA_FIELDS*/
	#define XML_DATA_NAMES	\
			"Exception"			\
		,	"ComPort"			\
		,	"tempC"				\
		,	"position"			\
		,	"pos_strt"			\
		,	"pos_home"			\
		,	"pos_end"			\
		,	"mov_speed"			\
		,	"state"				\
		,	"state_time"		\
		,	"status"				\
		,	"status_time"		\
		,	"RluSampl"			\
		,	"RluMesur"			\
		,	"Pulses"				\
		,	"ProcStep"			\
		,	"ProcState"			\
		,	"ProcEvent"			\
		,	"Version"			\
		,	"SchdStep"			\
		,	"Size"				\
		,	"Contnts"			\
		,	"ContAlrt"			\
		,	"Time"				\
		,	"TimeStrt"			\
		,	"TimeAlrt"			\
		,	"TimeEnd"			\
		,	"FillExpr"			\
		,	"PrepExpr"			\
		,	"ReadyExpr"			\
		,	"TcpIp"				\
		,	"TcpPort"			\
		/*XML_DATA_NAMES*/
	ENUM_DEFINE(XML_DATA, XML_DATA_FIELDS);
	ENUM_NAMES_EXTERN(XML_DATA);

	#define XML_PROP_FIELDS	\
			PROP_RESULT			\
		,	XML_PROP_TEXT		\
		,	XML_PROP_VALUE		\
		,	XML_PROP_PATH		\
		,	XML_PROP_TIME		\
		,	XML_PROP_DATA		\
		,	XML_PROP_TYPE		\
		,	XML_PROP_CONT		\
		/*CONN_FIELDS*/
	#define XML_PROP_NAMES	\
			"res=\""		\
		,	"text=\""		\
		,	"value=\""		\
		,	"path=\""		\
		,	"time=\""		\
		,	"data=\""		\
		,	"type=\""		\
		,	"contnt=\""		\
		/*CONN_NAMES*/
	ENUM_DEFINE(XML_PROP, XML_PROP_FIELDS);
	ENUM_NAMES_EXTERN(XML_PROP);








	/***********************************************************************\
	*																								*
	*								Applivcation Functions.									*
	*																								*
	\***********************************************************************/
	STRING	XmlPropGet(XML_PROP prop, STRING str);
	STRING	XmlPropGet(XML_PROP prop, long num);
	STRING	XmlPropData(XML_DATA data, STRING str);
	STRING	XmlPropData(XML_DATA data, long num);
#endif	/*XML_TYPES_H*/
