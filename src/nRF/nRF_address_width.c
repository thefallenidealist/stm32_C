/*************************************************************************************************
				nRF_set_address_width()
*************************************************************************************************/
void nRF_set_address_width(nRF_hw_t *nRF0, uint8_t width)				// reg 0x03
{
	if ( (width < 3) || (width > 5) )
	{
		ERROR("Wrong address width\n");
	}
	else
	{
		// 11 = 5, 10 = 4, 01 = 3 bytes width address
		uint8_t new_width = width - 2;	// jer mu je 0b00 zapravo 2

		bool b1, b0;
		b0 = new_width & 1;
		b1 = (new_width >> 1) & 1;

		reg_tmp[AW1] = b1;
		reg_tmp[AW0] = b0;
		write_reg(nRF0, REG_SETUP_AW);

		// write into object
		nRF0->address_width = width;
		//printf("%s(): address width is: %d\n", __func__, nRF0->address_width);
		//printf("%s(): address width is: %d\n", __func__, width);
	}
}

/*************************************************************************************************
				nRF_get_address_width()
*************************************************************************************************/
uint8_t nRF_get_address_width(nRF_hw_t *nRF0)							// reg 0x03
{
	//uint8_t width = read_reg(nRF0, REG_SETUP_AW) + 2; // jer mu je "0b01" zapravo 3	// XXX ovo
	//se sjebe na RX modulu, iako na TX radi

	uint8_t width = nRF0->address_width;

	if ( (width < 3) || (width > 5) )
	{
		ERROR("Width should be 3, 4 or 5\n");
	}

	//printf("%s(): address width: %d\n", __func__, width);

	return width;
}
