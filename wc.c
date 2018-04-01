#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#define IN 1
#define OUT 0
int main(int argc,const char *argv[])
{
    char buf[12];
    //统计行数、单词数与字符数
    int ch,nl,nw,nc,state;
    nl=nw=nc=0;
    state=OUT;
    if(argc<2)
    {
        printf("使用方法: %s 文件名\n",argv[0]);
        exit(-1);
    }
    //打开文件
    FILE *fd=fopen(argv[1],"r");
    if(!fd)
    {
        perror("open");
        exit(-1);
    }
    while((ch=fgetc(fd))!=EOF)
    {
        ++nc;//字符数
        if(ch=='\n')
        {
            ++nl;//行数
        }
        if(ch==' '||ch=='\n'||ch=='\t')
        {
            state=OUT;
        }
        else if(state==OUT)
        {
            ++nw;//单词数
            state=IN;
        }
    }
    printf("nl=%d\tnw=%d\tnc=%d\n",nl,nw,nc);
    return 0;
}