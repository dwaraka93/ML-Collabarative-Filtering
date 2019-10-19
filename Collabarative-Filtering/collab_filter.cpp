//
//  collab_filter.cpp
//  Testing
//
//  Created by Tuition.in on 10/8/19.
//  Copyright © 2019 Tuition.in. All rights reserved.
//

#include "collab_filter.hpp"
#include <math.h>

double findweights(unsigned int user, unsigned int commonuser,VUsersMoviedetails& vUsersMovieData, float *rating,  int moviescnt)
{
    double numerator = 0;
    double denominator[2] = {0,0};
    float rate = 0;
    map<unsigned int, float>::iterator itrrating;
    for(int i=0; i< vUsersMovieData[commonuser].size(); i++)
    {
        rate = *(rating + user*(moviescnt + 1) + vUsersMovieData[commonuser][i]);
        if(rate != 0)
        {
            float ratecommon = *(rating + commonuser*(moviescnt + 1) + vUsersMovieData[commonuser][i]);
            float rateavg = *(rating + user*(moviescnt + 1) + moviescnt);
            float ratecommonavg = *(rating + commonuser*(moviescnt + 1) + moviescnt);
            double num1 = (rate - rateavg);
            double num2 = (ratecommon - ratecommonavg);
            numerator += num1 * num2;
            denominator[0] += num1 * num1;
            denominator[1] += num2 * num2;
        }
    }
    if(denominator[0] ==0 || denominator[1] == 0)
        return 0;
    return numerator > 0 ? numerator/(sqrt(denominator[0] * denominator[0])) : 0;
}

double findprobability(VMovieUsersdetails &vMovieUserData,VUsersMoviedetails& vUserMovieData ,unsigned int user, float *rating, unsigned int movieid,MapWeights &userweights)
{
    
    MapWeights::iterator itruserweights;
    double weights = 0;
    double probability = 0;

    for(int i=0; i< vMovieUserData[movieid].size(); i++)
    {
            double weigt = 0;
        /*unsigned int smallusr = user;
        unsigned int bigusr = vMovieUserData[movieid][i];
            if(user > vMovieUserData[movieid][i])
            {
                smallusr = vMovieUserData[movieid][i];
                bigusr = user;
            }*/
                
            if((itruserweights = userweights.find(vMovieUserData[movieid][i])) != userweights.end())
            {
                weigt = itruserweights->second;
            }
            else{
                weigt = findweights(user, vMovieUserData[movieid][i],vUserMovieData,rating, (int)vMovieUserData.size());
                userweights[vMovieUserData[movieid][i]] = weigt;
            }
            float ratecommon = *(rating + vMovieUserData[movieid][i]*(vMovieUserData.size() + 1) + movieid);
            float ratecommonavg = *(rating + vMovieUserData[movieid][i]*(vMovieUserData.size() + 1) + vMovieUserData.size());
            probability += weigt*(ratecommon - ratecommonavg);
            weights += fabs(weigt);
    }
    probability *= (1.0/(weights == 0 ? 1:weights));
    probability += *(rating + user*(vMovieUserData.size() + 1) + vMovieUserData.size());
     
        return probability;
}

void predictedrating(MapTestData &mapTestData,VMovieUsersdetails &vMovieUserData,VUsersMoviedetails &vUserMovieData,float * rating)
{

    MapWeights userweights;
    double MAerror = 0;
    double RMSerror = 0;
    double error = 0;
    long long size = 0;
    int i = 0;
    for (auto itr = mapTestData.begin(); itr != mapTestData.end(); itr++)
    {
          for(int i=0; i < itr->second.size(); i++)
          {
                  
              error = fabs(itr->second[i].second - findprobability(vMovieUserData, vUserMovieData,itr->first, rating,itr->second[i].first, userweights));
                  
                  MAerror += error;
                  RMSerror += error*error;
        }
        userweights.clear();
        //cout << "completed for:"<< i++ <<"user" << endl;
        i++;
        size += itr->second.size();
        if(i%3000 == 0)
        {
            cout << "Error after " << i*100/mapTestData.size()<< "% of data processing:"<< endl;
            cout << "Mean Absolute error:"<<MAerror/size<< endl;
            cout << "Root Mean Square error:"<<sqrt(RMSerror/size)<< endl;
        }
    }
    cout << "Final error:" << endl;
    cout << "Mean Absolute error:"<<MAerror/size<< endl;
    cout << "Root Mean Square error:"<<sqrt(RMSerror/size)<< endl;
    //userweights.clear();
}
