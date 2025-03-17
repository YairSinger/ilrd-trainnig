#ifndef TRANSPORT_H
#define TRANSPORT_H 

#include <stdio.h>

typedef struct PublicTrasport PublicTransport_t;
typedef void (*vfunc)(void* params);


/*non virtual methods*/
PublicTransport_t *createTransportDefault(PublicTransport_t *this);
PublicTransport_t *createTransportCopy(PublicTransport_t *this, PublicTransport_t *other);

/*virtual methods*/
void destroyTransport(PublicTransport_t *this);
void displayTransport(PublicTransport_t *this);

/*static methods*/
void PrintPublicTransportCount(void);


/*static fields*/
int PublicTransportSCount = 0;

vfunc PublicTransportVTable[] = {(vfunc)destroyTransport,(vfunc)displayTransport};

typedef enum VTableFuncs
{
    DTOR,
    DISPLAY,
    WASH   
}VTableFuncs_t;

#endif /* TRANSPORT_H */