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

#include "plexe/scenarios/BrakingScenario.h"

using namespace veins;

namespace plexe {

Define_Module(BrakingScenario);

void BrakingScenario::initialize(int stage)
{

    BaseScenario::initialize(stage);

    if (stage == 0)
        // get pointer to application
        appl = FindModule<BaseApp*>::findSubModule(getParentModule());

    if (stage == 2) {
        // get acceleration
        acceleration = par("acceleration").doubleValue();
        // get braking deceleration
        brakingDeceleration = par("brakingDeceleration").doubleValue();
        // average speed
        leaderSpeed = par("leaderSpeed").doubleValue() / 3.6;
        // number of lanes
        nLanes = par("nLanes").intValue();
	// stop accelerating time
        stopAccelerating = SimTime(par("stopAccelerating").doubleValue());
        // start accelerating time
        startAccelerating = SimTime(par("startAccelerating").doubleValue());
        // start braking time
        startBraking = SimTime(par("startBraking").doubleValue());
	

        if (positionHelper->getId() == 0) {
            // setup braking message, only if i'm part of the first leaders
	    startAccelerationMsg = new cMessage("startAccelerationMsg");
	    scheduleAt(startAccelerating, startAccelerationMsg);

	    stopAccelerationMsg = new cMessage("stopAccelerationMsg");
	    scheduleAt(stopAccelerating, stopAccelerationMsg);           
            
            startBrakingMsg = new cMessage("startBrakingMsg");
	    scheduleAt(startBraking, startBrakingMsg);
            //if (simTime() > startBraking) {
            //    startBraking = simTime();
            //    scheduleAt(simTime(), startBrakingMsg);
            //}
            //else {
            //    scheduleAt(startBraking, startBrakingMsg);
            //}
            // set base cruising speed
            plexeTraciVehicle->setCruiseControlDesiredSpeed(leaderSpeed);
        }
        //else {
            // let the follower set a higher desired speed to stay connected
            // to the leader when it is accelerating
            //plexeTraciVehicle->setCruiseControlDesiredSpeed(leaderSpeed + 10);
        //}
    }
}

BrakingScenario::~BrakingScenario()
{
    cancelAndDelete(startAccelerationMsg);
    startAccelerationMsg = nullptr;
    cancelAndDelete(stopAccelerationMsg);
    stopAccelerationMsg = nullptr;
    cancelAndDelete(startBrakingMsg);
    startBrakingMsg = nullptr;
}

void BrakingScenario::handleSelfMsg(cMessage* msg)
{
    BaseScenario::handleSelfMsg(msg);
    if (msg == startAccelerationMsg) plexeTraciVehicle->setFixedAcceleration(1, acceleration);
    if (msg == startBrakingMsg) plexeTraciVehicle->setFixedAcceleration(1, -brakingDeceleration);
    if (msg == stopAccelerationMsg) plexeTraciVehicle->setFixedAcceleration(1, 0);
}

} // namespace plexe
