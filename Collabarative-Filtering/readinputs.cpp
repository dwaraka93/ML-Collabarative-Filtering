//
//  readinputs.cpp
//  collabarative_filtering
//
//  Created by Tuition.in on 10/8/19.
//  Copyright © 2019 Tuition.in. All rights reserved.
//

#include "readinputs.hpp"
bool readfile(string filename, VMovieUsersdetails& vMovieUsersdetails, VUsersMoviedetails& vUserMoviedetails, MapMovieIndex &mapMovieIndex, MapUserIndex &mapUserIndex, float **ratingmatrix)
{
    fstream fin;
    string  strline;
    char*   pchtoken;
    char    arrchdelims[] = ",";
    unsigned int movieindex = 0;
      unsigned int userindex = 0;
    vector<float> filevalues;
    MapUserData mapuserrating;
    MapUserData::iterator itrmapuser;
    MapMovieIndex::iterator mapMovieIndexitr;
    MapUserIndex::iterator mapUserIndexitr;
    fin.open(filename,ios::in);
    if(!fin.is_open())
    {
        cout << "Unable to open file: " << filename <<endl;
        return false;
    }
    while(getline(fin, strline))
    {
        pchtoken = strtok(&strline[0],arrchdelims);
        while(pchtoken != NULL)
        {
            filevalues.push_back(atof(pchtoken));
            pchtoken = strtok(NULL, arrchdelims);
        }
        if((mapMovieIndexitr = mapMovieIndex.find(filevalues[0])) != mapMovieIndex.end())
            vMovieUsersdetails[mapMovieIndexitr->second].push_back(filevalues[1]);
        else
        {
            vector<unsigned int> vUsers;
            vUsers.push_back(filevalues[1]);
            vMovieUsersdetails.push_back(vUsers);
            mapMovieIndex[filevalues[0]] = movieindex++;
        }
        
        if((mapUserIndexitr = mapUserIndex.find(filevalues[1])) != mapUserIndex.end())
             vUserMoviedetails[mapUserIndexitr->second].push_back(filevalues[0]);
         else
         {
             vector<unsigned int> vMovies;
             vMovies.push_back(filevalues[0]);
             vUserMoviedetails.push_back(vMovies);
             mapUserIndex[filevalues[1]] = userindex++;
         }

        if((itrmapuser = mapuserrating.find(filevalues[1])) != mapuserrating.end())
            itrmapuser->second.moviedetails[filevalues[0]] = filevalues[2];
        else
            mapuserrating[filevalues[1]].moviedetails[filevalues[0]] = filevalues[2];
        
        filevalues.clear();
    }
    
    fin.close();
    
    *ratingmatrix = new float[mapuserrating.size()*(mapMovieIndex.size()+1)];
    if(*ratingmatrix == NULL)
    {
        cout << "error allocating memory for matrix" << endl;
        return false;
    }
    
    for(auto itruser = mapuserrating.begin(); itruser != mapuserrating.end(); itruser++)
    {
        float ratingsum = 0;
        if((mapUserIndexitr = mapUserIndex.find(itruser->first)) != mapUserIndex.end())
        {
            for(auto itrmovie = itruser->second.moviedetails.begin(); itrmovie != itruser->second.moviedetails.end(); itrmovie++)
            {
                if((mapMovieIndexitr = mapMovieIndex.find(itrmovie->first)) != mapMovieIndex.end())
                {
                    *(*ratingmatrix + mapUserIndexitr->second*(mapMovieIndex.size()+1) + mapMovieIndexitr->second) = itrmovie->second;
                    ratingsum += itrmovie->second;
                }
                else
                    cout << "error in storing file info to matrix"<< endl;
            }
            *(*ratingmatrix + mapUserIndexitr->second*(mapMovieIndex.size()+1) + mapMovieIndex.size()) = ratingsum/itruser->second.moviedetails.size();
        }
        else
            cout << "error in storing file info to matrix"<<endl;
        
        //itr->second.favgrating = ratingsum/itr->second.moviedetails.size();
    }
    
    mapuserrating.clear();
    
    for(int i=0; i < vMovieUsersdetails.size(); i++)
    {
        for(int j=0; j < vMovieUsersdetails[i].size(); j++)
        {
            if((mapUserIndexitr = mapUserIndex.find(vMovieUsersdetails[i][j])) != mapUserIndex.end())
                vMovieUsersdetails[i][j] = mapUserIndexitr->second;
            else
                cout << "error in storing file info to matrix"<<endl;
        }
    }
    
    for(int i=0; i < vUserMoviedetails.size(); i++)
    {
        for(int j=0; j < vUserMoviedetails[i].size(); j++)
        {
            if((mapMovieIndexitr = mapMovieIndex.find(vUserMoviedetails[i][j])) != mapMovieIndex.end())
                vUserMoviedetails[i][j] = mapMovieIndexitr->second;
            else
                cout << "error in storing file info to matrix"<<endl;
        }
    }
    
    return true;
}

bool readtestfile(string filename, MapTestData &maptest, MapMovieIndex &mapMovieIndex, MapUserIndex &mapUserIndex)
{
    fstream fin;
    string  strline;
    char*   pchtoken;
    char    arrchdelims[] = ",";
    vector<float> filevalues;
    MapUserIndex::iterator itruser;
    MapMovieIndex::iterator itrmovie;
    
    fin.open(filename,ios::in);
    if(!fin.is_open())
    {
        cout << "Unable to open file: " << filename <<endl;
        return false;
    }
    while(getline(fin, strline))
    {
        pchtoken = strtok(&strline[0],arrchdelims);
        while(pchtoken != NULL)
        {
            filevalues.push_back(atof(pchtoken));
            pchtoken = strtok(NULL, arrchdelims);
        }
        
        if((itrmovie = mapMovieIndex.find(filevalues[0])) != mapMovieIndex.end() )
        {
            if((itruser = mapUserIndex.find(filevalues[1])) != mapUserIndex.end())
                maptest[itruser->second].push_back(make_pair(itrmovie->second,filevalues[2]));
            else
                cout << "no user: " << filevalues[1] << "in train data. so discarding"<< endl;
        }
        else
            cout << "no movie: " << filevalues[0] << "in train data. so discarding"<< endl;

        filevalues.clear();
    }
    fin.close();
    return true;
}
