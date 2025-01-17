/*This source code copyrighted by Lazy Foo' Productions 2004-2025
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile( std::string path );

#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif

	//Creates blank texture
	bool createBlank( int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING );

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );

	//Renders texture at given point
	void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	//Set self as render target
	void setAsRenderTarget();

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Pixel manipulators
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	void copyPixels( void* pixels );
	int getPitch();
	Uint32 getPixel32( unsigned int x, unsigned int y );

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	void* mPixels;
	int mPitch;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//The dot that will move around on the screen
class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	//Initializes the variables
	Dot();

	//Set dot position
	void set( int x, int y );

	//Takes key presses and adjusts the dot's velocity
	void handleEvent( SDL_Event& e );

	//Moves the dot
	void move( int levelWidth, int levelHeight );

	//Shows the dot on the screen relative to the camera
	void render( SDL_Rect camera );

	//Gets the collision box
	SDL_Rect getCollider();

private:
	//Got collision box
	SDL_Rect mBox;

	//The velocity of the dot
	int mVelX, mVelY;
};

class House
{
public:
	//The house dimensions
	static const int HOUSE_WIDTH = 40;
	static const int HOUSE_HEIGHT = 40;

	//Initializes variables
	House();

	//Sets the house's position/graphic
	void set( int x, int y, LTexture* houseTexture );

	//Renders house relative to the camera
	void render( SDL_Rect camera );

	//Gets the collision box
	SDL_Rect getCollider();

private:
    //The house graphic
    LTexture* mHouseTexture;

    //The collision box of the house
    SDL_Rect mBox;
};

class Door
{
public:
	//The door dimensions
	static const int DOOR_WIDTH = 20;
	static const int DOOR_HEIGHT = 40;

	//Initializes variables
	Door();

	//Sets the door position
	void set( int x, int y );

	//Shows the door
	void render();

	//Gets the collision box
	SDL_Rect getCollider();

private:
    //The area of the door
    SDL_Rect mBox;
};

//Game state base class
class GameState
{
public:
	//State transitions
	virtual bool enter() = 0;
	virtual bool exit() = 0;

	//Main loop functions
	virtual void handleEvent( SDL_Event& e ) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//Make sure to call child destructors
	virtual ~GameState(){};
};

class IntroState : public GameState
{
public:
	//Static accessor
	static IntroState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Static instance
	static IntroState sIntroState;

	//Private constructor
	IntroState();

	//Intro background
	LTexture mBackgroundTexture;

	//Intro message
	LTexture mMessageTexture;
};


class TitleState : public GameState
{
public:
	//Static accessor
	static TitleState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Static instance
	static TitleState sTitleState;

	//Private constructor
	TitleState();

	//Intro background
	LTexture mBackgroundTexture;

	//Intro message
	LTexture mMessageTexture;
};

class OverWorldState : public GameState
{
public:
	//Static accessor
	static OverWorldState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Level dimensions
	const static int LEVEL_WIDTH = SCREEN_WIDTH * 2;
	const static int LEVEL_HEIGHT = SCREEN_HEIGHT * 2;

	//Static instance
	static OverWorldState sOverWorldState;

	//Private constructor
	OverWorldState();

	//Overworld textures
	LTexture mBackgroundTexture;
	LTexture mRedHouseTexture;
	LTexture mBlueHouseTexture;

	//Game objects
	House mRedHouse;
	House mBlueHouse;
};

class RedRoomState : public GameState
{
public:
	//Static accessor
	static RedRoomState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Level dimensions
	const static int LEVEL_WIDTH = SCREEN_WIDTH;
	const static int LEVEL_HEIGHT = SCREEN_HEIGHT;

	//Static instance
	static RedRoomState sRedRoomState;

	//Private constructor
	RedRoomState();

	//Room textures
	LTexture mBackgroundTexture;

	//Game objects
	Door mExitDoor;
};

class BlueRoomState : public GameState
{
public:
	//Static accessor
	static BlueRoomState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Level dimensions
	const static int LEVEL_WIDTH = SCREEN_WIDTH;
	const static int LEVEL_HEIGHT = SCREEN_HEIGHT;

	//Static instance
	static BlueRoomState sBlueRoomState;

	//Private constructor
	BlueRoomState();

	//Room textures
	LTexture mBackgroundTexture;

	//Game objects
	Door mExitDoor;
};

class ExitState : public GameState
{
public:
	//Static accessor
	static ExitState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Static instance
	static ExitState sExitState;

	//Private constructor
	ExitState();
};

//Starts up SDL and creates window
bool init();

//Loads cross state assets
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Check collision
bool checkCollision( SDL_Rect a, SDL_Rect b );

//State managers
void setNextState( GameState* nextState );
void changeState();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Global assets
LTexture gDotTexture;
TTF_Font* gFont = NULL;

//Global game objects
Dot gDot;

//Game state object
GameState* gCurrentState = NULL;
GameState* gNextState = NULL;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPixels = NULL;
	mPitch = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0 );
		if( formattedSurface == NULL )
		{
			SDL_Log( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture( gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( newTexture == NULL )
			{
				SDL_Log( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );

				//Lock texture for manipulation
				SDL_LockTexture( newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch );

				//Copy loaded/formatted surface pixels
				memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

				//Get image dimensions
				mWidth = formattedSurface->w;
				mHeight = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)mPixels;
				int pixelCount = ( mPitch / 4 ) * mHeight;

				//Map colors
				Uint32 colorKey = SDL_MapRGB( formattedSurface->format, 0, 0xFF, 0xFF );
				Uint32 transparent = SDL_MapRGBA( formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00 );

				//Color key pixels
				for( int i = 0; i < pixelCount; ++i )
				{
					if( pixels[ i ] == colorKey )
					{
						pixels[ i ] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture( newTexture );
				mPixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface( formattedSurface );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			SDL_Log( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		SDL_Log( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

bool LTexture::createBlank( int width, int height, SDL_TextureAccess access )
{
	//Create uninitialized texture
	mTexture = SDL_CreateTexture( gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height );
	if( mTexture == NULL )
	{
		SDL_Log( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		mWidth = width;
		mHeight = height;
	}

	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		mPixels = NULL;
		mPitch = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void LTexture::setAsRenderTarget()
{
	//Make self render target
	SDL_SetRenderTarget( gRenderer, mTexture );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if( mPixels != NULL )
	{
		SDL_Log( "Texture is already locked!\n" );
		success = false;
	}
	//Lock texture
	else
	{
		if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
		{
			SDL_Log( "Unable to lock texture! %s\n", SDL_GetError() );
			success = false;
		}
	}

	return success;
}

bool LTexture::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if( mPixels == NULL )
	{
		SDL_Log( "Texture is not locked!\n" );
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture( mTexture );
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

void* LTexture::getPixels()
{
	return mPixels;
}

void LTexture::copyPixels( void* pixels )
{
	//Texture is locked
	if( mPixels != NULL )
	{
		//Copy to locked pixels
		memcpy( mPixels, pixels, mPitch * mHeight );
	}
}

int LTexture::getPitch()
{
	return mPitch;
}

Uint32 LTexture::getPixel32( unsigned int x, unsigned int y )
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)mPixels;

	//Get the pixel requested
	return pixels[ ( y * ( mPitch / 4 ) ) + x ];
}


Dot::Dot()
{
	//Initialize the offsets
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::set( int x, int y )
{
    //Set position
	mBox.x = x;
	mBox.y = y;
}

void Dot::handleEvent( SDL_Event& e )
{
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	//If a key was released
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: mVelY += DOT_VEL; break;
			case SDLK_DOWN: mVelY -= DOT_VEL; break;
			case SDLK_LEFT: mVelX += DOT_VEL; break;
			case SDLK_RIGHT: mVelX -= DOT_VEL; break;
		}
	}
}

void Dot::move( int levelWidth, int levelHeight )
{
	//Move the dot left or right
	mBox.x += mVelX;

	//If the dot went too far to the left or right
	if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > levelWidth ) )
	{
		//Move back
		mBox.x -= mVelX;
	}

	//Move the dot up or down
	mBox.y += mVelY;

	//If the dot went too far up or down
	if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > levelHeight ) )
	{
		//Move back
		mBox.y -= mVelY;
	}
}

void Dot::render( SDL_Rect camera )
{
	//Show the dot relative to the camera
	gDotTexture.render( mBox.x - camera.x, mBox.y - camera.y );
}

SDL_Rect Dot::getCollider()
{
	//Get collision box
	return mBox;
}

House::House()
{
	//Initialize position
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = HOUSE_WIDTH;
	mBox.h = HOUSE_HEIGHT;

	//Initialize texture
	mHouseTexture = NULL;
}

void House::set( int x, int y, LTexture* houseTexture )
{
	//Initialize position
	mBox.x = x;
	mBox.y = y;

	//Initialize texture
	mHouseTexture = houseTexture;
}

void House::render( SDL_Rect camera )
{
	//Show the house relative to the camera
	mHouseTexture->render( mBox.x - camera.x, mBox.y - camera.y );
}

SDL_Rect House::getCollider()
{
	//Get collision box
	return mBox;
}

Door::Door()
{
	//Initialize position
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = DOOR_WIDTH;
	mBox.h = DOOR_HEIGHT;
}

void Door::set( int x, int y )
{
	//Initialize position
	mBox.x = x;
	mBox.y = y;
}

void Door::render()
{
	//Draw rectangle for door
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( gRenderer, &mBox );
}

SDL_Rect Door::getCollider()
{
	//Get collision box
	return mBox;
}


IntroState* IntroState::get()
{
	//Get static instance
	return &sIntroState;
}

bool IntroState::enter()
{
	//Loading success flag
	bool success = true;

	//Load background
	if( !mBackgroundTexture.loadFromFile( "06_state_machines/introbg.png" ) )
	{
		printf( "Failed to intro background!\n" );
		success = false;
	}

	//Load text
	SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };
	if( !mMessageTexture.loadFromRenderedText( "Lazy Foo' Productions Presents...", textColor ) )
	{
		printf( "Failed to render intro text!\n" );
		success = false;
	}

	return success;
}

bool IntroState::exit()
{
	//Free background and text
	mBackgroundTexture.free();
	mMessageTexture.free();

	return true;
}

void IntroState::handleEvent( SDL_Event& e )
{
	//If the user pressed enter
	if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_RETURN ) )
	{
		//Move onto title state
		setNextState( TitleState::get() );
	}
}

void IntroState::update()
{

}

void IntroState::render()
{
	//Show the background
	mBackgroundTexture.render( 0, 0 );

	//Show the message
	mMessageTexture.render( ( SCREEN_WIDTH - mMessageTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - mMessageTexture.getHeight() ) / 2 );
}

//Declare static instance
IntroState IntroState::sIntroState;

IntroState::IntroState()
{
	//No public instantiation
}


TitleState* TitleState::get()
{
	//Get static instance
	return &sTitleState;
}

bool TitleState::enter()
{
	//Loading success flag
	bool success = true;

	//Load background
	if( !mBackgroundTexture.loadFromFile( "06_state_machines/titlebg.png" ) )
	{
		printf( "Failed to title background!\n" );
		success = false;
	}

	//Load text
	SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };
	if( !mMessageTexture.loadFromRenderedText( "A State Machine Demo", textColor ) )
	{
		printf( "Failed to render title text!\n" );
		success = false;
	}

	return success;
}

bool TitleState::exit()
{
	//Free background and text
	mBackgroundTexture.free();
	mMessageTexture.free();

	return true;
}

void TitleState::handleEvent( SDL_Event& e )
{
	//If the user pressed enter
	if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_RETURN ) )
	{
		//Move to overworld
		setNextState( OverWorldState::get() );
	}
}

void TitleState::update()
{

}

void TitleState::render()
{
	//Show the background
	mBackgroundTexture.render( 0, 0 );

	//Show the message
	mMessageTexture.render( ( SCREEN_WIDTH - mMessageTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - mMessageTexture.getHeight() ) / 2 );
}

//Declare static instance
TitleState TitleState::sTitleState;

TitleState::TitleState()
{
	//No public instantiation
}


OverWorldState* OverWorldState::get()
{
	//Get static instance
	return &sOverWorldState;
}

bool OverWorldState::enter()
{
	//Loading success flag
	bool success = true;

	//Load background
	if( !mBackgroundTexture.loadFromFile( "06_state_machines/greenoverworld.png" ) )
	{
		printf( "Failed to load overworld background!\n" );
		success = false;
	}

	//Load house texture
	if( !mBlueHouseTexture.loadFromFile( "06_state_machines/blue.bmp" ) )
	{
		printf( "Failed to load blue house texture!\n" );
		success = false;
	}

	//Load house texture
	if( !mRedHouseTexture.loadFromFile( "06_state_machines/red.bmp" ) )
	{
		printf( "Failed to load red house texture!\n" );
		success = false;
	}

	//Position houses with graphics
	mRedHouse.set( 0, 0, &mRedHouseTexture );
	mBlueHouse.set( LEVEL_WIDTH - House::HOUSE_WIDTH, LEVEL_HEIGHT - House::HOUSE_HEIGHT, &mBlueHouseTexture );

	//Came from red room state
	if( gCurrentState == RedRoomState::get() )
	{
		//Position below red house
		gDot.set( mRedHouse.getCollider().x + ( House::HOUSE_WIDTH - Dot::DOT_WIDTH ) / 2, mRedHouse.getCollider().y + mRedHouse.getCollider().h + Dot::DOT_HEIGHT );
	}
	//Came from blue room state
	else if( gCurrentState == BlueRoomState::get() )
	{
		//Position above blue house
		gDot.set( mBlueHouse.getCollider().x + ( House::HOUSE_WIDTH - Dot::DOT_WIDTH ) / 2, mBlueHouse.getCollider().y - Dot::DOT_HEIGHT * 2 );
	}
	//Came from other state
	else
	{
		//Position middle of overworld
		gDot.set( ( LEVEL_WIDTH - Dot::DOT_WIDTH ) / 2, ( LEVEL_HEIGHT - Dot::DOT_HEIGHT ) / 2 );
	}

	return success;
}

bool OverWorldState::exit()
{
	//Free textures
	mBackgroundTexture.free();
	mRedHouseTexture.free();
	mBlueHouseTexture.free();

	return true;
}

void OverWorldState::handleEvent( SDL_Event& e )
{
	//Handle dot input
	gDot.handleEvent( e );
}

void OverWorldState::update()
{
	//Move dot
	gDot.move( LEVEL_WIDTH, LEVEL_HEIGHT );

	//On red room collision
	if( checkCollision( gDot.getCollider(), mRedHouse.getCollider() ) )
	{
		//Got to red room
		setNextState( RedRoomState::get() );
	}
	//On blue room collision
	else if( checkCollision( gDot.getCollider(), mBlueHouse.getCollider() ) )
	{
		//Go to blue room
		setNextState( BlueRoomState::get() );
	}
}

void OverWorldState::render()
{
	//Center the camera over the dot
	SDL_Rect camera =
	{
		( gDot.getCollider().x + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2,
		( gDot.getCollider().y + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	};

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}

	//Render background
	mBackgroundTexture.render( 0, 0, &camera );

	//Render objects
	mRedHouse.render( camera );
	mBlueHouse.render( camera );
	gDot.render( camera );
}

//Declare static instance
OverWorldState OverWorldState::sOverWorldState;

OverWorldState::OverWorldState()
{
	//No public instantiation
}


RedRoomState* RedRoomState::get()
{
	//Get static instance
	return &sRedRoomState;
}

bool RedRoomState::enter()
{
	//Loading success flag
	bool success = true;

	//Load background
	if( !mBackgroundTexture.loadFromFile( "06_state_machines/redroom.png" ) )
	{
		printf( "Failed to load blue room background!\n" );
		success = false;
	}

	//Place game objects
	mExitDoor.set( ( LEVEL_WIDTH - Door::DOOR_WIDTH ) / 2, LEVEL_HEIGHT - Door::DOOR_HEIGHT );
	gDot.set( ( LEVEL_WIDTH - Dot::DOT_WIDTH ) / 2, LEVEL_HEIGHT - Door::DOOR_HEIGHT - Dot::DOT_HEIGHT * 2 );

	return success;
}

bool RedRoomState::exit()
{
	//Free background
	mBackgroundTexture.free();

	return true;
}

void RedRoomState::handleEvent( SDL_Event& e )
{
	//Handle dot input
	gDot.handleEvent( e );
}

void RedRoomState::update()
{
	//Move dot
	gDot.move( LEVEL_WIDTH, LEVEL_HEIGHT );

	//On exit collision
	if( checkCollision( gDot.getCollider(), mExitDoor.getCollider() ) )
	{
		//Go back to overworld
		setNextState( OverWorldState::get() );
	}
}

void RedRoomState::render()
{
	//Center the camera over the dot
	SDL_Rect camera = { 0, 0, LEVEL_WIDTH, LEVEL_HEIGHT };

	//Render background
	mBackgroundTexture.render( 0, 0, &camera );

	//Render objects
	mExitDoor.render();
	gDot.render( camera );
}

//Declare static instance
RedRoomState RedRoomState::sRedRoomState;

RedRoomState::RedRoomState()
{
	//No public instantiation
}


BlueRoomState* BlueRoomState::get()
{
	//Get static instance
	return &sBlueRoomState;
}

bool BlueRoomState::enter()
{
	//Loading success flag
	bool success = true;

	//Load background
	if( !mBackgroundTexture.loadFromFile( "06_state_machines/blueroom.png" ) )
	{
		printf( "Failed to load blue room background!\n" );
		success = false;
	}

	//Position game objects
	mExitDoor.set( ( LEVEL_WIDTH - Door::DOOR_WIDTH ) / 2, 0 );
	gDot.set( ( LEVEL_WIDTH - Dot::DOT_WIDTH ) / 2, Door::DOOR_HEIGHT + Dot::DOT_HEIGHT * 2 );

	return success;
}

bool BlueRoomState::exit()
{
	//Free background
	mBackgroundTexture.free();

	return true;
}

void BlueRoomState::handleEvent( SDL_Event& e )
{
	//Handle dot input
	gDot.handleEvent( e );
}

void BlueRoomState::update()
{
	//Move dot
	gDot.move( LEVEL_WIDTH, LEVEL_HEIGHT );

	//On exit collision
	if( checkCollision( gDot.getCollider(), mExitDoor.getCollider() ) )
	{
		//Back to overworld
		setNextState( OverWorldState::get() );
	}
}

void BlueRoomState::render()
{
	//Center the camera over the dot
	SDL_Rect camera = { 0, 0, LEVEL_WIDTH, LEVEL_HEIGHT };

	//Render background
	mBackgroundTexture.render( 0, 0, &camera );

	//Render objects
	mExitDoor.render();
	gDot.render( camera );
}

//Declare static instance
BlueRoomState BlueRoomState::sBlueRoomState;

BlueRoomState::BlueRoomState()
{
	//No public instantiation
}

//Hollow exit state
ExitState* ExitState::get()
{
	return &sExitState;
}

bool ExitState::enter()
{
	return true;
}
	
bool ExitState::exit()
{
	return true;
}

void ExitState::handleEvent( SDL_Event& e )
{

}

void ExitState::update()
{

}

void ExitState::render()
{

}

ExitState ExitState::sExitState;

ExitState::ExitState()
{

}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gDotTexture.loadFromFile( "06_state_machines/dot.bmp" ) )
	{
		printf( "Failed to load dot texture! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont( "06_state_machines/lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Free the surfaces
	gDotTexture.free();

	//Close the font that was used
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy windows
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void setNextState( GameState* newState )
{
    //If the user doesn't want to exit
    if( gNextState != ExitState::get() )
    {
        //Set the next state
        gNextState = newState;
    }
}

void changeState()
{
    //If the state needs to be changed
    if( gNextState != NULL )
    {
		gCurrentState->exit();
		gNextState->enter();

        //Change the current state ID
        gCurrentState = gNextState;
        gNextState = NULL;
    }
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Event handler
			SDL_Event e;

			//Set the current game state object
			gCurrentState = IntroState::get();
			gCurrentState->enter();

			//While the user hasn't quit
			while( gCurrentState != ExitState::get() )
			{
				//Do state event handling
				while( SDL_PollEvent( &e ) != 0 )
				{
					//Handle state events
					gCurrentState->handleEvent( e );

					//Exit on quit
					if( e.type == SDL_QUIT )
					{
						setNextState( ExitState::get() );
					}
				}

				//Do state logic
				gCurrentState->update();

				//Change state if needed
				changeState();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Do state rendering
				gCurrentState->render();

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

    return 0;
}
