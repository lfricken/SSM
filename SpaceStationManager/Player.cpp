#include "Player.hpp"
#include "Globals.hpp"
#include "Overlay.hpp"
#include "Panel.hpp"
#include "Universe.hpp"
#include "IOManager.hpp"
#include "Convert.hpp"
#include "LinearMeter.hpp"
#include "Particles.hpp"
#include "SoundManager.hpp"
#include "Convert.hpp"
#include "Decoration.hpp"
#include "Debugging.hpp"

#pragma warning( disable : 4800)

InputConfig::InputConfig()
{
	/**MOVEMENT**/
	up = sf::Keyboard::W;
	down = sf::Keyboard::S;
	rollCCW = sf::Keyboard::A;
	rollCW = sf::Keyboard::D;

	/**SPECIAL**/
	stealth = sf::Keyboard::Q;
	shield = sf::Keyboard::Space;
	teleport = sf::Keyboard::E;
	boost = sf::Keyboard::LShift;

	/**WEAPON**/
	primary = sf::Mouse::Left;
	secondary = sf::Mouse::Right;

	cgroup_1 = sf::Keyboard::Num1;
	cgroup_2 = sf::Keyboard::Num2;
	cgroup_3 = sf::Keyboard::Num3;
	cgroup_4 = sf::Keyboard::Num4;

	/**OTHER**/
	store = sf::Keyboard::B;
	respawn = sf::Keyboard::R;
	grabTarget = sf::Keyboard::T;

	buildHardpoint = sf::Keyboard::F;
	buildExtractor = sf::Keyboard::G;
	buildRelay = sf::Keyboard::H;
	buildMind = sf::Keyboard::J;
	buildReplicator = sf::Keyboard::K;

	cameraUp = sf::Keyboard::Up;
	cameraDown = sf::Keyboard::Down;
	cameraLeft = sf::Keyboard::Left;
	cameraRight = sf::Keyboard::Right;
}

Player::Player(const PlayerData& rData) : m_io(rData.ioComp, &Player::input, this), BasePlayerTraits(rData.name)
{
	m_hasFocus = true;
	m_canInteractWithUniverse = true;
}
Player::~Player()
{

}
Camera& Player::getCamera()
{
	return m_camera;
}
const InputConfig& Player::getInCfg() const
{
	return m_keyBindings;
}
bool Player::inGuiMode() const
{
	return m_canInteractWithUniverse;
}
bool Player::toggleGuiMode(bool isGuiModeOn)
{
	return m_canInteractWithUniverse = isGuiModeOn;
}
const sf::Vector2f& Player::getMouseWindowPos() const
{
	return m_mouseWindowPos;
}
void Player::setMouseWindowPos(const sf::Vector2f& rPos)
{
	sf::Mouse::setPosition(sf::Vector2i((int)rPos.x, (int)rPos.y), getGame()->getWindow());
	m_mouseWindowPos = rPos;
}
void Player::getLiveInput(Vec2 mouseScreenPosition)
{
	if(!m_canInteractWithUniverse && hasFocus())
	{
		// camera control
		const float speed = 0.05f;
		if(sf::Keyboard::isKeyPressed(m_keyBindings.cameraUp))
			m_camera.move(Vec2(0, speed));
		if(sf::Keyboard::isKeyPressed(m_keyBindings.cameraDown))
			m_camera.move(Vec2(0, -speed));
		if(sf::Keyboard::isKeyPressed(m_keyBindings.cameraLeft))
			m_camera.move(Vec2(-speed, 0));
		if(sf::Keyboard::isKeyPressed(m_keyBindings.cameraRight))
			m_camera.move(Vec2(speed, 0));

		// dev stuff
		static Timer spawnTimer(getGame());
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
		{
			if(spawnTimer.isTimeUp())
			{
				spawnTimer.setCountDown(0.1f);
				spawnTimer.restartCountDown();

				auto m_aim = Vec2(0, 0);

				getGame()->getUniverse().spawnParticles("LowSparks", m_aim, Vec2(0, 0), Vec2(0, 0));
				getGame()->getSound().playSound("default.wav", m_aim);
			}
		}
	}
}
void Player::getWindowEvents(sf::RenderWindow& rWindow)
{
	sf::Event event;

	while(rWindow.pollEvent(event))
	{
		if(event.type == sf::Event::LostFocus)
			toggleFocus(false);
		if(event.type == sf::Event::GainedFocus)
			toggleFocus(true);
		if(event.type == sf::Event::Resized)
		{
			// window was resized
			getGame()->resizeStaticView();
			m_camera.resize();
			getGame()->getOverlay().getGui().handleEvent(event, false);
		}

		if(event.type == sf::Event::Closed)
		{
			rWindow.close(); // if someone hits the window X, close the window
		}
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == m_keyBindings.buildExtractor)
			{
				// TODO add shortcuts
			}

			// TODO toggle gui mode in a sane way (disable others and only enable main menu panel)
			if(event.key.code == sf::Keyboard::Escape)
			{
				Message menu("overlay", "toggleMenu", voidPacket, 0, false);
				getGame()->getCoreIO().recieve(menu);
			}
		}



		getGame()->getOverlay().handleEvent(event); // TODO if we don't handle the event we should pass it to the universe


		if(m_canInteractWithUniverse)
		{
			// zoom
			if(event.type == sf::Event::MouseWheelMoved)
			{
				int change = -event.mouseWheel.delta;
				if(change < 0)
					m_camera.setZoom(m_camera.getZoom()*0.8f);
				else
					m_camera.setZoom(m_camera.getZoom()*1.2f);
			}

			if(event.type == sf::Event::KeyPressed)
			{
				// dev options
				if(event.key.code == sf::Keyboard::Numpad9)
					getGame()->getUniverse().toggleDebugDraw();
				if(event.key.code == sf::Keyboard::Numpad0)
					getGame()->getUniverse().pauser.togglePause();
			}
		}
	}
}
void Player::updateView()
{

}
IOComponent& Player::getIOComp()
{
	return m_io;
}
bool Player::toggleFocus(bool isWindowFocused)
{
	m_hasFocus = isWindowFocused;
	return m_hasFocus;
}
bool Player::hasFocus() const
{
	return m_hasFocus;
}
void Player::input(String rCommand, sf::Packet rData)
{
	sf::Packet data(rData);
	if(rCommand == "setGuiMode")
	{
		bool mode = false;
		data >> mode;
		toggleGuiMode(mode);
	}
	else if(rCommand == "cameraShake")
	{
		m_camera.shake(0.5f, 60.f, 0.4f);
	}
}


