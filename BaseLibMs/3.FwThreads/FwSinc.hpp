#ifndef FW_SINC_HPP
#define	FW_SINC_HPP
	#include "../../../0.Framework/BaseLib/0.Config/Config.h"
	#include "../../../0.Framework/BaseLib/0.Config/Includes.h"
	/**************************************************************************\
	*																									*
	*										Slave Thread											*
	*																									*
	\**************************************************************************/
	#include <mutex>          // std::mutex
	#include <chrono>
	#include <condition_variable>





	/**************************************************************************\
	*																									*
	*												Mutex												*
	*																									*
	\**************************************************************************/
	#define	MUTEX_DECLR(NAME)							\
			std::mutex					NAME##_mutex;	\
			/*SINC_FLAG_DECLR*/

	#define	MUTEX_LOCK(NAME)		NAME##_mutex.lock()
			/*MUTEX_LOCK*/

	#define	MUTEX_UNLOCK(NAME)	NAME##_mutex.unlock()
			/*MUTEX_UNLOCK*/





	/**************************************************************************\
	*																									*
	*										Slave Thread											*
	*																									*
	\**************************************************************************/
	#define	SINC_LOCK_DECLR(FLAG)					\
			std::mutex					FLAG##_mutex;	\
			std::condition_variable FLAG##_flag;	\
		/*SINC_FLAG_DECLR*/


	#define	SINC_LOCK(FLAG)													\
			std::unique_lock<std::mutex> FLAG##_lock(FLAG##_mutex, std::defer_lock_t);	\
			if(true != FLAG##_lock.try_lock()){								\
				FLAG##_flag.wait(FLAG##_lock);								\
			}																			\
		/*SLAVE_FLAG*/

	#define	SINC_UNLOCK(FLAG)			\
			/*FLAG##_processed = true;*/	\
			FLAG##_lock.unlock();			\
			FLAG##_flag.notify_one();		\
			/*SINC_FLAG_UNLOCK*/

	#define	SINC_QUITE(FLAG)				\
			FLAG##_quite = true;				\
			FLAG##_flag.notify_one();		\
			/*SINC_FLAG_UNLOCK*/

	#define	SINC_IS_ACTIVE(FLAG)	(true != FLAG##_quite)





			



	/**************************************************************************\
	*																									*
	*										Threads Sinc Flags 									*
	*																									*
	\**************************************************************************/
	#define	SINC_FLAG_DECLR(FLAG)						\
			std::mutex					FLAG##_mutex;		\
			std::condition_variable FLAG##_flag;		\
			bool				FLAG##_quite = false;		\
			bool				FLAG##_ready = false;		\
			bool				FLAG##_processed = true;	\
		/*SINC_FLAG_DECLR*/
	#define	SINC_FLAG_EXTERN(FLAG)							\
			extern std::mutex					FLAG##_mutex;	\
			extern std::condition_variable FLAG##_flag;	\
			extern bool				FLAG##_quite;				\
			extern bool				FLAG##_ready;				\
			extern bool				FLAG##_processed;			\

  	#define	SINC_QUITE(FLAG)				\
			FLAG##_quite = true;				\
			FLAG##_flag.notify_one();		\
			/*SINC_FLAG_UNLOCK*/

	#define	SINC_IS_ACTIVE(FLAG)	(true != FLAG##_quite)





	/**************************************************************************\
	*																									*
	*										Master Threads											*
	*																									*
	\**************************************************************************/
	#define	SINC_MASTER_LOCK(FLAG)													\
		std::lock_guard<std::mutex> FLAG##_lock(FLAG##_mutex);				\
		/*SINC_MASTER_LOCK*/

	#define	SINC_MASTER_WAITE(FLAG)													\
			FLAG##_ready = true;															\
			FLAG##_flag.notify_one();													\
			if(SINC_IS_ACTIVE(FLAG)){													\
				std::unique_lock<std::mutex> FLAG##_lock(FLAG##_mutex);		\
				FLAG##_flag.wait(FLAG##_lock, []{return FLAG##_processed;});\
				FLAG##_processed = false;												\
			}
			/*SINC_MASTER_WAITE*/


	#define	SINC_MASTER_PLOCK_MMBR(FLAG)											\
		PTR_MEMBER(std::lock_guard<std::mutex>, FLAG##_plock);				\

	#define	SINC_MASTER_PLOCK_MMBR_INIT(FLAG)									\
		PTR_MEMBER_INIT(FLAG##_plock)													\

	#define	SINC_MASTER_PLOCK_DCLR(FLAG)											\
		PTR_DECLR(std::lock_guard<std::mutex>, FLAG##_plock);					\
		/*SINC_MASTER_LOCK*/

	#define	SINC_MASTER_PLOCK_LOCK(FLAG)													\
		PTR_CREATE_INIT(std::lock_guard<std::mutex>,FLAG##_plock, FLAG##_mutex);\
		/*SINC_MASTER_PLOCK_LOCK*/

	#define	SINC_MASTER_PLOCK_WAITE(FLAG)													\
			FLAG##_ready = true;															\
			PTR_DESTROY(FLAG##_plock);													\
			FLAG##_flag.notify_one();													\
			if(SINC_IS_ACTIVE(FLAG)){													\
				std::unique_lock<std::mutex> FLAG##_lock(FLAG##_mutex);		\
				FLAG##_flag.wait(FLAG##_lock, []{return FLAG##_processed;});\
				FLAG##_processed = false;												\
			}
			/*SINC_MASTER_WAITE*/




	/**************************************************************************\
	*																									*
	*										Slave Thread											*
	*																									*
	\**************************************************************************/
	#define	SINC_SLAVE_WAITE(FLAG)											\
			std::unique_lock<std::mutex> FLAG##_lock(FLAG##_mutex);	\
			FLAG##_flag.wait(FLAG##_lock, []{return FLAG##_ready;});	\
			FLAG##_ready = false;												\
		/*SLAVE_FLAG*/

	#define	SINC_SLAVE_END(FLAG)			\
			FLAG##_processed = true;		\
			FLAG##_lock.unlock();			\
			FLAG##_flag.notify_one();		\
			/*SINC_FLAG_UNLOCK*/

#endif // !FW_SINC_HPP
