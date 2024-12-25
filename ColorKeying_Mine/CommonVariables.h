#pragma once

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int SCREEN_EXTENTION = 250;

const int SCREEN_WIDTH_CAMERA = 1280;
const int SCREEN_HEIGHT_CAMERA = 720;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum ButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

const int JOYSTICK_DEAD_ZONE = 8000;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

const int TOTAL_DATA = 10;

//Maximum number of supported recording device
const int MAX_RECORDING_DEVICES = 10;

//Maximum recording time
const int MAX_RECORDING_SECONDS = 5;

//Maximum recording time plus padding
const int RECORDING_BUFFER_SECONDS = MAX_RECORDING_SECONDS + 1;

//The various recording actions we can take
enum RecordingState
{
	SELECTING_DEVICE,
	STOPPED,
	RECORDING,
	RECORDED,
	PLAYBACK,
	ERROR
};

//Total windows
const int TOTAL_WINDOWS = 1;

//Particle Count
const int TOTAL_PARTICLES = 20;