ohc_core_field_t**	core_fields = NULL;
uint16_t			core_fieldnum = 0;

//Initializes OHC_CORE. Must be called before calling any other functions from core
uint8_t core_setup(uint16_t fieldnum)
{
	if(fieldnum > 0)
	{
		core_fieldnum = fieldnum;
		core_fields = malloc(fieldnum * sizeof(ohc_core_field_t*));
		if(core_fields == NULL)
			return CORE_ERROR_OUT_OF_MEM;
	}
	return CORE_OK;
}

uint8_t core_register_field(uint16_t id, uint8_t* fieldptr, uint16_t length, uint8_t r, uint8_t w)
{
	if(id >= core_fieldnum)
		return CORE_ERROR_NO_SUCH_FIELD;
	ohc_core_field_t* field = malloc(sizeof(ohc_core_field_t));
	if(field == NULL)
		return CORE_ERROR_OUT_OF_MEM;
	field->data = fieldptr;
	field->length = length;
	field->perms.r = r;
	field->perms.w = w;
	core_fields[id] = field;
	return CORE_OK;
}

uint8_t core_unregister_field(uint16_t id)
{
	if(id >= core_fieldnum)
		return CORE_ERROR_NO_SUCH_FIELD;
	free(core_fields[id]);
	core_fields[id] = NULL;
	return CORE_OK;
}

uint8_t core_write_field(uint16_t id, uint8_t* data, uint16_t offset, uint16_t length)
{
	if(id >= core_fieldnum)
		return CORE_ERROR_NO_SUCH_FIELD;
	ohc_core_field_t* field = core_fields[id];
	if(field == NULL)
		return CORE_ERROR_EMPTY_FIELD;
	if(length > field->length)
		return CORE_ERROR_OUT_OF_FIELD_BOUNDS;
	memcpy(field->data, data + offset, length);
	return CORE_OK;
}

uint8_t core_read_field(uint16_t id, uint8_t* data, uint16_t offset, uint16_t length)
{
	if(id >= core_fieldnum)
		return CORE_ERROR_NO_SUCH_FIELD;
	ohc_core_field_t* field = core_fields[id];
	if(field == NULL)
		return CORE_ERROR_EMPTY_FIELD;
	if((length + offset) > field->length)
		return CORE_ERROR_OUT_OF_FIELD_BOUNDS;
	memcpy(data, field->data + offset, length);
	return CORE_OK;
}

uint8_t core_write_field_ext(uint16_t id, uint8_t* data, uint16_t offset, uint16_t length)
{
	if(id >= core_fieldnum)
		return CORE_ERROR_NO_SUCH_FIELD;
	ohc_core_field_t* field = core_fields[id];
	if(field == NULL)
		return CORE_ERROR_EMPTY_FIELD;
	if(!field->perms.w)
		return CORE_ERROR_PERMISSION_DENIED;
	if(length > field->length)
		return CORE_ERROR_OUT_OF_FIELD_BOUNDS;
	memcpy(field->data, data + offset, length);
	return CORE_OK;
}

uint8_t core_read_field_ext(uint16_t id, uint8_t* data, uint16_t offset, uint16_t length)
{
	if(id >= core_fieldnum)
		return CORE_ERROR_NO_SUCH_FIELD;
	ohc_core_field_t* field = core_fields[id];
	if(field == NULL)
		return CORE_ERROR_EMPTY_FIELD;
	if(!field->perms.r)
		return CORE_ERROR_PERMISSION_DENIED;
	if((length + offset) > field->length)
		return CORE_ERROR_OUT_OF_FIELD_BOUNDS;
	memcpy(data, field->data + offset, length);
	return CORE_OK;
}
