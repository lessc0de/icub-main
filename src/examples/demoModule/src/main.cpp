// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* 
 * Copyright (C) 2009 RobotCub Consortium, European Commission FP6 Project IST-004370
 * Authors: David Vernon, Lorenzo Natale
 * email:   $YOUR_EMAIL
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

/**
 * @file main.cpp
 * @brief main code for your module. This shows up in the list of files.
 */

#include "iCub/demoModule.h" 

using namespace yarp::os;
using namespace yarp::sig;


int main(int argc, char * argv[]) {
   /* initialize yarp network */ 
   Network yarp;
   /* create your module */
   demoModule module; 

   /* prepare and configure the resource finder */
   ResourceFinder rf;
   rf.setVerbose(true);
   rf.setDefaultConfigFile("demo.ini"); //overridden by --from parameter
   rf.setDefaultContext("demo");        //overridden by --context parameter
   rf.configure(argc, argv);
 
   /* run the module: runModule() calls configure first and, if successful, it then runs */
   module.runModule(rf);

   return 0;
}

