#pragma once

#include <iostream>
#include <string>
#include "utils.h"

using namespace utils;

class Sprite
{

public:

	Texture m_Texture{};
	Point2f m_CellSize{};

	void Load(const std::string& fileLocation, int rows = { 1 }, int columns = { 1 })
	{
		rows = std::max(1, rows);
		columns = std::max(1, columns);


		TextureFromFile(fileLocation, m_Texture);
		m_CellSize.x = m_Texture.width / rows;
		m_CellSize.y = m_Texture.height / columns;


		std::cout << "Texture Loaded: " << fileLocation << std::endl;
	}

	~Sprite()
	{
		DeleteTexture(m_Texture);
		std::cout << "Texture Deleted" << std::endl;
	}

	void Draw(const Rectf& drawRect)
	{
		DrawTexture(m_Texture, drawRect);
	}

	void Draw(const Rectf& drawRect, int row, int column = {})
	{
		DrawTexture(m_Texture, drawRect,{ m_CellSize.x * row,m_CellSize.y * (column + 1),m_CellSize.x,m_CellSize.y});
	}

	void Draw(const Point2f& drawPosition, int row, int column = {})
	{
		DrawTexture(m_Texture, drawPosition, { m_CellSize.x * row,m_CellSize.y * (column + 1),m_CellSize.x,m_CellSize.y });
	}

	void Draw(const Point2f& drawPosition)
	{
		DrawTexture(m_Texture, drawPosition);
	}

};

