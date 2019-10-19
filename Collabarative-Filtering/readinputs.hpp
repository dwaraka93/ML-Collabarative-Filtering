//
//  readinputs.hpp
//  collabarative_filtering
//
//  Created by Tuition.in on 10/8/19.
//  Copyright © 2019 Tuition.in. All rights reserved.
//

#ifndef readinputs_hpp
#define readinputs_hpp

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct userdata
{
    map<unsigned int,float> moviedetails;
};


typedef vector<vector<unsigned int>> VMovieUsersdetails;
typedef vector<vector<unsigned int>> VUsersMoviedetails;
typedef map<unsigned int, unsigned int> MapMovieIndex;
typedef map<unsigned int, unsigned int> MapUserIndex;


//typedef map<unsigned int, vector<unsigned int>> MapMovieUser;
typedef map<unsigned int, userdata> MapUserData;
typedef map<unsigned int, vector<pair<unsigned int, float>>> MapTestData;

bool readfile(string infilename, VMovieUsersdetails &outvecmovieuser, VUsersMoviedetails&  outvecusermovie,MapMovieIndex &outmapmovie, MapUserIndex &outmapuser, float **rating);

bool readtestfile(string filename, MapTestData &maptest, MapMovieIndex &outmapmovie, MapUserIndex &outmapuser);

#endif /* readinputs_hpp */
