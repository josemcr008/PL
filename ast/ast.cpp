/*!
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author
	\date    2018-12-13
	\version 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

// Para usar la funciones pow y std::abs
#include <cmath>

#include "ast.hpp"

#include "../table/table.hpp"

// warning
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

//
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"
#include "../table/CadVariable.hpp"

#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

#include "../parser/interpreter.tab.h"



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST *root; //!< Reference to the object at the base of the AST


///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::CadNode::getType()
{
	return CADENA;
}


void lp::CadNode::print()
{
  std::cout << "CadNode: " << this->_id;
  std::cout << " (Type: " << this->getType() << ")" << std::endl;
}


std::string lp::CadNode::evaluateCad()
{
/*	std::string value = "";
	if (this->getType() == CADENA)
	{
		// Get the identifier in the table of symbols as NumericVariable

		lp::CadVariable *var = (lp::CadVariable *) table.getSymbol(this->_id);
		value = var->getValue();

		// Copy the value of the NumericVariable

	}
	else
	{
		warning("Runtime error in evaluateNumber(): the variable is not string",
				   this->_id);
	}

	// Return the value of the NumericVariable

	return value;
	*/
	   return this->_id;

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::VariableNode::getType()
{
	// Get the identifier in the table of symbols as Variable
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Return the type of the Variable
	return var->getType();
}


void lp::VariableNode::print()
{
  std::cout << "VariableNode: " << this->_id;
  std::cout << " (Type: " << this->getType() << ")" << std::endl;
}


double lp::VariableNode::evaluateNumber()
{
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::NumericVariable *var = (lp::NumericVariable *) table.getSymbol(this->_id);

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{
		warning("Runtime error in evaluateNumber(): the variable is not numeric",
				   this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}


bool lp::VariableNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::LogicalVariable *var = (lp::LogicalVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Runtime error in evaluateBool(): the variable is not boolean",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}
std::string lp::VariableNode::evaluateCad()
{
	std::string result = "";

	if (this->getType() == CADENA)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::CadVariable *var = (lp::CadVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Runtime error in evaluateCad(): the variable is not string",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConstantNode::print()
{
  std::cout << "ConstantNode: " << this->_id;
  std::cout << " (Type: " << this->getType() << ")" << std::endl;
}

int lp::ConstantNode::getType()
{
	// Get the identifier in the table of symbols as Constant
	lp::Constant *var = (lp::Constant *) table.getSymbol(this->_id);

	// Return the type of the Constant
	return var->getType();
}


double lp::ConstantNode::evaluateNumber()
{
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericConstant
		lp::NumericConstant *constant = (lp::NumericConstant *) table.getSymbol(this->_id);

		// Copy the value of the NumericConstant
		result = constant->getValue();
	}
	else
	{
		warning("Runtime error in evaluateNumber(): the constant is not numeric",
				   this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}

bool lp::ConstantNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalConstant
		lp::LogicalConstant *constant = (lp::LogicalConstant *) table.getSymbol(this->_id);

		// Copy the value of the LogicalConstant
		result = constant->getValue();
	}
	else
	{
		warning("Runtime error in evaluateBool(): the constant is not boolean",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::NumberNode::getType()
{
	return NUMBER;
}


void lp::NumberNode::print()
{
  std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluateNumber()
{
    return this->_number;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::NumericUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == NUMBER)
	{
		result = NUMBER;
	}
	else
	{
		warning("Runtime error: incompatible types for", "Numeric Unary Operator");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == BOOL)
	{
		result = BOOL;
	}
	else
	{
		warning("Runtime error: incompatible types for", "Logical Unary Operator");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
	int result = 0;

	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = NUMBER;
	else
		warning("Runtime error: incompatible types for", "Numeric Operator");

	return	result;
}

int lp::StringOperatorNode::getType()
{
	int result = 0;

	if ( (this->_left->getType() == CADENA) and (this->_right->getType() == CADENA))
		result = CADENA;
	else
		warning("Runtime error: incompatible types for", "String Operator");

	return	result;
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::RelationalOperatorNode::getType()
{
	int result = 0;

	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = BOOL;
	else if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
		result = BOOL;
	else
		warning("Runtime error: incompatible types for", "Relational Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode:: getType()
{
	int result = 0;

	if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
	{
		//
		result = BOOL;
	}
	else
		warning("Runtime error: incompatible types for", "Logical Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::print()
{
  std::cout << "UnaryMinusNode: -"  << std::endl;
  std::cout << "\t";
  this->_exp->print();
}

double lp::UnaryMinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Minus
		result = - this->_exp->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "UnaryMinus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::print()
{
  std::cout << "UnaryPlusNode: +"  << std::endl;
  std::cout << "\t";
  this->_exp->print();
}

double lp::UnaryPlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		result = this->_exp->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ","UnaryPlus");
	}

  return result;
}

/////////////////////////////////////////

void lp::Plus_unoNode::print()
{
  std::cout << "Plus_unoNode: ++"  << std::endl;
  std::cout << "\t";
  this->_exp->print();
}

double lp::Plus_unoNode::evaluateNumber()
{
	double result = 0.0;
	if (this->getType() == NUMBER)
	{
		result = this->_num->evaluateNumber();
	}

  return result++;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::print()
{
  std::cout << "PlusNode: +"  << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

double lp::PlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() + this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "Plus");
	}

  return result;
}

void lp::ConcatNode::print()
{
  std::cout << "ConcatNode: +"  << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

std::string lp::ConcatNode::evaluateCad()
{
	std::string result = "";

	// Ckeck the types of the expressions
	if (this->getType() == CADENA)
	{
		result = this->_left->evaluateCad() + this->_right->evaluateCad();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "Plus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::print()
{
  std::cout << "MinusNode: -"  << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

double lp::MinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() - this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "Minus");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::print()
{
  std::cout << "MultiplicationNode: *"  << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

double lp::MultiplicationNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() * this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ","Multiplication");
	}

  return result;
}




void lp::PotenciaNode::print()
{
  std::cout << "PotenciaNode: **"  << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

double lp::PotenciaNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = pow(this->_left->evaluateNumber(),this->_right->evaluateNumber());
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ","Potencia");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::print()
{
  std::cout << "DivisionNode: /" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

double lp::DivisionNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				result = leftNumber / rightNumber;
		}
		else
		{
			warning("Runtime error", "Division by zero");
		}
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Division");
	}

  return result;
}

void lp::DivisionEnteraNode::print()
{
  std::cout << "DivisionEnteraNode: /" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

double lp::DivisionEnteraNode::evaluateNumber()
{
	int result = 0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		int leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				result = leftNumber / rightNumber;
		}
		else
		{
			warning("Runtime error", "Division by zero");
		}
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Division");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::print()
{
  std::cout << "ModuloNode: %" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

double lp::ModuloNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

    	if(std::abs(rightNumber) > ERROR_BOUND)
				result = (int) leftNumber % (int) rightNumber;
		else
			warning("Runtime error", "Division by zero");
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Modulo");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::print()
{
  std::cout << "PowerNode: ^"  << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

double lp::PowerNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = pow(this->_left->evaluateNumber(), this->_right->evaluateNumber());
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Power");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::BuiltinFunctionNode_0::getType()
{
	return	NUMBER;
}


void lp::BuiltinFunctionNode_0::print()
{
  std::cout << "BuiltinFunctionNode_0: "  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
}

double lp::BuiltinFunctionNode_0::evaluateNumber()
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *) table.getSymbol(this->_id);

	// Apply the function and copy the result
   	return f->getFunction()();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
	int result = 0;

	if (this->_exp->getType() == NUMBER)
		result = NUMBER;
	else
		warning("Runtime error: incompatible type for", "BuiltinFunctionNode_1");

	return	result;
}

void lp::BuiltinFunctionNode_1::print()
{
  std::cout << "BuiltinFunctionNode_1: "  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";
	this->_exp->print();
	std::cout << std::endl;
}

double lp::BuiltinFunctionNode_1::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter1
		lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol( this->_id);

		// Apply the function to the parameter and copy the result
		result = f->getFunction()(this->_exp->evaluateNumber());
	}
	else
	{
		warning("Runtime error: incompatible type of parameter for ", this->_id);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_2::getType()
{
	int result = 0;

	if (this->_exp1->getType() == this->_exp2->getType())
		result = this->_exp1->getType();
	else
		warning("Runtime error: incompatible types for", "BuiltinFunctionNode_2");

	return	result;
}


void lp::BuiltinFunctionNode_2::print()
{
  std::cout << "BuiltinFunctionNode_2: " << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";
  this->_exp1->print();
  std::cout << "\t";
	this->_exp2->print();
	std::cout << std::endl;
}

double lp::BuiltinFunctionNode_2::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter2
		lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *) table.getSymbol(this->_id);

		// Apply the function to the parameters and copy the result
	  	result = f->getFunction()(this->_exp1->evaluateNumber(),this->_exp2->evaluateNumber());
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", this->_id);
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::print()
{
  std::cout << "GreaterThanNode: >" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

bool lp::GreaterThanNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber > rightNumber);
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Greater than");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::print()
{
  std::cout << "GreaterOrEqualNode: >= " << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

bool lp::GreaterOrEqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber >= rightNumber);
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Greater or equal than");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::print()
{
  std::cout << "LessThanNode: <" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

bool lp::LessThanNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber < rightNumber);
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Less than");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::print()
{
  std::cout << "LessOrEqualNode: <=" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

bool lp::LessOrEqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber <= rightNumber);
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Less or equal than");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::print()
{
  std::cout << "EqualNode: ==" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

bool lp::EqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		switch(this->_left->getType()){
			case NUMBER:
				double leftNumber, rightNumber;
				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = ( std::abs(leftNumber - rightNumber) < ERROR_BOUND );
			break;
			case BOOL:
				bool leftBoolean, rightBoolean;
				leftBoolean = this->_left->evaluateBool();
				rightBoolean = this->_right->evaluateBool();

				//
				result = (leftBoolean == rightBoolean);
				break;
		  default:
				warning("Runtime error: incompatible types of parameters for ",
								"Equal operator");
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ",
						"Equal operator");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::print()
{
  std::cout << "NotEqualNode: !=" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

bool lp::NotEqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		switch(this->_left->getType()){
			case NUMBER:
				double leftNumber, rightNumber;
				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = ( std::abs(leftNumber - rightNumber) >= ERROR_BOUND );
			break;
			case BOOL:
				bool leftBoolean, rightBoolean;
				leftBoolean = this->_left->evaluateBool();
				rightBoolean = this->_right->evaluateBool();

				//
				result = (leftBoolean != rightBoolean);
				break;
		  default:
				warning("Runtime error: incompatible types of parameters for ",
								"Not Equal operator");
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "Not Equal operator");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::print()
{
  std::cout << "AndNode: &&" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

bool lp::AndNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool and rightBool;
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator And");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::print()
{
  std::cout << "OrNode: ||" << std::endl;
  std::cout << "\t";
	this->_left->print();
	std::cout << "\t";
	this->_right->print();
}

bool lp::OrNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool or rightBool;
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Or");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::print()
{
  std::cout << "NotNode: !" << std::endl;
  std::cout << "\t";
  this->_exp->print();
}

bool lp::NotNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		result = not this->_exp->evaluateBool();
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Not");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::print()
{
  std::cout << "assignment_node: ="  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::AssignmentStmt::evaluate()
{
	/* Get the identifier in the table of symbols as Variable */
	/*
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{

		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable
					// with the type NUMBER and the value
					lp::NumericVariable *v = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,value);
					table.installSymbol(v);
				}
			}
			break;

			case BOOL:
			{
				bool value;
				// evaluate the expression as BOOL
			 	value = this->_exp->evaluateBool();

				if (firstVar->getType() == BOOL)
				{
				  	// Get the identifier in the table of symbols as LogicalVariable
					lp::LogicalVariable *v = (lp::LogicalVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not BOOL
				else
				{
					// Delete the variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable
					// with the type BOOL and the value
					lp::LogicalVariable *v = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,value);
					table.installSymbol(v);
				}
			}
			break;

			case CADENA:
			{

				std::string value;

				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateCad();
				// Check the type of the first varible
				if (firstVar->getType() == CADENA)
				{
				  	// Get the identifier in the table of symbols as NumericVariable

					lp::CadVariable *v = (lp::CadVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols
					table.eraseSymbol(this->_id);
					// Insert the variable in the table of symbols as NumericVariable
					// with the type NUMBER and the value
					lp::CadVariable *v = new lp::CadVariable(this->_id,
											VARIABLE,CADENA,value);
					table.installSymbol(v);
				}
			}
			break;
			default:
				warning("Runtime error: incompatible type of expression for ", "Assigment");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else // this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->_id);

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the first variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable
					// with the type NUMBER and the value of the previous variable
					lp::NumericVariable *firstVar = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case BOOL:
			{
				/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
				lp::LogicalVariable *secondVar = (lp::LogicalVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == BOOL)
				{
				/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
				lp::LogicalVariable *firstVar = (lp::LogicalVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not BOOL
				else
				{
					// Delete the first variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable
					// with the type BOOL and the value of the previous variable
					lp::LogicalVariable *firstVar = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case CADENA:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::CadVariable *secondVar = (lp::CadVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == CADENA)
				{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::CadVariable *firstVar = (lp::CadVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not CADENA
				else
				{
					// Delete the first variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable
					// with the type CADENA and the value of the previous variable
					lp::CadVariable *firstVar = new lp::CadVariable(this->_id,
											VARIABLE,CADENA,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;
			default:
				warning("Runtime error: incompatible type of expression for ", "Assigment");
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::print()
{
  std::cout << "PrintStmt: print"  << std::endl;
  std::cout << "\t";
  this->_exp->print();
  std::cout << std::endl;
}


void lp::PrintStmt::evaluate()
{
	std::string aux;
	int i=0;

	if(this->_exp->getType()==CADENA)
		aux=this->_exp->evaluateCad();

	switch(this->_exp->getType())
	{
		case NUMBER:
				std::cout << this->_exp->evaluateNumber() << std::endl;
				break;
		case BOOL:
			if (this->_exp->evaluateBool())
				std::cout << "true" << std::endl;
			else
				std::cout << "false" << std::endl;
				break;

		case CADENA:
				while(i<(int)aux.length()){
					if(aux[i]==(char)92 && aux[i+1]== (char)110){
						std::cout << std::endl;
						i+=2;
					}
					else if (aux[i]==(char)92 && aux[i+1]== (char)116){
						std::cout << "    ";
						i+=2;
					}

					else if (aux[i]==(char)92 && aux[i+1]==(char)39)
					{
						std::cout<<"'";
						i+=2;
					}

					else {
						std::cout << aux[i];
						i++;
					}
				}
				break;
		default:
			warning("Runtime error: incompatible type for ", "print");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::print()
{
  std::cout << "ReadStmt: read"  << std::endl;
  std::cout << "\t";
  std::cout << this->_id;
  std::cout << std::endl;
}


void lp::ReadStmt::evaluate()
{
	double value;

	std::cin >> value;
	std::cin.ignore();


	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is NUMBER
	if (var->getType() == NUMBER)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable
		// with the type NUMBER and the read value
		lp::NumericVariable *n = new lp::NumericVariable(this->_id,
									  VARIABLE,NUMBER,value);

		table.installSymbol(n);
	}
}

void lp::ReadStringStmt::print()
{
  std::cout << "ReadStringStmt: read"  << std::endl;
  std::cout << "\t";
  std::cout << std::endl;
}
void lp::ReadStringStmt::evaluate()
{
	std::string value;
	//std::cin >> value;
	std::getline(std::cin,value);

	/* Get the identifier in the table of symbols as Variable */
	lp::CadVariable *var = (lp::CadVariable *) table.getSymbol(this->_id);
	// Check if the type of the variable is NUMBER
	if (var->getType() == CADENA)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::CadVariable *n = (lp::CadVariable *) table.getSymbol(this->_id);
		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable
		// with the type NUMBER and the read value
		lp::CadVariable *n = new lp::CadVariable(this->_id,
									  VARIABLE,CADENA,value);

		table.installSymbol(n);
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::print()
{
  std::cout << "EmptyStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate()
{
  // Empty
}


///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LugarStmt::print()
{
  std::cout << "LugarStmt "  << std::endl;
}

void lp::LugarStmt::evaluate()
{
	PLACE((int)this->_exp1->evaluateNumber()+1, (int)this->_exp2->evaluateNumber());

}
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::IfStmt::print()
{

  std::cout << "IfStmt: "  << std::endl;


}


void lp::IfStmt::evaluate()
{
   // If the condition is true,
	if (this->_cond->evaluateBool() == true )
	{
		std::list<Statement *>::iterator stmtIter;

		for (stmtIter = this->_stmt1->begin(); stmtIter != this->_stmt1->end(); stmtIter++)
		{
			(*stmtIter)->evaluate();
		}
	}
     // the consequent is run

    // Otherwise, the alternative is run if exists

	else if (this->_stmt2!=NULL)
	{
		std::list<Statement *>::iterator stmtIter;

		for (stmtIter = this->_stmt2->begin(); stmtIter != this->_stmt2->end(); stmtIter++)
		{
			(*stmtIter)->evaluate();
		}
	}


}

///////////////////////////////////////////////////////////////////////////////////////////////
void lp::ForStmt::print()
{

  std::cout << "ForStmt: "  << std::endl;

}

void lp::ForStmt::evaluate()
{
    NumericVariable * from = new NumericVariable("__f__",VARIABLE,NUMBER,this->_from->evaluateNumber());
    NumericVariable * until = new NumericVariable("__u__",VARIABLE,NUMBER,this->_until->evaluateNumber());
    NumericVariable * pass;

    if(this->_pass!=NULL){
        pass = new NumericVariable("__s__",VARIABLE,NUMBER,this->_pass->evaluateNumber());

				if(this->_pass->evaluateNumber()==0)
				{
					std::cout<<" !!Bucle infinito!! >> Paso se ha cambiado a 1\n";
					pass = new NumericVariable("__s__",VARIABLE,NUMBER,1);
				}
			}
    else{
        pass = new NumericVariable("__s__",VARIABLE,NUMBER,1);

			}
    lp::NumericVariable *v;
   if (table.lookupSymbol(this->_id) == true)
       table.eraseSymbol(this->_id);



    v = new lp::NumericVariable(this->_id,VARIABLE,NUMBER,from->getValue());
    table.installSymbol(v);



  while (from->getValue() <= until->getValue())
  {

      v->setValue(from->getValue());

      std::list<Statement *>::iterator stmtIter;

      for (stmtIter = this->_stmt->begin(); stmtIter != this->_stmt->end(); stmtIter++)
      {
         (*stmtIter)->evaluate();


      }
      from->setValue(from->getValue() + pass->getValue());
  }

}
///////////////////////////////////////////////////////////////////////////////////////////////
void lp::CasosStmt::print()
{
  std::cout << "CaseStmt: "  << std::endl;
  // Condition
  std::cout << "\t";


  std::cout << std::endl;
}


void lp::CasosStmt::evaluate(double valor)
{
	//VALUE
	if(this->_type == 0){
		if(this->_exp->evaluateNumber() == valor){

			std::list<Statement *>::iterator stmtIter;

			for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++)
			{
				(*stmtIter)->evaluate();

			}
		}
		else
	  		this->_valores->evaluate(valor);

	}


	//DEFECT
	if(this->_type == 1){
		std::list<Statement *>::iterator stmtIter;

	  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++)
	  {
	     (*stmtIter)->evaluate();

	  }
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
void lp::SwitchStmt::print()
{
  std::cout << "SwitchStmt: "  << std::endl;
  // Condition
  std::cout << "\t";


  this->_exp->print();

  std::cout << std::endl;
}


void lp::SwitchStmt::evaluate()
{
  // While the condition is true. the body is run

	 this->_valores->evaluate(this->_exp->evaluateNumber());


}
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::WhileStmt::print()
{
  std::cout << "WhileStmt: "  << std::endl;
  // Condition
	/*  std::cout << "\t";
  this->_cond->print();

  // Body of the while loop
  std::cout << "\t";
  this->_stmt->print();

  std::cout << std::endl;*/
}


void lp::WhileStmt::evaluate()
{
  // While the condition is true. the body is run
  while (this->_cond->evaluateBool() == true)
  {
		std::list<Statement *>::iterator stmtIter;

		for (stmtIter = this->_stmt->begin(); stmtIter != this->_stmt->end(); stmtIter++)
		{
			(*stmtIter)->evaluate();
		}
  }

}


////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::RepetirStmt::print()
{
  std::cout << "RepetirStmt: "  << std::endl;
  // Condition
  /*std::cout << "\t";
  this->_cond->print();

  // Body of the loop
  std::cout << "\t";
  this->_stmt->print();

  std::cout << std::endl;*/
}


void lp::RepetirStmt::evaluate()
{
  do
  {
		std::list<Statement *>::iterator stmtIter;

		for (stmtIter = this->_stmt->begin(); stmtIter != this->_stmt->end(); stmtIter++)
		{
			(*stmtIter)->evaluate();
		}
  }
  while (this->_cond->evaluateBool() == false);

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BorrarStmt::print()
{
  std::cout << "BorrarStmt: "  << std::endl;

  std::cout << std::endl;
}


void lp::BorrarStmt::evaluate()
{
  // While the condition is true. the body is run

	std::cout<<CLEAR_SCREEN;


}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::BlockStmt::print()
{
  std::list<Statement *>::iterator stmtIter;

  std::cout << "BlockStmt: "  << std::endl;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++)
  {
     (*stmtIter)->print();
  }
}


void lp::BlockStmt::evaluate()
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++)
  {
    (*stmtIter)->evaluate();
  }
}





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AST::print()
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++)
  {
     (*stmtIter)->print();
  }
}



void lp::AST::evaluate()
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++)
  {
    (*stmtIter)->evaluate();
  }
}
