/*************************************************************************************************
				ce()
*************************************************************************************************/
static void ce(nRF_hw_t *nRF0, state_t state)
{
	char *ce = nRF0->ce;
	gpio_write(ce, state);
}

/*************************************************************************************************
				cs()
*************************************************************************************************/
static void cs(nRF_hw_t *nRF0, state_t state)
{
	char *cs = nRF0->cs;
	gpio_write(cs, state);
}
