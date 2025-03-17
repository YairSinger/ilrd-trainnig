#include "transport.h"

struct PublicTrasport{
    vfunc (*methods)[];
    int m_license_plate;
    
};

PublicTransport_t *createTransportDefault(PublicTransport_t *this){
    this->methods = &PublicTransportVTable;
    this->m_license_plate = ++PublicTransportSCount;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
    return this;
}

PublicTransport_t *createTransportCopy(PublicTransport_t *alloced, PublicTransport_t *other){
    alloced->m_license_plate = ++PublicTransportSCount;
    printf("PublicTransport::CCtor() %d\n", alloced->m_license_plate);
    return alloced;
}

void destroyTransport(PublicTransport_t *this){
    --PublicTransportSCount;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void displayTransport(PublicTransport_t *this){
    printf("PublicTransport::Display() %d\n", this->m_license_plate);
}

void PrintPublicTransportCount(void){
    printf("s_count:  %d\n", PublicTransportSCount);
}
static GetId(PublicTransport_t *this){return this->m_license_plate;}



