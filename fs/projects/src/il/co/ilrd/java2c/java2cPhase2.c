/*Project: Java2C phase 2
Group: ilrd_fs149-150
Writer: Yair Singer
Reviewer: Yuval
Date: 15.01.2024
Status: Approved*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TO_STRING_LENGTH 40
#define HASH_MAX_VALUE 857567
/********************* typedefs ***********************/
typedef void (*vfunc)(void* params);




/********************* static fields ******************/
int animal_counter = 0;

/****************** structs ******************************/

typedef struct class_class
{
    const char *class_name;
    size_t size;
    struct class_class *superclass;
    vfunc (*methods)[];

}class_class;


typedef struct Object
{
    class_class *metadata;
}Object;


typedef struct Animal /*extendes Object*/
{
    Object superclass;
    int num_legs;
    int num_master;
    int *animal_counter_ptr;
    int id;

}Animal;

typedef struct Dog /*extends Animal*/
{
    Animal superclass;
    int num_legs;
}Dog;

typedef struct Cat /*extends Animal*/
{
    Animal superclass;
    char *colors;
    int num_master;
}Cat;

typedef struct LegendaryAnimal /*extends Cat*/
{
    Cat superclass;
}LegendaryAnimal;



/*********************** enum ***********************/
typedef enum vfunc_names
{
    EQUALS = 0,
    HASH_CODE,
    GET_CLASS,
    TO_STRING,
    FINALIZE,
    SAY_HELLOW,
    NUM_MASTER
}vfunc_names;

enum animals
{
    ANIMAL,
    DOG,
    CAT,
    LEGENDARY,
    NUM_OF_ANIMALS
};

typedef enum boolean{
    FALSE,
    TRUE
}boolean;





/****************   function declarations**************/

void ObjectCtor(Object *this);

Object *Alloc(class_class *classMetaData);
boolean ObjectEquals(Object *this, Object *other);
int ObjectHashcode(Object *this);
class_class *ObjectGetClass(Object *this);
char *ObjectToString(Object *this);
void ObjectFinalize(Object *this);
char *AnimalToString(Animal *this);
void AnimalFinalize(Animal *this);
void AnimalSayHellow(Animal *this);
void AnimalShowCounter(); /*static method*/
int AnimalGetNumMaster(Animal *this);
void DogSayHellow(Animal *this);
void DogFinalize(Dog *this);
char *DogToString(Animal *this);
void CatFinalize(Animal *this);
char *CatToString(Animal *this);
char *LegendaryAnimalToString(Animal *this);
void LegendaryAnimalFinalize(LegendaryAnimal *this);
void LegendaryAnimalSayHellow (Animal *this);



/******************** globals ****************************/

vfunc Object_vfunc[] = {(vfunc)ObjectEquals,(vfunc)ObjectHashcode, (vfunc)ObjectGetClass,
                        (vfunc)ObjectToString, (vfunc)ObjectFinalize};

vfunc Animal_vfunc[] = {(vfunc)ObjectEquals,(vfunc)ObjectHashcode, (vfunc)ObjectGetClass,
                        (vfunc)AnimalToString, (vfunc)AnimalFinalize, (vfunc)AnimalSayHellow,
                        (vfunc)AnimalGetNumMaster};
vfunc Dog_vfunc[] = {(vfunc)ObjectEquals,(vfunc)ObjectHashcode, (vfunc)ObjectGetClass,
                        (vfunc)DogToString, (vfunc)DogFinalize, (vfunc)DogSayHellow, 
                        (vfunc)AnimalGetNumMaster};
vfunc Cat_vfunc[] = {(vfunc)ObjectEquals,(vfunc)ObjectHashcode, (vfunc)ObjectGetClass,
                        (vfunc)CatToString, (vfunc)CatFinalize, (vfunc)AnimalSayHellow,
                        (vfunc)AnimalGetNumMaster};
vfunc Legendary_vfunc[] = {(vfunc)ObjectEquals,(vfunc)ObjectHashcode, (vfunc)ObjectGetClass,
                        (vfunc)LegendaryAnimalToString, (vfunc)LegendaryAnimalFinalize, (vfunc)LegendaryAnimalSayHellow,
                        (vfunc)AnimalGetNumMaster};

class_class Object_class = {"il.co.ilrd.Object", sizeof(Object), NULL, &Object_vfunc};
class_class Animal_class = {"il.co.ilrd.Animal", sizeof(Animal), &Object_class, &Animal_vfunc};
class_class Dog_class = {"il.co.ilrd.Dog", sizeof(Dog),&Animal_class, &Dog_vfunc};
class_class Cat_class = {"il.co.ilrd.Cat", sizeof(Cat),&Animal_class, &Cat_vfunc};
class_class LegendaryAnimal_class = {"il.co.ilrd.LegendaryAnimal", sizeof(LegendaryAnimal),&Cat_class, &Legendary_vfunc};

/********************* class init flags *****************/
boolean IsClassLoaded[NUM_OF_ANIMALS] = {FALSE};
boolean IsAnimalClassLoad = FALSE;
boolean IsDogClassLoad = FALSE;
boolean IsCatClassLoad = FALSE;
boolean IsLegendaryAnimalClassLoad = FALSE;

/*********************static methods********************/

void ObjectCtor(Object *this)
{
    
}

void AnimalStaticInit()
{
    if(IsClassLoaded[ANIMAL] == FALSE)
    {
        IsClassLoaded[ANIMAL] = TRUE;
        printf("Static block Animal 1\n");
        printf("Static block Animal 2\n");
    }    
}

void AnimalInstanseInit(Animal *this)
{
    this->animal_counter_ptr = &animal_counter;
    this->num_legs = 5;
    this->num_master = 1;
    printf("Instance initialization block Animal\n");
}

void AnimalCtor(Animal *this)
{
    
    char *to_string = NULL;
    if(IsClassLoaded[ANIMAL] == FALSE)
    {
        AnimalStaticInit();
    }
    AnimalInstanseInit(this);
    printf("Animal Ctor\n");
    (*(this->animal_counter_ptr)) += 1;
    this->id = (*(this->animal_counter_ptr));
    ((void(*)(Animal *))(*(((Object*)this)->metadata->methods))[SAY_HELLOW])(this);
    AnimalShowCounter(this);
    to_string = ((char * (*)(Animal *))(*(this->superclass.metadata->methods))[TO_STRING])(this);
    printf("%s\n", to_string);
    free(to_string);

    to_string = ObjectToString((Object *) this);
    printf("%s\n", to_string); 
    free(to_string);
}

void AnimalCtorInt(Animal *this, int num_masters)
{
   if(IsClassLoaded[ANIMAL] == FALSE)
    {
        AnimalStaticInit();
    }
    AnimalInstanseInit(this);
    printf("Animal Ctor int\n");
     (*(this->animal_counter_ptr)) += 1;
    this->id = (*(this->animal_counter_ptr));
    this->num_master = num_masters;
}

/***************Animal class ****************************/
/***************Dog class *******************************/
void DogStaticInit()
{ 
     if(IsClassLoaded[ANIMAL] == FALSE)
    {
        AnimalStaticInit();
    }

    if(IsClassLoaded[DOG] == FALSE)
    {
        IsClassLoaded[DOG] = TRUE;
        printf("Static block Dog\n");
    }
}

void DogInstanceInit(Dog *this)
{
    this->num_legs = 4;
    printf("Instance initialization block Dog\n");
}

void DogCtor(Dog *this)
{

    DogStaticInit();
    AnimalCtorInt((Animal*)this, 2);
    DogInstanceInit(this);
    printf("Dog Ctor\n");
}
/******************** Dog class****************/
/******************** Cat class****************/
void CatStaticInit()
{
    if(IsClassLoaded[ANIMAL] == FALSE)
    {
        AnimalStaticInit();
    }
    if(IsClassLoaded[CAT] == FALSE)
    {
       IsClassLoaded[CAT] = TRUE;
       printf("Static block Cat\n");
    }
}

void CatInstanceInit(Cat *this, const char *color, int num_master)
{
    this->colors = (char *)color;
    this->num_master = num_master;
}

void CatCtorChar(Cat *this, const char *color)
{

    CatStaticInit();
    AnimalCtor((Animal*)this);
    CatInstanceInit(this, color, 3);
    printf("Cat Ctor with color: %s\n", this->colors);
}

void CatCtor(Cat *this)
{
    CatCtorChar(this, "black");
    printf("Cat Ctor\n");
    this->num_master = 2;
}

/******************** Cat class****************/
/********** LegendaryAnimal class**************/
void LegendaryAnimalStaticInit()
{
     if(IsClassLoaded[ANIMAL] == FALSE)
    {
        AnimalStaticInit();
    }
      if (IsClassLoaded[CAT]){
        CatStaticInit();
      }
    if(IsClassLoaded[LEGENDARY] == FALSE)
    {
        IsClassLoaded[LEGENDARY] = TRUE;
        printf("Static block Legendary Animal\n");
    }
}

void LegendaryAnimalCtor(LegendaryAnimal *this)
{
    if (IsClassLoaded[LEGENDARY] == false){
        LegendaryAnimalStaticInit();
    }
    CatCtor((Cat *)this);
    printf("Legendary Ctor\n");
}

Object *Alloc(class_class *classMetaData)
{
    Object *obj = (Object *)malloc(classMetaData->size);
    if(NULL == obj )
    {
        return NULL;
    }
    obj->metadata = classMetaData;
    return obj;
}


/********************* virtual methods ********************************/


boolean ObjectEquals(Object *this, Object *other)
{
    return this == other;
}

int ObjectHashcode(Object *this)
{
    return (*((int *)this)) % HASH_MAX_VALUE;
}

class_class *ObjectGetClass(Object *this)
{
    return this->metadata;
}

char *ObjectToString(Object *this)
{   
    char *result = (char *)malloc(sizeof(char) * 40);
    if(NULL == result)
    {
        return NULL;
    }
    sprintf(result,"%s@%x", this->metadata->class_name, 
                            ((int (*)(Object*))(*(this->metadata->methods))[HASH_CODE])(this));
    return result;
}

void ObjectFinalize(Object *this)
{
    memset(this,0,this->metadata->size);
    free(this);
}

/****************************Object class*****************************************/
/****************************Animal class*****************************************/
char *AnimalToString(Animal *this) /*override*/
{
    char *result = (char *)malloc(sizeof(char) * TO_STRING_LENGTH);
    if(NULL == result)
    {
        return NULL;
    }
    sprintf(result,"Animal with ID: %d", this->id);
    return result;
}

void AnimalFinalize(Animal *this)
{
    printf("finalize Animal with ID: %d\n", this->id);
    ((void (*)(Object *))(*(Animal_class.superclass->methods))[FINALIZE])((Object *)this);
}

void AnimalSayHellow(Animal *this)
{
    printf("Animal Hello!\n");
    printf("I have  %d legs\n", this->num_legs);
}

void AnimalShowCounter()/*static method*/
{
    if(IsClassLoaded[ANIMAL] == false){
        AnimalStaticInit;
        IsClassLoaded[ANIMAL] = true;
    }
    printf("%d\n", animal_counter);
}

int AnimalGetNumMaster(Animal *this)
{
    return this->num_master;
}
/****************************Animal class*****************************************/
/****************************Dog class*****************************************/
void DogSayHellow(Animal *this)/*override*/
{
    printf("Dog Hello!\n");
    printf("I have %d legs\n", ((Dog *)this)->num_legs);
}

void DogFinalize(Dog *this)/*override*/
{
    printf("finalize Dog with ID:%d\n",((Animal*)this)->id);
    ((void (*)(Object *))(*(Dog_class.superclass->methods))[FINALIZE])((Object *)this);
}

char *DogToString(Animal *this)/*override*/
{
    char *result = (char *)malloc(sizeof(char) * TO_STRING_LENGTH);
    if(NULL == result)
    {
        return NULL;
    }
    sprintf(result,"Dog with ID: %d", this->id);
    return result;
}

void CatFinalize(Animal *this) /*override*/
{
    printf("finalize Cat with ID:%d\n",((Animal*)this)->id);
   ((void (*)(Object *))(*(Cat_class.superclass->methods))[FINALIZE])((Object *)this);
}

char *CatToString(Animal *this)
{
    char *result = (char *)malloc(sizeof(char) * TO_STRING_LENGTH);
    if(NULL == result)
    {
        return NULL;
    }
    sprintf(result,"Cat with ID: %d", this->id);
    return result;
}

void LegendaryAnimalSayHellow (Animal *this)/*overide*/
{
    printf("Legendary Hello!\n");
}

void LegendaryAnimalFinalize(LegendaryAnimal *this) /*override*/
{
    printf("finalize LegendaryAnimal with ID:%d\n",((Animal*)this)->id);
    ((void (*)(Object *))(*(LegendaryAnimal_class.superclass->methods))[FINALIZE])((Object *)this);
   
}

char *LegendaryAnimalToString(Animal *this) /*override*/
{
      char *result = (char *)malloc(sizeof(char) * TO_STRING_LENGTH);
    if(NULL == result)
    {
        return NULL;
    }
    sprintf(result,"LegendaryAnimal with ID: %d", this->id);
    return result;
}


int main ()
{
    Object obj = {0};
    Animal *animal = (Animal *)Alloc(&Animal_class);
    Dog *dog = (Dog *)Alloc(&Dog_class);
    Cat *cat = (Cat*)Alloc(&Cat_class);
    LegendaryAnimal *la = (LegendaryAnimal *)Alloc(&LegendaryAnimal_class);
    Animal *arr[5] = {0};
    size_t i = 0;
    char *to_string = NULL;

    AnimalCtor(animal);
    CatCtor(cat);
    DogCtor(dog);
    LegendaryAnimalCtor(la);

    AnimalShowCounter();

    printf("%d\n", animal->id);
    printf("%d\n", ((Animal *)dog)->id);
    printf("%d\n", ((Animal *)cat)->id);
    printf("%d\n", ((Animal *)la)->id);

    arr[0] = (Animal *)Alloc(&Dog_class);
    DogCtor((Dog *)arr[0]);

    arr[1] = (Animal *)Alloc(&Cat_class);
    CatCtor((Cat *)arr[1]);

    arr[2] = (Animal *)Alloc(&Cat_class);
    CatCtorChar((Cat *)arr[2], "white");

    arr[3] = (Animal *)Alloc(&LegendaryAnimal_class);
    LegendaryAnimalCtor((LegendaryAnimal *)arr[3]);

    arr[4] = (Animal *)Alloc(&Animal_class);
    AnimalCtor(arr[4]);

    for (i = 0; i < 5; ++i)
    {
        ((void (*)(Animal *))(*(((Object *)arr[i])->metadata->methods))[SAY_HELLOW])(arr[i]);
        printf("%d\n", AnimalGetNumMaster(arr[i]));
    }

    for (i = 0; i < 5; ++i)
    {
      to_string = ((char * (*)(Animal *))(*(((Object *)arr[i])->metadata->methods))[TO_STRING])(arr[i]);
      printf("%s\n", to_string);
      free(to_string);
      ((void(*)(Animal *))(*(((Object *)arr[i])->metadata->methods))[FINALIZE])(arr[i]);
    }

     for (i = 4; i < 5; --i)
     {
        ((void(*)(Animal *))(*(((Object *)arr[i])->metadata->methods))[FINALIZE])(arr[i]);
     {

    ((void(*)(Animal *))(*(((Object *)la)->metadata->methods))[FINALIZE])((Animal *)la);
    ((void(*)(Animal *))(*(((Object *)cat)->metadata->methods))[FINALIZE])((Animal *)cat);
    ((void(*)(Animal *))(*(((Object *)dog)->metadata->methods))[FINALIZE])((Animal *)dog);
    ((void(*)(Animal *))(*(((Object *)animal)->metadata->methods))[FINALIZE])(animal);


    return 0;
}