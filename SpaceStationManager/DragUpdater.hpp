#pragma once

#include "stdafx.hpp"
#include "NonCopyable.hpp"

namespace leon
{
	class DragComponent;

	/// <summary>
	/// Has update called to send mouse coordinates to the drag components.
	/// </summary>
	class DragUpdater : Core::INonCopyable
	{
	public:
		DragUpdater();
		~DragUpdater();

		/// <summary>
		/// Given the mouse position as screen coordinates, any DragComponents::isDragging == true objects should get moved to that position.
		/// </summary>
		void update(const sf::Vector2f& rPos);

		/// <summary>
		/// Each component registers itself here.
		/// </summary>
		void give(leon::DragComponent* pComp);

		/// <summary>
		/// Remove an object from the listener.
		/// </summary>
		void freeThis(leon::DragComponent* pCompToDelete);

	private:

		/// <summary>
		/// List of components to notify of a mouse move event.
		/// </summary>
		List<leon::DragComponent*> m_components;
	};
}
