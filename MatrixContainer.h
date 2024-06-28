//Student1 Noor Zerene ID 212015168
//Student2 Malak Masarwe ID 213622194


#ifndef UNTITLED15_MATRIXCONTAINER_H
#define UNTITLED15_MATRIXCONTAINER_H

#include <iostream>
#include <stdexcept>
#include "Matrix.h"
#define INITIAL_CAPACITY 1 // Define the initial capacity for the container

// Template class for MatrixContainer
template<int rows=0 , int cols=0, class T=int >
class MatrixContainer
{
private:
    Matrix<rows,cols,T> *array; // Pointer to an array of Matrix objects
    int containerSize; // Number of matrices currently in the container
    int containerCapacity; // Current capacity of the container


public:
    MatrixContainer(); // Default constructor
    MatrixContainer(int capacity); // Constructor with capacity parameter
    ~MatrixContainer();  // Destructor
    MatrixContainer(const MatrixContainer &other); // Copy constructor
    MatrixContainer<rows,cols,T>& operator=(const MatrixContainer &other); // Copy assignment operator
    void addMatrix(const Matrix<rows, cols, T>& matrix); // Method to add a matrix to the container
    void removeLastMatrix();  // Method to remove the last matrix from the container
    Matrix<rows, cols, T>& operator[](int index); // Overloaded subscript operator
    friend std::ostream& operator<<(std::ostream& os, const MatrixContainer& container)
    {
        os << "There are " << container.containerSize << " matrices in the container. The matrices:" << std::endl;
        for (int i=0;i< container.containerSize;i++)
        {
            os << container.array[i] << std::endl;  // Output each matrix
        }
        return os;
    }
    int size() const; // Method to get the size of the container
    int capacity() const; // Method to get the capacity of the container
    void resizeArray(); // Method to resize the array when it's full
    void shrinkArray(); // Method to shrink the array when it's too empty

};

// Default constructor
template<int rows, int cols, class T>
MatrixContainer<rows, cols, T>::MatrixContainer() :containerSize(0),containerCapacity(INITIAL_CAPACITY)
{
    array = new Matrix<rows, cols, T>[containerCapacity];
}

// Constructor with capacity parameter
template<int rows, int cols, class T>
MatrixContainer<rows, cols, T>::MatrixContainer(int capacity) :containerSize(0),containerCapacity(capacity)
{
    array = new Matrix<rows, cols, T>[containerCapacity];
}

// Destructor
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

// Copy assignment operator
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
            array[i] = other.array[i]; // Uses the assignment operator of the Matrix class
        }
    }
    return *this;
}
// Copy constructor
template<int rows, int cols, class T>
MatrixContainer<rows, cols, T>::MatrixContainer(const MatrixContainer& other)
        :containerSize(other.containerSize),containerCapacity(other.containerCapacity)
{

    array=new Matrix<rows, cols, T>[containerCapacity];

    for (int i=0;i<containerSize;i++)
    {
        array[i]=other.array[i];
    }
}

// Method to resize the array when it's full
template<int rows, int cols, class T>
void MatrixContainer<rows, cols, T>::resizeArray()
{
    int newCapacity=containerCapacity*2;
    Matrix<rows,cols,T> *newArray=new Matrix<rows, cols, T>[newCapacity];
    for(int i=0;i<containerSize;i++)
    {
        newArray[i]=array[i];
    }
    delete[] array;
    array=newArray;
    containerCapacity=newCapacity;

}
// Method to add a matrix to the container
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

// Method to shrink the array when it's too empty
template<int rows, int cols, class T>
void MatrixContainer<rows, cols, T>::shrinkArray()
{
    int newCapacity=containerCapacity/2;
    Matrix<rows,cols,T> *newArray=new Matrix<rows, cols, T>[newCapacity];
    for(int i=0;i<containerSize;i++)
    {
        newArray[i]=array[i]; //=operator of matrix class
    }
    delete[] array;
    array=newArray;
    containerCapacity=newCapacity;
}

// Method to remove the last matrix from the container
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

// Overloaded subscript operator
template<int rows, int cols, class T>
Matrix<rows, cols, T>& MatrixContainer<rows, cols, T>::operator[](int index)
{
    if (index < 0 || index >= containerSize) {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

// Method to get the size of the container
template<int rows, int cols, class T>
int MatrixContainer<rows,cols,T>::size() const
{
    return containerSize;
}

// Method to get the capacity of the container
template<int rows, int cols, class T>
int MatrixContainer<rows,cols,T>::capacity() const
{
    return containerCapacity;
}










#endif //UNTITLED15_MATRIXCONTAINER_H
