/*************************************************************************************************
				nRF_is_TX_data_sent()
*************************************************************************************************/
bool nRF_is_TX_data_sent(nRF_hw_t *nRF0)							// reg 0x06, b5
{
	//Data Sent TX FIFO interrupt. Asserted when 
	//packet transmitted on TX. If AUTO_ACK is acti-
	//vated, this bit is set high only when ACK is 
	//received.
	//Write 1 to clear bit.

	uint8_t status = read_reg(nRF0, REG_STATUS);
	return ((status >> TX_DS) & 1);		// after reset: 0
}
// INFO provjereno
