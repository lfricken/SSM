#include "Blueprintable.hpp"
#include "JSON.hpp"

void BlueprintableData::loadJson(const Json::Value& root)
{

}
Blueprintable::Blueprintable(const BlueprintableData& data, BlueprintParams params)
{
	m_title = data.title;
	m_core = params;
}
Blueprintable::~Blueprintable()
{

}
const String& Blueprintable::getTitle() const
{
	return m_title;
}
const BlueprintParams& Blueprintable::getCore() const
{
	return m_core;
}
