#pragma once

struct MousePoint
{
int x;
int y;
};

class MouseEvent
{
	public:
		enum EventType
		{
			LPress,
			LRelese,
			RPress,
			RRelese,
			MPress,
			MRelese,
			WheelUp,
			WheelDown,
			Move,
			RAW_MOVE,
			Invalid,
		};

	private:
		EventType type;
		int x;
		int y;
	public:
		MouseEvent();
		MouseEvent(const EventType type, const int x, const int y);
		bool IsValid() const;
		MouseEvent::EventType GetType() const;
		MousePoint GetPos() const;
		int GetPosX() const;
		int GetPosY() const;
};