/*************************************************************************************************
				nRF_set_mode()
*************************************************************************************************/
void nRF_set_mode(nRF_hw_t *nRF0, nRF_mode_t mode)
{
	// INFO PWR_UP treba bit 1 prije stimanja?
	// TODO
	if (nRF0 == NULL)
	{
		ERROR("Wrong nRF module address\n");
		printf("Wrong nRF module address\n");
	}
	else if (mode > RX)
	{
		ERROR("Wrong mode\n");
		printf("Wrong mode\n");
	}
	else
	{
		/*
		if ( (mode == RX) || (mode == TX) )
		{
			reg_tmp[PRIM_RX] = mode;
			write_reg(nRF0, REG_CONFIG);
			delay_us(130);	// TX/RX settling, datasheet page 22
			// zapisi i u objekt
			nRF0->mode = mode;
		}
		*/
		// CHANGED 160613
		/*
		For nRF24L01+ to go from power down mode to TX or RX mode it must first pass through stand-by mode. 
		There must be a delay of Tpd2stby (see Table 16.) after the nRF24L01+ leaves power down mode before 
		the CE is set high.
		*/
		if (mode == RX)
		{
			delay_ms(5);	// worst case Tpd2stby
			ce(nRF0, 1);
			reg_tmp[PRIM_RX] = 1;
			write_reg(nRF0, REG_CONFIG);
			delay_us(130);	// TX/RX settling, datasheet page 22

			// zapisi i u objekt
			nRF0->mode = mode;
			// sad je u RX modu
		}
		else if (mode == TX)
		{
			delay_ms(5);	// worst case Tpd2stby
			ce(nRF0, 0);
			reg_tmp[PRIM_RX] = 0;
			write_reg(nRF0, REG_CONFIG);
			delay_us(130);	// TX/RX settling, datasheet page 22

			// zapisi i u objekt
			nRF0->mode = mode;
			// sad je u TX modu
		}
		else
		{
			ERROR("Wrong mode\n");
			printf("Wrong mode\n");
		}
	}
}

/*************************************************************************************************
				nRF_get_mode()
*************************************************************************************************/
nRF_mode_t nRF_get_mode(nRF_hw_t *nRF0)
{
	nRF_mode_t mode = MODE_ERROR;

	uint8_t status = read_reg(nRF0, REG_CONFIG);
	mode = status & 1;

	return mode;
}
