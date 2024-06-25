#include <iostream>
#include <cfloat>
#include <stdexcept>

template<int rows=0, int cols=0, class T=int >
class Matrix
{
private:
    int rowsSize;
    int colsSize;
    T** data;
public:
    Matrix();//constructor
    Matrix(T value);//constructor with initial value
    ~Matrix();//destructor
    Matrix(const Matrix& other);//copy cstr
    Matrix<rows,cols,T>& operator=(const Matrix<rows,cols,T>& other);//assignment operator

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    void allocateData(int,int);//since allocateData is void do we have to write this.allocate or to make it reurn data?
    void fillData(int value,int ,int );//since fill is void do we have to write this.fill or to make it reurn data?
    void copyData(T** dataTocopy, T** matData,int row,int col);

    T* getDiag(int &num);//return the diag of the mat
    Matrix<rows,cols,T> getIdentityMatrix();


    Matrix<rows,cols,T> operator+(const T& scalar);//mat+scalar
    Matrix<rows,cols,T> operator-(const T& scalar);
    Matrix<rows,cols,T> operator-(double scalar);//mat-scalar
    Matrix<rows,cols,T> operator*(const T& scalar);//mat*scalar

    Matrix<rows, cols, T> operator+(const Matrix<rows, cols, T>& mat1); //mat+mat
    Matrix<rows, cols, T> operator-(const Matrix<rows, cols, T>& other) const;//mat-mat
    Matrix<rows, cols, double> operator-(const Matrix<rows, cols, double>& other) ;//mat-mat


    Matrix<rows,cols,T>& operator++();//prefix ++mat
    const Matrix<rows,cols,T> operator++(int);//postfix mat++

    Matrix<rows,cols,T>& operator--();//prefix --mat
    const Matrix<rows,cols,T> operator--(int);//postfix mat--


    Matrix<rows, cols, T> operator-() const; // -mat


    T rowColMultipy(int row,int col,const Matrix<rows, cols, T> &other);



    Matrix<rows, cols, T> operator*(const Matrix<rows, cols, T>& other) const;//mat*mat

    T& operator()(int row, int col);//op()modify a specific cell
    const T& operator()(int row, int col)const; //const op()version

   // template<typename U> operator U() const;//return trace sum
    bool operator==(const Matrix<rows, cols, T>& other) const;
    bool operator!=(const Matrix<rows, cols, T>& other) const;



    friend Matrix<rows,cols,T> operator+(const T& scalar,const Matrix<rows, cols, T>& mat)//scalar+mat
    {
        Matrix<rows, cols, T> result(mat);
        return result+scalar;
    }
    friend Matrix<rows,cols,T> operator-(const T& scalar,const Matrix<rows, cols, T>& mat)//scalar-mat
    {
        Matrix<rows, cols, T> result(mat);
        return result-scalar;
    }
    friend Matrix<rows,cols,T> operator*(const T& scalar,const Matrix<rows, cols, T>& mat)//scalar*mat
    {
        Matrix<rows, cols, T> result(mat);
        return result*scalar;
    }


   friend std::ostream& operator<<(std::ostream& os, const Matrix<rows,cols,T>& mat)
   {
       for(int i=0;i<mat.rowsSize;i++)
       {
           for (int j = 0; j < mat.colsSize; j++)
           {
               os << mat.data[i][j] << " ";

           }
           os << std::endl;
       }
       return os;
   }

    explicit operator double();
    explicit operator float();
    explicit operator int();


};

template<int rows, int cols, class T>
void Matrix<rows, cols, T>::allocateData(int rowsSize, int colsSize) {
    if (rowsSize <= 0 || colsSize <= 0)
        return;

        data = new T*[rowsSize];
        for (int i = 0; i < rowsSize; i++)
        {
            data[i] = new T[colsSize]();
        }

}

template<int rows, int cols, class T>
void Matrix<rows, cols, T>::fillData(int value,int rowsSize,int colsSize)
{
    if(rowsSize<=0 || colsSize<=0)
        return ;
    // allocateData(rowsSize,colsSize);
    data = new T*[rowsSize];
    for (int i = 0; i < rowsSize; i++)
    {
        data[i] = new T[colsSize]();
    }
     for(int i=0;i<rowsSize;i++)
    {
        for(int j=0;j<colsSize;j++)
        {
            data[i][j]=value;
        }
    }

}
template<int rows, int cols, class T>
void Matrix<rows, cols, T>::copyData(T **dataTocopy, T** matData,int row,int col)
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            matData[i][j]=dataTocopy[i][j];
        }
    }
}


template<int rows, int cols, class T>
Matrix<rows,cols,T>::Matrix() :data(nullptr),rowsSize(rows),colsSize(cols)
{
    if(rowsSize>0 && colsSize>0)
    {
        //fillData(0,rowsSize,colsSize);
        data = new T*[rowsSize];
        for (int i = 0; i < rowsSize; i++)
        {
            data[i] = new T[colsSize]();
        }
        for(int i=0;i<rowsSize;i++)
        {
            for(int j=0;j<colsSize;j++)
            {
                data[i][j]=0;
            }
        }
    }
}
template<int rows, int cols, class T>
Matrix<rows,cols,T>::Matrix(T value) :data(nullptr),rowsSize(rows),colsSize(cols)
{
    if(rowsSize>0 && colsSize>0)
    {
        //fillData(0,rowsSize,colsSize);
        data = new T*[rowsSize];
        for (int i = 0; i < rowsSize; i++)
        {
            data[i] = new T[colsSize]();
        }
        for(int i=0;i<rowsSize;i++)
        {
            for(int j=0;j<colsSize;j++)
            {
                data[i][j]=value;
            }
        }
    }
}
template<int rows, int cols, class T>
Matrix<rows,cols,T>::Matrix(const Matrix<rows, cols, T> &other)
{
    data = new T*[other.rowsSize];
        rowsSize=other.rowsSize;
        colsSize=other.colsSize;
    for (int i = 0; i < other.rowsSize; i++)
    {
        data[i] = new T[colsSize]();
    }
    for(int i=0;i<rowsSize;i++)
    for (int j = 0; j < colsSize; j++)
    {
        data[i][j] =other.data[i][j];
    }
//        allocateData(other.rowsSize,other.colsSize);
//        copyData(other.data,data,other.rowsSize);
}
template<int rows, int cols, class T>
Matrix<rows, cols, T>& Matrix<rows, cols, T>::operator=(const Matrix<rows, cols, T> &other) {
    if (*this != other) {
        if (data != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
        //allocateData(other.rowsSize, other.colsSize);
        //copyData(other.data, data, other.rowsSize);
        data = new T*[rowsSize];
        for (int i = 0; i < rowsSize; i++)
        {
            data[i] = new T[colsSize]();
        }
        for(int i=0;i<rowsSize;i++)
            for (int j = 0; j < colsSize; j++)
            {
                data[i][j]=other.data[i][j];
            }
    }
        return *this;
}

template<int rows, int cols, class T>
Matrix<rows, cols, T>::~Matrix()
{
    if(data!= nullptr)
    {
        for(int i=0;i<rowsSize;i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }
    rowsSize=0;
    colsSize=0;
}

template<int rows, int cols, class T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator+(const T &scalar)
{
    Matrix<rows, cols, T> result;
    for(int i=0;i<rowsSize;i++)
    {
        for(int j=0;j<colsSize;j++)
        {
            result.data[i][j]= data[i][j]+scalar;
        }
    }
    return result;
}

template<int rows, int cols, class T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator+(const Matrix<rows, cols, T> &mat1)
{
    Matrix<rows, cols, T> result;
    for(int i=0;i<mat1.rowsSize;i++)
    {
        for( int j=0;j<mat1.colsSize;j++)
        {
            result.data[i][j]= mat1.data[i][j]+ data[i][j];
        }
    }
    return result;

}
//template<int rows, int cols, class T>
//Matrix<rows, cols, T>& Matrix<rows, cols, T>::operator+(const Matrix<rows, cols, T> &other) const
//{
//    Matrix<rows, cols, T> result;
//    for(int i=0;i<rowsSize;i++)
//    {
//        for( int j=0;j<colsSize;j++)
//        {
//            result.data[i][j]= data[i][j]+other.data[i][j];
//        }
//    }
//    return result;
//}
template<int rows, int cols, class T>
Matrix<rows, cols, T>& Matrix<rows, cols, T>::operator++()
{
    for(int i=0;i<rowsSize;i++)
    {
        for(int j=0;j<colsSize;j++)
        {
            data[i][j]+=1;
        }
    }
    return (*this);
}
template<int rows, int cols, class T>
const Matrix<rows, cols, T> Matrix<rows, cols, T>::operator++(int)
{
    Matrix<rows,cols,T> result(*this);
    ++(*this);
    return result;
}
/////////////////////////////////////////////////////
template<int rows, int cols, class T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator-(const T& scalar)
{
    Matrix<rows, cols, T> result;
    for(int i=0;i<rowsSize;i++)
    {
        for(int j=0;j<colsSize;j++)
        {
            result.data[i][j]= data[i][j]-scalar;
        }
    }
    return result;
}
template<int rows, int cols, class T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator-(const double scalar)
{
    Matrix<rows, cols, T> result;
    for(int i=0;i<rowsSize;i++)
    {
        for(int j=0;j<colsSize;j++)
        {
            result.data[i][j]= data[i][j]-scalar;
        }
    }
    return result;
}

template<int rows, int cols, class T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator-(const Matrix<rows, cols, T> &other) const
{
    Matrix<rows, cols, T> result;
    for(int i=0;i<rowsSize;i++)
    {
        for( int j=0;j<colsSize;j++)
        {
            result.data[i][j]= data[i][j]-other.data[i][j];
        }
    }
    return result;
}
template<int rows, int cols, class T>
Matrix<rows, cols, double> Matrix<rows, cols, T>::operator-(const Matrix<rows, cols, double> &other)
{
    Matrix<rows, cols, T> result;
    for(int i=0;i<rowsSize;i++)
    {
        for( int j=0;j<colsSize;j++)
        {
            result.data[i][j]= data[i][j]-other.data[i][j];
        }
    }
    return result;
}
template<int rows, int cols, class T>
Matrix<rows, cols, T>& Matrix<rows, cols, T>::operator--()
{

    for(int i=0;i<rowsSize;i++)
    {
        for(int j=0;j<colsSize;j++)
        {
            data[i][j]-=1;
        }
    }
    return (*this);
}
template<int rows, int cols, class T>
const Matrix<rows, cols, T> Matrix<rows, cols, T>::operator--(int)
{
    Matrix<rows,cols,T> result(*this);
    --(*this);
    return result;
}
template<int rows, int cols, class T>
T *Matrix<rows, cols, T>::getDiag(int &num)
{
    num= (rowsSize<=colsSize)?rowsSize : colsSize;
    T* diag = new T[num];
    for(int i=0;i<num;i++)
    {
        diag[i]=data[i][i];
    }
    return diag;
}
// in case of rows!=cols what to do??
template<int rows, int cols, class T>
Matrix<rows,cols,T> Matrix<rows,cols,T>::getIdentityMatrix()
{
    Matrix<rows,cols,T> idMatrix;
    for(int i=0;i<rowsSize;i++)
    {
        for(int j=0;j<colsSize;j++)
        {
            if(i==j)
                idMatrix.data[i][j]=1;
            else idMatrix.data[i][j]=0;
        }
    }
    return idMatrix;
}
//////////////////////////////////////operator*

template<int rows, int cols, class T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator*(const T &scalar)
{
    Matrix<rows, cols, T> result;
    for(int i=0;i<rowsSize;i++)
    {
        for(int j=0;j<colsSize;j++)
        {
            result.data[i][j]= data[i][j]*scalar;
        }
    }
    return result;
}

template<int rows, int cols, class T>
T Matrix<rows,cols,T>::rowColMultipy(int row, int col, const Matrix<rows, cols, T> &other)
{
    T sum=0;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<cols;j++)
        {
            sum+= (data[i][j]*other.data[i][j]);

        }
    }
    return sum;
}
template<int rows, int cols, class T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator*(const Matrix<rows, cols, T> &other) const
{
    Matrix<rows, cols, T> result;
    for(int i=0;i<rowsSize;i++)
    {
        for( int j=0;j<colsSize;j++)
        {
            result.data[i][j]= rowColMultipy(i,j,other);
        }
    }
    return result;
}
template<int rows, int cols, class T>
T& Matrix<rows,cols,T>::operator()(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data[row][col];
}
template<int rows, int cols, class T>
const T& Matrix<rows,cols,T>::operator()(int row, int col)const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data[row][col];
}
//template<int rows, int cols, class T>
//template<typename U>
//Matrix<rows, cols, T>::operator U() const {
//    U trace = U();
//    int minSize = (rows < cols) ? rows : cols;
//    for (int i = 0; i < minSize; i++)
//    {
//        trace += static_cast<U>(data[i][i]);
//    }
//    return trace;
//}
template<int rows, int cols, class T>
bool Matrix<rows, cols, T>::operator==(const Matrix<rows, cols, T>& other) const
{
    T diff;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
        {
            diff= (data[i][j] - other.data[i][j]);
            if (diff<0)
                diff= -diff;
            if (diff>DBL_EPSILON)
            {
                return false;
            }
        }
    }
    return true;
}
template<int rows, int cols, class T>
bool Matrix<rows, cols, T>::operator!=(const Matrix<rows, cols, T>& other) const
{
    return !((*this) == other);
}
template<int rows, int cols, class T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator-() const
{
    Matrix<rows, cols, T> result;
    for (int i = 0; i < rowsSize;i++)
    {
        for (int j = 0; j < colsSize;j++)
        {
            result.data[i][j] = -data[i][j];
        }
    }
    return result;
}
template<int rows, int cols, class T>
Matrix<rows, cols, T>::operator float()
{
    float trace = 0.0f;
    int minSize = (rows < cols) ? rows : cols;
    for (int i = 0; i < minSize; i++) {
        trace += static_cast<float>(data[i][i]);
    }
    return trace;
}
template<int rows, int cols, class T>
Matrix<rows, cols, T>::operator double()
{
    double trace = 0.0;
    int minSize = (rows < cols) ? rows : cols;
    for (int i = 0; i < minSize; i++) {
        trace += static_cast<double>(data[i][i]);
    }
    return trace;
}
template<int rows, int cols, class T>
Matrix<rows, cols, T>::operator int()
{
    float trace = 0;
    int minSize = (rows < cols) ? rows : cols;
    for (int i = 0; i < minSize; i++) {
        trace += static_cast<int>(data[i][i]);
    }
    return trace;
}
