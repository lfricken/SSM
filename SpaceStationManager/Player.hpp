#pragma once

#include "stdafx.hpp"
#include "Controller.hpp"
#include "Camera.hpp"
#include "BasePlayerTraits.hpp"
#include "Resources.hpp"


class QuadComponent;
class LinearMeter;
class Minimap;
namespace leon
{
	class Grid;
}

/// \brief Key configurations.
///
/// This system would allow loading and saving of key configurations.
struct InputConfig
{
	InputConfig();

	/**MOVEMENT**/
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key rollCCW;
	sf::Keyboard::Key rollCW;

	/**SPECIAL**/
	sf::Keyboard::Key stealth;
	sf::Keyboard::Key shield;
	sf::Keyboard::Key teleport;
	sf::Keyboard::Key boost;
	sf::Keyboard::Key grabTarget;

	/**WEAPON**/
	sf::Mouse::Button primary;
	sf::Mouse::Button secondary;

	sf::Keyboard::Key cgroup_1;
	sf::Keyboard::Key cgroup_2;
	sf::Keyboard::Key cgroup_3;
	sf::Keyboard::Key cgroup_4;

	/**OTHER**/
	sf::Keyboard::Key store;
	sf::Keyboard::Key respawn;

	sf::Keyboard::Key buildExtractor;
	sf::Keyboard::Key buildRelay;
	sf::Keyboard::Key buildHardpoint;
	sf::Keyboard::Key buildMind;
	sf::Keyboard::Key buildReplicator;

	sf::Keyboard::Key cameraUp;
	sf::Keyboard::Key cameraDown;
	sf::Keyboard::Key cameraLeft;

	sf::Keyboard::Key cameraRight;
};
/// Data necessary for local player.
struct PlayerData
{
	PlayerData() :
		ioComp(&getGame()->getCoreIO()),
		keyConfig(),
		tracking(true)
	{
		ioComp.name = "local_player";
		name = "default_local_player_name";
	}
	String name;
	IOComponentData ioComp;
	InputConfig keyConfig;
	bool tracking;
};


/// <summary>
/// Represents the local player on this machine.
/// This class also handles all user input through it's getLiveInput and getWindowEvents functions
/// those commands are then sent to a controller. Variables must be reset in universeDestroyed.
/// </summary>
class Player : public BasePlayerTraits
{
public:
	Player(const PlayerData& rData);
	virtual ~Player();

	/// Returns Camera for local player.
	Camera& getCamera();
	/// Returns keyboard input configuration.
	const InputConfig& getInCfg() const;
	/// Return IO component of the Player.
	IOComponent& getIOComp();
	/// Is the player in GUI mode or Game mode?
	/// If in GUI mode, the commands to go the GUI instead of the players ship.
	bool inGuiMode() const;
	/// Toggle GUI mode on or off.
	bool toggleGuiMode(bool isGuiModeOn);
	/// Toggle whether the Game have "Window Focus"? This is an OS related feature.
	bool toggleFocus(bool isWindowFocused);
	/// Does the Game have Window Focus?
	bool hasFocus() const;

	/// Return the position of the players cursor in window coordinates.
	const sf::Vector2f& getMouseWindowPos() const;
	/// Set the position of the players cursor in window coordinates.
	void setMouseWindowPos(const sf::Vector2f& rPos);

	/// Get direct feed from keyboard and mouse. Gets their states only, not events.
	void getLiveInput(Vec2 mouseScreenPosition);
	/// Get events, such as keydown, keyup, mouse-button-down, mouse-button-up etc.
	void getWindowEvents(sf::RenderWindow& rWindow);

	/// <summary>
	/// TODO This does nothing!
	/// </summary>
	void updateView();

protected:
	void input(String rCommand, sf::Packet rData);

private:

	sf::Vector2f m_mouseWindowPos; // where is the players mouse on the screen?

	/// <summary>
	/// Controls zoom and where on the map is being displayed.
	/// </summary>
	Camera m_camera;

	/// <summary>
	/// Keybindings
	/// </summary>
	InputConfig m_keyBindings;

	/// <summary>
	/// True if player click events can make it through to the grid.
	/// </summary>
	bool m_canInteractWithUniverse;

	/// <summary>
	/// True if the sfml window has focus.
	/// </summary>
	bool m_hasFocus;

	/// <summary>
	/// Send messages to this player.
	/// </summary>
	IOComponent m_io;
};

