/*Copyright 2021 MetalCat

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>

#include <World/WorldObjects.h>
#include <Camera/Camera.h>
#include <glm/vec3.hpp>

#include <Texture/Texture.h>
#include <Player/Player.h>

#include <UI/Button.h>

struct AtlasTexture
{
	std::string name;
	SDL_Texture* texture;

	AtlasTexture(std::string _name, SDL_Texture* _texture);
};

enum class RenderLayers :int
{
	Background = 0,
	GameplayObjects = 1,
	Wall = 2,
	Snake = 3,
	UI = 4,
	MAX
};

class Game
{
protected:
	SDL_Renderer* renderer = nullptr;

	std::vector<WorldObject*>objects = std::vector<WorldObject*>();

	std::vector<Button*>ui = std::vector<Button*>();

	/**to make drawing easier objects can use differnt layers to be drawn
	* 0 is background
	* 1 is gameplay
	* 2 is for snake
	*/
	std::vector<WorldObject*>RenderLayersObjects[(int)RenderLayers::MAX];

	SDL_Window* window = nullptr;


	/**
	* this value is equal to the size of the window before resizing
	* */
	glm::vec2 window_size_old = { 500,500 };

	/**
	* curent size of the window
	* */
	glm::vec2 window_size = { 500,500 };

	/**
	* Window size that this game starts with
	*/
	glm::vec2 default_window_size = { 500,500 };

	glm::vec3 defaultClearColor = { 0,0,0 };

	Uint64 lastTime = 0;
	float deltaTime = 0;

	int totalAppleCount = 0;
public:
	Button* EndInfoCard = nullptr;
	Button* EndMenu = nullptr;

	/**
	* to avoid making every object load texture every time we need and to save up some space
	* textures are going to use atlases
	* and some atlases are going to be loaded from the start(atlas.png MUST be present for game to function)
	* */
	std::vector<AtlasTexture>textures = std::vector< AtlasTexture>();

	Player* player = nullptr;

	Game();

	SDL_Texture* GetTexture(std::string name);

	SDL_Renderer* GetRenderer() { return renderer; };

	SDL_Texture* LoadTextureFromFile(std::string fileName);

	glm::vec2 GetOldWindowSize()const { return window_size_old; }

	glm::vec2 GetWindowSize()const { return window_size; }

	glm::vec2 GetWindowScale()const { return window_size / default_window_size; }

	glm::vec2 GetDefaultWindowSize()const { return default_window_size; }

	int GetTotalAppleCount()const { return totalAppleCount; }

	std::vector<WorldObject*> GetObjectsInRenderLayer(int id) { return RenderLayersObjects[id]; }

	/**
	* This function shows end level ui
	*/
	void EndLevel();

	/**
	* Load new level.
	* Note this adds to the currently existing levels so make sure previous data is cleare
	*/
	bool LoadLevel(std::string levelFilePath);

	/**
	* This function does the same thing as Close() but does not destroy sdl objects
	*/
	void ClearLevel();

	Camera* CurrentCamera = nullptr;

	float GetDeltaTime()const { return deltaTime; }

	int GridSize = 64;

	template<class Class,class ...Args>
	Class* SpawnWorldObject(std::string name, int renderLayerId, Args...args);

	template<class Class, class ...Args>
	Class* SpawnUIObject(std::string name, Args...args);

	SDL_Event event;

	bool needsToClose = false;

	void Init();

	void Close();

	void Draw();

	void Update();

	/*test objects*/
	Texture* test = nullptr;
};

template<class Class, class ...Args>
inline Class* Game::SpawnWorldObject(std::string name,int renderLayerId, Args ...args)
{
	Class* obj = new Class(this,renderLayerId, name, args...);
	objects.push_back(obj);
	RenderLayersObjects[renderLayerId].push_back(obj);
	return obj;
}

template<class Class, class ...Args>
inline Class* Game::SpawnUIObject(std::string name, Args ...args)
{
	Class* uio = new Class(this, (int)RenderLayers::UI, name, args...);
	RenderLayersObjects[(int)RenderLayers::UI].push_back(uio);
	ui.push_back(uio);
	return uio;
}
