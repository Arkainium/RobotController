#include "loiter.h"
#include <cmath>
using namespace PlayerCc;

// odometry
static const double distance  = 0.5; // in meters
static const double theta     = M_PI_2; // in radians

// velocities
static const double xvel = 1.0; // meters/second
static const double avel = 2.0; // radians/second

static bool is_moving(Position2dProxy& pp)
{
	return pp.GetXSpeed() || pp.GetYSpeed() || pp.GetYawSpeed();
}

Loiter::Loiter(PlayerClient& pc)
:Behavior(pc), mPosition2D(&mPlayerClient, 0)
{
	// initial state: STRAIGHT
	mCurrentState = STRAIGHT;
	mInitState = false;
	lastPos = distanceTraveled = 0;
	lastYaw = distanceRotated  = 0;
}

Loiter::~Loiter()
{
	Stop();
}

void Loiter::Restart()
{
	// initial state: STRAIGHT
	mCurrentState = STRAIGHT;
	mInitState = false;
	lastPos = distanceTraveled = 0;
	lastYaw = distanceRotated  = 0;
	mPosition2D.SetSpeed(0, 0);
}

void Loiter::Stop()
{
	mPosition2D.SetSpeed(0, 0);
}

void Loiter::Update()
{
	mIsMobile = is_moving(mPosition2D);
	if (!mInitState && mIsMobile) {
		mPosition2D.SetSpeed(0, 0);
	} else if (!mInitState && !mIsMobile) {
		mInitState = true;
	} else if (mInitState && !mIsMobile) {
		switch (mCurrentState) {
			case STRAIGHT: {
				mPosition2D.SetSpeed(xvel,0);
			} break;
			case TURNING: {
				mPosition2D.SetSpeed(0,avel);
			} break;
			default: break;
		}
	} else if (mInitState && mIsMobile) {
		switch (mCurrentState) {
			case STRAIGHT: {
				// Are we there yet?
				double pos = mPosition2D.GetXPos();
				distanceTraveled += fabs(pos - lastPos);
				lastPos = pos;
				if (distanceTraveled >= distance) {
					distanceTraveled = 0;
					mCurrentState = TURNING;
					mInitState = false;
					mPosition2D.SetSpeed(0,0); // stop
				}
			} break;
			case TURNING: {
				// Are we there yet?
				double yaw = mPosition2D.GetYaw();
				distanceRotated += fabs(yaw - lastYaw);
				lastYaw = yaw;
				if (distanceRotated >= theta) {
					distanceRotated = 0;
					mCurrentState = STRAIGHT;
					mInitState = false;
					mPosition2D.SetSpeed(0,0); // stop
				}
			} break;
			default: break;
		}
	}
}
