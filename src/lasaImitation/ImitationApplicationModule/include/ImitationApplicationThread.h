// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
/* 
 * Copyright (C) 2009 RobotCub Consortium, European Commission FP6 Project IST-004370
 * Author:  Eric Sauser
 * email:   eric.sauser@a3.epfl.ch
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

#ifndef ImitationApplicationTHREAD_H_
#define ImitationApplicationTHREAD_H_

#include <yarp/os/RateThread.h>
#include <yarp/os/Semaphore.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Time.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Vector.h>

using namespace yarp::os;
using namespace yarp::sig;

#include <vector>
#include <string>

using namespace std;

class ImitationApplicationThread: public RateThread
{
private:    
    Semaphore               mMutex;
    int                     mPeriod;
    char                    mBaseName[256];

    enum Mode{
        MODE_BASICCOMMAND = 0,
        MODE_STATEMACHINE
    };
    Mode                    mMode;

    BufferedPort<Vector>    mWiimotePort;

    
    BufferedPort<Bottle>    mVelocityControllerPort;
    BufferedPort<Bottle>    mRobotControllerPort;
    BufferedPort<Bottle>    m3DMouseControllerPort;
    BufferedPort<Bottle>    mTouchpadControllerPort;
    BufferedPort<Bottle>    mGMMRightPort;
    BufferedPort<Bottle>    mGMMLeftPort;
    BufferedPort<Bottle>    mRefTransRightPort;
    BufferedPort<Bottle>    mRefTransLeftPort;

    enum PortId{
        PID_Velocity = 0,
        PID_Robot,
        PID_3DMouse,
        PID_Touchpad,
        PID_GMMRight,
        PID_GMMLeft,
        PID_RefTransRight,
        PID_RefTransLeft,
        PID_SIZE
    };
    
    enum SrcPortId{
        SPID_Touchpad = 0,
        SPID_3DMouse,
        SPID_TouchpadSignal,
        SPID_3DMouseSignal,
        SPID_RWristRef,
        SPID_LWristRef,
        SPID_RArmCartPos,
        SPID_LArmCartPos,
        SPID_EyeCartPos,
        SPID_GMMRightCartPos,
        SPID_GMMLeftCartPos,
        SPID_MotionSensorsArm,
        SPID_MotionSensorsHand,
        SPID_Vision0,
        SPID_Vision1,
        SPID_SIZE
    };
    enum DstPortId{
        DPID_Touchpad = 0,
        DPID_3DMouse,
        DPID_RArmDesCartVel,
        DPID_LArmDesCartVel,
        DPID_RArmDesCartPos,
        DPID_LArmDesCartPos,
        DPID_RWristDesCartVel,
        DPID_LWristDesCartVel,
        DPID_RArmHandPos,
        DPID_LArmHandPos,
        DPID_RArmJointsPos,
        DPID_LArmJointsPos,
        DPID_EyeInEyeDesCartPos,
        DPID_EyeDesCartPos,
        DPID_GMMRightSignal,
        DPID_GMMLeftSignal,
        DPID_SIZE
    };
    char                    mSrcPortName[SPID_SIZE][256];
    char                    mDstPortName[DPID_SIZE][256];
    char                    mSrcCtrlPortName[PID_SIZE][256];
    char                    mDstCtrlPortName[PID_SIZE][256];
    
    vector<int>             mCommandsType;
    vector<SrcPortId>       mConnexionsSrcPort;
    vector<DstPortId>       mConnexionsDstPort;
    vector<string>          mCommands;
    vector<PortId>          mCommandsPort;
    
    BufferedPort<Bottle>   *mPorts[PID_SIZE];
    
    enum State{
        IAS_NONE=0,
        IAS_IDLE,
        IAS_INIT,
        IAS_RUN,
        IAS_PAUSE,
        IAS_DELAY,
        IAS_STOP,
        
        IAS_DEVTPAD,
        IAS_DEVTPAD_INIT,
        IAS_DEVTPAD_RUN,
        IAS_DEVTPAD_STOP,
        
        IAS_DEV3DM,
        IAS_DEV3DM_INIT,
        IAS_DEV3DM_RUN,
        IAS_DEV3DM_STOP,
        
        IAS_DEVSENSORS,
        IAS_DEVSENSORS_INIT,
        IAS_DEVSENSORS_READY,
        IAS_DEVSENSORS_RUN,
        IAS_DEVSENSORS_STOP,
        
        IAS_DEMO,
        IAS_DEMO_INIT,
        IAS_DEMO_RUN,
        IAS_DEMO_STOP,
        
        IAS_SIZE
    };
    
    State                   mState;
    State                   mPrevState;
    State                   mNextState;
    State                   mDelayedState;
    double                  mDelayedStateTime;
    
    char                    mStateName[IAS_SIZE][256];
    
    enum StateSignal{
        SSIG_NONE = 0,
        SSIG_OK,
        SSIG_ABORT,
        SSIG_NEXT,
        SSIG_PREV
    };
    StateSignal             mStateSignal;
    
    enum BasicCommand{
        BC_NONE = 0,
        BC_INIT,
        BC_CLEAR,
        BC_RUN,
        BC_STOP,
        BC_REST,
        BC_3DMOUSE_TO_NONE,
        BC_3DMOUSE_TO_RIGHTARM_NONE,
        BC_3DMOUSE_TO_RIGHTARM,
        BC_3DMOUSE_TO_LEFTARM_NONE,
        BC_3DMOUSE_TO_LEFTARM,
        BC_TOUCHPAD_TO_RIGHTARM_NONE,
        BC_TOUCHPAD_TO_RIGHTARM,
        BC_SENSORS_TO_LEFTARM,
        BC_SENSORS_TO_LEFTARM_NONE,
        BC_TRACK_NONE,
        BC_TRACK_RIGHTARM,
        BC_TRACK_LEFTARM,
        BC_HAND_OPENRIGHT,
        BC_HAND_OPENLEFT,
        BC_HAND_CLOSERIGHT,
        BC_HAND_CLOSELEFT,
        BC_EYETARGET_TO_NONE,
        BC_EYETARGET_TO_RIGHTARM,
        BC_EYETARGET_TO_LEFTARM,
        BC_GMM_LEARN_RIGHT,
        BC_GMM_LEARN_LEFT,
        BC_GMM_LEARN_CORR_RIGHT,
        BC_GMM_LEARN_CORR_LEFT,
        BC_GMM_REC_RIGHT_START,
        BC_GMM_REC_LEFT_START,
        BC_GMM_RIGHT_STOP,
        BC_GMM_LEFT_STOP,
        BC_GMM_REPRO_RIGHT_START,
        BC_GMM_REPRO_LEFT_START,
        BC_GMM_LOAD_RIGHT,
        BC_GMM_LOAD_LEFT,
        BC_GMM_CORR_RIGHT_START,
        BC_GMM_CORR_LEFT_START,
        BC_GMM_DEMONAME_RIGHT,
        BC_GMM_CORRNAME_RIGHT,
        BC_GMM_DEMONAME_LEFT,
        BC_GMM_CORRNAME_LEFT
    };
    BasicCommand            mBasicCommand;
    string                  mBasicCommandParams;

    void                    ProcessBasicCommand();
    void                    ProcessStateMachine();
    
    bool                    ProcessWiimote(bool flush = false);
    Vector                  mWiimoteEvent;
    
public:
    ImitationApplicationThread(int period, const char* baseName);
    virtual ~ImitationApplicationThread();

            void    ConnectToNetwork(bool bConnect);

            void    ClearCommands();
            void    SendCommands();
            void    AddCommand(PortId port, const char *cmd, const char *params=NULL);
            void    AddConnexion(SrcPortId src, DstPortId dst, bool bUnique = true);
            void    RemConnexion(SrcPortId src, DstPortId dst);
            void    RemAllSrcConnexions(DstPortId dst);
            void    RemAllDstConnexions(SrcPortId src);
            void    RemAllConnexions();
    
            void    PrepareToStop();

            void    InitStateMachine();
            void    SendBasicCommand(const char* cmd);
            void    DelayNextState(State nextState, double delay);
    
            int     respond(const Bottle& command, Bottle& reply);
            int     respondToBasicCommand(const Bottle& command, Bottle& reply);
            int     respondToStateMachine(const Bottle& command, Bottle& reply);

    virtual void    run();
    virtual bool    threadInit();
    virtual void    threadRelease();
};

#endif

