#include "condition_parser.h"


using namespace std;

template <class It> shared_ptr<Node> ParseComparison(It& current, It end) {
    if (current == end) {
        throw logic_error("Expected column name: date or event");
    }

    Token& column = *current;
    if (column.type != TokenType::COLUMN) {
        throw logic_error("Expected column name: date or event");
    }
    ++current;

    if (current == end) {
        throw logic_error("Expected comparison operation");
    }

    Token& op = *current;
    if (op.type != TokenType::COMPARE_OP) {
        throw logic_error("Expected comparison operation");
    }
    ++current;

    if (current == end) {
        throw logic_error("Expected right value of comparison");
    }

    Comparison cmp;
    if (op.value == "<") {
        cmp = Comparison::Less;
    }
    else if (op.value == "<=") {
        cmp = Comparison::LessOrEqual;
    }
    else if (op.value == ">") {
        cmp = Comparison::Greater;
    }
    else if (op.value == ">=") {
        cmp = Comparison::GreaterOrEqual;
    }
    else if (op.value == "==") {
        cmp = Comparison::Equal;
    }
    else if (op.value == "!=") {
        cmp = Comparison::NotEqual;
    }
    else {
        throw logic_error("Unknown comparison token: " + op.value);
    }

    const string& value = current->value;
    ++current;

    if (column.value == "date") {
        istringstream is(value);
        return make_shared<DateComparisonNode>(cmp, ParseDate(is));
    }
    else {
        return make_shared<EventComparisonNode>(cmp, value);
    }
}

template <class It>
shared_ptr<Node> ParseExpression(It& current, It end, unsigned precedence) {
    if (current == end) {
        return shared_ptr<Node>();
    }

    shared_ptr<Node> left;

    if (current->type == TokenType::PAREN_LEFT) {
        ++current; // consume '('
        left = ParseExpression(current, end, 0u);
        if (current == end || current->type != TokenType::PAREN_RIGHT) {
            throw logic_error("Missing right paren");
        }
        ++current; // consume ')'
    }
    else {
        left = ParseComparison(current, end);
    }

    const map<LogicalOperation, unsigned> precedences = {
        {LogicalOperation::Or, 1}, {LogicalOperation::And, 2}
    };

    while (current != end && current->type != TokenType::PAREN_RIGHT) {
        if (current->type != TokenType::LOGICAL_OP) {
            throw logic_error("Expected logic operation");
        }

        const auto logical_operation = current->value == "AND" ? LogicalOperation::And
            : LogicalOperation::Or;
        const auto current_precedence = precedences.at(logical_operation);
        if (current_precedence <= precedence) {
            break;
        }

        ++current; // consume op

        left = make_shared<LogicalOperationNode>(
            logical_operation, left, ParseExpression(current, end, current_precedence)
            );
    }

    return left;
}

shared_ptr<Node> ParseCondition(istream& is) {
    auto tokens = Tokenize(is);
    auto current = tokens.begin();
    auto top_node = ParseExpression(current, tokens.end(), 0u);

    if (!top_node) {
        top_node = make_shared<EmptyNode>();
    }

    if (current != tokens.end()) {
        throw logic_error("Unexpected tokens after condition");
    }

    return top_node;
}

Date ParseDate(istream& is) {
    string input_date;
    is >> input_date;
    auto it_1 = find(input_date.begin(), input_date.end(), '-');
    string year;
    copy(input_date.begin(), it_1, back_inserter(year));
    auto it_2 = find(++it_1, input_date.end(), '-');
    string month;
    copy(it_1, it_2, back_inserter(month));
    string day;
    copy(++it_2, input_date.end(), back_inserter(day));
    return Date(stoi(year), stoi(month), stoi(day));
}
