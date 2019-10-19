//
//  collab_filter.hpp
//  Testing
//
//  Created by Tuition.in on 10/8/19.
//  Copyright © 2019 Tuition.in. All rights reserved.
//

#ifndef collab_filter_hpp
#define collab_filter_hpp

#include <stdio.h>
#include "readinputs.hpp"


typedef map< unsigned int, float> MapWeights;

double findprobability(VMovieUsersdetails &vMovieUserData,VUsersMoviedetails& vUserMovieData,unsigned int user, float *rating, unsigned int movieid, MapWeights &userweights);
void predictedrating(MapTestData &maptestdata,VMovieUsersdetails &vmoviedata,VUsersMoviedetails &vuserdata,float * rating);
double findweights(unsigned int user, unsigned int commonuser,VUsersMoviedetails& vUsersMovieData, float *rating,  int moviescnt);


#endif /* collab_filter_hpp */
