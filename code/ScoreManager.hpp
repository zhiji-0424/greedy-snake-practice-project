#ifndef SCORE_HPP
#define SCORE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
using std::string;

#define ScoreManager_LOG_TAG "ScoreManager"

class ScoreManager {
    public:
        ScoreManager();
        ~ScoreManager();
        ScoreManager(const char* path); //包含文件名称
        void set_score_file_path(const char* path) {data_score_file_path=path;}
        void score_add()  {data_score+=1;}
        void score_add(int n)  {data_score+=n;}
        void score_zero() {data_score=0;}
        void highest_update() {if(data_highest<data_score){data_highest=data_score;save();}}
        void highest_zero()   {data_highest=0;}
        void save();
        void read();
        int  score()   const {return data_score;}
        int  highest() const {return data_highest;}
        const string& score_file_path() const {return data_score_file_path;}
    private:
        int         data_score;
        int         data_highest;
        string   data_score_file_path;
};


#endif
