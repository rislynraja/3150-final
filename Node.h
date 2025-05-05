#pragma once

#include "TimedSharedPtr.h"

struct Node {
    Node(int v) : val{v} {};
    int val;
    TimedSharedPtr<Node> next;
};