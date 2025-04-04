#include "Overlay.hpp"

#include "Globals.hpp"
#include "Panel.hpp"
#include "Picture.hpp"
#include "Button.hpp"
#include "Courier.hpp"
#include "EditBox.hpp"
#include "Chatbox.hpp"
#include "Draggable.hpp"
#include "DraggableSurface.hpp"
#include "Debugging.hpp"
#include "NumericDisplay.hpp"
#include "ReturnSelection.hpp"
#include "Tooltip.hpp"
#include "JSON.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "IOManager.hpp"

using namespace leon;

Overlay::Overlay(const IOComponentData& rData, const Core::IClock* _clock, Game* _parent) : m_gui(getGame()->getWindow()), m_io(rData, &Overlay::input, this), params(_clock, rData.pMyManager)
{
	parent = _parent;
	clock = _clock;
	ioManager = rData.pMyManager;

	m_gui.setGlobalFont(contentDir() + "TGUI/fonts/DejaVuSans.ttf");
	m_menuShowing = true;
	m_scoreboardShowing = false;
	/**If we call loadMenus now, we try and access this very Overlay object before it has been returned to game**/
}
Overlay::~Overlay()
{

}
void Overlay::addPanel(sptr<leon::Panel> spPanel)
{
	m_panelList.push_back(spPanel);
}

void Overlay::mouseMoveToPosition(sf::Vector2f pos)
{
	for each(auto panel in m_panelList)
	{
		panel->mouseMoveToPosition(pos);
	}
}
bool Overlay::handleEvent(sf::Event& rEvent)
{
	return m_gui.handleEvent(rEvent, false);
}
tgui::Gui& Overlay::getGui()
{
	return m_gui;
}
void Overlay::loadMenus()
{


	auto pMain_menu = loadMainMenu();
	getGame()->getOverlay().addPanel(sptr<leon::Panel>(pMain_menu));
	//load other menus
	getGame()->getOverlay().addPanel(sptr<leon::Panel>(loadConnectionHub(pMain_menu)));
	getGame()->getOverlay().addPanel(sptr<leon::Panel>(loadMultiplayerLobby(pMain_menu)));
	getGame()->getOverlay().addPanel(sptr<leon::Panel>(loadSellMenu()));

	//unlock some initially for debugging


	/**MESSAGE**/
	sf::Vector2f closePanelSize = sf::Vector2f(640, 480);
	leon::PanelData messagePanel(params);
	messagePanel.ioComp.name = "message_panel";
	messagePanel.startHidden = true;
	messagePanel.backgroundColor = sf::Color::Blue;
	messagePanel.screenCoords = sf::Vector2f(getGame()->getWindow().getSize().x / 2 - closePanelSize.x / 2, getGame()->getWindow().getSize().y / 2 - closePanelSize.y / 2);
	messagePanel.size = sf::Vector2f(closePanelSize.x, closePanelSize.y);
	leon::Panel* pMessBox = new leon::Panel(getGame()->getOverlay().getGui(), messagePanel);
	/**====OK====**/
	leon::ButtonData closeMessBox(params);
	closeMessBox.size = sf::Vector2f(50, 50);
	closeMessBox.buttonText = "OK";
	closeMessBox.screenCoords = sf::Vector2f(closePanelSize.x / 2 - 50 / 2, closePanelSize.y - (50 + 5));
	Courier closeMess;
	closeMess.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
	closeMess.message.reset("message_panel", "toggleHidden", voidPacket, 0, false);
	closeMessBox.ioComp.courierList.push_back(closeMess);
	leon::WidgetBase* pClose = new leon::Button(*pMessBox->getPanelPtr(), closeMessBox);
	pMessBox->add(sptr<leon::WidgetBase>(pClose));
	getGame()->getOverlay().addPanel(sptr<leon::Panel>(pMessBox));
}
leon::Panel* Overlay::loadSellMenu()
{
	leon::Panel* panel = nullptr;
	sf::Vector2i panelSize(100, 25);

	{
		leon::ReturnSelectionData data(params);
		data.ioComp.name = "return_selection";
		data.startHidden = true;
		data.backgroundColor = sf::Color(50, 50, 50, 128);
		data.screenCoords = sf::Vector2f(getGame()->getWindow().getSize().x / 2.f - panelSize.x / 2.f, getGame()->getWindow().getSize().y / 2.f - panelSize.y / 2.f);
		data.size = sf::Vector2f((float)panelSize.x, (float)panelSize.y);
		panel = new leon::ReturnSelection(getGame()->getOverlay().getGui(), data);
	}
	{
		leon::ButtonData sell(params);
		sell.size = sf::Vector2f(100, 25);
		sell.buttonText = "Sell";
		sell.ioComp.name = "sell_button";
		sell.screenCoords = sf::Vector2f(0, 0);

		panel->add(sptr<leon::WidgetBase>(new leon::Button(*panel->getPanelPtr(), sell)));
	}

	return panel;
}
leon::Panel* Overlay::loadMainMenu()
{
	leon::Panel* pMain_menu = nullptr;
	leon::Panel* pButtons = nullptr;
	//main menu panel
	{
		leon::PanelData mainMenuData(params);
		mainMenuData.ioComp.name = "main_menu";
		mainMenuData.backgroundTex = "core/screen_1";
		mainMenuData.screenCoords = sf::Vector2f(0, 0);
		mainMenuData.size = sf::Vector2f(1920, 1080);
		pMain_menu = new leon::Panel(getGame()->getOverlay().getGui(), mainMenuData);
	}
	//banner
	{
		leon::PictureData pictureData(params);
		pictureData.texName = "core/main_menu_logo";
		pictureData.screenCoords = sf::Vector2f(20, 20);
		pictureData.size = sf::Vector2f(847, 104);
		leon::WidgetBase* picture = new leon::Picture(*pMain_menu->getPanelPtr(), pictureData);
		pMain_menu->add(sptr<leon::WidgetBase>(picture));
	}

	//buttons panel
	{
		leon::PanelData mainMenuData(params);
		mainMenuData.ioComp.name = "main_menu_buttons";
		mainMenuData.backgroundColor = sf::Color::Transparent;
		mainMenuData.screenCoords = sf::Vector2f(0, 0);
		mainMenuData.size = sf::Vector2f(1920, 1080);
		mainMenuData.movesWithMouse = true;
		pButtons = new leon::Panel(*pMain_menu->getPanelPtr(), mainMenuData);
		pMain_menu->add(sptr<leon::WidgetBase>(pButtons));
	}

	//resume button
	{
		leon::ButtonData resumeButtonData(params);
		resumeButtonData.size = sf::Vector2f(150, 50);
		resumeButtonData.buttonText = "Resume";
		resumeButtonData.screenCoords = sf::Vector2f(20, 300);
		resumeButtonData.startHidden = true;
		resumeButtonData.ioComp.name = "resume_button";

		Courier resumeMessage1;
		resumeMessage1.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		resumeMessage1.message.reset("overlay", "toggleMenu", voidPacket, 0, false);

		resumeButtonData.ioComp.courierList.push_back(resumeMessage1);
		leon::WidgetBase* pResume = new leon::Button(*pButtons->getPanelPtr(), resumeButtonData);
		pButtons->add(sptr<leon::WidgetBase>(pResume));
	}
	//multiplayer
	{
		leon::ButtonData multiplayer(params);
		multiplayer.size = sf::Vector2f(275, 50);
		multiplayer.buttonText = "Multiplayer";
		multiplayer.ioComp.name = "multiplayer_button";
		multiplayer.screenCoords = sf::Vector2f(20, 400);

		Courier hideMultiplayerButton;
		//show connection screen
		hideMultiplayerButton.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		hideMultiplayerButton.message.reset("multiplayer_connect_lobby", "toggleHidden", voidPacket, 0, false);
		multiplayer.ioComp.courierList.push_back(hideMultiplayerButton);

		//hide multiplayer button
		hideMultiplayerButton.message.reset("multiplayer_button", "toggleHidden", voidPacket, 0, false);
		multiplayer.ioComp.courierList.push_back(hideMultiplayerButton);

		pButtons->add(sptr<leon::WidgetBase>(new leon::Button(*pButtons->getPanelPtr(), multiplayer)));
	}
	//exit game
	{
		Courier buttonMessage;
		buttonMessage.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		buttonMessage.message.reset("game", "exit", voidPacket, 0, false);

		leon::ButtonData exitButtonData(params);
		exitButtonData.size = sf::Vector2f(100, 50);
		exitButtonData.buttonText = "Exit";
		exitButtonData.screenCoords = sf::Vector2f(20, 600);
		exitButtonData.ioComp.courierList.push_back(buttonMessage);

		pButtons->add(sptr<leon::WidgetBase>(new leon::Button(*pButtons->getPanelPtr(), exitButtonData)));
	}

	return pMain_menu;
}
leon::Panel* Overlay::loadConnectionHub(leon::Panel* pMain_menu)
{
	leon::Panel* pMultMenu = nullptr;

	/**MULTIPLAYER**/
	{
		sf::Vector2f multPanelSize = sf::Vector2f(640, 480);
		leon::PanelData multiplayerConnect(params);
		multiplayerConnect.ioComp.name = "multiplayer_connect_lobby";
		multiplayerConnect.startHidden = true;
		multiplayerConnect.backgroundColor = sf::Color(50, 50, 50, 128);
		multiplayerConnect.screenCoords = sf::Vector2f(getGame()->getWindow().getSize().x / 2 - multPanelSize.x / 2, getGame()->getWindow().getSize().y / 2 - multPanelSize.y / 2);
		multiplayerConnect.size = sf::Vector2f(multPanelSize.x, multPanelSize.y);
		multiplayerConnect.movesWithMouse = true;
		multiplayerConnect.percievedDistance = 30.f;
		pMultMenu = new leon::Panel(*pMain_menu->getPanelPtr(), multiplayerConnect);
	}
	/**JOIN**/
	{
		leon::ButtonData joinButt(params);
		joinButt.ioComp.name = "join_button";
		joinButt.size = sf::Vector2f(100, 50);
		joinButt.buttonText = "Join";
		joinButt.screenCoords = sf::Vector2f(5, 5);
		Courier joinMess;
		joinMess.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		joinMess.message.reset("networkboss", "join", voidPacket, 0, false);
		joinButt.ioComp.courierList.push_back(joinMess);
		pMultMenu->add(sptr<leon::WidgetBase>(new leon::Button(*pMultMenu->getPanelPtr(), joinButt)));
	}
	/**HOST**/
	{
		leon::ButtonData hostButt(params);
		hostButt.size = sf::Vector2f(100, 50);
		hostButt.buttonText = "Host";
		hostButt.screenCoords = sf::Vector2f(110, 5);
		Courier hostMess;
		hostMess.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		hostMess.message.reset("networkboss", "host", voidPacket, 0, false);
		hostButt.ioComp.courierList.push_back(hostMess);
		pMultMenu->add(sptr<leon::WidgetBase>(new leon::Button(*pMultMenu->getPanelPtr(), hostButt)));
	}
	/**PORT**/
	{
		leon::EditBoxData port(params);
		port.size = sf::Vector2f(125, 50);
		port.startingText = "5050";
		port.screenCoords = sf::Vector2f(215, 5);
		Courier portMess;
		portMess.condition.reset(EventType::TextChanged, 0, 'd', true);
		portMess.message.reset("networkboss", "joinPort", voidPacket, 0, true);
		port.ioComp.courierList.push_back(portMess);
		pMultMenu->add(sptr<leon::WidgetBase>(new leon::EditBox(*pMultMenu->getPanelPtr(), port)));
	}
	/**IP**/
	{
		leon::EditBoxData ipAdd(params);
		ipAdd.ioComp.name = "ipaddress_editbox";
		ipAdd.size = sf::Vector2f(335, 50);
		ipAdd.startingText = "IP Address";
		ipAdd.screenCoords = sf::Vector2f(5, 60);
		Courier ipAddMess;
		ipAddMess.condition.reset(EventType::TextChanged, 0, 'd', true);
		ipAddMess.message.reset("networkboss", "joinIP", voidPacket, 0, true);
		ipAdd.ioComp.courierList.push_back(ipAddMess);
		pMultMenu->add(sptr<leon::WidgetBase>(new leon::EditBox(*pMultMenu->getPanelPtr(), ipAdd)));
	}
	return pMultMenu;
}
leon::Panel* Overlay::loadMultiplayerLobby(leon::Panel* pMain_menu)
{
	leon::Panel* pLobby = nullptr;

	sf::Vector2f lobbyPanelSize = sf::Vector2f(750, 500);

	//lobby panel
	{
		leon::PanelData lobbyPanel(params);
		lobbyPanel.ioComp.name = "lobby";
		lobbyPanel.startHidden = true;
		lobbyPanel.backgroundColor = sf::Color(50, 50, 50, 128);
		lobbyPanel.screenCoords = sf::Vector2f(getGame()->getWindow().getSize().x / 2 - lobbyPanelSize.x / 2, getGame()->getWindow().getSize().y / 2 - lobbyPanelSize.y / 2);
		lobbyPanel.size = sf::Vector2f(lobbyPanelSize.x, lobbyPanelSize.y);
		pLobby = new leon::Panel(*pMain_menu->getPanelPtr(), lobbyPanel);
	}
	// disconnect button
	{
		leon::ButtonData disconnect(params);
		disconnect.ioComp.name = "lobby_disconnect";
		disconnect.size = sf::Vector2f(250, 50);
		disconnect.buttonText = "Disconnect";
		disconnect.screenCoords = sf::Vector2f(lobbyPanelSize.x - (disconnect.size.x + 5), lobbyPanelSize.y - (disconnect.size.y + 5));
		Courier disconnectMess1;
		disconnectMess1.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		disconnectMess1.message.reset("lobby", "toggleHidden", voidPacket, 0, false);
		Courier disconnectMess2;
		disconnectMess2.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		disconnectMess2.message.reset("networkboss", "localOnly", voidPacket, 0, false);

		disconnect.ioComp.courierList.push_back(disconnectMess1);
		disconnect.ioComp.courierList.push_back(disconnectMess2);

		pLobby->add(sptr<leon::WidgetBase>(new leon::Button(*pLobby->getPanelPtr(), disconnect)));
	}
	//add AI button
	{
		leon::ButtonData addAI(params);
		addAI.size = sf::Vector2f(150, 50);
		addAI.buttonText = "AI+";
		addAI.screenCoords = sf::Vector2f(5, lobbyPanelSize.y - (addAI.size.y + 5 + 50));
		Courier aiMessage1;
		aiMessage1.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		aiMessage1.message.reset("networkboss", "addAI", voidPacket, 0, false);

		addAI.ioComp.courierList.push_back(aiMessage1);

		pLobby->add(sptr<leon::WidgetBase>(new leon::Button(*pLobby->getPanelPtr(), addAI)));
	}
	// launch game button
	{
		leon::ButtonData launch(params);
		launch.ioComp.name = "lobby_launch";
		launch.size = sf::Vector2f(150, 50);
		launch.buttonText = "Launch";
		launch.screenCoords = sf::Vector2f(5, lobbyPanelSize.y - (launch.size.y + 5));

		Courier launchGame;
		launchGame.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		launchGame.message.reset("networkboss", "launch", voidPacket, 0, false);

		Courier hideMenu;
		hideMenu.condition.reset(EventType::LeftMouseClicked, 0, 'd', true);
		hideMenu.message.reset("hud_panel", "toggleHidden", voidPacket, 0, false);

		launch.ioComp.courierList.push_back(launchGame);
		launch.ioComp.courierList.push_back(hideMenu);

		pLobby->add(sptr<leon::WidgetBase>(new leon::Button(*pLobby->getPanelPtr(), launch)));
	}
	//chatbox
	{
		leon::ChatboxData chatbox(params);
		chatbox.ioComp.name = "lobby_chatbox";
		chatbox.size = sf::Vector2f(400, 300);
		chatbox.screenCoords = sf::Vector2f(3, 7);

		pLobby->add(sptr<leon::WidgetBase>(new leon::Chatbox(*pLobby->getPanelPtr(), chatbox)));
	}

	return pLobby;
}
void Overlay::toggleMenu(bool show)//display menu, assume gui control, send pause game command
{
	m_menuShowing = show;

	sf::Packet guiMode;
	guiMode << (show);
	sf::Packet hideMenu;
	hideMenu << (!show);
	sf::Packet pause;
	pause << (show);
	sf::Packet hideHUD;
	hideHUD << (show);

	Universe* x = &getGame()->getUniverse();

	if(x->started)
	{

		Message mes1("main_menu", "setHidden", hideMenu, 0, false);
		Message mes2("local_player", "setGuiMode", guiMode, 0, false);
		Message mes3("universe", "setPause", pause, 0, false);
		Message mes4("hud_panel", "setHidden", hideHUD, 0, false);
		Message mes5("resume_button", "setHidden", hideMenu, 0, false);

		parent->getCoreIO().recieve(mes1);
		parent->getCoreIO().recieve(mes2);
		parent->getCoreIO().recieve(mes3);
		parent->getCoreIO().recieve(mes4);
		parent->getCoreIO().recieve(mes5);

	}

}
void Overlay::toggleScoreboard(bool show)
{

}
void Overlay::input(const String rCommand, sf::Packet rData)
{
	if(rCommand == "toggleMenu")
	{
		toggleMenu(!m_menuShowing);
	}
	else if(rCommand == "toggleScoreboard")
	{
		toggleScoreboard(!m_scoreboardShowing);
	}
	else if(rCommand == "setMenu")
	{
		bool show;
		rData >> show;
		toggleMenu(show);
	}
	else
	{
		WARNING;
	}
}



