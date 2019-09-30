#pragma once

#include<string>
#include<memory>
#include<iostream>
#include "date.h"

enum class LogicalOperation {
	And, Or
};

enum class Comparison {
	Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual
};

template<class T>
bool compare(T lhs, T rhs, Comparison cmp);

class Node {
public:
	virtual bool Evaluate(const Date &date, const std::string &event) = 0;
	virtual ~Node() {
	}
	;
};

class EmptyNode: public Node {
public:
	bool Evaluate(const Date &date, const std::string &event) override;
};

class LogicalOperationNode: public Node {
private:
	const LogicalOperation _op;
	const std::shared_ptr<Node> _lhs, _rhs;
public:
	LogicalOperationNode(const LogicalOperation op, std::shared_ptr<Node> lhs,
			std::shared_ptr<Node> rhs) :
			_op(op), _lhs(lhs), _rhs(rhs) {
	}
	bool Evaluate(const Date &date, const std::string &event) override;
};

class DateComparisonNode: public Node {
private:
	const Comparison _cmp;
	const Date _date;
public:
	DateComparisonNode(const Comparison cmp, const Date date) :
			_cmp(cmp), _date(date) {
	}
	bool Evaluate(const Date &date, const std::string &event) override;
};

class EventComparisonNode: public Node {
private:
	const Comparison _cmp;
	const std::string _event;
public:
	EventComparisonNode(const Comparison cmp, const std::string &event) :
			_cmp(cmp), _event(event) {
	}
	bool Evaluate(const Date &date, const std::string &event) override;
};
