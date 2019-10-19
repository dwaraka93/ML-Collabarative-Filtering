//
//  main.cpp
//  Testing
//
//  Created by Tuition.in on 10/8/19.
//  Copyright © 2019 Tuition.in. All rights reserved.
//

#include <stdio.h>
#include "iostream"
#include "readinputs.hpp"
#include "collab_filter.hpp"

int main(int argc, const char * argv[]) {
    VMovieUsersdetails vmovietraindata;
    VUsersMoviedetails vusertraindata;
    MapMovieIndex mapMovieIndex;
    MapUserIndex mapUserIndex;
    MapTestData maptestdata;
    float *rating = NULL;
    //float fpredictedrating = 0;
  //  cout << "Reading Train data\n";
    if(!readfile(argv[1], vmovietraindata, vusertraindata,mapMovieIndex, mapUserIndex,&rating))
        return 0;
  //  cout << "Reading complete\n";
    if(!readtestfile(argv[2], maptestdata, mapMovieIndex, mapUserIndex))
        return 0;
    
    mapMovieIndex.clear();
    mapUserIndex.clear();
  //  cout << "preidction start\n";
    predictedrating(maptestdata, vmovietraindata,vusertraindata,rating);

    return 0;
}
