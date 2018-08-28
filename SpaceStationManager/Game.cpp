#include "Game.hpp"

#include "Globals.hpp"
#include "TextureAllocator.hpp"
#include "AnimAlloc.hpp"
#include "SoundManager.hpp"
#include "DragUpdater.hpp"

#include "BatchLayers.hpp"
#include "GraphicsComponentUpdater.hpp"
#include "Overlay.hpp"
#include "IOManager.hpp"
#include "Player.hpp"
#include "Universe.hpp"
#include "NetworkBoss.hpp"
#include "Convert.hpp"
#include "QuadComponent.hpp"
#include "Spinner.hpp"
#include "LinearMeter.hpp"
#include "Beam.hpp"
#include "Directory.hpp"
#include "DecorationEngine.hpp"
#include "MemoryDump.hpp"
#include "TimeConfig.hpp"
#include "JSON.hpp"

using namespace leon;

Game::Game()
{
}
void Game::initialize()
{
	m_spDragUpdater = sptr<DragUpdater>(new DragUpdater());

	loadWindow(contentDir() + "settings/" + "window.ini");

	std::srand((unsigned int)std::time(nullptr));
	m_sampleClock = 0;
	m_sampleFreq = 40;
	m_lastTime = 0;

	m_spSound = sptr<SoundManager>(new SoundManager);
	sf::Listener::setDirection(0, 0, -1);//make sure all sounds are heard with the listener looking at the screen
	m_spAnimAlloc = sptr<AnimAlloc>(new AnimAlloc);
	coreIO = sptr<IOManager>(new IOManager(true));

	NetworkBossData nwData;
	m_spNetworkBoss = sptr<NetworkBoss>(new NetworkBoss(nwData));
	IOComponentData overlayData(&getCoreIO());
	overlayData.name = "overlay";
	m_spOverlay = sptr<Overlay>(new Overlay(overlayData, this, this));
	m_spOverlay->loadMenus();

	loadPlayer(contentDir() + "settings/GeneralSettings.cfg");

	/**== GAME IO COMPONENT ==**/
	IOComponentData gameData(&getCoreIO());
	gameData.name = "game";
	gameIOComponent = sptr<IOComponent>(new IOComponent(gameData, &Game::input, this));

	loadUniverse("RANDOMTEXT");//TODO RANDOMTEXT
	m_spUniverse->pauser.togglePause(true);
	m_spUniverse->started = false;

	m_spDir = sptr<Directory>(new Directory(contentDir()));

	m_spIcon.reset(new sf::Image());
	if(m_spIcon->loadFromFile(contentDir() + "textures/" + "gameicon.png"))
		getWindow().setIcon(64, 64, m_spIcon->getPixelsPtr());
}
Game::~Game()
{

}
void Game::loadPlayer(const String& rFileName)
{
	PlayerData data(coreIO.get());

	Json::Value root;//Let's parse it
	Json::Reader reader;
	std::ifstream test(rFileName, std::ifstream::binary);
	bool parsedSuccess = reader.parse(test, root, false);

	if(!parsedSuccess)
	{
		DEBUGOUTPUT("Parse failed on " + rFileName);
	}
	else
	{
		data.name = root["PlayerName"].asString();
	}

	m_spLocalPlayer.reset(new Player(data));
}
Player& Game::getLocalPlayer()
{
	return *m_spLocalPlayer;
}
sf::RenderWindow& Game::getWindow()
{
	return *m_spWindow;
}
Overlay& Game::getOverlay()
{
	return *m_spOverlay;
}
IOManager& Game::getCoreIO()
{
	return *coreIO;
}
NetworkBoss& Game::getNwBoss()
{
	return *m_spNetworkBoss;
}
TextureAllocator& Game::getTextureAllocator()
{
	return *m_spTexAlloc;
}
AnimAlloc& Game::getAnimAlloc()
{
	return *m_spAnimAlloc;
}
Universe& Game::getUniverse()
{
	return *m_spUniverse;
}
DragUpdater& Game::getDragUpdater()
{
	return *m_spDragUpdater;
}
const Directory& Game::getDir() const
{
	return *m_spDir;
}
void Game::launchGame(const GameLaunchData& data)
{
	getGame()->loadUniverse("meaninglessString");
	getGame()->getUniverse().loadLevel(data);

	sf::Packet boolean;
	boolean << false;

	Message closeMenu("overlay", "setMenu", boolean, 0, false);
	getGame()->getCoreIO().recieve(closeMenu);
}
SoundManager& Game::getSound()
{
	return *m_spSound;
}
float Game::getTime() const
{
	return m_lastTime;
}
void Game::updateTime()
{
	m_lastTime = m_clock.getElapsedTime().asSeconds();
	m_spUniverse->pauser.setRealTime(m_lastTime);
}
void Game::run()
{
	sf::RenderWindow& rWindow = *m_spWindow;
	float frameTime = 0.f;
	float lastTime = m_clock.getElapsedTime().asSeconds();
	float ticksNeeded = 0.f;

	while(rWindow.isOpen())
	{
		frameTime = m_clock.getElapsedTime().asSeconds() - lastTime;
		lastTime = m_clock.getElapsedTime().asSeconds();
		
		tick(frameTime);
	}
}
void Game::tick(float frameTime)
{
	sf::RenderWindow& rWindow = *m_spWindow;

	float physTickTimeRemaining = 0;
	const float timeStep = TimeConfig::Instance->getWorldTimeStep();
	const Vec2 mouseSfmlWorldPos = (Vec2)getWindow().mapPixelToCoords(sf::Mouse::getPosition(getGame()->getWindow()), getLocalPlayer().getCamera().getView());

	// show framerate
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
		Print << "\nFPS: " << 1.f / frameTime;

	// io
	getCoreIO().update(frameTime);
	getUniverse().getUniverseIO().update(frameTime);
	getGame()->updateTime();

	// physics
	physTickTimeRemaining += frameTime;
	while(physTickTimeRemaining >= timeStep)
	{
		getUniverse().prePhysUpdate();
		getUniverse().physUpdate();

		getLocalPlayer().updateView();
		rWindow.setView(getLocalPlayer().getCamera().getView());
		getLocalPlayer().getLiveInput(mouseSfmlWorldPos);

		getUniverse().postPhysUpdate();
		physTickTimeRemaining -= timeStep;
	}


	/**NETWORK**/
	if(m_spNetworkBoss->getNWState() != NWState::Local)
		m_spNetworkBoss->update();


	/**== WINDOW ==**/
	getDragUpdater().update(getLocalPlayer().getMouseWindowPos());
	rWindow.setView(*m_spStaticView);
	getLocalPlayer().getWindowEvents(rWindow);
	const Vec2 camPos = getLocalPlayer().getCamera().getPosition();
	const Vec2 halfSize = Convert::screenToUniverse((Vec2)rWindow.getSize()) / 2;
	const float maxZoom = getLocalPlayer().getCamera().m_maxZoom * 1.5f;
	const Vec2 maxHalfSize(halfSize.x * maxZoom, halfSize.y * maxZoom);
	const float zoom = getLocalPlayer().getCamera().getZoom();
	getUniverse().getDecors().update(camPos, maxHalfSize, zoom);
	getUniverse().getGfxUpdater().update();//update graphics components



	/**== DRAW UNIVERSE ==**/
	rWindow.clear(sf::Color::Black);

	rWindow.setView(getLocalPlayer().getCamera().getView());
	if(getUniverse().debugDraw())
	{
		// TODO do debug draw
	}
	else
		getUniverse().getBatchLayers().drawWorld(rWindow);


	/**== DRAW GUI/OVERLAYS ==**/
	m_spOverlay->getGui().draw(false); // TODO pass true here ?
	m_spOverlay->mouseMoveToPosition((sf::Vector2f)sf::Mouse::getPosition(rWindow));

	/**== DISPLAY ==**/
	rWindow.display();
}
/// <summary>
/// Literally exits the getGame()->
/// </summary>
void Game::exit()
{
	m_spWindow->close();
}
/// <summary>
/// Destroys old universe and makes new one!
/// </summary>
void Game::loadUniverse(const String& stuff)
{
	IOComponentData universeData(&getCoreIO());
	universeData.name = "universe";


	m_spUniverse.reset();
	m_spUniverse.reset(new Universe(universeData));


	registerClasses();


	m_spUniverse->getUniverseIO().give(gameIOComponent.get());

	if(getGame()->getNwBoss().getNWState() == NWState::Client)
		getUniverse().getUniverseIO().toggleAcceptsLocal(false);
	else
		getUniverse().getUniverseIO().toggleAcceptsLocal(true);
}
/// <summary>
/// Initializes the window from a json file with the needed data.
/// </summary>
void Game::loadWindow(const String& windowFile)
{
	sf::ContextSettings settings;
	struct WindowInitData
	{
		WindowInitData()
		{
			windowName = "FIXME";
			windowed = true;

			mode = sf::VideoMode(640, 640, 32);

			antiAliasLevel = 0;
			smoothTextures = false;

			vSinc = false;
			targetFPS = 10;
		}
		String windowName;//name of window to display
		bool windowed;//windowed vs fullscreen

		sf::VideoMode mode;

		int antiAliasLevel;
		bool smoothTextures;

		bool vSinc;
		int targetFPS;

		void loadJson(const Json::Value& root)
		{
			GETJSON(windowName);
			GETJSON(windowed);

			mode = sf::VideoMode(root["resX"].asInt(), root["resY"].asInt(), root["color"].asInt());

			GETJSON(antiAliasLevel);
			GETJSON(smoothTextures);

			GETJSON(vSinc);
			GETJSON(targetFPS);
		}
	};
	WindowInitData windowData;


	Json::Value root;//Let's parse it
	Json::Reader reader;
	std::ifstream test(windowFile, std::ifstream::binary);
	bool parsedSuccess = reader.parse(test, root, false);

	if(!parsedSuccess)
		Print << "\nParse Failed [" << windowFile << "]." << std::endl << FILELINE;
	else
		windowData.loadJson(root);


	settings.antialiasingLevel = windowData.antiAliasLevel;
	int style;//the sf::style enum has no name!!
	if(windowData.windowed)//windowed or fullscreen?
	{
		style = sf::Style::Default;
	}
	else
	{
		style = sf::Style::Fullscreen;
	}


	/**CREATE THE WINDOW AND TEXTURE ALLOC**/
	if(m_spWindow)//if we are already pointing at something
	{
		///close the old window???
		m_spWindow->create(windowData.mode, windowData.windowName, style, settings);
		m_spTexAlloc->smoothTextures(windowData.smoothTextures);
	}
	else//if this is the first time we created something
	{
		m_spWindow.reset(new sf::RenderWindow(windowData.mode, windowData.windowName, style, settings));
		m_spTexAlloc.reset(new TextureAllocator(windowData.smoothTextures));
	}

	m_spWindow->setVerticalSyncEnabled(windowData.vSinc);
	if(!windowData.vSinc)
		m_spWindow->setFramerateLimit(windowData.targetFPS);

	resizeStaticView();
}
void Game::resizeStaticView()
{
	m_spStaticView.reset(new sf::View(sf::Vector2f(m_spWindow->getSize().x / 2.f, m_spWindow->getSize().y / 2.f), static_cast<sf::Vector2f>(m_spWindow->getSize())));
}
/// <summary>
/// process the command
/// </summary>
/// <param name="rCommand">The r command.</param>
/// <param name="rData">The r data.</param>
void Game::input(String rCommand, sf::Packet rData)
{
	if(rCommand == "exit")
	{
		exit();
	}
	else if(rCommand == "load")
	{
		///TODO
	}
	else if(rCommand == "printToConsole")
	{
		String str;
		rData >> str;
		Print << "\nprintToConsole: " << str;
	}
	else
	{
		Print << "Game: [" << rCommand << "] not found.";
	}
}

