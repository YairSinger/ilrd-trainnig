#include "minibus.h"


 struct Minibus{
    vfunc (*methods)[];
    PublicTransport_t parent;
    int seats;
 };

/*non static methods*/
Minibus_t *createMinibusdefault(Minibus_t *thise){
    createTransportDefault(&(thise->parent));
    thise->methods = &MinibusVTable;
    thise->seats = 20;
    printf("Minibus::Ctor()\n");
    return thise;
}

Minibus_t *createMinibusCopyCtor(Minibus_t *thise,  const Minibus_t *other){
    createTransportCopy(&(thise->parent), &(other->parent));
    thise->methods = &MinibusVTable;
    thise->seats = other->seats;
    printf("Minibus::CCtor()\n");
    return thise;
}

/*virtual methdos*/
void destroyMinibus(Minibus_t *thise){
    
    printf("Minibus::Dtor()\n");
}
void displayMinibus(Minibus_t *thise){
    printf("Minibus::Display() ID:%d num seats:%d\n",GetId(&(thise->parent)), thise->seats);
}
void Minibus_wash(Minibus_t *thise, int minutes){
    printf("Minibus::Wash(%d) ID:%d\n",minutes, GetId(&(thise->parent)));
}