//递归显示目录及子目录内容
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <dirent.h> //目录操作相关,ent是entry,项的意思
#include <sys/stat.h>

int retrav(const char *path)
{

    struct dirent * ent;
    struct stat st;
   // stat(ent->d_name,&st);
   //打开目录
    DIR *dir=opendir(path);
    //进入目录
    chdir(path);
    //读取目录项
    while(ent=readdir(dir))
    {
        //忽略目录项.和..
        if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0)
        {
            continue;
        }
        int ret=stat(ent->d_name,&st);
        if(ret==-1)
        {
            perror("stat");
            continue;
        }
        //如果是文件就打印
        if(S_ISREG(st.st_mode))
        {
            printf("%s文件\n",ent->d_name);
            continue;
        }
        //如果是目录就打印，然后进入目录
        else if(S_ISDIR(st.st_mode))
        {
            printf("%s目录\n",ent->d_name);
            retrav(ent->d_name);
           // struct dirent *entnow=ent;
           
        }
    }
    //回到上级目录
    chdir("..");
    closedir(dir);
}

int main(int argc,const char *argv[])
{
    if(argc<2)
    {
        printf("使用: %s 路径\n",argv[0]);
        exit(-1);
    }
    retrav(argv[1]);

    return 0;
}

