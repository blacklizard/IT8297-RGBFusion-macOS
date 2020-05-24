//
// Created by blacklizard on 15/05/2020.
//
#ifndef RGBFUSSION_CONTROLLER_H
#define RGBFUSSION_CONTROLLER_H

#include <iostream>
#include "hidapi.h"

class Controller {
private:
	enum leds{
		IO = 0,
		RAM = 1,
		CHIPSET = 2,
		AUDIO = 3,
		DLED_TOP = 4,
		DLED_BOTTOM = 5,
	};

#pragma pack(push, 1) // [StructLayout(LayoutKind.Explicit, Pack = 1)]
	struct ControllerInfo {
		uint8_t ReportId; //0
		uint8_t Product; //1
		uint8_t DeviceNum; //2
		uint8_t StripDetect; //3
		uint32_t FW_Ver; //4
		uint16_t Strip_Ctrl_Length0; //8
		uint16_t Reserve0; //10
		unsigned char ProductString[28]; //12 -> 12 + 28 => 40
		uint32_t CalStrip3; //40
		uint32_t CalStrip0; //44
		uint32_t CalStrip1; //48
		uint32_t CalStrip2; //52
		uint32_t ChipId; //56
		uint32_t Reserve1; //60
		// total 64 byte
	};
#pragma pack(pop)
	hid_device * device{};
	ControllerInfo info{};
	const uint8_t reportId = 0xCC;
	const uint16_t VID = 0x048D;
	const uint16_t PID = 0x8297;
	int read(unsigned char * data);
public:
	Controller();
	~Controller();
	int write(unsigned char * data);
	void applyChanges();
	uint8_t getDeviceNum() const;
	void saveSettingToMCU();
};

#endif //RGBFUSSION_CONTROLLER_H
