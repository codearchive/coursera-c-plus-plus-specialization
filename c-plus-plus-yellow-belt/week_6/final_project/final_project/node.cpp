#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
    : cmp_(cmp), date_(date)
{}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) {
    if (cmp_ == Comparison::Less) {
        return date < date_;
    }
    if (cmp_ == Comparison::LessOrEqual) {
        return date <= date_;
    }
    if (cmp_ == Comparison::Greater) {
        return date > date_;
    }
    if (cmp_ == Comparison::GreaterOrEqual) {
        return date >= date_;
    }
    if (cmp_ == Comparison::Equal) {
        return date == date_;
    }
    if (cmp_ == Comparison::NotEqual) {
        return date != date_;
    }
    throw std::logic_error("Expected comparison operation");
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const std::string& event)
    : cmp_(cmp), event_(event)
{}

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

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation,
                                           const std::shared_ptr<Node>& left,
                                           const std::shared_ptr<Node>& right)
    : logical_operation_(logical_operation), left_(left), right_(right)
{}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) {
    if (logical_operation_ == LogicalOperation::And) {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
    return left_->Evaluate(date, event) || right_->Evaluate(date, event);
}