#include <stdio.h>
#include <stdlib.h>


#define UID_LENGTH 40
#define HASH_MAX_VALUE 857
/********************* typedefs ***********************/
typedef void (*vfunc)(void* params);

/****************** structs ******************************/

typedef struct class_class
{
    const char *class_name;
    size_t size;
    struct class_class *parent;
    vfunc (*methods)[];

}class_class;


typedef struct Object
{
    class_class *metadata;
}Obeject;

typedef struct MutableInteger
{
   Obeject parent;
   int num;

}MutableInteger;

/*********************** enum ***********************/
typedef enum vfunc_names
{
    EQUALS = 0,
    HASH_CODE,
    GET_CLASS,
    SET_INT,
    GET_INT
}vfunc_names;

typedef enum boolean{
    FALSE,
    TRUE
}boolean;





/****************   function declarations**************/

void ObjectCtor(Obeject this);
void MutMutableIntegerableCtor(MutableInteger *this, int value);
Obeject *Alloc(class_class *classMetaData);
boolean ObjectEquals(Obeject *this, Obeject *other);
int ObjectHashcode(Obeject *this);
class_class *ObjectGetClass(Obeject *this);
void MutableIntegerSet(MutableInteger *this, int num);
int MutableIntegerGet(MutableInteger *this);
boolean  MutableIntegerEquals(MutableInteger *this, Obeject *other);


/******************** globals ****************************/

vfunc Object_vfunc[] = {(vfunc)ObjectEquals,(vfunc)ObjectHashcode, (vfunc)ObjectGetClass};
vfunc MutableInteger_vfunc[] = {(vfunc)MutableIntegerEquals,(vfunc)ObjectHashcode, (vfunc)ObjectGetClass,
                                (vfunc)MutableIntegerSet, (vfunc)MutableIntegerGet};

class_class Object_class = {"Object", sizeof(Obeject), NULL, &Object_vfunc};
class_class MutableInteger_class = {"MutableInteger", sizeof(MutableInteger), &Object_class, &MutableInteger_vfunc};



/*********************static methods********************/



void ObjectCtor(Obeject this)
{
    
}

void MutMutableIntegerableCtor(MutableInteger *this, int value)
{
        this->num = value;
}

Obeject *Alloc(class_class *classMetaData)
{
    Obeject *obj = (Obeject *)malloc(classMetaData->size);
    if(NULL == obj )
    {
        return NULL;
    }
    obj->metadata = classMetaData;
    return obj;
}


/********************* virtual methods ********************************/


boolean ObjectEquals(Obeject *this, Obeject *other)
{
    return this == other;
}

int ObjectHashcode(Obeject *this)
{
    return (*((int *)this)) % HASH_MAX_VALUE;
}

class_class *ObjectGetClass(Obeject *this)
{
    return this->metadata;
}

void MutableIntegerSet(MutableInteger *this, int num)
{
    this->num = num;
}

int MutableIntegerGet(MutableInteger *this)
{
    return this->num;
}

boolean  MutableIntegerEquals(MutableInteger *this, Obeject *other)
{
   if (this->parent.metadata != other->metadata)
   {
        return FALSE;
   }
   return (MutableIntegerGet(this) == MutableIntegerGet((MutableInteger *)other)) ? TRUE : FALSE;
}

int main ()
{
    MutableInteger *num1 = (MutableInteger *)Alloc(&MutableInteger_class);
    MutableInteger *num2 = (MutableInteger *)Alloc(&MutableInteger_class);
    if(NULL == num1)
    {
        printf("MutblableInt Alloc Faild\n");
    }

    if(NULL == num2)
    {
        printf("MutblableInt Alloc Faild\n");
    }
    
    MutMutableIntegerableCtor(num1, 5);
    MutMutableIntegerableCtor(num2, 4);
   if(TRUE == ((boolean (*)(MutableInteger*, Obeject *))(*(num1->parent.metadata->methods))[EQUALS])(num1, (Obeject *)num2))
   {
        printf("Yes!\n");
   }
   else
   {
        printf("No!\n");
   }
   
    free(num1);
    free(num2);

   

    return 0;
}