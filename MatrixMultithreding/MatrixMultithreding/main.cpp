#include <iostream>
#include <thread>
#include <mutex>
#include "Matrix.h"

std::mutex lock_;

Matrix Multiply(const Matrix& matrix1, const Matrix& matrix2)
{
 Matrix res = Matrix(matrix1.GetSize());
 for (int i = 0; i < res.GetSize(); ++i)
 {
	for (int j = 0; j < res.GetSize(); ++j)
	{
	 for (int k = 0; k < res.GetSize(); ++k)
	 {
		res.SetElem(res.GetElem(i,j) + matrix1.GetElem(i,k) * matrix2.GetElem(k, j),i,j);
	 }
	}
 }
 return res;
}

void MultiplyBlocks(Matrix& res, const Matrix& matrix1, const Matrix& matrix2,
 int row_1, int clmn_1, int row_2, int clmn_2, int block_size)
{
 for (int i = row_1; i < row_1 + block_size; ++i)
 {
	for (int j = clmn_2; j < clmn_2 + block_size; ++j)
	{
	 double elem = 0;
	 for (int k = 0; k < block_size; ++k)
	 {
		elem += matrix1.GetElem(i, clmn_1 + k) * matrix2.GetElem(row_2 + k, j);
	 }
	 lock_.lock();
	 res.SetElem(res.GetElem(i, j) + elem, i, j);
	 lock_.unlock();
	}
 }
}

Matrix MultiplyByBlocks(const Matrix& matrix1, const Matrix& matrix2, int blocks_number)
{
 int block_size = matrix1.GetSize() / blocks_number;
 Matrix res = Matrix(matrix1.GetSize());
 std::vector<std::thread> threads;
 for (int i = 0; i < res.GetSize(); i += block_size)
 {
	for (int j = 0; j < res.GetSize(); j += block_size)
	{
	 for (int k = 0; k < res.GetSize(); k += block_size)
	 {
		std::thread thread(MultiplyBlocks, std::ref(res),
		 std::ref(matrix1), std::ref(matrix2), i, k, k, j, block_size);
		threads.push_back(std::move(thread));
	 }
	}
 }
 for (std::thread& thread : threads)
 {
	thread.join();
 }
 return res;
}


int main()
{
 int n = 50;
 Matrix matrix1(n,10);
 //std::cout << matrix1 << std::endl;
 Matrix matrix2(n,10);
 //std::cout << matrix2 << std::endl;
 int start = clock();
 Matrix matrix3 = Multiply(matrix1, matrix2);
// std::cout << matrix3;
 int end = clock();
 std::cout << "Size: " << n << " Time: " << end - start << std::endl;
 for (int number_blocks = 1; number_blocks <= n; number_blocks++)
 {
	if (n % number_blocks == 0)
	{
	 int start = clock();
	 Matrix matrix4 = MultiplyByBlocks(matrix1, matrix2, number_blocks);
	 int end = clock();
	 std::cout  << "Number of blocks: " << number_blocks * number_blocks<<" Time: " << end - start << std::endl;
	// std::cout << matrix4 << std::endl;
	}
 }
}
