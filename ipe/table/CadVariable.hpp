/*!	
	\file    CadVariable.hpp
	\brief   Declaration of CadVariable class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _CADVARIABLE_HPP_
#define _CADVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class CadVariable
  \brief Definition of atributes and methods of CadVariable class
  \note  CadVariable Class publicly inherits from Variable class
*/
class CadVariable:public lp::Variable
{
/*!		
\name Private atributes of CadVariable class
*/
	private:
		std::string _value;   //!< \brief string value of the CadVariable

/*!		
\name Public methods of CadVariable class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Variable's constructor as members initializer
	\param name: name of the CadVariable
	\param token: token of the CadVariable
	\param type: type of the CadVariable
	\param value: string value of the CadVariable
	\pre   None
	\post  A new CadVariable is created with the values of the parameters
	\sa   setName, setValue
*/
	inline CadVariable(std::string name="", int token = 0, int type = 0, std::string value=""): Variable(name,token,type)
	{
		this->setValue(value);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param n: object of CadVariable class
	\pre   None
	\post  A new CadVariable is created with the values of an existent CadVariable
	\sa    setName, setValue
*/
	CadVariable(const CadVariable & n)
	{
		// Inherited methods
		this->setName(n.getName());

		this->setToken(n.getToken());

		this->setType(n.getType());
		
		// Own method
		this->setValue(n.getValue());
	}


/*!	
	\name Observer
*/
	
/*!	
	\brief  Public method that returns the value of the CadVariable
	\note   Función inline
	\pre    None
	\post   None
    \return Value of the CadVariable
	\sa		getValue
*/
	inline std::string getValue() const
	{
		return this->_value;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This functions modifies the value of the CadVariable
	\note    Inline function
	\param   value: new value of the CadVariable
	\pre     None
	\post    The value of the CadVariable is equal to the parameter 
	\return  void
	\sa 	 setValue
*/
	inline void setValue(const std::string & value)
	{
	    this->_value = value;
	}



		
/*!	
	\name I/O Functions
*/
		
/*!		
	\brief Read a CadVariable
	\pre   None
	\post  The atributes of the CadVariable are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write a CadVariable
	\pre   None
	\post  None
    \sa    read
*/
	void write() const;

	CadVariable &operator=(const CadVariable &n);

	friend std::istream &operator>>(std::istream &i, CadVariable &n);

	friend std::ostream &operator<<(std::ostream &o, CadVariable const &n);
/*!	
	\name Operators
*/
	//CadVariable &operator||(const CadVariable &n, const CadVariable &m);
	
// End of CadVariable class
};

// End of name space lp
}

// End of _CadVariable_HPP_
#endif
