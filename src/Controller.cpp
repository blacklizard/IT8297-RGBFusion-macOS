//
// Created by blacklizard on 15/05/2020.
//
#include "Controller.h"

Controller::Controller() {
	int responseSize = 0;
	responseSize = hid_init();
	if (responseSize < 0) {
		throw std::runtime_error("Failed to hid_init");
	}
	unsigned char buffer[64];
	device = hid_open(VID, PID, nullptr);
	if (!device) {
		throw std::runtime_error("Failed to open LED controller");
	}

	memset(buffer, 0, 64);
	buffer[0] = reportId;
	buffer[1] = 0x60;
	write(buffer);
	
	memset(buffer, 0, 64);
	buffer[0] = reportId;
	read(buffer);
	
	info = *reinterpret_cast<ControllerInfo *>(buffer);
}

Controller::~Controller() {
	if(device) {
		hid_close(device);
		device = nullptr;
	}
	hid_exit();
}

int Controller::read(unsigned char * data) {
	int byteSent = hid_get_feature_report(device, data, 64);
	if (byteSent < 0) {
		throw std::runtime_error("Failed to get feature report ");
	}
	return byteSent;
}

int Controller::write(unsigned char * data) {
	int byteSent = hid_send_feature_report(device, data, 64);
	if (byteSent < 0) {
		throw std::runtime_error("Failed to set feature report");
	}
	return byteSent;
}

void Controller::applyChanges() {
	unsigned char apply[64];
	memset(apply, 0, 64);
	apply[0] = reportId;
	apply[1] = 0x28;
	apply[2] =0xFF;
	write(apply);
}

uint8_t Controller::getDeviceNum() const {
	return info.DeviceNum;
}

void Controller::saveSettingToMCU() {
	// this does not have any effect
	// instead this is being called to save data to bios via SMBus
	// dllexp_SetLedModeToBios
	// dllexp_SetLedPwrOnStateToBios
	// dllexp_SetTrueColorValueToBios
	// dllexp_SaveToBios
	unsigned char save[64];
	memset(save, 0, 64);
	save[0] = reportId;
	save[1] = 0x5E;
	write(save);
}

