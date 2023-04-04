#ifndef RECCHECK
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#endif


#include "wordle.h"
#include "dict-eng.h"
using namespace std;




// Add prototypes of helper functions here
void wordsGenerate(int count, int n, std::string floating, std::string word, int index,std::set<std::string>& result,std::map<char,int>& floatingLetters,const std::set<std::string>& dict);
bool isValidCheck(std::string word, std::string floating,const std::set<std::string>& dict);
// Definition of primary wordle functi
std::set<std::string> wordle(
   const std::string& in,
   const std::string& floating,
   const std::set<std::string>& dict)
{
   int count = 0;
   for(size_t i=0; i<in.length(); i++){
       if(in[i] == '-' ){
           count ++;
       }
   }
   std::map<char,int> floatingLetters;//this data structure stores the floating letters and the amount
   for(size_t i = 0; i < floating.length(); i++){
       if(floatingLetters.find(floating[i]) == floatingLetters.end()){
           floatingLetters.insert(std::make_pair(floating[i],1));
       }
       else{
           floatingLetters[floating[i]]++;
       }
   }


   std::set<std::string> result;
  
 std::string word = in;
   wordsGenerate(count,in.length(), floating, word, 0, result,floatingLetters, dict);
   
   return result;
}


//use a recursive approach to find all combinations of letters to form the length-n word.
void wordsGenerate(int count, int n, std::string floating, std::string word, int index,std::set<std::string>& result,std::map<char,int>& floatingLetters,const std::set<std::string>& dict)
{
   bool fixedLettersCheck = false;
   bool specialCases = false;
   if(n == 0){
       if(isValidCheck(word, floating,dict)){
           result.insert(word);
       }
       return;
   }
   if(count==0){
       if(isValidCheck(word, floating,dict)){
           result.insert(word);
       }
       return;
   }
   if(word[index] != '-'){//checked if the current index is a fixed letter
       fixedLettersCheck = true;
       wordsGenerate(count, n-1, floating, word, index+1, result,floatingLetters,dict);   
   }
   //special case
   if(word == "bi--"){
       cout<<"";
   }
   size_t count_ = count;
   if(count_ <= floating.length() ){
       specialCases = true;
       std::map<char,int>::iterator it1;
       for(it1 = floatingLetters.begin(); it1!=floatingLetters.end(); ++it1){
           if(it1->second == 0){
             continue;
           }
           bool floatingLetterCheck = false;
           string temp = floating;
           word[index] = it1->first;
          
           std::map<char,int>::iterator it = floatingLetters.find(it1->first);
           if(it != floatingLetters.end()){//floating letter check
               if(it->second > 0 ){
                   (it->second) -=1;
                   temp.pop_back();
                   floatingLetterCheck = true;
               }
           }


           wordsGenerate(count-1,n-1, temp, word, index+1, result,floatingLetters,dict);
           if(floatingLetterCheck){
             it1->second ++;
           }
       }
   }


   for(char i = 'a'; i<= 'z'; i++){
       //float letter check
       if(fixedLettersCheck || specialCases){
           break;
       }
       bool floatingLetterCheck = false;
       string temp = floating;
       word[index] = i;
      
       // size_t found = floating.find(i);
       // if(found != std::string::npos){//this is a floating letter
       //     temp.erase(found,1);//remove the floating letter from the floating string   
       // }
       std::map<char,int>::iterator it = floatingLetters.find(i);
       if(it != floatingLetters.end()){
           if(it->second > 0 ){
               floatingLetterCheck = true;
               (it->second) -=1;
               temp.pop_back();
           }
          
       }  
  
       wordsGenerate(count-1,n-1, temp, word, index+1, result, floatingLetters,dict);
       //if it is a floating letter, need to add it back in flaoting when iterating to next char
       if(floatingLetterCheck){
           floatingLetters[i] ++;
       }
   }
}       
  


//check if the word has enough float number
bool isValidCheck(std::string word,std::string floating, const std::set<std::string>& dict){
   if(dict.find(word) == dict.end() || !floating.empty()){
       return false;
   }
   return true;
}

