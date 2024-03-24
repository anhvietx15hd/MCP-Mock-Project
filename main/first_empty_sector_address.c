uint32_t first_empty_sector_address(void)
{
	uint32_t sector_address;
	uint32_t * sector_address_ptr = (uint32_t*)malloc(sizeof(uint32_t));

	(*sector_address_ptr) = 0x00000800U; //start at sector 3

	while ( (*(uint32_t*)*sector_address_ptr) != 0xFFFFFFFF )
	{
		(*sector_address_ptr) += 0x00000400U;
	}

	sector_address = (*sector_address_ptr);
	free(sector_address_ptr);

	return sector_address;
}