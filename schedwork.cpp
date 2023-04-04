#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool search(size_t day, vector<std::vector<bool>> avail, vector<vector<Worker_T>> &sched, vector<int> &availableDaysLeft,const size_t & dailyNeed);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,//Number of workers needed per day (aka d)
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t n_worker = avail[0].size();
    //everytime someone works, subtract 1 from the maxShifts. If this path failed, plus it back
    vector<int> availableDaysLeft(n_worker,maxShifts);
    return search(0,avail,sched,availableDaysLeft,dailyNeed);
    

}

bool search(size_t day, vector<std::vector<bool>> avail, vector<vector<Worker_T>> &sched, vector<int> &availableDaysLeft,const size_t& dailyNeed)
{
    if(day == avail.size()){
        return true;
    }
    //iterator through the workers first
    for(size_t i = 0; i<avail[day].size(); i++){
        if(avail[day][i] == true){
            //check if the worker is available
            if(availableDaysLeft[i] > 0){
                //if available, add to the schedule
                //also need to check if this is the first worker added. If so, add a new vector
                if(sched.size() == day){
                    vector<Worker_T> temp;
                    sched.push_back(temp);
                }
                
                sched[day].push_back(i);
                //subtract 1 from the maxShifts mapb
                availableDaysLeft[i]--;
                //add more workers to the schedule if dailyNeed is not reached
                if(sched[day].size() < dailyNeed){
                    continue;
                }
                
                
                //check if the next row is valid
                if(search(day+1,avail,sched,availableDaysLeft,dailyNeed)){
                    return true;
                }
                //if not, add it back
                sched[day].pop_back();
                availableDaysLeft[i]++;
            }
        }
    }
    return false;
}