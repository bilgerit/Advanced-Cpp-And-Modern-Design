#pragma once
#include "Producer.h"

Producer::Producer(int id, BarberShop& shop) : id(id), shop(shop) {}

bool Producer::operator()() {
    return shop.try_enter_shop(id);
}
