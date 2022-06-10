//
// Created by arels on 6/4/22.
//

#ifndef MEMALLOCATOR_GLOBALDEF_H
#define MEMALLOCATOR_GLOBALDEF_H

#include "log.h"

//This will return the data start value(After the allocation header)
#define getKey(l) (unsigned long) l + sizeof(ListNode)

#endif//MEMALLOCATOR_GLOBALDEF_H
