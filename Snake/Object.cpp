#include "Object.h"

Object::Object(Game* _game, std::string _name, Vector2 loc)
	:location(loc), name(_name), game(_game)
{

}

void Object::SetLocation(Vector2 loc)
{
	location = loc;
}

void Object::Invalidate()
{
	pending_kill = true;
}

void Object::Destroy()
{
}
