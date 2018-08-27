#pragma once

#include "Game.hpp"
#include "ClassRegisterType.hpp"

#include "DecorationEngine.hpp"
#include "Particles.hpp"

#define REGISTER(base, type) \
instance->store<base>(#type, new type())

void* Game::getClassRegister()
{
	return classRegister.get();
}
void Game::registerClasses()
{
	auto instance = new ClassRegisterType;
	classRegister.reset(instance);

	REGISTER(Particles, Particles);
}
