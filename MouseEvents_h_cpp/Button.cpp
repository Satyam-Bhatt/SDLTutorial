#include "Button.h"

Button::Button()
{
	mPosition.x = 0;
	mPosition.y = 0;

	currentSprite = BUTTON_SPRITE_MOUSE_OUT;

	for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
	{
		clip[i].x = 0;
		clip[i].y = i * 200;
		clip[i].w = BUTTON_WIDTH;
		clip[i].h = BUTTON_HEIGHT;
	}
}

void Button::SetPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Button::HandleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}

		//Mouse right of the button
		else if (x > mPosition.x + BUTTON_WIDTH/ 4)
		{
			inside = false;
		}

		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}

		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT/ 4)
		{
			inside = false;
		}

		if (!inside)
		{
			currentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				currentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

void Button::Render(Texture_Mine* myTexture, SDL_Renderer* renderer)
{
	myTexture->RenderRotate(mPosition.x, mPosition.y, 4 , renderer, &clip[currentSprite]);
}