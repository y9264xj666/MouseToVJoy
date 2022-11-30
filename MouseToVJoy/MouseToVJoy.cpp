#include "mousetovjoy.h"
#include <iostream>
#include <math.h>
#define STEERING_MAX 16384
#define STEERING_MIN -16384
//Function responsible for getting and modifying vars for throttle, break, clutch.
void MouseToVjoy::inputLogic(CInputDevices input, INT &axisX, INT &axisY, INT &axisZ, INT &axisRX, INT& axisRY, INT& axisRZ, BOOL &isButton1Clicked, BOOL &isButton2Clicked, BOOL &isButton3Clicked, DOUBLE attackTimeThrottle, DOUBLE releaseTimeThrottle, DOUBLE attackTimeBreak, DOUBLE releaseTimeBreak, DOUBLE attackTimeClutch, DOUBLE releaseTimeClutch, INT throttleKey, INT breakKey, INT clutchKey, INT gearShiftUpKey, INT gearShiftDownKey, INT handBrakeKey, INT mouseLockKey, INT mouseCenterKey, INT useMouse, DOUBLE accelerationThrottle, DOUBLE accelerationBreak, DOUBLE accelerationClutch, INT useWheelAsShifter, DOUBLE deltaTime) {
	
	if (useMouse == 1) {
		if (input.isLeftMouseButtonDown() && axisY < 32767) {
			axisY = (axisY + (attackTimeThrottle*deltaTime)) * accelerationThrottle;
		}
		if (!input.isLeftMouseButtonDown() && axisY > 1) {
			axisY = (axisY - (releaseTimeThrottle*deltaTime)) / accelerationThrottle;;
		}
		if (input.isRightMouseButtonDown() && axisZ < 32767) {
			axisZ = (axisZ + (attackTimeBreak*deltaTime)) * accelerationBreak;
		}
		if (!input.isRightMouseButtonDown() && axisZ > 1) {
			axisZ = (axisZ - (releaseTimeBreak*deltaTime)) / accelerationBreak;
		}
	}
	else {
		if (input.isAlphabeticKeyDown(throttleKey) && axisY < 32767) {
			axisY = (axisY + (attackTimeThrottle*deltaTime)) * accelerationThrottle;
		}
		if (!input.isAlphabeticKeyDown(throttleKey) && axisY > 1) {
			axisY = (axisY - (releaseTimeThrottle*deltaTime)) / accelerationThrottle;
		}
		if (input.isAlphabeticKeyDown(breakKey) && axisZ < 32767) {
			axisZ = (axisZ + (attackTimeBreak*deltaTime)) * accelerationBreak;
		}
		if (!input.isAlphabeticKeyDown(breakKey) && axisZ > 1) {
			axisZ = (axisZ - (releaseTimeBreak*deltaTime)) / accelerationBreak;
		}
	}

	if (input.isAlphabeticKeyDown(clutchKey) && axisRX < 32767) {
		axisRX = (axisRX + (attackTimeClutch*deltaTime)) * accelerationClutch;
	}
	if (!input.isAlphabeticKeyDown(clutchKey) && axisRX > 1) {
		axisRX = (axisRX - (releaseTimeClutch*deltaTime)) / accelerationClutch;
	}
	if (input.isAlphabeticKeyDown(mouseLockKey)) {
		SleepEx(250, !(input.isAlphabeticKeyDown(mouseLockKey)));
		if (_isCursorLocked == false) {
			_isCursorLocked = true;
		}
		else {
			_isCursorLocked = false;
		}
	}
	if (input.isAlphabeticKeyDown(mouseCenterKey)) {
		SleepEx(250, !(input.isAlphabeticKeyDown(mouseCenterKey)));
		axisX = (32766 / 2);
	}
	if (useWheelAsShifter == 0) {
		if (input.isAlphabeticKeyDown(gearShiftUpKey)) {
			isButton1Clicked = true;
		}
		else isButton1Clicked = false;
		if (input.isAlphabeticKeyDown(gearShiftDownKey)) {
			isButton2Clicked = true;
		}
		else isButton2Clicked = false;
	}
	if (input.isAlphabeticKeyDown(handBrakeKey)){
		isButton3Clicked = true;
	}
	else isButton3Clicked = false;
	if (_isCursorLocked == true) {
		SetCursorPos(0, 0);
	}

}
//Function responsible for getting and modifying vars for steering wheel.
void MouseToVjoy::mouseLogic(CInputDevices input, INT &X, DOUBLE sensitivity, DOUBLE sensitivityCenterReduction, INT useCenterReduction, BOOL &isButton1Clicked, BOOL &isButton2Clicked, INT useWheelAsShifter){
	//vjoy max value is 0-32767 to make it easier to scale linear reduction/acceleration I subtract half of it so 16384 to make it -16384 to 16384.
	X = X - 16384;
	if (X > 0) {
		_centerMultiplier = pow(sensitivityCenterReduction, (1 - (double)((double)X / (double)STEERING_MAX)));
	}
	else if(X < 0){
		_centerMultiplier = pow(sensitivityCenterReduction, (1 - (double)((double)X / (double)STEERING_MIN)));
	}
	if (useCenterReduction == 1) {
		X = X + ((input.getMouseChangeX() * sensitivity) / _centerMultiplier);
	}
	else {
		X = X + (input.getMouseChangeX() * sensitivity);
	}

	if (X > 16384) {
		X = 16384;
	}
	else if (X < -16384) {
		X = -16384;
	}
	X += 16384;
	if (useWheelAsShifter == 1) {		
		if (input.isMouseWheelUp()) {
			//printf("UP\n");
		}
		else ;
		if (input.isMouseWheelDown()) {
			//printf("DOWN\n");
			
		}
		else ;
	}
};