#include "MemoryDump.hpp"
#include "Globals.hpp"
#include "OOCore.hpp"

Game* getGame(Game* instance)
{
	static Game* inst;

	if(instance == nullptr)
	{
		return inst;
	}
	else
	{
		inst = instance;
		return nullptr;
	}
}

int main()
{
	SIMPLEOUTPUT("\n");
	SIMPLEOUTPUT("Program Started.");
	{
		sp<Game> game(new Game());
		getGame(game.get());
		game->initialize();
		getGame()->run();
	}
	_CrtDumpMemoryLeaks();

	SIMPLEOUTPUT("Program ended.");
	SIMPLEOUTPUT("\n");
	return 0;
}

