#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h>
#include "Matrix.h"

HANDLE lock_ = CreateMutex(NULL, FALSE, NULL);

struct ThreadFun
{
 HANDLE HLock;
 Matrix& res_;
 const Matrix& matrix1_;
 const Matrix& matrix2_;
 int row1_;
 int column1_;
 int row2_;
 int column2_;
 int block_size_;

 ThreadFun(HANDLE lock, Matrix& result, const Matrix& matrix1, const Matrix& matrix2,
	int row1, int column1, int row2, int column2, int block_size) :
	HLock(lock), res_(result), matrix1_(matrix1), matrix2_(matrix2), row1_(row1), column1_(column1), row2_(row2), column2_(column2), block_size_(block_size)
 {
 }
};

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

DWORD WINAPI MultiplyBlocks(LPVOID param_)
{
 ThreadFun* param = (ThreadFun*)param_;
 for (int i = param->row1_; i < param->row1_ + param->block_size_; ++i)
 {
	for (int j = param->column2_; j < param->column2_ + param->block_size_; ++j)
	{
	 double temp = 0;
	 for (int k = 0; k < param->block_size_; ++k)
	 {
		temp += param->matrix1_.GetElem(i, param->column1_ + k) * param->matrix2_.GetElem(param->row2_ + k, j);
	 }
	 WaitForSingleObject(param->HLock, INFINITE);
	 param->res_.SetElem(param->res_.GetElem(i, j) + temp, i, j);
	 ReleaseMutex(param->HLock);
	}
 }
 ExitThread(0);
}

Matrix MultiplyByBlocks(const Matrix& matrix1, const Matrix& matrix2, int blocks_number)
{
 int block_size = matrix1.GetSize() / blocks_number;
 Matrix res = Matrix(matrix1.GetSize());
 std::vector<HANDLE> threads;
 std::vector<ThreadFun*> params;
 for (int i = 0; i < res.GetSize(); i += block_size)
 {
	for (int j = 0; j < res.GetSize(); j += block_size)
	{
	 for (int k = 0; k < res.GetSize(); k += block_size)
	 {
		ThreadFun* param = new ThreadFun(lock_, res, matrix1, matrix2, i, k, k, j, block_size);
		HANDLE h_thread = CreateThread(NULL, 0, MultiplyBlocks, param, 0, NULL);
		threads.push_back(h_thread);
		params.push_back(param);
	 }
	}
 }
 WaitForMultipleObjects(threads.size(), &threads[0], TRUE, INFINITE);
 for (int i = 0; i < threads.size(); ++i)
 {
	CloseHandle(threads[i]);
 }
 return res;
}


int main()
{
 int n = 20;
 Matrix matrix1(n,10);
 //std::cout << matrix1 << std::endl;
 Matrix matrix2(n,10);
 //std::cout << matrix2 << std::endl;
 int start = clock();
 Matrix matrix3 = Multiply(matrix1, matrix2);
 //std::cout << matrix3;
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
	 //std::cout << matrix4 << std::endl;
	}
 }
 CloseHandle(lock_);
}
