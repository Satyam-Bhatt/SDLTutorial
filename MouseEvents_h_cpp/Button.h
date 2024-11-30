#include <SDL.h>
#include "../ColorKeying_Mine/CommonVariables.h"
#include "../ColorKeying_Mine/Texture_Mine.h"
//#include "../StartupStuff.h"

#pragma once


class Button
{
public:

	//Initialize
	Button();

	void SetPosition(int x, int y);

	void HandleEvent(SDL_Event* e);

	void Render(Texture_Mine* texture, SDL_Renderer* renderer);

private:

	SDL_Point mPosition;
	ButtonSprite currentSprite;
	SDL_Rect clip[ BUTTON_SPRITE_TOTAL ];

};

