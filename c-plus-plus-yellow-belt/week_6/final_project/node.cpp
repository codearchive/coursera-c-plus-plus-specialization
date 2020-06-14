#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) {
    return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) {
    if (cmp_ == Comparison::Less) {
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

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) {
    if (cmp_ == Comparison::Less) {
        return event < event_;
    }
    if (cmp_ == Comparison::LessOrEqual) {
        return event < event_ || event == event_;
    }
    if (cmp_ == Comparison::Greater) {
        return event > event_;
    }
    if (cmp_ == Comparison::GreaterOrEqual) {
        return event > event_ || event == event_;
    }
    if (cmp_ == Comparison::Equal) {
        return event == event_;
    }
    if (cmp_ == Comparison::NotEqual) {
        return event != event_;
    }
    throw std::logic_error("Expected comparison operation");
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) {
    if (logical_operation_ == LogicalOperation::And) {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
    return left_->Evaluate(date, event) || right_->Evaluate(date, event);
}