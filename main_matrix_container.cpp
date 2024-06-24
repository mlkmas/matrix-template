//#include "MatrixContainer.h"
//
//int main()
//{
//
//	freopen("output_matrix_container.txt", "w", stdout);
//
//	Matrix<3, 3> mat1(4);
//	Matrix<3, 3> mat2(1);
//	Matrix<3, 3> mat3(3);
//	std::cout << "mat1:" << std::endl << mat1 << std::endl;
//	std::cout << "mat2:" << std::endl << mat2 << std::endl;
//	std::cout << "mat3:" << std::endl << mat3 << std::endl;
//
//	MatrixContainer<3, 3> container; //you may assume that all the matrices in the container have the same template parameters
//	container.addMatrix(mat1);
//	container.addMatrix(mat2);
//
//	std::cout << "Current size of the container is: " << container.size() << std::endl;
//
//	container.addMatrix(mat3);
//	container.addMatrix(mat1);
//
//
//	std::cout << container;
//	container.removeLastMatrix();
//	std::cout << container;
//
//	std::cout << std::endl;
//	std::cout << std::endl;
//
//	std::cout << container[2]++<< std::endl;
//	std::cout << container[2] << std::endl;
//
//	std::cout << std::endl;
//	std::cout << std::endl;
//	return 0;
//}