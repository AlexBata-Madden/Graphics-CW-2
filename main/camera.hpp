#pragma once

#include "../vmlib/vec4.hpp"
#include "../vmlib/mat44.hpp"

class Camera
{
public:

	Camera();
	Vec3f GetPostition();

	void SetPostition(float x, float y, float z);

	void SetSpeed(float s);

	void SetMouseSensitivity(float s);

	void MoveForwards(float deltaTime);

	void MoveBackwards(float deltaTime);

	void MoveLeft(float deltaTime);

	void MoveRight(float deltaTime);

	void MoveUp(float deltaTime);

	void MoveDown(float deltaTime);

	void togglemovingForward();

	void togglemovingBack();

	void togglemovingLeft();

	void togglemovingRight();

	void togglemovingUp();
	
	void togglemovingDown();

	bool getCameraActive();

	void toggleCameraActive();

	void Update(float deltaTime);

	void UpdateOrientation(double aX, double aY);

	Mat44f GetMatrix();

private:

	bool cameraActive;
	bool movingForward;
	bool movingBack;
	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;

	Vec3f pos;
	Vec3f target;
	Vec3f up;

	float lastX;
	float lastY;
	float speed;
	float phi;
	float theta;
	float mouseSensitivity;

};
