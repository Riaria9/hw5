#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    //find which letters are fixed
    std::map<int,char> fixedLetters;//this data structure stores the fixed letters and their positions
    for(size_t i = 0; i < in.length(); i++){
        if(in[i] != '-'){
            fixedLetters.insert(std::make_pair(i,in[i]));
        }
    }
    std::set<std::string> result;
    std::set<std::string>::iterator it;
    for(it = dict.begin(); it != dict.end(); ++it){
        if(it->length() == in.length()){//size matches
            //fixed letter check
            bool fixedLetterCheck = true;
            bool floatingLetterCheck = true;
            bool upperCaseCheck = true;
            std::map<int,char>::iterator it2;
            //check if upper case letter exist
            for(size_t i = 0; i < it->length(); i++){
                if(isupper(it->at(i))){
                    upperCaseCheck = false;
                    break;
                }
            }
            if(!upperCaseCheck)
                continue;
            for(it2 = fixedLetters.begin(); it2 != fixedLetters.end(); ++it2){
                if(it->at(it2->first) != it2->second){
                    fixedLetterCheck = false;
                    break;
                }
            }
            if(!fixedLetterCheck)
                continue;
            else{
                //floating letter check
                string tempWord = *it;
                for(size_t i = 0; i<floating.length(); ++i){
                    int index = tempWord.find(floating[i]);

                    if(tempWord.find(floating[i]) == std::string::npos){
                        floatingLetterCheck = false;
                        break;
                    }
                    else{
                        tempWord.at(index) = ' ';
                    }
                }
                if(floatingLetterCheck)
                    result.insert(*it);
            }
        }
    }
    return result;

}

// Define any helper functions here
