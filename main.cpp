#include <iostream>
#include "src/Controller.h"
#include "src/Effect.h"

int main() {
	Controller controller;
	Effect effect;
	
	effect.setBrightness(100);
	effect.setSpeed(10);
	std::cout << controller.getDeviceNum() << std::endl;
	
	for (int i = 0; i < 8; ++i) {
		unsigned char data[64];
		memcpy(data, effect.getEffectSetting(Effect::PULSE, i, 0xFF0000), 64);
		controller.write(data);
	}
	controller.applyChanges();
	return 0;
}
