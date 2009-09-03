// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#include "graspDetector.h"

graspDetector::graspDetector(int n, fingerDetector **fingDet, int rate): RateThread(rate)
{
    nFingers = n;
    fd = fingDet;
    s = new double[nFingers];
}

graspDetector::~graspDetector()
{    
    delete[] s;
}

bool graspDetector::threadInit()
{
    return 1;
}

void graspDetector::run()
{
    for(int i=0; i < nFingers; i++)
        s[i] =  (double) fd[i]->status;
    
    bool print = false;
    for(int i=0; i < nFingers; i++)
        print = print || (s[i]!=0.0);
            
    if (print)
        {
            fprintf(stderr, "Following fingers are grasping: ");
            
            for(int i=0; i < nFingers; i++)    
                if (s[i]!=0.0)
                    fprintf(stderr, "finger%d[%.2f]", i, s[i]);
            
            fprintf(stderr, "\n");
        }
}

void graspDetector::stop()
{
 
}
