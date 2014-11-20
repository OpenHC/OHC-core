#ifndef _OHC_CORE_H_
#define _OHC_CORE_H_

	#include <stdlib.h>
	#include <string.h>
	
	//Typedef
	typedef struct  
	{
		uint8_t*	data;
		uint16_t	length;
		struct
		{
			uint8_t r:1;
			uint8_t w:1;
		}
		perms;
	}
	ohc_core_field_t;
	
	//Exit codes
	#define CORE_OK 0
	#define CORE_ERROR_OUT_OF_MEM 1
	#define CORE_ERROR_NO_SUCH_FIELD 2
	#define CORE_ERROR_EMPTY_FIELD 3
	#define CORE_ERROR_OUT_OF_FIELD_BOUNDS 4
	#define CORE_ERROR_PERMISSION_DENIED 5
	
	extern uint8_t core_setup(uint16_t fieldnum);
	extern uint8_t core_register_field(uint16_t id, uint8_t* fieldptr, uint16_t length, uint8_t r, uint8_t w);
	extern uint8_t core_unregister_field(uint16_t id);
	extern uint8_t core_write_field_ext(uint16_t id, uint8_t* data, uint16_t offset, uint16_t length);
	extern uint8_t core_read_field_ext(uint16_t id, uint8_t* data, uint16_t offset, uint16_t length);
	
	#include "core.c"
#endif