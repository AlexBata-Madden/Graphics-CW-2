#include "camera.hpp"
#include <utility>
#include <iostream>

Camera::Camera()
{
	pos = Vec3f{ 0.0f, 5.0f, 10.0f };
	target = Vec3f{ 0.0f, 0.0f, 1.0f };
	up = Vec3f{ 0.0f, 1.0f, 0.0f };
    speed = 10.f;
    movingForward = false;
    movingBack = false;
    movingLeft = false;
    movingRight = false;
    movingUp = false;
    movingDown = false;
    cameraActive = false;
    lastX = 0;
    lastY = 0;
    phi = 0;
    theta = 0;
    mouseSensitivity = 0.01f;
}
Vec3f Camera::GetPostition() {
    return pos;
}

void Camera::SetPostition(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Camera::SetSpeed(float s)
{
    speed = s;
}

void Camera::SetMouseSensitivity(float s)
{
    mouseSensitivity = s;
}

void Camera::MoveForwards(float deltaTime)
{
    Vec3f direction = normalise(target);
    direction.y = 0;
    pos -= (direction * speed * deltaTime);
}

void Camera::MoveBackwards(float deltaTime)
{
    Vec3f direction = normalise(target);
    direction.y = 0;
    pos += (direction * speed * deltaTime);
}

void Camera::MoveLeft(float deltaTime)
{
    Vec3f Left = cross(up, target);
    Left = normalise(Left);
    Left *= speed;
    pos -= Left * deltaTime;
}

void Camera::MoveRight(float deltaTime)
{
    Vec3f Right = cross(target,up);
    Right = normalise(Right);
    Right *= speed;
    pos -= Right * deltaTime;
}

void Camera::MoveUp(float deltaTime)
{
    pos.y += speed * deltaTime;
}

void Camera::MoveDown(float deltaTime)
{
    pos.y -= speed * deltaTime;
}

void Camera::togglemovingForward()
{
    movingForward = !movingForward;
}

void Camera::togglemovingBack()
{
    movingBack = !movingBack;
}

void Camera::togglemovingLeft()
{
    movingLeft = !movingLeft;
}

void Camera::togglemovingRight()
{
    movingRight = !movingRight;
}

void Camera::togglemovingUp()
{
    movingUp = !movingUp;
}

void Camera::togglemovingDown()
{
    movingDown = !movingDown;
}

bool Camera::getCameraActive()
{
    return cameraActive;
}

void Camera::toggleCameraActive()
{
    cameraActive = !cameraActive;
}

void Camera::Update(float deltaTime) {
    if (movingForward)
        MoveForwards(deltaTime);
    else if (movingBack)
        MoveBackwards(deltaTime);
    if (movingLeft)
        MoveLeft(deltaTime);
    else if (movingRight)
        MoveRight(deltaTime);
    if (movingUp)
        MoveUp(deltaTime);
    else if (movingDown)
        MoveDown(deltaTime);
}

void Camera::UpdateOrientation(double aX, double aY)
{

        if (cameraActive)
        {
            auto const dx = float(aX - lastX);
            auto const dy = float(aY - lastY);

            phi += dx * mouseSensitivity;
            theta += dy * mouseSensitivity;

            // Clamp theta to a range of -pi/2 to pi/2
            theta = std::max(-3.1415926f / 2.f, std::min(theta, 3.1415926f / 2.f));

            // Calculate the new target position based on the updated angles
            target = normalise(Vec3f{
                - (std::sin(phi)) * std::cos(theta),
                0,
                std::cos(phi) * std::cos(theta)
            });

        }

        lastX = float(aX);
        lastY = float(aY);        

}

Mat44f Camera::GetMatrix()
{

    Vec3f N = normalise(target);
    
    Vec3f U = normalise(cross(up, N));
    Vec3f V = cross(N, U);



    Mat44f Camera = make_rotation_x(theta)* make_rotation_y(phi)*
        Mat44f{      U.x,	U.y,	U.z,	-pos.x,
                     V.x,	V.y,	V.z,	-pos.y,
                     N.x,	N.y,	N.z,	-pos.z,
                     0.f,	0.f,	0.f,	1.0f };



    return Camera;
}
