#ifndef _LOITER_H
#define _LOITER_H

#include "behavior.h"

class Loiter : public Behavior
{
	public:
		Loiter(PlayerCc::PlayerClient& pc);
		~Loiter();

		virtual void Restart();
		virtual void Stop();
		virtual void Update();

	protected:
		// Player client proxies.
		PlayerCc::Position2dProxy mPosition2D;

		// Internal properties.
		enum { STRAIGHT, TURNING } mCurrentState;
		bool mInitState;
		bool mIsMobile;
		double lastPos, distanceTraveled;
		double lastYaw, distanceRotated;
};

#endif
