#include"Robot_DH.h"
#include<iostream>


RobotDH::RobotDH(std::vector<DHLink> links, std::vector<std::string> offsets){
    

    n_of_links = links.size();
    
    //Ensure that the lists are the same sizes
    if (n_of_links != offsets.size()){
        std::cout << "WARNING: Setup vectors are different lengths";
        
    }

    //Assign all the parameters
    link_list = links;

    offset_config = offsets;
   
   //Update the coupled offsets
    update_link_offsets();

    //Update the position and orientation
    update_pos_orient();
    
}


//Calcualtes the transform matrix from the current links and joint angles
void RobotDH::calc_transform(){
   
    //Reset the transform matrix to the first transform
    trans_mat = link_list.at(0).get_hg();   

    std::cout << trans_mat << "\n";
    
    int n_of_links = link_list.size();

    //Iterate through the links   - start one later
    for (int i = 1; i < n_of_links; i++){
        //std::cout << link_list.at(i).get_hg();
        //std::cout << "\n";

        trans_mat = trans_mat * link_list.at(i).get_hg();

        //std::cout << trans_mat;
        //std::cout << "\n";

    }
}


//Updates the poisiton vector and orient based on the transformation matrix
void RobotDH::update_pos_orient(){
    //Calculate the transform matrix
    calc_transform();

    pos = {trans_mat(0,3), trans_mat(1,3), trans_mat(2,3)};

    orient_mat << trans_mat(0,0), trans_mat(0,1), trans_mat(0,2),
                  trans_mat(1,0), trans_mat(1,1), trans_mat(1,2),
                  trans_mat(2,0), trans_mat(2,1), trans_mat(2,2);

}

//Gets the posstion in XYZ coords
std::vector<float> RobotDH::get_pos(){
    return pos;
}

//Gets the orientation matrix
Matrix3f RobotDH::get_orient(){
    return orient_mat;
}


//Updates the link offsets (primarily for coupled joints)
void RobotDH::update_link_offsets(){        

    coupled_offsets.clear();

    //Check if offsets are coupled with other joints
    for(std::string c : offset_config){


        if (c.substr(0, 1).compare("p") == 0){    

            coupled_offsets.push_back(link_list.at(std::stoi(c.substr(1, c.size()))).get_theta());          

        }
        else if (c.substr(0, 1).compare("m") == 0){
            coupled_offsets.push_back(-link_list.at(std::stoi(c.substr(1, c.size()))).get_theta());
            
        }
        else{
            coupled_offsets.push_back(0);
        }

    }


    //For the coupled joint offsets - update the link offsets
    for(int i = 0; i < n_of_links; i++){

        link_list[i].set_off(coupled_offsets[i]);

    }
}

//Adds a new link to the robot
void RobotDH::add_link(DHLink new_link, std::string config){

    link_list.push_back(new_link);

    offset_config.push_back(config);

    //Update the coupled offsets
    update_link_offsets();

    //Update the position and orientation
    update_pos_orient();
}

//Removes a link for a given index
//Be very careful when removing links that are coupled - will produce unexpected behaviour
void RobotDH::remove_link(int link_n){

    link_list.erase(link_list.begin() + link_n);
    offset_config.erase(offset_config.begin() + link_n);

}



