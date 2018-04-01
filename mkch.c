#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define err(msg) perror(msg)
int mkch(const char *dir)
{
    char tmp[1024];
    char *p;
    if(strlen(dir)==0||dir==NULL)
    {
        printf("strlen(dir) is 0 or dir is NULL.\n");
        return 0;
    }
    memset(tmp,0,sizeof(tmp));
    strncpy(tmp,dir,strlen(dir));
    if(tmp[0]=='/'&&tmp[1]=='/')
    {
        p=strchr(tmp+2,'/');
    }
    else
    {
        p=strchr(tmp,'/');
    }
    if(p)
    {
        *p='\0';
        mkdir(tmp,0777);//创建目录
        chdir(tmp);//进入目录
    }
    else
    {
        mkdir(tmp,0777);
        chdir(tmp);
        return 0;
    }
    mkch(p+1);//递归进入目录创建目录
}

int main(int argc,const char*argv[])
{
    if(argc<2)
    {
        printf("使用方法: %s 路径\n",argv[0]);
        exit(-1);
    }
    mkch(argv[1]);
    return 0;
}