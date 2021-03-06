/*Copyright 2021 MetalCat

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#pragma once
#include "Object.h"
#include <Texture/Texture.h>

/**
* This class contains basic objects for displaying objects that will be used in gameplay
*/
class WorldObject :public Object
{
protected:
	Texture* objectTexture = nullptr;

	int renderLayerId = 0;
public:

	bool Visible = true;

	WorldObject(Game* game, int renderLayerId, std::string name = "", Vector2 loc = { 0,0 });

	/**
	* Spawns object that will have use global atlas and display part of the atlas cut by frame
	*/
	WorldObject(Game* game, int renderLayerId, std::string name = "", glm::vec4 frame = { 0,0,0,0 }, Vector2 loc = { 0,0 });

	int GetRenderLayerId()const { return renderLayerId; }

	virtual void SetLocation(glm::vec2 loc)override;

	Texture* GetTexture()const { return objectTexture; }

	virtual void Draw();

	virtual void Destroy()override;
};

