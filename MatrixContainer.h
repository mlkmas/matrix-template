#ifndef UNTITLED15_MATRIXCONTAINER_H
#define UNTITLED15_MATRIXCONTAINER_H

#include <iostream>
#include <stdexcept>
#include "Matrix.h"
#define INITIAL_CAPACITY 1

template<int rows=0 , int cols=0, class T=int >
class MatrixContainer
{
private:
Matrix<rows,cols,T> *array;
int containerSize;
int containerCapacity;


public:
    MatrixContainer();
    MatrixContainer(int capacity);
    ~MatrixContainer();
    MatrixContainer(const MatrixContainer &other);
    MatrixContainer<rows,cols,T>& operator=(const MatrixContainer &other);
    void addMatrix(const Matrix<rows, cols, T>& matrix);
    void removeLastMatrix();
    Matrix<rows, cols, T>& operator[](int index);
    friend std::ostream& operator<<(std::ostream& os, const MatrixContainer& container);
    int size() const;
    int capacity() const;
    void resizeArray();
    void shrinkArray();

};

template<int rows, int cols, class T>
MatrixContainer<rows, cols, T>::MatrixContainer() :containerSize(0),containerCapacity(INITIAL_CAPACITY)
{
    array = new Matrix<rows, cols, T>[containerCapacity];
}
template<int rows, int cols, class T>
MatrixContainer<rows, cols, T>::MatrixContainer(int capacity) :containerSize(0),containerCapacity(capacity)
{
    array = new Matrix<rows, cols, T>[containerCapacity];
}
template<int rows, int cols, class T>
MatrixContainer<rows, cols, T>::~MatrixContainer()
{
    for (int i = 0; i < containerSize;i++)
    {
        array[i].~Matrix();
    }
    delete[] array;
    containerCapacity=0;
    containerSize=0;
}
template<int rows, int cols, class T>
MatrixContainer<rows, cols, T>& MatrixContainer<rows, cols, T>::operator=(const MatrixContainer& other) {
    if (this != &other)
    {
        delete[] array;
        containerSize = other.containerSize;
        containerCapacity = other.containerCapacity;
        array = new Matrix<rows, cols, T>[containerCapacity];
        for (int i = 0; i < containerSize;i++)
        {
            array[i] = other.array[i]; //this use =operator of matrix class?
        }
    }
    return *this;
}
template<int rows, int cols, class T>
MatrixContainer<rows, cols, T>::MatrixContainer(const MatrixContainer& other)
:containerSize(other.containerSize),containerCapacity(other.containerCapacity)
{
    //do we have to delete this array first??
    array=new Matrix<rows, cols, T>[containerCapacity];
    for (int i=0;i<containerSize;i++)
    {
        array[i]=other.array[i];
    }
}
template<int rows, int cols, class T>
void MatrixContainer<rows, cols, T>::resizeArray()
{
    int newCapacity=containerCapacity*2;
    Matrix<rows,cols,T> *newArray=new Matrix<rows, cols, T>[newCapacity];
    for(int i=0;i<containerSize;i++)
    {
        newArray[i]=array[i]; //=operator of matrix class?
    }
   delete[] array;
    array=newArray;
    containerCapacity=newCapacity;

}
template<int rows, int cols, class T>
void MatrixContainer<rows, cols, T>::addMatrix(const Matrix<rows, cols, T>& matrix)
{
    if(containerSize==containerCapacity)
    {
        resizeArray();
    }
    array[containerSize] = matrix;
    containerSize++;
}
template<int rows, int cols, class T>
void MatrixContainer<rows, cols, T>::shrinkArray()
{
    int newCapacity=containerCapacity/2;
    Matrix<rows,cols,T> *newArray=new Matrix<rows, cols, T>[newCapacity];
    for(int i=0;i<containerSize;i++)
    {
        newArray[i]=array[i]; //=operator of matrix class?
    }
    delete[] array;
    array=newArray;
    containerCapacity=newCapacity;
}
template<int rows, int cols, class T>
void MatrixContainer<rows, cols, T>::removeLastMatrix()
{
    if(containerSize>0)
    {
        array[containerSize - 1].~Matrix();
        containerSize--;
    }
    if(containerSize<= (containerCapacity/4))
    {
        shrinkArray();
    }

}

template<int rows, int cols, class T>
Matrix<rows, cols, T>& MatrixContainer<rows, cols, T>::operator[](int index)
{
    if (index < 0 || index >= containerSize) {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

template<int rows, int cols, class T>
std::ostream& operator<<(std::ostream& os, const MatrixContainer<rows, cols, T>& container)
{
    os << "There are " << container.containerSize << " matrices in the container. The matrices:" << std::endl;
    for (int i=0;i< container.containerSize;i++)
    {
        os << container.array[i] << std::endl;
    }
    return os;
}
template<int rows, int cols, class T>
int MatrixContainer<rows,cols,T>::size() const
{
    return containerSize;
}
template<int rows, int cols, class T>
int MatrixContainer<rows,cols,T>::capacity() const
{
    return containerCapacity;
}




















#endif //UNTITLED15_MATRIXCONTAINER_H
