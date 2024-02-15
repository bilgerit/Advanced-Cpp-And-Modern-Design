// DoubleFormatObserver: Observer Impl
//
// Displays a Counter Subject in double format w/ 2-digit precision.
//
// Tobias Bilgeri, 11.02.2024
#pragma once
#include "Observer.h"

class DoubleFormatObserver : public Observer {
public:
    ~DoubleFormatObserver() override = default;
    void Update(Subject* subject) override;
};