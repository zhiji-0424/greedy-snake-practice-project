#include <SDL3/SDL.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/stat.h>

static char log_file_name[150];
static void log_cat(const char *msg) {
    FILE* fp = fopen(log_file_name, "a");
    if (!fp) {
        return;
    }
    fprintf(fp, "%s\n", msg);
    fclose(fp);
}

static void show_logcat(void)
{
    // 显示发送到系统的 logcat
    char cmd[1000];
    sprintf(cmd, "logcat -v threadtime >> %s", log_file_name);
    log_cat(cmd);
    system(cmd);
}

static void clear_logcat(void)
{
    char cmd[10];
    sprintf(cmd, "logcat -c");
    system(cmd);
}

typedef int (*MainFunc)(int,char**);
static const char* exPath;
static const char* inPath;

#define OK  1
#define ERR 0
static int check(void)
{
    char* msg = dlerror();
    if (msg != NULL) {
        // 有错误信息
        log_cat(msg);
        return ERR;
    }
    return OK;
}

#define yes 1
#define no  0
int is_program_so_file_exist()
{
    exPath = SDL_GetAndroidExternalStoragePath();
    char external_lib_path[150];
    sprintf(external_lib_path, "%s/libmain.so", exPath);
    
    struct stat buffer;
    // stat 返回 0 表示成功（文件存在），非 0 表示失败（文件不存在或其他错误）
    return (stat(external_lib_path, &buffer) == 0);
}

int loader(int argc, char** argv)
{
    exPath = SDL_GetAndroidExternalStoragePath();
    inPath = SDL_GetAndroidInternalStoragePath();

    // 指定日志位置
    sprintf(log_file_name, "%s/loader.log", exPath);
    log_cat("");    // 分割上一次的信息

    // 打印时间
    time_t now = time(NULL);
    char time_str[30];
    strftime(time_str, sizeof(time_str), "    [%Y-%m-%d %H:%M:%S]", localtime(&now));
    log_cat(time_str);

    // 显示上一次的logcat
    show_logcat();
    clear_logcat();

    // 复制库文件
    char cmd[2000];
    sprintf(cmd, "cp %s/libmain.so %s/libmain.so 2>> %s", exPath, inPath, log_file_name);
    log_cat(cmd);
    system(cmd);

    // 指定库的路径
    char lib_path[150];
    sprintf(lib_path, "%s/libmain.so", inPath);

    // 读取库文件
    void* lib = dlopen(lib_path, RTLD_NOW);
    log_cat("dlopen(lib)");
    int ret = -1;
    if (check() == OK) {
        // 解析函数并运行
        MainFunc f = (MainFunc)dlsym(lib, "SDL_main");
        log_cat("dlsym(SDL_main)");
        if (check() == OK) {
            ret = f(argc, argv);
        }
    }

    // 关闭库文件
    log_cat("dlclose(lib)");
    dlclose(lib);

    return ret;
}

