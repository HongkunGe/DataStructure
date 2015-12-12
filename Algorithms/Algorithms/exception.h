#pragma once
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
using namespace std;

class notFoundException : public exception {
	virtual const char* what() const throw() {
		return "not found!";
	};
} notFound;

#endif