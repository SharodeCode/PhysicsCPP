#pragma once
#include <memory>
#include "Components/RigidbodyComponent.h"

class BaseBoundary {
public:
    virtual ~BaseBoundary() = default;
    virtual void resolve(std::shared_ptr<RigidbodyComponent>& rb) const = 0;
};
