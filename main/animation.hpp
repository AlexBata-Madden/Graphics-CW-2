#pragma once
class animation
{

public:

	animation();
	bool GetPaused();
	float GetSpeed();
	void ChangeSpeed(float s);
	void togglePause();

private:

	bool paused;
	float speed;

};

