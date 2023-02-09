#include "pch.h"
#include "Piece.h"

int Piece::GetType()
{
	return m_Type;
}

void Piece::SetType(const int type)
{
	m_Type = type;
}


int Piece::GetRotation()
{
	return m_Rotation;
}

void Piece::SetRotation(const int rotation)
{
	m_Rotation = rotation;
}


void Piece::MovePiece(const int moveDeltaX, const int moveDeltaY)
{
	m_Position.x += moveDeltaX;
	m_Position.y += moveDeltaY;
}

void Piece::SetPosition(const int positionX, const int positionY)
{
	m_Position.x = positionX;
	m_Position.y = positionY;
}

int Piece::GetStyle()
{
	return PIECES[m_Type].style; 
}

Point2f Piece::GetCenterOffset()
{
	return PIECES[m_Type].centerOffset;
}


std::list<Point2> Piece::GetBlocks()
{
	std::list<Point2> blockPositions{};

	for (int y = 0; y < PIECES_BLOCKS_SIDE_COUNT; ++y)
	{
		for (int x = 0; x < PIECES_BLOCKS_SIDE_COUNT; ++x)
		{
			if (PIECES[m_Type].rotations[m_Rotation][PIECES_BLOCKS_SIDE_COUNT - y - 1][x])
			{
				blockPositions.push_front(Point2{ x + m_Position.x,y + m_Position.y });
			}
		}
	}

	return blockPositions;
}
