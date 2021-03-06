/*Copyright 2021 MetalCat

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#pragma once
#include <World/WorldObjects.h>
#include <vector>

class Snake : public WorldObject
{
public:
	enum Rotation
	{
		Up = 0,
		Down = 1,
		Right = 2,
		Left = 3
	};

	enum Type
	{
		Head = 0,
		Tail = 16,
		BodyCurved = 32,
		Body = 48,
	};

	Rotation BodyRotation = Rotation::Up;

	Type BodyType = Type::Body;

	Snake(Game*game, int renderLayerId, std::string name = "snake", Type type = Type::Head, glm::vec2 location = { 0,0 });

	/**
	* This changes snake image to use proper frames
	* To keep performance good call this function on newly spawned parts and parts before them
	*/
	void UpdateFrame(Snake* prevPart);


	void UpdateRotation(int value);
};

