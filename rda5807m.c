// @File		RDA5807.C		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		10/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#include "rda5807m.h"
#include "wire.h"
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Write(unsigned char reg, unsigned int data)
{
	Wire_Start();
	Wire_Write(RDA5807M_SLA_W);
	Wire_Write(reg);
	Wire_Write(data>>8);
	Wire_Write(data);
	Wire_Stop();
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned int RDA5807_Read(unsigned char reg)
{
	unsigned int data = 0;
	
	Wire_Start();
	Wire_Write(RDA5807M_SLA_W);
	Wire_Write(reg);
	Wire_Start();
	Wire_Write(RDA5807M_SLA_R);
	data |= Wire_Ack();
	data <<= 8;
        data |= Wire_Nack();
	Wire_Stop();
	
	return (data);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Enable(unsigned char En)
{
	unsigned int reg02 = RDA5807_Read(0x02);
	
	// CLEAR ENABLE BIT
	reg02 &=~ (1 << 0);
	
	// SET EN BIT
	reg02 |= (En << 0);
	
	// WRITE TO RADIO
	RDA5807_Write(0x02, reg02);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Frequency(unsigned int freq)
{
	freq -= 870;
	freq <<= 6; 
	freq |= 0x0010;
	
	// WRITE TO RADIO
	RDA5807_Write(0x03, freq);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Mute(unsigned char mute)
{
	// READ REG02
	unsigned int reg02 = RDA5807_Read(0x02);
	
	reg02 &=~(1 << 14); // RESET MUTE: OFF
	
	reg02 |= (mute << 14); // SET MUTE 1 ~ 0
	
	// WRITE TO RADIO
	RDA5807_Write(0x02, reg02);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Volume(unsigned char vol)
{
	vol %= 16;	// CHECK MAX VOLUME
	
	// WRITE TO RADIO
	RDA5807_Write(0x05, (unsigned int) (0x00F0 | vol) );
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Bass(unsigned char bass)
{
	unsigned int reg02 = RDA5807_Read(0x02);
	
	reg02 &=~(1 << 12); // CLEAR BASS BIT
	
	reg02 |= (bass << 12); // SET BASS BIT 1 ~ 0
	
	// WRITE TO RADIO 
	RDA5807_Write(0x02, reg02);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Mono(unsigned char mono)
{
	unsigned int reg02 = RDA5807_Read(0x02);
	
	reg02 &=~(1 << 13); // CLEAR MONO BIT
	
	reg02 |= (mono << 13); // SET MONO BIT 1 ~ 0
	
	// WRITE TO RADIO
	RDA5807_Write(0x02, reg02);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Band(unsigned char band)
{
	unsigned int reg03 = RDA5807_Read(0x03);
	
	reg03 &=(~((1 << 2)|(1 << 3))); // CLEAR BAND BITS
	
	reg03 |= (band << 2); // SET BAND BITS 
	
	// WRITE TO RADIO
	RDA5807_Write(0x03, reg03);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Space(unsigned char space)
{
	unsigned int reg03 = RDA5807_Read(0x03);
	
	reg03 &=(~((1 << 0)|(1 << 1))); // CLEAR SPACE BITS
	
	reg03 |= space; // SET SPACE BITS
	
	// WRITE TO RADIO
	RDA5807_Write(0x03, reg03);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Tune(unsigned char tune)
{
	unsigned int reg03 = RDA5807_Read(0x03);
	
	reg03 &=~(1 << 4); // CLEAR TUNE BITS
	
	reg03 |= (tune << 4); // SET TUNE BITS
	
	// WRITE TO RADIO
	RDA5807_Write(0x03, reg03);
}

void RDA5807_Set_Seekup(unsigned char seekup)
{
	unsigned int reg02 = RDA5807_Read(0x02);
	
	reg02 &=~(1 << 9); // CLEAR SEEKUP BITS
	
	reg02 |= (seekup << 9); // SET SEEKUP BITS
	
	// WRITE TO RADIO
	RDA5807_Write(0x02, reg02);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Set_Seek_Mode(unsigned char mode)
{
	unsigned int reg02 = RDA5807_Read(0x02);
	
	reg02 &=~(1 << 7); // CLEAR SEEKUP BITS
	
	reg02 |= (mode << 7); // SET SEEKUP BITS
	
	// WRITE TO RADIO
	RDA5807_Write(0x02, reg02);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_Stereo_Indicator()
{
	unsigned int reg0A = RDA5807_Read(0x0A);
	return ((unsigned char) ( reg0A >> 10 ) & 1);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_Seek_Indicator()
{
	unsigned int reg0A = RDA5807_Read(0x0A);
	return ((unsigned char) ( reg0A >> 14) & 1 );
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_Seek_Fail()
{
	unsigned int reg0A = RDA5807_Read(0x0A);
	return ((unsigned char) ( reg0A >> 13 ) & 1);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_FM_True()
{
	unsigned int reg0B = RDA5807_Read(0x0B);
	return ((unsigned char) ( reg0B >> 8 ) & 1 );
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_FM_Ready()
{
	unsigned int reg0B = RDA5807_Read(0x0B);
	return ((unsigned char) ( reg0B >> 7 ) & 1 );
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_RSSI()
{
	unsigned int reg0B = RDA5807_Read(0x0B);
	return ( (unsigned char) (reg0B >> 9) & 0x007F);
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
void RDA5807_Seek()
{
	unsigned int reg02 = RDA5807_Read(0x02);
	
	reg02 |= (1 << 8); // SET SEEK BIT
	
	// WRITE TO RADIO
	RDA5807_Write(0x02, reg02);
} 
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_ABCD_E()
{
	unsigned int reg0B = RDA5807_Read(0x0B);
	return ( (unsigned char) ( reg0B >> 4) & 0x0001 );
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_BLK_E()
{
	unsigned int reg0A = RDA5807_Read(0x0A);
	return ( (unsigned char) ( reg0A >> 11) & 0x0001 );
}
//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned char RDA5807_Read_Volume()
{
	unsigned int reg05 = RDA5807_Read( 0x05 );
	return ( (unsigned char) ( reg05 & 0x000F ) );
}

//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
unsigned int RDA5807_Read_Frequency()
{
	unsigned int reg0A = RDA5807_Read( 0x0A );
	return ( ( reg0A & 0x03FF ) + 870 );
}
