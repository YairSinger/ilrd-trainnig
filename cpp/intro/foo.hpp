
#ifndef __ILRD_FOO_H__
#define __ILRD_FOO_H__

struct tempStruct{
    int val1;
    int val2;
    char letter;
};

template <typename T> 
T Max(T t1, T t2) 
{ 
    (t1 > t2) ? t1 : t2;  
  
} 


#endif /* __ILRD_FOO_H__ */