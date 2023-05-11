// @File		RDA5807.H		 		
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
#ifndef RDA5807M_H_
#define RDA5807M_H_

#define RDA5807M_SLA_W			0x22
#define RDA5807M_SLA_R			0x23


void RDA5807_Write(unsigned char reg, unsigned int data);	
void RDA5807_Seek();
		
// SET
void RDA5807_Set_Enable(unsigned char En);
void RDA5807_Set_Frequency(unsigned int freq);
void RDA5807_Set_Mute(unsigned char mute);
void RDA5807_Set_Volume(unsigned char vol);
void RDA5807_Set_Bass(unsigned char bass);
void RDA5807_Set_Mono(unsigned char mono);
void RDA5807_Set_Band(unsigned char band);
void RDA5807_Set_Space(unsigned char space); 
void RDA5807_Set_Tune(unsigned char tune );
void RDA5807_Set_Seekup(unsigned char seekup);
void RDA5807_Set_Seek_Mode(unsigned char mode);
		
// READ
unsigned int RDA5807_Read(unsigned char reg);
unsigned char RDA5807_Read_Stereo_Indicator();
unsigned char RDA5807_Read_Seek_Indicator();
unsigned char RDA5807_Read_Seek_Fail();
unsigned char RDA5807_Read_FM_True();
unsigned char RDA5807_Read_FM_Ready();
unsigned char RDA5807_Read_RSSI();
unsigned char RDA5807_Read_Volume();
unsigned char RDA5807_Read_BLK_E();
unsigned char RDA5807_Read_ABCD_E();
unsigned int RDA5807_Read_Frequency();


#endif /* RDA5807M_H_ */
