//
// Created by blacklizard on 15/05/2020.
//
#include "Effect.h"
#include <cmath>

void Effect::DataFormat::setDefault(uint32_t iDivis) {
	memset(setting, 0, sizeof(setting));
	format.report_id = 0xCC;
	
	if(iDivis != -1) {
		// this.setting_buf[1] = (byte) (32 + iDivis); -> iDivis != -1
		format.header = (32 + iDivis);
		// iDivis != -1 ? (uint) Math.Pow(2.0, (double) iDivis) : (uint) byte.MaxValue;
		format.Zone_Sel0 = (uint32_t)pow(2, iDivis);;
	} else {
		format.header = 32;
		format.Zone_Sel0 = 255;
	}

	format.Mode_Sel = effects::STATIC;
	format.MaxBrightness = 100;
	format.dwColor0 = 0xFFFFFF; //white
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
unsigned char * Effect::getEffectSetting(Effect::effects effect, uint32_t iDivs, uint32_t color) {
	dataFormat.setDefault(iDivs);
	dataFormat.format.Mode_Sel = effect;
	dataFormat.format.dwColor0 = color;
	dataFormat.format.MaxBrightness = brightness;
	
	switch (effect) {
		case Effect::STATIC:
			break;
		case PULSE:
			dataFormat.format.CtrlVal0 = 0;
			dataFormat.format.CtrlVal1 = 1;
			dataFormat.format.wTime_base0 = PulseTiming[speed -1][0];
			dataFormat.format.wTime_base1 = PulseTiming[speed -1][1];
			dataFormat.format.wTime_base2 = PulseTiming[speed -1][2];
			break;
		case FLASH:
			dataFormat.format.CtrlVal0 = 0;
			dataFormat.format.CtrlVal1 = 1;
			dataFormat.format.CtrlOem0 = 1;
			dataFormat.format.wTime_base0 = FlashTiming[speed -1][0];
			dataFormat.format.wTime_base1 = FlashTiming[speed -1][1];
			dataFormat.format.wTime_base2 = FlashTiming[speed -1][2];
			break;
		case COLORCYCLE:
			dataFormat.format.wTime_base0 = 400;
			dataFormat.format.wTime_base1 = 200;
			dataFormat.format.CtrlVal0 = 7;
			break;
		case RANDOM:
			dataFormat.format.CtrlVal0 = 5;
			break;
		case DFLASH:
			dataFormat.format.Mode_Sel = Effect::FLASH;
			dataFormat.format.CtrlVal0 = 0;
			dataFormat.format.CtrlVal1 = 1;
			dataFormat.format.CtrlOem0 = 2;
			dataFormat.format.wTime_base0 = FlashTiming[speed -1][0];
			dataFormat.format.wTime_base1 = FlashTiming[speed -1][1];
			dataFormat.format.wTime_base2 = FlashTiming[speed -1][2];
			break;
		default:
			break;
	}
	
	return dataFormat.setting;
}

void Effect::setBrightness(uint8_t brightness) {
	this->brightness = brightness;
}
void Effect::setSpeed(int speed) {
	this->speed = speed;
}

Effect::Effect() {
	brightness = 100;
	speed = 10;
};

#pragma clang diagnostic pop
