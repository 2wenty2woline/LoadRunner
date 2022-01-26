#include <iostream>
#include "MyRedefinition.h"

MyRedefinition::MyRedefinition()
{

}

MyRedefinition::~MyRedefinition()
{
}

bool MyRedefinition::CheckCollideAnyObject(Object* Object1, Object* Object2)
{
	if ((*&Object1 == nullptr) || (*&Object2 == nullptr))
	{
		return false;
	}
																			//bonusItemsStar
	if (
		(Object1->posX - 16 < Object2->posX + 16) &&
		(Object1->posY + 16 > Object2->posY - 16) &&
		(Object1->posX + 16 > Object2->posX - 16) &&
		(Object1->posY - 16 < Object2->posY + 16)
		)
	{
		return true;
	}

	return false;
}

void MyRedefinition::PreInit(int& width, int& height, bool& fullscreen)
{
	width					= 800;
	height					= 600;
	fullscreen				= false;
}

bool MyRedefinition::Init()
{
																			// controller
	ControllerSprite[0].key			= FRKey::UP;
	ControllerSprite[0].firstSpite	= createSprite("C:/Users/habea/source/repos/LoadRunner/LoadRunner/data/player_left.png");

	ControllerSprite[1].key			= FRKey::DOWN;
	ControllerSprite[1].firstSpite	= createSprite("C:/Users/habea/source/repos/LoadRunner/LoadRunner/data/player_left.png");

	ControllerSprite[2].key			= FRKey::LEFT;
	ControllerSprite[2].firstSpite	= createSprite("C:/Users/habea/source/repos/LoadRunner/LoadRunner/data/player_left.png");

	ControllerSprite[3].key			= FRKey::RIGHT;
	ControllerSprite[3].firstSpite	= createSprite("C:/Users/habea/source/repos/LoadRunner/LoadRunner/data/player_right.png");

																			// player
	player.Sprite					= createSprite("C:/Users/habea/source/repos/LoadRunner/LoadRunner/data/player_left.png");
	player.posX						= 200;
	player.posY						= 546;
	player.currentSide				= FRKey::UP;

																			// Enemy
	enemy.Sprite					= createSprite("C:/Users/habea/source/repos/LoadRunner/LoadRunner/data/player_left.png");
	enemy.posX						= 32;
	enemy.posY						= 546;
	
																			// brick
	brick.posX						= 0;
	brick.posY						= 0;
	brick.Sprite					= createSprite("C:/Users/habea/source/repos/LoadRunner/LoadRunner/data/wall2.png");
	
																			// stairs
	stairs.posX						= 0;
	stairs.posY						= 0;
	stairs.Sprite					= createSprite("C:/Users/habea/source/repos/LoadRunner/LoadRunner/data/stairs.png");
	
	int	h, w;
	getSpriteSize(player.Sprite, h, w);

	AllObjectInScen[0]				= &player;
	AllObjectInScen[1]				= &enemy;

	return true;
}

void MyRedefinition::checksPlayerMoveUP()
{
	int px							= player.posX / 32;
	int py							= (player.posY - player.speedMovement) / 32;

	if (map[py][px] == 3)
	{
		player.posY					-= player.speedMovement;
	}
	else if(map[py + 1][px] == 3)
	{
		player.posY					-= player.speedMovement;
	}
}

void MyRedefinition::checksPlayerMoveDOWN()
{
	int px							= player.posX / 32;
	int py							= (player.posY + player.speedMovement) / 32;
	int corpy						= player.posY / 32;
		
	if (map[py][px] == 3 && map[corpy + 1][px] != 0)
	{
		player.posY += player.speedMovement;
	}
	else if (map[py + 1][px] == 3 && map[py][px] != 3)
	{
		player.posY += player.speedMovement;
	}
}

void MyRedefinition::checksPlayerMoveRIGHT()
{
	int px							= (player.posX + player.speedMovement) / 32;
	int py							= player.posY / 32;

	if (map[py][px] != 0)
	{
		player.posX					+= player.speedMovement;
		std::cout << "px " << px << std::endl;
		std::cout << "py " << py << std::endl;
		std::cout << "Character px " << player.posX << std::endl;
		std::cout << "Character py " << player.posY << std::endl;
	}
}
void MyRedefinition::checksPlayerMoveLEFT()
{
	int px							= (player.posX - player.speedMovement) / 32;
	int py							= player.posY / 32;

	if (map[py][px] != 0)
	{
		player.posX					-= player.speedMovement;

		std::cout << "LEFT" << std::endl;
		std::cout << "Character px " << player.posX << std::endl;
		std::cout << "Character py " << player.posY << std::endl;
	}
}

void MyRedefinition::Close()
{
}

bool MyRedefinition::Tick()
{
	drawTestBackground();
																			// brick
	brick.posX				= 0;
	brick.posY				= 0;
	stairs.posX				= 0;
	stairs.posY				= 0;

	for (int row = 0; row < 19; ++row)										// доступ по строкам
	{
		for (int col = 0; col < 25; ++col)									// доступ к каждому элементу в строке
		{
			if (map[row][col] == 0)
			{
				drawSprite(brick.Sprite, brick.posX, brick.posY);
			}
			else if (map[row][col] == 3)
			{
				drawSprite(stairs.Sprite, stairs.posX, stairs.posY);
			}
			stairs.posX		+= 32;
			brick.posX		+= 32;
																			//std::cout << map[row][col];
																			//std::cout << "\t";
		}
		stairs.posX			= 0;
		brick.posX			= 0;

		stairs.posY			+= 32;
		brick.posY			+= 32;
																			//std::cout << std::endl;
	}
																			//player
	drawSprite(player.Sprite, player.posX, player.posY);
																			// enemy
	drawSprite(enemy.Sprite, enemy.posX, enemy.posY);

	if (CheckCollideAnyObject(AllObjectInScen[0], AllObjectInScen[1]))
	{
		std::cout << "123 ";
		return false;
	}

	/*if (enemy.posX != player.posX)
	{
		int posPE = player.posX - enemy.posX;
		if (posPE <= 0)
		{
			enemy.posX -= enemy.speedMovement;
		}
		else if (posPE >= 0)
		{
			enemy.posX += enemy.speedMovement;
		}
	}
	else if (enemy.posY != player.posY)
	{
		int posPE = player.posY - enemy.posY;
		if (posPE <= 0)
		{
			enemy.posY -= enemy.speedMovement;
		}
		else if (posPE >= 0)
		{
			enemy.posY += enemy.speedMovement;
		}
	}*/
	
	return false;
}

void MyRedefinition::onMouseMove(int x, int y, int xrelative, int yrelative)
{
}

void MyRedefinition::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
}

void MyRedefinition::onKeyPressed(FRKey k)
{
	switch (k)
	{
	case FRKey::RIGHT:
	{
		if (player.Sprite != ControllerSprite[3].firstSpite)
		{
			player.Sprite		= ControllerSprite[3].firstSpite;
		}
		checksPlayerMoveRIGHT();		
		player.currentSide		= k;
		break;
	};
	case FRKey::LEFT:
	{
		if (player.Sprite != ControllerSprite[2].firstSpite)
		{
			player.Sprite		= ControllerSprite[2].firstSpite;
		}
		checksPlayerMoveLEFT();		
		player.currentSide		= k;
		break;
	};
	case FRKey::DOWN:
	{
		if (player.Sprite != ControllerSprite[1].firstSpite)
		{
			player.Sprite			= ControllerSprite[1].firstSpite;
		}
		checksPlayerMoveDOWN();
		player.currentSide		= k;
		break;
	};
	case FRKey::UP:
	{
		if (player.Sprite != ControllerSprite[0].firstSpite)
		{
			player.Sprite		= ControllerSprite[0].firstSpite;
		}
		checksPlayerMoveUP();
		player.currentSide		= k;
		break;
	};
	case FRKey::COUNT:
		break;
	default:
		break;
	}
}

void MyRedefinition::onKeyReleased(FRKey k)
{
}

const char* MyRedefinition::GetTitle()
{
	return "Lode Runner";
}
