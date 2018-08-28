#include "Universe.hpp"
#include "BlueprintLoader.hpp"
#include "Globals.hpp"
#include "BatchLayers.hpp"
#include "GraphicsComponentUpdater.hpp"
#include "IOManager.hpp"
#include "Player.hpp"
#include "QuadComponent.hpp"
#include "LinearMeter.hpp"
#include "Convert.hpp"
#include "DecorationEngine.hpp"
#include "Overlay.hpp"
#include "NetworkComponent.hpp"


void Universe::loadLevel(const GameLaunchData& data)//loads a level using blueprints
{
	loadBlueprints("blueprints/");

	const String levelFile = "level.lcfg";
	const String levelFolder = "levels";
	const String thisLevelFolder = contentDir() + levelFolder + "/" + data.level + "/";
	const String modDir = "mods/";

	std::ifstream level(thisLevelFolder + levelFile, std::ifstream::binary);
	Json::Reader reader;
	Json::Value root;

	bool parsedSuccess = reader.parse(level, root, false);

	if(!parsedSuccess)
	{
		Print << "\nParse Failed [" << thisLevelFolder + levelFile << "].\n" << FILELINE;
		return;
	}
	else
	{
		/**Decorations**/
		DecorationEngine& decorations = *m_spDecorEngine;
		LOADJSON(decorations);
	}

	Message initBackground(this->m_io.getName(), "initBackgroundCommand", voidPacket, 0, false);
	Message::SendUniverse(initBackground);

	getGame()->getOverlay().resetStore();
}
Universe::Universe(const IOComponentData& rData) : m_io(rData, &Universe::input, this), pauser(getGame()->getTime())
{
	m_nw.reset(new NetworkComponent(NetworkComponentData(), &Universe::pack, &Universe::unpack, this, getGame()->getNwBoss().getNWFactoryTcp()));

	m_spBPLoader = sptr<BlueprintLoader>(new BlueprintLoader);
	m_spBatchLayers = sptr<BatchLayers>(new BatchLayers);
	m_spGfxUpdater = sptr<GraphicsComponentUpdater>(new GraphicsComponentUpdater);


	m_spUniverseIO = sptr<IOManager>(new IOManager(true, true));
	m_spUniverseIO->give(&m_io);
	m_spUniverseIO->give(&getGame()->getLocalPlayer().getIOComp());


	m_spDecorEngine.reset(new DecorationEngine);


	m_debugDrawEnabled = false;
}
Universe::~Universe()
{

}
ProjectileMan& Universe::getProjMan()
{
	return *m_spProjMan;
}
DecorationEngine& Universe::getDecors()
{
	return *m_spDecorEngine;
}
BlueprintLoader& Universe::getBlueprints()
{
	return *m_spBPLoader;
}
BatchLayers& Universe::getBatchLayers()
{
	return *m_spBatchLayers;
}
GraphicsComponentUpdater& Universe::getGfxUpdater()
{
	return *m_spGfxUpdater;
}
void Universe::toggleDebugDraw()
{
	m_debugDrawEnabled = !m_debugDrawEnabled;
}
void Universe::prePhysUpdate()
{

}
void Universe::physUpdate()
{

}
void Universe::postPhysUpdate()
{

}
bool Universe::listContains(std::list<Team> intList, Team value)
{
	if(intList.empty())
		return true;

	for(auto it = intList.begin(); it != intList.end(); ++it)
	{
		if((*it) == value)
			return true;
	}
	return false;
}
bool Universe::debugDraw() const
{
	return m_debugDrawEnabled;
}
void Universe::loadBlueprints(const String& bpDir)//loads blueprints
{
	m_spBPLoader->loadBlueprints(bpDir);
}
void Universe::pack(sf::Packet& data)
{
	//TODO sync money maybe? Looks like that's already being done via seperate message
}
void Universe::unpack(sf::Packet& data)
{

}
void Universe::input(String rCommand, sf::Packet rData)
{
	sf::Packet data(rData);
	if(rCommand == "togglePause")
	{
		pauser.togglePause(!pauser.isPaused());
	}
	else if(rCommand == "setPause")
	{
		bool mode;
		data >> mode;
		pauser.togglePause(mode);
	}
	else if(rCommand == "initBackgroundCommand")
	{
		float maxZoom = getGame()->getLocalPlayer().getCamera().m_maxZoom * 0.4f;
		float sizeInUniverse = Convert::screenToUniverse((float)getGame()->getWindow().getSize().x);
		m_spDecorEngine->initSpawns(Vec2(0, 0), Vec2(maxZoom * sizeInUniverse, maxZoom * sizeInUniverse));
	}
	else
	{
		Print << "\n" << m_io.getName() << ":[" << rCommand << "] not found." << FILELINE;
	}
}
void Universe::spawnParticles(const String& particleBP, const Vec2& pos, const Vec2& dir, const Vec2& transverse)
{
	m_spDecorEngine->spawnParticles(particleBP, pos, dir, transverse);
}
