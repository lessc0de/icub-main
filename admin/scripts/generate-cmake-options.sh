### parameters are 
# $1: hostname (could be also buildtype)
# $2: os type (macos, winxp, lenny, etch, karmic ...)

case $2 in
# no special condition for macos any more
#    macos)
#    CMAKE_OPTIONS="-DCREATE_GUIS:BOOL=FALSE -DCREATE_LIB_MATH:BOOL=TRUE -DENABLE_DASHBOARD_SUBMIT:BOOL=TRUE -DUSE_PORT_AUTHENTICATION:BOOL=TRUE"
#    ;;
    *)
    CMAKE_OPTIONS="-DENABLE_icubmod_cartesiancontrollerclient:BOOL=TRUE \
                        -DENABLE_icubmod_cartesiancontrollerserver:BOOL=TRUE \
                        -DENABLE_icubmod_gazecontrollerclient:BOOL=TRUE \
                        -DENABLE_icubmod_icubarmcalibrator:BOOL=TRUE \
                        -DENABLE_icubmod_icubarmcalibratorj8:BOOL=TRUE \
                        -DENABLE_icubmod_icubhandcalibrator:BOOL=TRUE \
                        -DENABLE_icubmod_icublegscalibrator:BOOL=TRUE \
                        -DENABLE_icubmod_logpolarclient:BOOL=TRUE \
                        -DENABLE_icubmod_logpolargrabber:BOOL=TRUE \
                        -DENABLE_icubmod_skinprototype:BOOL=TRUE \
                        -DENABLE_icubmod_fakecan:BOOL=TRUE \
                        -DENABLE_icubmod_canmotioncontrol:BOOL=FALSE\
                        -DENABLE_icubmod_debugInterfaceClient:BOOL=TRUE\
                        -DICUB_DASHBOARD_SUBMIT:BOOL=TRUE"
esac

case $3 in
    experimental)
        CMAKE_OPTIONS="$CMAKE_OPTIONS -DICUB_ICUBINTERFACE_EXPERIMENTAL:BOOL=TRUE"
esac
