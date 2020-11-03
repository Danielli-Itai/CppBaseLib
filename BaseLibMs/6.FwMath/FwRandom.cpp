/********************************************************************\
*																							*
*									Random Numbers										*
*																							*
\********************************************************************/
#include "../../../0.Framework/BaseLib/0.Config/Config.h"
#include "../../../0.Framework/BaseLib/0.Config/Includes.h"




/********************************************************************\
*																							*
*									Include Files										*
*																							*
\********************************************************************/
#include	<cstdlib>
#include	HDR_FW_RANDOM





/********************************************************************\
*																							*
*									Include Files										*
*																							*
\********************************************************************/
// Generate a random number with power-law distribution.
double rand_ps(double base)
{
	double n = rand() % 100;
	n = n * n * n;
	return n / 100;
}
