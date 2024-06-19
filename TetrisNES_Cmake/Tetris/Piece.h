#pragma once
#include <list>

#include "Sprite.h"


const int PIECE_ROTATION_COUNT			{ 4 };
const int PIECES_BLOCKS_SIDE_COUNT	{ 4 };

const int AMOUNT_OF_TYPES_OF_PIECES	{ 7 };

const int KICK_CHECK_TYPES			{ 2 };
const int KICK_CHECK_SETS			{ 4 };
const int KICK_CHECK_TESTS			{ 5 };

enum class RotationDirection
{
	left = -1,
	right = 1
};

struct PieceSettings
{
	int style;
	Point2f centerOffset; // Only used for centering piece in the preview
	bool rotations[PIECE_ROTATION_COUNT][PIECES_BLOCKS_SIDE_COUNT][PIECES_BLOCKS_SIDE_COUNT]{};
};

const PieceSettings PIECES[AMOUNT_OF_TYPES_OF_PIECES]
{
	PieceSettings // I
	{
		0,
		{2.0f,1.5f},
		{
			{
				{0,0,0,0},
				{1,1,1,1},
				{0,0,0,0},
				{0,0,0,0},},
			{
				{0,0,1,0},
				{0,0,1,0},
				{0,0,1,0},
				{0,0,1,0},
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,1},
				{0,0,0,0},
			},
			{
				{0,1,0,0},
				{0,1,0,0},
				{0,1,0,0},
				{0,1,0,0},
			}
		}
	},
	PieceSettings // J
	{
		2,
		{1.5f,1.0f},
		{
			{
				{0,0,0,0},
				{1,0,0,0},
				{1,1,1,0},
				{0,0,0,0},
			},
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,0,0},
				{0,1,0,0},
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,0},
				{0,0,1,0},
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,1,0,0},
				{1,1,0,0},
			}
		}
	},
	PieceSettings // L
	{
		1,
		{1.5f,1.0f},
		{
			{
				{0,0,0,0},
				{0,0,1,0},
				{1,1,1,0},
				{0,0,0,0},
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,1,0,0},
				{0,1,1,0},
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,0},
				{1,0,0,0},
			},
			{
				{0,0,0,0},
				{1,1,0,0},
				{0,1,0,0},
				{0,1,0,0},
			}
		},
	},
	PieceSettings // O
	{
		0,
		{2.0f,2.0f},
		{
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0},
			},
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0},
			},
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0},
			},
			{
				{0,0,0,0},
				{0,1,1,0},
				{0,1,1,0},
				{0,0,0,0},
			}
		}
	},
	PieceSettings // S
	{
		2,
		{1.5f,1.0f},
		{
			{
				{0,0,0,0},
				{0,1,1,0},
				{1,1,0,0},
				{0,0,0,0},
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,1,1,0},
				{0,0,1,0},
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{0,1,1,0},
				{1,1,0,0},
			},
			{
				{0,0,0,0},
				{1,0,0,0},
				{1,1,0,0},
				{0,1,0,0},
			}
		}
	},
	PieceSettings // T
	{
		0,
		{1.5f,1.0f},
		{
			{
				{0,0,0,0},
				{0,1,0,0},
				{1,1,1,0},
				{0,0,0,0},
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{0,1,1,0},
				{0,1,0,0},
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,0},
				{0,1,0,0},
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{1,1,0,0},
				{0,1,0,0},
			}
		},
	},
	PieceSettings // Z
	{
		1,
		{1.5f,1.0f},
		{
			{
				{0,0,0,0},
				{1,1,0,0},
				{0,1,1,0},
				{0,0,0,0},
			},
			{
				{0,0,0,0},
				{0,0,1,0},
				{0,1,1,0},
				{0,1,0,0},
			},
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,0,0},
				{0,1,1,0},
			},
			{
				{0,0,0,0},
				{0,1,0,0},
				{1,1,0,0},
				{1,0,0,0},
			}
		},
	},
};

const Point2 KICK_CHECKS[KICK_CHECK_TYPES][KICK_CHECK_SETS][KICK_CHECK_TESTS]
{
	{ // Checks for J L T S Z
		{{  0 ,  0 },{ -1 ,  0 },{ -1 ,  1 },{  0 , -2 },{ -1 , -2 },},
		{{  0 ,  0 },{  1 ,  0 },{  1 , -1 },{  0 ,  2 },{  1 ,  2 },},
		{{  0 ,  0 },{  1 ,  0 },{  1 ,  1 },{  0 , -2 },{  1 , -2 },},
		{{  0 ,  0 },{ -1 ,  0 },{ -1 , -1 },{  0 ,  2 },{ -1 ,  2 },},
	},
	{ // Checks for I
		{{  0 ,  0 },{ -2 ,  0 },{  1 ,  0 },{ -2 , -1 },{  1 ,  2 },},
		{{  0 ,  0 },{  2 ,  0 },{ -1 ,  0 },{  2 ,  1 },{ -1 , -2 },},
		{{  0 ,  0 },{ -1 ,  0 },{  2 ,  0 },{ -1 ,  2 },{  2 , -1 },},
		{{  0 ,  0 },{  1 ,  0 },{ -2 ,  0 },{  1 , -2 },{ -2 ,  1 },},
	},
};



class Piece
{
public:

	Piece() :
		m_Type{0},
		m_Rotation{2},
		m_Position{0,0}
	{}


private:

	int m_Type;
	int m_Rotation;
	Point2 m_Position;


public:

	int GetType();
	void SetType(const int type);

	int GetRotation();
	void SetRotation(const int rotation);

	void MovePiece(const int moveDeltaX, const int moveDeltaY);

	void SetPosition(const int positionX, const int positionY);

	int GetStyle();
	Point2f GetCenterOffset();

	std::list<Point2> GetBlocks();

	void Draw(const Sprite& sprite, const int positionX, const int positionY);
};
