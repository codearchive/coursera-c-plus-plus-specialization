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
    bool Evaluate(const Date& date, const std::string& event) override { return true; };
};


class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& date)
        : cmp_(cmp), date_(date)
    {}

    bool Evaluate(const Date& date, const std::string& event) override {
        if (cmp_ == Comparison::Less ) {
            return date < date_;
        }
        if (cmp_ == Comparison::LessOrEqual) {
            return date < date_ || date == date_;
        }
        if (cmp_ == Comparison::Greater) {
            return date > date_;
        }
        if (cmp_ == Comparison::GreaterOrEqual) {
            return date > date_ || date == date_;
        }
        if (cmp_ == Comparison::Equal) {
            return date == date_;
        }
        if (cmp_ == Comparison::NotEqual) {
            return date != date_;
        }
        throw std::logic_error("Expected comparison operation");
    }
private:

    Comparison cmp_;
    Date date_;
};


class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const std::string& event)
        : cmp_(cmp), event_(event)
    {}

    bool Evaluate(const Date& date, const std::string& event) override {
        if (cmp_ == Comparison::Equal) {
            return event_ == event;
        }
        return event_ != event;
    }
private:
    Comparison cmp_;
    std::string event_;
};


class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& logical_operation, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
        : logical_operation_(logical_operation), left_(left), right_(right)
    {}

    bool Evaluate(const Date& date, const std::string& event) override {
        if (logical_operation_ == LogicalOperation::And) {
            return left_->Evaluate(date, event) && right_->Evaluate(date, event);
        }
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    }
private:
    LogicalOperation logical_operation_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
};