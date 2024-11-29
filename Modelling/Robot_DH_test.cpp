#include"Robot_DH.h"
#include <iostream>




//Helper function to convert from degrees to radians
float degtorad(float deg){

    float rad = (deg*EIGEN_PI)/180;

    return rad;
}


int main(){



    DHLink link_0 = DHLink(240, EIGEN_PI/2, 800, 0, 0);

    DHLink link_1 = DHLink(1050, 0, 0, 0, EIGEN_PI/2);

    DHLink link_2 = DHLink(225, EIGEN_PI/2, 0, 0, 0);

    DHLink link_3 = DHLink(0, -EIGEN_PI/2, 1520, 0, 0);
    
    DHLink link_4 = DHLink(0, EIGEN_PI/2, 0, degtorad(-30), 0);

    DHLink link_5 = DHLink(0, 0, 200, 0, 0);

    std::vector<std::string> offset_config = {"0", "0", "m1", "0", "0", "0"};


    std::vector<DHLink> link_list = {link_0, link_1, link_2, link_3, link_4, link_5};

    RobotDH test = RobotDH(link_list, offset_config);


    for(float coord : test.get_pos()){
        std::cout << coord;
        std::cout << "\n";
    }

    return 1;
}



