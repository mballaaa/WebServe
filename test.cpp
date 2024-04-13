// implemtion a example of ierate into directory



#include<iostream>
#include<dirent.h>
int main()
{
    std ::string s("/home/mballa/Desktop/WebS/src/test");
    DIR *ptr=opendir(s.c_str());
    if(ptr)
    {
           struct dirent *entry;
           entry=readdir(ptr);
           while (entry!=NULL)
           {
            std :: cout << entry->d_name << std ::endl;
            entry=readdir(ptr);
           }
            closedir(ptr);
    }
}