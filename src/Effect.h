//
// Created by blacklizard on 15/05/2020.
//
#ifndef RGBFUSSION_EFFECT_H
#define RGBFUSSION_EFFECT_H

#include <iostream>

class Effect {
private:
#pragma pack(push, 1) // [StructLayout(LayoutKind.Explicit, Pack = 1)]
	union DataFormat {
		unsigned char setting[64];
		struct Format {
			uint8_t report_id; // 0 => 0xCC;
			uint8_t header; // 1 => 0x20;
			uint32_t Zone_Sel0;//2
			uint32_t Zone_Sel1;//6
			uint8_t Reserve0;//10
			uint8_t Mode_Sel;//11
			uint8_t MaxBrightness;//12
			uint8_t MinBrightness;//13
			uint32_t dwColor0;//14
			uint32_t dwColor1;//18
			uint16_t wTime_base0;//22
			uint16_t wTime_base1;//24
			uint16_t wTime_base2;//26
			uint16_t wTime_base3;//28
			uint8_t CtrlVal0;//30
			uint8_t CtrlVal1;//31
			uint8_t CtrlOem0;//32
			uint8_t CtrlOem1;//33
			uint8_t empty[28];
		} format;

		DataFormat() : setting{0} {
			memset(setting, 0, sizeof(setting));
			setDefault(-1);
		};
		
		void setDefault(uint32_t iDivis = -1);
	};
#pragma pack(pop)
	
	DataFormat dataFormat;
	int PulseTiming[10][3]
	{
		{1600,1600,200},
		{1400,1400,200},
		{1200,1200,200},
		{1000,1000,200},
		{900,900,200},
		{800,800,200},
		{700,700,200},
		{600,600,200},
		{500,500,200},
		{400,400,200}
	};

	int FlashTiming[10][ 3]
	{
		{100,100,2400},
		{100,100,2200},
		{100,100,2000},
		{100,100,1800},
		{100,100,1600},
		{100, 100,1400},
		{100,100,1200},
		{100,100,1000},
		{100,100,800},
		{100,100,600}
	};
	
	int speed;
	uint8_t brightness;
public:
	enum effects {
		STATIC = 1,
		PULSE = 2,
		FLASH = 3,
		COLORCYCLE = 4,
		RANDOM = 8,
		DFLASH = 51, // 0x33
	};
	Effect();
	unsigned char * getEffectSetting(effects effect, uint32_t iDivs, uint32_t color);
	void setBrightness(uint8_t brightness);
	void setSpeed(int speed);
};


#endif //RGBFUSSION_EFFECT_H
