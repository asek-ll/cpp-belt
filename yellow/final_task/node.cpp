#include "node.h"

#include <iostream>

template<class T>
bool compare(T lhs, T rhs, Comparison cmp) {

	switch (cmp) {
	case Comparison::Equal:
		return lhs == rhs;
	case Comparison::Greater:
		return lhs > rhs;
	case Comparison::GreaterOrEqual:
		return lhs >= rhs;
	case Comparison::Less:
		return lhs < rhs;
	case Comparison::LessOrEqual:
		return lhs <= rhs;
	case Comparison::NotEqual:
		return lhs != rhs;
	default:
		return false;
	}

}

bool EmptyNode::Evaluate(const Date &date, const std::string &event) {
	return true;
}

bool LogicalOperationNode::Evaluate(const Date &date,
		const std::string &event) {
	switch (_op) {
	case LogicalOperation::And:
		return _lhs->Evaluate(date, event) && _rhs->Evaluate(date, event);
	case LogicalOperation::Or:
		return _lhs->Evaluate(date, event) || _rhs->Evaluate(date, event);
	default:
		return false;
	}
}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) {
	return compare(date, _date, _cmp);
}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) {
	return compare(event, _event, _cmp);
}
