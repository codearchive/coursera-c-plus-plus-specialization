#pragma once
#include "node.h"
#include "token.h"

#include <map>
#include <memory>


using namespace std;

shared_ptr<Node> ParseCondition(std::istream& is);

void TestParseCondition();

void TestDatabase();