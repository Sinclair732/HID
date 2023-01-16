/*
Copyright (c) 2014-2015 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// Include guard
#pragma once

#include <Arduino.h>
#include "HID-Settings.h"

// Dpad directions
#define JOYSTICK_DPAD_CENTERED 0
#define JOYSTICK_DPAD_UP 1
#define JOYSTICK_DPAD_UP_RIGHT 2
#define JOYSTICK_DPAD_RIGHT 3
#define JOYSTICK_DPAD_DOWN_RIGHT 4
#define JOYSTICK_DPAD_DOWN 5
#define JOYSTICK_DPAD_DOWN_LEFT 6
#define JOYSTICK_DPAD_LEFT 7
#define JOYSTICK_DPAD_UP_LEFT 8

#define EXCLUDE_HAT
#define EXCLUDE_8BIT_AXES
#define EXCLUDE_R_AXES
#define REDUCE_BUTTONS

typedef union ATTRIBUTE_PACKED {
	// 32 Buttons, 6 Axis, 2 D-Pads
	uint8_t whole8[0];
	uint16_t whole16[0];
	uint32_t whole32[0];
#ifndef REDUCE_BUTTONS	
	uint32_t buttons;
#else
	uint8_t buttons;
#endif

	struct ATTRIBUTE_PACKED {
		uint8_t button1 : 1;
		uint8_t button2 : 1;
		uint8_t button3 : 1;
		uint8_t button4 : 1;
		uint8_t button5 : 1;
		uint8_t button6 : 1;
		uint8_t button7 : 1;
		uint8_t button8 : 1;

#ifndef REDUCE_BUTTONS
		uint8_t button9 : 1;
		uint8_t button10 : 1;
		uint8_t button11 : 1;
		uint8_t button12 : 1;
		uint8_t button13 : 1;
		uint8_t button14 : 1;
		uint8_t button15 : 1;
		uint8_t button16 : 1;

		uint8_t button17 : 1;
		uint8_t button18 : 1;
		uint8_t button19 : 1;
		uint8_t button20 : 1;
		uint8_t button21 : 1;
		uint8_t button22 : 1;
		uint8_t button23 : 1;
		uint8_t button24 : 1;

		uint8_t button25 : 1;
		uint8_t button26 : 1;
		uint8_t button27 : 1;
		uint8_t button28 : 1;
		uint8_t button29 : 1;
		uint8_t button30 : 1;
		uint8_t button31 : 1;
		uint8_t button32 : 1;
#endif

		int16_t	xAxis;
		int16_t	yAxis;

#ifndef EXCLUDE_R_AXES
		int16_t	rxAxis;
		int16_t	ryAxis;
#endif

#ifndef EXCLUDE_8BIT_AXES
		int8_t	zAxis;
		int8_t	rzAxis;
#endif

#ifndef EXCLUDE_HAT
		uint8_t	dPad1 : 4;
		uint8_t	dPad2 : 4;
#endif
	};
} HID_JoystickReport_Data_t;

class JoystickAPI{
public:
	inline JoystickAPI(void);

	inline void begin(void);
	inline void end(void);
	inline void write(void);
	inline void press(uint8_t b);
	inline void release(uint8_t b);
	inline void releaseAll(void);

	inline void buttons(uint32_t b);
	inline void xAxis(int16_t a);
	inline void yAxis(int16_t a);
	inline void zAxis(int8_t a);
	inline void rxAxis(int16_t a);
	inline void ryAxis(int16_t a);
	inline void rzAxis(int8_t a);
	inline void dPad1(int8_t d);
	inline void dPad2(int8_t d);

	// Sending is public in the base class for advanced users.
	virtual void SendReport(void* data, int length) = 0;

protected:
	HID_JoystickReport_Data_t _report;
};

// Implementation is inline
#include "JoystickAPI.hpp"
