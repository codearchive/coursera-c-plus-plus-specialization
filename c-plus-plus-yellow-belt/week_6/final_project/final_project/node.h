#pragma once
#include "date.h"

#include <memory>
#include <string>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const std::string& event) override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const std::string& event) override;
private:
    Comparison cmp_;
    Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const std::string& event);
    bool Evaluate(const Date& date, const std::string& event) override;
private:
    Comparison cmp_;
    std::string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& logical_operation,
        const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right);
    bool Evaluate(const Date& date, const std::string& event) override;
private:
    LogicalOperation logical_operation_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
};