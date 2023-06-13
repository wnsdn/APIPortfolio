#pragma once

class GameEngineObject
{
public:
	GameEngineObject();
	virtual ~GameEngineObject();
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	int GetOrder() const
	{
		return Order;
	}
	void SetOrder(const int _RenderOrder)
	{
		Order = _RenderOrder;
	}

	bool GetOrderChange() const
	{
		return OrderChange;
	}
	void SetOrderChange(const bool _OrderChange)
	{
		OrderChange = _OrderChange;
	}

	void On()
	{
		IsUpdateValue = true;
	}
	void Off()
	{
		IsUpdateValue = false;
	}
	bool IsUpdate() const
	{
		return IsUpdateValue;
	}

	void Death()
	{
		IsDeathValue = true;
		IsUpdateValue = false;
	}
	bool IsDeath() const
	{
		return IsDeathValue;
	}

	float GetLiveTime() const
	{
		return LiveTime;
	}
	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}
	void AddLiveTime(float _Delta)
	{
		LiveTime += _Delta;
	}

protected:
	int Order = 0;
	bool OrderChange = false;
	bool IsUpdateValue = true;
	bool IsDeathValue = false;
	float LiveTime = 0.0f;

	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Render(float _Delta) {}
	virtual void Release() {}
};