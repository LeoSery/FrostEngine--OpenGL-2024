#include "Core/Serial/XmlParser.h"
#include "Core/Serial/Save.h"
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include <iostream>

namespace frost::core
{
	bool XmlParser::Parse(const char* filePath)
	{
		if (!filePath)
		{
			return false;
		}

		rapidxml::file<> xmlFile(filePath);
		if (xmlFile.size() == 0)
		{
			return false;
		}
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		return ParseRootNode(doc);
	}

	void XmlParser::SetParser()
	{
		frost::core::XmlParser parser;

		if (parser.Parse("../FrostEngine/Ressources/Save.xml"))
		{
			std::cout << "xml file loaded" << std::endl;
		}
		else
		{
			std::cout << "cannot open the xml file" << std::endl;
		}
	}

	bool XmlParser::ParseRootNode(rapidxml::xml_document<>& xmlDoc)
	{
		rapidxml::xml_node<>* node = xmlDoc.first_node("root");
		if (!node)
		{
			return false;
		}
		return ParsePlayerNode(node);
	}

	bool XmlParser::ParsePlayerNode(rapidxml::xml_node<>* xmlNode)
	{
		rapidxml::xml_node<>* EntityNode = xmlNode->first_node("Entity");
		if (!EntityNode)
		{
			return false;
		}

		rapidxml::xml_node<>* PlayerNode = EntityNode->first_node("Player");
		if (!PlayerNode)
		{
			return false;
		}

		rapidxml::xml_node<>* PositionNode = PlayerNode->first_node("Position");
		if (!PositionNode)
		{
			return false;
		}

		rapidxml::xml_node<>* RotationNode = PositionNode->next_sibling("Rotation");
		if (!RotationNode)
		{
			std::cout << "n0";
			return false;
		}

		rapidxml::xml_node<>* LifePointNode = RotationNode->next_sibling("LifePoint");
		if (!LifePointNode)
		{
			std::cout << "n0";
			return false;
		}

		rapidxml::xml_node<>* TexturePathNode = RotationNode->next_sibling("TexturePath");
		if (!TexturePathNode)
		{
			std::cout << "n088";
			return false;
		}

		rapidxml::xml_node<>* InnerNodeTP = TexturePathNode->first_node("Value");
		std::string valueTP(InnerNodeTP->value(), InnerNodeTP->value_size());
		Save s;
		s.ImagePath = valueTP.c_str();
		if (!InnerNodeTP)
		{
			return false;
		}

		rapidxml::xml_node<>* InnerNodeLP = LifePointNode->first_node("Value");
		std::string valueLP(InnerNodeLP->value(), InnerNodeLP->value_size());

		s.LifePoint = atoi(valueLP.c_str());
		if (!InnerNodeLP)
		{
			return false;
		}

		rapidxml::xml_node<>* InnerNodeR = RotationNode->first_node("Value");
		std::string valueR(InnerNodeR->value(), InnerNodeR->value_size());

		s.Rotation = atoi(valueR.c_str());
		if (!InnerNodeR)
		{
			return false;
		}
		
		rapidxml::xml_node<>* InnerNodePx = PositionNode->first_node("XValue");
		std::string valuePx(InnerNodePx->value(), InnerNodePx->value_size());
		s.Pos.x = atoi(valuePx.c_str());
		if (!InnerNodePx)
		{
			return false;
		}

		rapidxml::xml_node<>* InnerNodePy = InnerNodePx->next_sibling("YValue");
		std::string valuePy(InnerNodePy->value(), InnerNodePy->value_size());
		s.Pos.y = atoi(valuePy.c_str());
		if (!InnerNodePy)
		{
			return false;
		}
		return true;
	}
}
