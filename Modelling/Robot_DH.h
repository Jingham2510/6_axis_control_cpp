#include"DH_Link.h"
#include<math.h>
#include<list>

#ifndef Robot_DH
#define Robot_DH

//Class that defines the DH representation of a robot
class RobotDH{
    public:

        RobotDH(list<DHLink> link_list);
};



#endif