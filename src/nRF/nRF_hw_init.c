/*************************************************************************************************
				nRF_hw_init()
*************************************************************************************************/
int8_t nRF_hw_init(nRF_hw_t *nRF0)
{
	DEBUG_START;

	char *cs = nRF0->cs;
	char *ce = nRF0->ce;
	char *irq = nRF0->irq;
	uint16_t prescaler = nRF0->spi_prescaler;

	if (strlen(cs) != 0)
	{
		//printf("%s(): cs: %s\n", __func__, cs);
		gpio_init(cs, OUT);
	}
	else
	{
		ERROR("CS pin not connected\n");
	}

	if (strlen(ce) != 0)
	{
		//printf("%s(): ce: %s\n", __func__, nRF0->ce);
		gpio_init(ce, OUT);
	}
	else
	{
		ERROR("CE pin not connected\n");
	}

	if (strlen(irq) != 0)
	{
		//printf("%s(): irq: %s\n", __func__, nRF0->irq);
		gpio_init(irq, IN);
	}
	else
	{
		DEBUG_INFO("IRQ pin not connected\n");
	}

	//if (spi_init(1, prescaler))
	if (spi_init(nRF0->spi_port, prescaler))
	{
		ERROR("SPI not initialized\n");

		DEBUG_END;
		return -1;
	}

	DEBUG_END;
	return 0;
}
