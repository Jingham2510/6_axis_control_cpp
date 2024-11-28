
#include<Eigen\Dense>
#include<math.h>

using Eigen::Matrix4d;

#ifndef DH_LINK
#define DH_LINK

//Link that forms part of a DH representation of a robot
class DHLink{
    
    public:
        //Constructor
        DHLink (float,float,float,float);
        //Update the joint angle
        void set_theta(float);
        //Get the current homogeneous transformation matrix
        Matrix4d get_hg();

    private:
        //Only accessed once on creation (then just theta)
        float a, alpha, d, theta;
        //The homogeneous transformation matrix
        Matrix4d hg_mat;
        //Should only be called when parameters change
        void update_hg();
};


DHLink::DHLink(float link_length, float link_twist, float link_offset, float joint_angle){

    a = link_length;
    alpha = link_twist;
    d = link_offset;
    theta = joint_angle;

    update_hg();

}

//Compute the homogeneous transofmration matrix as according to M.Spong
void DHLink::update_hg(){

    hg_mat << cos(theta), -sin(theta)*cos(alpha), sin(theta)*sin(alpha),  a*cos(theta),
              sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha),  a*sin(theta),
                  0     ,         sin(alpha)   ,          cos(alpha)   ,        d     ,
                  0     ,             0        ,              0        ,        1     ;
        
    return;
}

//Update the joint angle of the link
void DHLink::set_theta(float new_theta){
    theta = new_theta;
    update_hg();
    return;
}


//Provide the homogeneous matrix
Matrix4d DHLink::get_hg(){
    return hg_mat;
}


#endif