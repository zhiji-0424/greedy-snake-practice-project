#include "ScoreManager.hpp"


ScoreManager::ScoreManager() : data_score(0), data_highest(0)
{
    data_score_file_path = "";
}

ScoreManager::~ScoreManager()
{
    data_score      = 0;
    data_highest    = 0;
    data_score_file_path = "";
}

ScoreManager::ScoreManager(const char* path) : data_score(0), data_highest(0)
{
    set_score_file_path(path);
}

void ScoreManager::save()
{
    FILE* f = fopen(data_score_file_path.c_str(), "w");
    if (f != nullptr) {
        fprintf(f, "highest: %d", data_highest);
        fclose(f);
    } else {
        // zj_logger_e(ScoreManager_LOG_TAG, "save(): 文件打开失败！(%s)", data_score_file_path.c_str());
    }
}

void ScoreManager::read()
{
    FILE* f = fopen(data_score_file_path.c_str(), "r");
    if (f != nullptr) {
        if ( 1 != fscanf(f, "highest: %d", &data_highest) ) {
            // zj_logger_e(ScoreManager_LOG_TAG, "read(): 读取时发生错误！");
            data_highest = 0;
        }
        fclose(f);
    } else {
        // zj_logger_d(ScoreManager_LOG_TAG, "read(): 文件打开失败！(%s)", data_score_file_path.c_str());
    }
}
