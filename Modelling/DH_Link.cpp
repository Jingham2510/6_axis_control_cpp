#include"DH_Link.h"
#include<iostream>



int main(){

    DHLink test_link = DHLink(1, EIGEN_PI/2, 1, EIGEN_PI);

    std::cout << test_link.get_hg();

    return 1; 
}