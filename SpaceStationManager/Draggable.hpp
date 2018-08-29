#pragma once

#include "Button.hpp"
#include "Picture.hpp"

namespace leon
{
	class DragComponent;
	class DraggableSurface;

	/// \brief Data to initialize Draggable.
	struct DraggableData : public ButtonData
	{
		DraggableData(BlueprintParams params) :
			ButtonData(params),
			icon(params),
			parentPtr(nullptr),
			myPanelOffset(0, 0)
		{
			this->configFile = "TGUI/widgets/Transparency.conf";
			buttonText = "";
			size = sf::Vector2f(64, 64);
			icon.texName = "menu/default_icon";
			icon.size = sf::Vector2f(64, 64);
		}

		String metaData;

		DraggableSurface* parentPtr;

		sf::Vector2f myPanelOffset;//position of our panel so we know how to place ourselves
		PictureData icon;
	};

	/// \brief Something that can be dragged around the screen.
	///
	/// Obtains mouse coordinates from DragComponent.
	class Draggable : public Button
	{
	public:
		Draggable(tgui::Gui& gui, const DraggableData& rData);
		Draggable(tgui::Container& container, const DraggableData& rData);
		virtual ~Draggable();

		/// <summary>
		/// Arbitrary data this draggable holds.
		/// </summary>
		const String& getMetaData() const;
		
		/// <summary>
		/// Checks whether the DraggableSurface already has a Draggable at that position before setting position.
		/// </summary>
		bool trySetGridPosition(const sf::Vector2i& rGridPos);

		/// <summary>
		/// Given the mouse position in screen coordinates, any DragComponents::isDragging == true objects get moved.
		/// </summary>
		void setPosition(const sf::Vector2f& rPos);

	protected:
		virtual bool callbackHook2(const tgui::Callback& callback);

		/// <summary>
		/// We were dropped from being dragged.
		/// </summary>
		void dropped();

	private:
		/// <summary>
		/// Bit of data this draggable holds.
		/// </summary>
		String m_metaData;

		/// <summary>
		/// Called by the draggable component when we are getting dragged around.
		/// </summary>
		void f_update(const sf::Vector2f& rPos);
		void f_initialize(const DraggableData& rData);

		/// <summary>
		/// Gets mouse coordinates for us.
		/// </summary>
		sptr<DragComponent> m_spDrag;

		/// <summary>
		/// If we want to set this objects position in the panel, given a window coordinate (mouse position),
		/// we need to be able to subtract out the panels position.
		/// </summary>
		sf::Vector2f m_parentPanelOffset;

		/// <summary>
		/// Image to be displayed for this draggable.
		/// </summary>
		sptr<Picture> m_spPic;

		/// <summary>
		/// Used to check that the draggable wont overlap with another on the grid being dragged on.
		/// </summary>
		DraggableSurface* m_pParent;
	};
}
