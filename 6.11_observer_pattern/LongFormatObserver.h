// LongFormatObserver: Observer impl
//
// Displays a Counter Subject in long format.
//
// Tobias Bilgeri, 11.02.2024
#pragma once
#include "Observer.h"

class LongFormatObserver : public Observer {
public:
    ~LongFormatObserver() override = default;
    void Update(Subject* subject) override;
};
