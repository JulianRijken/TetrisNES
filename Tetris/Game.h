#pragma once

#include "Piece.h"
#include "Sprite.h"
#include "AudioManager.h"
#include "Counter.h"

using namespace utils;


struct Block
{
	bool active{};
	int style{ 0 };
};


const int GRID_SIZE_X{ 10 };
const int GRID_SIZE_Y{ 20 };

const int WINDOW_SCALE{ 4 };
const int PIXEL_WIDTH{ 256 };
const int PIXEL_HEIGHT{ 224 };
const int NUMBER_SIZE{ 7 * WINDOW_SCALE };

const int PLAY_FIELD_OFFSET_X{ 96 * WINDOW_SCALE };
const int PLAY_FIELD_OFFSET_Y{ 25 * WINDOW_SCALE };

const float CELL_SIZE{ 8 * WINDOW_SCALE };

const int MAX_LINES{ 4 };
const int SCORE_PER_ROW[MAX_LINES]{ 40, 100, 300, 1200 };

const int MAX_LEVELS_SPRITES{ 10 };
const int MAX_LEVELS{ 30 };

const int FRAMES_FOR_LOCK{ 40 };
const int FRAMES_FOR_ROW_REMOVE{ 5 };

const int GAME_FRAMES_PER_CELL_PER_LEVEL[MAX_LEVELS]
{
	48, // 0
	43,	// 1
	38,	// 2
	33,	// 3
	28,	// 4
	23,	// 5
	18,	// 6
	13,	// 7
	8 ,	// 8
	9 ,	// 9

	5,	// 10
	5,	// 11
	5,	// 12

	4,	// 13
	4,	// 14
	4,	// 15

	3,	// 16
	3,	// 17
	3,	// 18

	2,	// 19
	2,	// 20
	2,	// 21
	2,	// 22
	2,	// 23
	2,	// 24
	2,	// 25
	2,	// 26
	2,	// 27
	2,	// 28

	1,	// 29
};


std::string g_WindowTitle{ "Tetris for the NES by Julian Rijken" };
float g_WindowWidth{ PIXEL_WIDTH * WINDOW_SCALE };
float g_WindowHeight{ PIXEL_HEIGHT * WINDOW_SCALE };

int g_CurrentLevel{ 0 };
int g_MoveFrameCounter{ 0 };
int g_LockFrameCounter{ 0 };

bool g_HardDrop{ false };

Counter g_Counter{};

std::list<int> g_RowsToRemove{};


int g_Statistics[AMOUNT_OF_TYPES_OF_PIECES]{};
int g_Score{};
int g_LinesCleared{};

Sprite g_BackgroundSprite{};
Sprite g_BlocksSpriteSheet{};
Sprite g_NumbersSpriteSheet{};

AudioManager g_AudioManager{};


Block g_PlacedGrid[GRID_SIZE_X][GRID_SIZE_Y];
Piece g_ActivePiece{};
Piece g_NexPiece{};



void DrawNumber(const int size, const int number, Point2f position);

void HandleDrawGrid();

void HandleDrawPieces();

void HandlePieceMovement();

bool TryRemovingRows();

void MovePieceSideways(const int moveDelta);

bool CanMove(const int moveDeltaX, const int moveDeltaY);

void RotatePiece(RotationDirection direction);

void OnGameOver();

void PlaceActivePiece();

void CheckFullRows();

void RestartGame();

void SpawnNextPiece();

void ClearRows(std::list<int> rowsToRemove);

void UpdateCurrentLevel();

std::list<Point2> GetPlacedBlocks();

void MovePieceDown();

#pragma region gameFunctions

void Start();
void Draw();
void Update(float elapsedSec);
void End();

#pragma endregion gameFunctions

#pragma region inputHandling

void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);

#pragma endregion inputHandling
