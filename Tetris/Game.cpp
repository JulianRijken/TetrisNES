#include "pch.h"
#include "Game.h"

#include <iostream>
#include "AudioManager.h"
#include "Jul.h"
#include "Counter.h"

void Start()
{
	ShowWindow(GetConsoleWindow(), SW_MINIMIZE);

	g_BackgroundSprite.Load("Assets/BackGround.png");
	g_BlocksSpriteSheet.Load("Assets/Blocks.png", 5, 10);
	g_NumbersSpriteSheet.Load("Assets/Numbers.png", 10);

	g_AudioManager.AddSound("Assets/Audio/SFX 8.mp3","place");
	g_AudioManager.AddSound("Assets/Audio/SFX 4.mp3","sideMove");
	g_AudioManager.AddSound("Assets/Audio/SFX 6.mp3","rotate");
	g_AudioManager.AddSound("Assets/Audio/SFX 11.mp3","lineClear");
	g_AudioManager.AddSound("Assets/Audio/SFX 10.mp3","tetris");
	g_AudioManager.AddSound("Assets/Audio/SFX 7.mp3","levelClear");
	g_AudioManager.AddSound("Assets/Audio/SFX 14.mp3","gameOver");

	SpawnNextPiece();
}


void Draw()
{
	ClearBackground(0, 0, 0);

	HandleDrawGrid();
	HandleDrawPieces();


	g_BackgroundSprite.Draw({ 0,0,g_WindowWidth,g_WindowHeight });

	//for (int i = 0; i < AMOUNT_OF_TYPES_OF_PIECES; ++i)
	//{
	//	DrawNumber(3, g_Statistics[i], { 48,float(33 + 16 * i) });
	//}

	//// Draw Score
	//DrawNumber(6, g_Score, { 192,161 });

	//// Draw level
	//DrawNumber(2, g_CurrentLevel, { 208,57 });

	//// Draw levels Cleared
	//DrawNumber(3, g_LinesCleared, { 152,201 });


	//// TEMP
	////Point2f offset{ 767,355 };
	//Point2f offset{ 832,416 };

	//offset.x -= g_NexPiece.GetCenterOffset().x * CELL_SIZE;
	//offset.y -= g_NexPiece.GetCenterOffset().y * CELL_SIZE;

	//for (const Point2 blockPosition : g_NexPiece.GetBlocks())
	//{
	//	Rectf fillRect
	//	{
	//		blockPosition.x * CELL_SIZE + offset.x,
	//		blockPosition.y * CELL_SIZE + offset.y,
	//		CELL_SIZE,
	//		CELL_SIZE,
	//	};

	//	g_BlocksSpriteSheet.Draw(fillRect, g_NexPiece.GetStyle(), ClampLoop(g_CurrentLevel, 0, MAX_LEVELS_SPRITES - 1));
	//}
}

void Update(float elapsedSec)
{
	if(TryRemovingRows())
		return;

	HandlePieceMovement();

	frameCount++;
	std::cout << 1.0f / elapsedSec << std::endl;
}

void End()
{
}


void HandleDrawGrid()
{
	for (int x = 0; x < GRID_SIZE_X; ++x)
	{
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			Rectf fillRect
			{
				x * CELL_SIZE + PLAY_FIELD_OFFSET_X,
				y * CELL_SIZE + PLAY_FIELD_OFFSET_Y,
				CELL_SIZE,
				CELL_SIZE,
			};

			Block block{ g_PlacedGrid[x][y] };
			if (block.active)
			{
				g_BlocksSpriteSheet.Draw(fillRect,block.style, ClampLoop(g_CurrentLevel, 0, MAX_LEVELS_SPRITES - 1));
			}
		}
	}
}

void HandleDrawPieces()
{
	// Draw Preview
	for (int y = 0; y < GRID_SIZE_Y + PIECES_BLOCKS_SIDE_COUNT; ++y)
	{
		if (!CanMove(0, -(y + 1)))
		{
			for (const Point2 blockPosition : g_ActivePiece.GetBlocks())
			{
				Rectf fillRect
				{
					blockPosition.x * CELL_SIZE + PLAY_FIELD_OFFSET_X,
					(blockPosition.y - y) * CELL_SIZE + PLAY_FIELD_OFFSET_Y,
					CELL_SIZE,
					CELL_SIZE,
				};

				g_BlocksSpriteSheet.Draw(fillRect, 4, ClampLoop(g_CurrentLevel, 0, MAX_LEVELS_SPRITES - 1));
			}
			break;
		}
	}

	// Draw piece
	for (const Point2 blockPosition : g_ActivePiece.GetBlocks())
	{
		Rectf fillRect
		{
			blockPosition.x * CELL_SIZE + PLAY_FIELD_OFFSET_X,
			blockPosition.y * CELL_SIZE + PLAY_FIELD_OFFSET_Y,
			CELL_SIZE,
			CELL_SIZE,
		};

		g_BlocksSpriteSheet.Draw(fillRect,g_ActivePiece.GetStyle(), ClampLoop(g_CurrentLevel, 0, MAX_LEVELS_SPRITES - 1));
	}


	// Draw locking piece
	for (const Point2 blockPosition : g_ActivePiece.GetBlocks())
	{
		Rectf fillRect
		{
			blockPosition.x * CELL_SIZE + PLAY_FIELD_OFFSET_X,
			blockPosition.y * CELL_SIZE + PLAY_FIELD_OFFSET_Y,
			CELL_SIZE,
			CELL_SIZE,
		};

		float lockPercent{ float(g_LockFrameCounter) / FRAMES_FOR_LOCK };


		SetColor(0, 0, 0, SmoothEndLerp(0.0f, 0.75f, lockPercent));
		FillRect(fillRect);
		//g_BlocksSpriteSheet.Draw(fillRect, 3, ClampLoop(g_CurrentLevel, 0, MAX_LEVELS_SPRITES - 1));
	}
}

void HandlePieceMovement()
{
	g_MoveFrameCounter++;
	if (g_MoveFrameCounter > GAME_FRAMES_PER_CELL_PER_LEVEL[Clamp(g_CurrentLevel, 0, MAX_LEVELS)] || g_HardDrop)
	{
		g_MoveFrameCounter = 0;

		MovePieceDown();
	}

	if (CanMove(0, -1))
	{
		g_LockFrameCounter = 0;
	}
	else
	{
		g_LockFrameCounter++;
		if (g_LockFrameCounter > FRAMES_FOR_LOCK || g_HardDrop)
		{
			PlaceActivePiece();
		}
	}
}

void MovePieceDown()
{
	if (CanMove(0, -1))
		g_ActivePiece.MovePiece(0, -1);
}


bool TryRemovingRows()
{
	if (g_RowsToRemove.size() > 0)
	{
		if (g_Counter.CheckCounter("frameDelay", FRAMES_FOR_ROW_REMOVE, true))
			return true;

		if (g_Counter.CheckCounter("colCounter", 5))
		{
			int col{ g_Counter.GetCounterIndex("colCounter") };

			// Remove rows
			for (int row : g_RowsToRemove)
			{
		
					g_PlacedGrid[4 - col][row].active = false;
					g_PlacedGrid[5 + col][row].active = false;
				
			}
		}
		else
		{
			g_Counter.ResetCounter("colCounter");

			// Move down rows above
			for (int row : g_RowsToRemove)
			{
				for (int y = row; y < GRID_SIZE_Y - 1; ++y)
				{
					for (int x = 0; x < GRID_SIZE_X; ++x)
					{
						g_PlacedGrid[x][y] = g_PlacedGrid[x][y + 1];
					}
				}
			}

			g_RowsToRemove.clear();

			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}


void MovePieceSideways(const int moveDelta)
{
	if (CanMove(moveDelta, 0))
	{
		g_ActivePiece.MovePiece(moveDelta, 0);

		g_AudioManager.PlaySound("sideMove");

		g_LockFrameCounter = 0;
	}
}

bool CanMove(const int moveDeltaX, const int moveDeltaY)
{
	for (Point2 blockPosition : g_ActivePiece.GetBlocks())
	{
		const Point2 blockTargetPosition{ blockPosition.x + moveDeltaX, blockPosition.y + moveDeltaY };

		if (blockTargetPosition.x < 0 || blockTargetPosition.x >= GRID_SIZE_X)
			return false;

		if (blockTargetPosition.y < 0)
			return false;

		for (Point2 placedBlock : GetPlacedBlocks())
		{
			// Check if block is inside of placed block
			if (blockTargetPosition.x == placedBlock.x && blockTargetPosition.y == placedBlock.y)
			{
				return false;
			}
		}
	}

	return true;
}

void RotatePiece(RotationDirection direction)
{
	const int fromR{ g_ActivePiece.GetRotation() };
	const int toR{ ClampLoop(g_ActivePiece.GetRotation() + int(direction),0,PIECE_ROTATION_COUNT - 1) };

	g_AudioManager.PlaySound("rotate");
	g_LockFrameCounter = 0;
	g_ActivePiece.SetRotation(toR);

	int checkSet{};
	int checkType{ g_ActivePiece.GetType() == 0 ? 1 : 0};
	if (checkType == 0) // J L T S Z Piece Sets 
	{
			 if (fromR == 0 && toR == 1 || fromR == 2 && toR == 1)	checkSet = 0;
		else if (fromR == 1 && toR == 0 || fromR == 1 && toR == 2)	checkSet = 1;
		else if (fromR == 2 && toR == 3 || fromR == 0 && toR == 3)	checkSet = 2;
		else if (fromR == 3 && toR == 2 || fromR == 3 && toR == 0)	checkSet = 3;
	}
	else // I Piece Sets
	{
			 if (fromR == 0 && toR == 1 || fromR == 3 && toR == 2)	checkSet = 0;
		else if (fromR == 1 && toR == 0 || fromR == 2 && toR == 3)	checkSet = 1;
		else if (fromR == 1 && toR == 2 || fromR == 0 && toR == 3)	checkSet = 2;
		else if (fromR == 2 && toR == 1 || fromR == 3 && toR == 0)	checkSet = 3;
	}

	for (Point2 kick : KICK_CHECKS[checkType][checkSet])
	{
		if (CanMove(kick.x, kick.y))
		{
			g_ActivePiece.MovePiece(kick.x, kick.y);
			return;
		}
	}

	// Reset if no rotation was possible
	g_ActivePiece.SetRotation(fromR);
}

void OnGameOver()
{
	g_AudioManager.PlaySound("gameOver");

	RestartGame();
}

void PlaceActivePiece()
{
	for (Point2 blockPosition : g_ActivePiece.GetBlocks())
	{
		if(blockPosition.y >= GRID_SIZE_Y)
		{
			OnGameOver();
			return;
		}

		Block& gridBlock{ g_PlacedGrid[blockPosition.x][blockPosition.y] };

		gridBlock.style = PIECES[g_ActivePiece.GetType()].style;
		gridBlock.active = true;
	}

	g_HardDrop = false;
	g_AudioManager.PlaySound("place");
	g_Statistics[g_ActivePiece.GetType()]++;
	SpawnNextPiece();
	CheckFullRows();
}

void CheckFullRows()
{
	// Find rows
	std::list<int> rowsToRemove{};
	for (int y = 0; y < GRID_SIZE_Y; ++y)
	{
		int blocksInRow{};
		for (int x = 0; x < GRID_SIZE_X; ++x)
		{
			if (g_PlacedGrid[x][y].active)
				blocksInRow++;
		}

		if (blocksInRow == GRID_SIZE_X)
			rowsToRemove.push_front(y);
	}

	if(rowsToRemove.size() > 0)
		ClearRows(rowsToRemove);
}

void RestartGame()
{
	for (int y = 0; y < GRID_SIZE_Y; ++y)
	{
		for (int x = 0; x < GRID_SIZE_X; ++x)
		{
			g_PlacedGrid[x][y].active = false;
		}
	}

	g_Score = 0;

	for (int& statistic : g_Statistics)
		statistic = 0;

	g_LinesCleared = 0;

	g_CurrentLevel = 0;

	SpawnNextPiece();
}

void SpawnNextPiece()
{
	// Set to next Piece
	g_ActivePiece.SetType(g_NexPiece.GetType());


	// Calculate Nex Piece
	do
	{
		g_NexPiece.SetType(rand() % AMOUNT_OF_TYPES_OF_PIECES);
	}
	while (g_ActivePiece.GetType() == g_NexPiece.GetType());


	g_ActivePiece.SetRotation(2);
	g_ActivePiece.SetPosition(GRID_SIZE_X / 2 - PIECES_BLOCKS_SIDE_COUNT / 2, GRID_SIZE_Y);
}

void ClearRows(std::list<int> rowsToRemove)
{
	int rowCount{ int(rowsToRemove.size()) };

	g_LinesCleared += rowCount;

	g_Score += SCORE_PER_ROW[rowCount - 1];
	g_AudioManager.PlaySound(rowCount >= 4 ? "tetris" : "lineClear");

	UpdateCurrentLevel();

	g_RowsToRemove = rowsToRemove;
}

void UpdateCurrentLevel()
{
	int newLevel{ g_LinesCleared / 10 };

	if(newLevel > g_CurrentLevel)
	{
		g_AudioManager.PlaySound("levelClear");
		g_CurrentLevel = newLevel;
	}
}

void DrawNumber(const int size, const int number, Point2f position)
{
	for (int i = 0; i < size; ++i)
	{
		g_NumbersSpriteSheet.Draw
		(
			{
				position.x * WINDOW_SCALE + (size - 1 - i) * (NUMBER_SIZE + WINDOW_SCALE),
				position.y* WINDOW_SCALE,
				NUMBER_SIZE,
				NUMBER_SIZE
			},
			int(number / pow(10,i))% 10
		);
	}
}



std::list<Point2> GetPlacedBlocks()
{
	std::list<Point2> placedBlocks{};
	for (int y = 0; y < GRID_SIZE_Y; ++y)
	{
		for (int x = 0; x < GRID_SIZE_X; ++x)
		{
			if (g_PlacedGrid[x][y].active)
				placedBlocks.push_front(Point2{ x,y });
		}
	}

	return placedBlocks;
}



#pragma region inputHandling

void OnKeyDownEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_q:
	case SDLK_LEFT:
		RotatePiece(RotationDirection::left);
		break;
	case SDLK_e:
	case SDLK_RIGHT:
		RotatePiece(RotationDirection::right);
		break;
	case SDLK_d:
		MovePieceSideways(1);
		break;
	case SDLK_a:
		MovePieceSideways(-1);
		break;
	case SDLK_s:
		g_HardDrop = true;
		break;
	case SDLK_ESCAPE:
		RestartGame();
		break;
	}
}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_s:
		g_HardDrop = false;
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}

#pragma endregion inputHandling
