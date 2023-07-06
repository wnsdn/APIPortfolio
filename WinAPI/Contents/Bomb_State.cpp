#include "Bomb.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Tile.h"

void Bomb::StateUpdate(float _Delta)
{
	if (State == "Move")
	{
		MoveUpdate(_Delta);
	}
	else if (State == "Fly")
	{
		FlyUpdate(_Delta);
	}
}

void Bomb::MoveUpdate(float _Delta)
{
	MoveSpeed = 1300.0f;
	if (Dir == "Left")
	{
		Pos.X -= MoveSpeed * _Delta;
	}
	else if (Dir == "Right")
	{
		Pos.X += MoveSpeed * _Delta;
	}
	else if (Dir == "Up")
	{
		Pos.Y -= MoveSpeed * _Delta;
	}
	else if (Dir == "Down")
	{
		Pos.Y += MoveSpeed * _Delta;
	}

	Index = PosToIndex(Pos);
	MoveDist += MoveSpeed * _Delta;

	if (MoveDist >= TileSize.X)
	{
		State = "";
		Pos = IndexToPos(Index);
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr->GetIndex() == Index)
			{
				dynamic_cast<Tile*>(Ptr)->Full();
			}
		}
		LeftMove = 0.0f;
		MoveDist = 0.0f;

		if (Dir == "Left")
		{
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr->GetIndex() == Index + int2::Left &&
					dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
				{
					State = "Move";
					for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
					{
						if (Ptr->GetIndex() == Index)
						{
							dynamic_cast<Tile*>(Ptr)->Empty();
						}
					}
				}
			}

			for (auto MonPtr : Level->FindActor(UpdateOrder::Monster))
			{
				if (MonPtr->GetIndex() == Index + int2::Left)
				{
					State = "";
					for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
					{
						if (Ptr->GetIndex() == Index)
						{
							dynamic_cast<Tile*>(Ptr)->Full();
						}
					}
				}
			}
		}
		else if (Dir == "Right")
		{
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr->GetIndex() == Index + int2::Right &&
					dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
				{
					State = "Move";
					for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
					{
						if (Ptr->GetIndex() == Index)
						{
							dynamic_cast<Tile*>(Ptr)->Empty();
						}
					}
				}
			}

			for (auto MonPtr : Level->FindActor(UpdateOrder::Monster))
			{
				if (MonPtr->GetIndex() == Index + int2::Right)
				{
					State = "";
					for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
					{
						if (Ptr->GetIndex() == Index)
						{
							dynamic_cast<Tile*>(Ptr)->Full();
						}
					}
				}
			}
		}
		else if (Dir == "Up")
		{
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr->GetIndex() == Index + int2::Up &&
					dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
				{
					State = "Move";
					for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
					{
						if (Ptr->GetIndex() == Index)
						{
							dynamic_cast<Tile*>(Ptr)->Empty();
						}
					}
				}
			}

			for (auto MonPtr : Level->FindActor(UpdateOrder::Monster))
			{
				if (MonPtr->GetIndex() == Index + int2::Up)
				{
					State = "";
					for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
					{
						if (Ptr->GetIndex() == Index)
						{
							dynamic_cast<Tile*>(Ptr)->Full();
						}
					}
				}
			}
		}
		else if (Dir == "Down")
		{
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr->GetIndex() == Index + int2::Down &&
					dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
				{
					State = "Move";
					for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
					{
						if (Ptr->GetIndex() == Index)
						{
							dynamic_cast<Tile*>(Ptr)->Empty();
						}
					}
				}
			}

			for (auto MonPtr : Level->FindActor(UpdateOrder::Monster))
			{
				if (MonPtr->GetIndex() == Index + int2::Down)
				{
					State = "";
					for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
					{
						if (Ptr->GetIndex() == Index)
						{
							dynamic_cast<Tile*>(Ptr)->Full();
						}
					}
				}
			}
		}
	}
}

void Bomb::FlyUpdate(float _Delta)
{
	MoveSpeed = 400.0f;
	bool Check = true;

	FindRenderer("Bubble.bmp")->AddPos({ 0, RendererMoveDir * RendererMoveSpeed * _Delta });
	RendererMoveDist += RendererMoveSpeed * _Delta;
	if (RendererMoveDist >= RendererMaxDist)
	{
		RendererMoveDir *= -1.0f;
		RendererMoveDist -= RendererMaxDist;
		FindRenderer("Bubble.bmp")->AddPos({ 0, RendererMoveDir * RendererMoveDist });
	}

	if (Dir == "Left")
	{
		Pos.X -= MoveSpeed * _Delta;

		if (Pos.X <= MapLeft)
		{
			Pos.X = MapRight;
		}
	}
	else if (Dir == "Right")
	{
		Pos.X += MoveSpeed * _Delta;

		if (Pos.X >= MapRight)
		{
			Pos.X = MapLeft;
		}
	}
	else if (Dir == "Up")
	{
		Pos.Y -= MoveSpeed * _Delta;

		if (Pos.Y <= MapTop)
		{
			Pos.Y = MapBottom;
		}
	}
	else if (Dir == "Down")
	{
		Pos.Y += MoveSpeed * _Delta;

		if (Pos.Y >= MapBottom)
		{
			Pos.Y = MapTop;
		}
	}

	if (Pos.X < MapLeft || Pos.X > MapRight ||
		Pos.Y < MapTop || Pos.Y > MapBottom)
	{
		Check = false;
	}

	if (Check)
	{
		Index = PosToIndex(Pos);
		MoveDist += MoveSpeed * _Delta;
		if (MoveDist >= TileSize.X)
		{
			Pos = IndexToPos(Index);
			++MoveIdx;
			LiveTime = 0.0f;
			MoveDist = 0.0f;

			if (MoveIdx >= 10)
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
					{
						State = "";
						FindRenderer("Bubble.bmp")->SetPos({ 0, 0 });
						dynamic_cast<Tile*>(Ptr)->Full();
						MoveIdx = 0;
						Index = PosToIndex(Pos);
					}
				}
			}
		}
	}
}
