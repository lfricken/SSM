#pragma once

#include "stdafx.hpp"
#include "Clock.hpp"

struct BlueprintableData;
class IOManager;

/// <summary>
/// Core stuff.
/// </summary>
struct BlueprintParams
{
	BlueprintParams(const Core::IClock* _clock, IOManager* _manager)
	{
		clock = _clock;
		manager = _manager;
	}

	/// <summary>
	/// Get time from here.
	/// </summary>
	const Core::IClock* clock;

	/// <summary>
	/// Get time from here.
	/// </summary>
	IOManager* manager;
};

/// <summary>
/// This is a blueprint.
/// </summary>
class Blueprintable
{
public:
	Blueprintable(const BlueprintableData& data, BlueprintParams params);
	virtual ~Blueprintable();

	/// <summary>
	/// Title of the blueprint type.
	/// </summary>
	const String& getTitle() const;

	/// <summary>
	/// Get core access stuff.
	/// </summary>
	const BlueprintParams& getCore() const;

private:
	/// <summary>
	/// Title of the blueprint type.
	/// </summary>
	String m_title;

	/// <summary>
	/// Core stuff.
	/// </summary>
	BlueprintParams m_core;
};

/// <summary>
/// This can load json from a root.
/// </summary>
class ILoadsJson
{
public:
	/// <summary>
	/// Fill this object with data from a json file.
	/// </summary>
	virtual void loadJson(const Json::Value& root) = 0;
};

/// <summary>
/// You can clone this.
/// </summary>
class ICloneable
{
public:
	/// <summary>
	/// Return a new copy of this object.
	/// </summary>
	virtual ICloneable* clone() = 0;
};

/// <summary>
/// The interface for blueprint data.
/// </summary>
struct BlueprintableData : public ILoadsJson, public ICloneable
{
	BlueprintableData()
	{
		title = "BADTITLE";
	}

	/// <summary>
	/// Title of the blueprint type. NOT LOADED FROM JSON.
	/// </summary>
	String title;

	/// <summary>
	/// Fill this object with data from a json file.
	/// </summary>
	virtual void loadJson(const Json::Value& root);

	/// <summary>
	/// Make a copy of this object.
	/// </summary>
	virtual BlueprintableData* clone()
	{
		auto copy = new BlueprintableData();
		*copy = *this;
		return copy;
	}
};

