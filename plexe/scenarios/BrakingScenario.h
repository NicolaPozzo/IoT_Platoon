//
// Copyright (C) 2012-2021 Michele Segata <segata@ccs-labs.org>
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef BRAKINGSCENARIO_H_
#define BRAKINGSCENARIO_H_

#include "plexe/scenarios/BaseScenario.h"
#include "plexe/apps/BaseApp.h"

namespace plexe {

class BrakingScenario : public BaseScenario {

public:
    virtual void initialize(int stage);

protected:
    // leader average speed
    double leaderSpeed;
    // acceleration intensity in m/s/s
    double acceleration;
    // braking intensity in m/s/s
    double brakingDeceleration;
    // number of lanes in the scenario
    int nLanes;
    // message used to tell the car to start accelerating
    cMessage* startAccelerationMsg;
    // message used to tell the car to start braking
    cMessage* startBrakingMsg;
    // message used to tell the car to start braking
    cMessage* stopAccelerationMsg;
    // start accellerating time
    SimTime stopAccelerating;
    // start accellerating time
    SimTime startAccelerating;
    // start braking time
    SimTime startBraking;
    // application layer, used to stop the simulation
    BaseApp* appl;

public:
    BrakingScenario()
    {
        leaderSpeed = 0;
        acceleration = 0;
        brakingDeceleration = 0;
        nLanes = 0;
        startAccelerationMsg = nullptr;
        startBrakingMsg = nullptr;
	stopAccelerationMsg = nullptr;
        stopAccelerating = SimTime(0);
        startBraking = SimTime(0);
        startAccelerating = SimTime(0);
        appl = 0;
    }
    virtual ~BrakingScenario();

protected:
    virtual void handleSelfMsg(cMessage* msg);
};

} // namespace plexe

#endif
