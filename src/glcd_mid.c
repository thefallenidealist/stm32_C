/*
   srednji layer, mijenja se u ovisnosti o LCDu, vjerojatno i protokolu

   sadrzi init
   	writeCmd
	writeData

   moguce da send* pizdarije pripadaju low level dijelu

   */

// preimenovat writeCmd u writeCmd i sl

#include "glcd_mid.h"

	//printf("\t\t\tDEBUG\n");

void glcd_writeCmd(uint8_t data)
{
	glcd_dc_low();
	glcd_cs_low();
	//spi_write(data);
	spi_write_fast(1, data);
	//spi_rw(data);
	glcd_cs_high();
}

void glcd_writeData(uint8_t data)
{
	glcd_dc_high();
	glcd_cs_low();
	//spi_write(data);
	spi_write_fast(1, data);
	//spi_rw(data);
	glcd_cs_high();
}

void glcd_writeData16(uint16_t data)
{
	/*
	unsigned char dataH = data >> 8;
	unsigned char dataL = data & 0xFF;
	*/

	glcd_dc_high();
	glcd_cs_low();
	/*
	spi_write_fast(dataH);
	spi_write_fast(dataL);
	*/
	spi_write16_fast(1, data);
	//spi_rw16(data);	// XXX razjebe
	glcd_cs_high();
}

void glcd_ili9341_init(void)
{
	glcd_cs_high();
	glcd_dc_high();

	glcd_rst_on();
	delay_ms(10);
	glcd_rst_off();

	// "neka se nadje": u boljim danima radi bez toga, kad zvijezde nisu dobro nastimane
	// onda radi samo nakon prvog reflasha

	//glcd_setOrientation(P1);	// default

	glcd_writeCmd(ILI9341_CMD_POWER_ON_SEQ_CONTROL);
	glcd_writeData(ILI9341_CMD_IDLE_MODE_ON);
	glcd_writeData(ILI9341_CMD_MEMORY_WRITE);
	glcd_writeData(ILI9341_CMD_NOP);
	glcd_writeData(ILI9341_CMD_TEARING_EFFECT_LINE_OFF);
	glcd_writeData(0x02); 

	glcd_writeCmd(ILI9341_CMD_POWER_CONTROL_B);
	glcd_writeData(ILI9341_CMD_NOP);
	glcd_writeData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_writeData(ILI9341_CMD_PARTIAL_AREA);

	glcd_writeCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
	glcd_writeData(0x85);
	glcd_writeData(ILI9341_CMD_NOP);
	glcd_writeData(0x78);

	glcd_writeCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
	glcd_writeData(ILI9341_CMD_NOP);
	glcd_writeData(ILI9341_CMD_NOP);

	glcd_writeCmd(0xED);
	glcd_writeData(0x64);
	glcd_writeData(0x03);
	glcd_writeData(ILI9341_CMD_PARTIAL_MODE_ON);
	glcd_writeData(0X81);

	glcd_writeCmd(ILI9341_CMD_PUMP_RATIO_CONTROL);
	glcd_writeData(ILI9341_CMD_DISP_INVERSION_OFF);

	glcd_writeCmd(ILI9341_CMD_POWER_CONTROL_1);
	glcd_writeData(0x23);	//VRH[5:0]

	glcd_writeCmd(ILI9341_CMD_POWER_CONTROL_2);
	glcd_writeData(ILI9341_CMD_ENTER_SLEEP_MODE);
	delay_ms(DELAY120);						// neka se nadje

	glcd_writeCmd(ILI9341_CMD_VCOM_CONTROL_1);
	glcd_writeData(ILI9341_CMD_READ_MEMORY_CONTINUE);
	glcd_writeData(ILI9341_CMD_DISPLAY_OFF);
	delay_ms(DELAY120);		// treba inace inicijalizira 2/3 ekrana

	glcd_writeCmd(ILI9341_CMD_VCOM_CONTROL_2);
	glcd_writeData(0x86);

	glcd_writeCmd(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_writeData(0x48);	//C8	//48 68gal.gal.gal.//28 E8 gal.gal.gal.	

	glcd_writeCmd(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
	glcd_writeData(ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS);

	glcd_writeCmd(ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL);
	glcd_writeData(ILI9341_CMD_NOP);
	glcd_writeData(0x18); 

	glcd_writeCmd(ILI9341_CMD_DISPLAY_FUNCTION_CONTROL);
	glcd_writeData(0x08); 
	glcd_writeData(0x82);
	glcd_writeData(0x27);

	glcd_writeCmd(ILI9341_CMD_ENABLE_3_GAMMA_CONTROL);
	glcd_writeData(ILI9341_CMD_NOP);

	glcd_writeCmd(0x26);	//Gamma curve selected 	
	glcd_writeData(ILI9341_CMD_SOFTWARE_RESET);

	glcd_writeCmd(ILI9341_CMD_POSITIVE_GAMMA_CORRECTION);
	glcd_writeData(0x0F);
	glcd_writeData(0x31);
	glcd_writeData(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_writeData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_writeData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_writeData(0x08);
	glcd_writeData(0x4E);
	glcd_writeData(0xF1);
	glcd_writeData(ILI9341_CMD_VERT_SCROLL_START_ADDRESS);
	glcd_writeData(0x07);
	glcd_writeData(ILI9341_CMD_ENTER_SLEEP_MODE);
	delay_ms(DELAY120);						// neka se nadje
	glcd_writeData(0x03);
	glcd_writeData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_writeData(ILI9341_CMD_READ_DISP_STATUS);
	glcd_writeData(ILI9341_CMD_NOP);

	glcd_writeCmd(ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION);
	glcd_writeData(ILI9341_CMD_NOP);
	glcd_writeData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_writeData(0x14);
	glcd_writeData(0x03);
	glcd_writeData(ILI9341_CMD_SLEEP_OUT);
	delay_ms(DELAY120);						// neka se nadje
	glcd_writeData(0x07);
	glcd_writeData(0x31);
	glcd_writeData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_writeData(0x48);
	glcd_writeData(0x08);
	glcd_writeData(0x0F);
	glcd_writeData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_writeData(0x31);
	glcd_writeData(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_writeData(ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC);

	glcd_writeCmd(ILI9341_CMD_SLEEP_OUT);
	delay_ms(DELAY120); 	// nakon sleep outa treba 120 ms

	glcd_writeCmd(ILI9341_CMD_DISPLAY_ON);
	glcd_writeCmd(ILI9341_CMD_MEMORY_WRITE);
	//glcd_bg(bgcolor);	// ovo je high layer
	glcd_set_hw_orientation(P1);
}

int8_t glcd_set_hw_orientation(glcd_orientation_t orientation)
{
	//if ( (orientation < 0) || (orientation > 7) )
	if (orientation > 7)	// unsigned enum
	{
		printf("ERROR %s(): wrong orientation: %d\n", __func__, orientation);
		return -1;
	}

	//printf("%s(): argument: %d\n", __func__, orientation);

	uint8_t MV, ML, MH, BGR, MX, MY;
	//BGR = 0;	// D3
	BGR = 1;	// D3
	ML = 1;		// D4	don't care
	MH = 1;		// D2	don't care
	MY = (orientation >> 2) & 1;
	MX = (orientation >> 1) & 1;
	MV = (orientation >> 0) & 1;

	//printf("pretvoreno u bitove: MY: %d MX: %d MV: %d\n", MY, MX, MV);

	glcd_writeCmd(0x36);
	glcd_writeData( (MY << 7) | (MX << 6) | (MV << 5) | (ML << 4) | (BGR << 3) | (MH << 2) );

	return 0;

}
