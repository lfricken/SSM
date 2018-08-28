#pragma once

#include "stdafx.hpp"
#include "IOComponent.hpp"
#include "NonCopyable.hpp"
#include "Clock.hpp"
#include "Blueprintable.hpp"

class Game;

namespace leon
{
	class Panel;

	/// Holds a list of all Panel, which then contain everything with the GUI.
	class Overlay : Core::INonCopyable
	{
	public:
		Overlay(const IOComponentData& rData, const Core::IClock* _clock, Game* _parent);
		virtual ~Overlay();

		/// Add a Panel to the list.
		void addPanel(sptr<leon::Panel> spPanel);

		/// <summary>
		/// 
		/// </summary>
		void mouseMoveToPosition(sf::Vector2f pos);

		/// <summary>
		/// Returns true if the overlays handled the event.
		/// </summary>
		bool handleEvent(sf::Event& rEvent);

		/// Load the menus.
		void loadMenus();
		/// <summary>
		/// Store
		/// </summary>
		leon::Panel* loadMainMenu();
		leon::Panel* loadSellMenu();
		leon::Panel* loadMultiplayerLobby(leon::Panel* pMain_menu);
		leon::Panel* loadConnectionHub(leon::Panel* pMain_menu);
		/// Return TGUI Gui.
		tgui::Gui& getGui();

		void resetStore();

		/// Turn the Main Menu on or off. Handles input switching, pausing game, visuals switch.
		void toggleMenu(bool show);
		/// Toggle whether the scoreboard should be visible or not.
		void toggleScoreboard(bool show);

		sptr<Panel> storePanel;
	protected:
		void input(const String rCommand, sf::Packet rData);

	private:

		Game* parent;
		BlueprintParams params;

		const Core::IClock* clock;
		IOManager* ioManager;

		bool m_menuShowing;//true if menu is showing
		bool m_scoreboardShowing;//true if the scoreboard is showing

		IOComponent m_io;
		tgui::Gui m_gui;//the TGUI gui that handles most things
		List<sptr<leon::Panel> > m_panelList;//all the Panels that can get displayed, each item can be active or inactive, if its active, it gets displayed.
	};
}
