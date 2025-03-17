#ifndef MINIBUS_H
#define MINIBUS_H

#include "transport.c"

typedef struct Minibus Minibus_t;

/*non static methods*/
Minibus_t *createMinibusdefault(Minibus_t *thise);
Minibus_t *createMinibusCopyCtor(Minibus_t *thise,  const Minibus_t *other);

/*virtual methdos*/
void destroyMinibus(Minibus_t *thise);
void displayMinibus(Minibus_t *thise);
void Minibus_wash(Minibus_t *thise, int minutes);

vfunc MinibusVTable[] = {(vfunc)destroyMinibus,(vfunc)displayMinibus, (vfunc)Minibus_wash};
#endif /* MINIBUS_H */