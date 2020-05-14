#pragma once
#include "node.h"
#include "token.h"

#include <map>
#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

Date ParseDate(istream& is);