#ifndef __MATRIX_STACK_H
#define __MATRIX_STACK_H

#include "mat4.h"
#include <stack>

//holds matrices and can popped and pushed to the top
template<typename type>
class MatrixStack
{
public:
    MatrixStack();
    virtual ~MatrixStack();

    //adds a matrix to the top of the matrix stack
    void PushMatrix(const mat4<type>& t);
    //adds a matrix to the top of the matrix stack
    void PushMatrix(const mat4<type>&& t);

    //multiplies the top matrix and push the new one onto the stack
    void Multiply(const mat4<type>& t);
    //mutliplies the top matrix and pushes the new one onto the stack
    void Multiply(const mat4<type>&& t);
    //clear the stack down to the identity matrix
    void Clear();
    //get the top matrix
    mat4<type>& Top();

    //pop the top matrix
    void Pop();

    //returns the size of the stack
    unsigned int Size();

private:
    std::stack<mat4<type>> m_MatrixStack;
};


template<typename type>
MatrixStack<type>::MatrixStack()
{
    m_MatrixStack.emplace();
}

template<typename type>
MatrixStack<type>::~MatrixStack()
{

}

//adds a matrix to the top of the matrix stack
template<typename type>
void MatrixStack<type>::PushMatrix(const mat4<type>& t)
{
    m_MatrixStack.push(t);
}
//adds a matrix to the top of the matrix stack
template<typename type>
void MatrixStack<type>::PushMatrix(const mat4<type>&& t)
{
    m_MatrixStack.push(t);
}

//multiplies the top matrix and push the new one onto the stack
template<typename type>
void MatrixStack<type>::Multiply(const mat4<type>& t)
{
	if (!m_MatrixStack.empty())
	{
		m_MatrixStack.push(m_MatrixStack.top() * t);
	}
	else
	{
		m_MatrixStack.push(t);
	}
}
//mutliplies the top matrix and pushes the new one onto the stack
template<typename type>
void MatrixStack<type>::Multiply(const mat4<type>&& t)
{
	if (!m_MatrixStack.empty())
	{
		m_MatrixStack.push(m_MatrixStack.top() * t);
	}
	else
	{
		m_MatrixStack.push(t);
	}
}
//clear the stack down to the identity matrix
template<typename type>
void MatrixStack<type>::Clear()
{
    for (int i = 0; i < m_MatrixStack.size(); i++)
    {
        m_MatrixStack.pop();
    }
    m_MatrixStack.emplace();
}
//get the top matrix
template<typename type>
mat4<type>& MatrixStack<type>::Top()
{
    return m_MatrixStack.top();
}

//pop the top matrix
template<typename type>
void MatrixStack<type>::Pop()
{
    m_MatrixStack.pop();
}

//returns the size of the stack
template<typename type>
unsigned int MatrixStack<type>::Size()
{
    return m_MatrixStack.size();
}

using MatrixStackf = MatrixStack < float > ;
using MatrixStackd = MatrixStack < double >;

#endif //__MATRIX_STACK_H