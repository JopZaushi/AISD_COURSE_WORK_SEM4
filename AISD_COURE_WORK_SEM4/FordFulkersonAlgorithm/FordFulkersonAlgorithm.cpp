#include "pch.h"
#include "CppUnitTest.h"
#include "..\AISD_COURE_WORK_SEM4\FordFulkersonAlgorithm.h"
#include "..\AISD_COURE_WORK_SEM4\String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FordFulkersonAlgorithm
{
	TEST_CLASS(FordFulkersonAlgorithm)
	{
	public:
		
		TEST_METHOD(ROW_OF_VERTEXES)
		{
			const int buff = 512;
			char* start_text = new char[buff];
			start_text = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			String only_peaks;
			only_peaks = string_peaks(start_text);
			Assert::IsTrue(only_peaks[0] == 'S');
			Assert::IsTrue(only_peaks[2] == 'O');
			Assert::IsTrue(only_peaks[4] == 'P');
			Assert::IsTrue(only_peaks[6] == 'Q');
			Assert::IsTrue(only_peaks[8] == 'R');
			Assert::IsTrue(only_peaks[10] == 'T');
			
		}

		TEST_METHOD(SIZE)
		{
			const int buff = 512;
			char* start_text = new char[buff];
			start_text = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			String only_peaks;
			only_peaks = string_peaks(start_text);
			Assert::IsTrue(only_peaks[0] == 'S');
			Assert::IsTrue(only_peaks[2] == 'O');
			Assert::IsTrue(only_peaks[4] == 'P');
			Assert::IsTrue(only_peaks[6] == 'Q');
			Assert::IsTrue(only_peaks[8] == 'R');
			Assert::IsTrue(only_peaks[10] == 'T');

			Assert::IsTrue(dimension(only_peaks) == 6);
		}

		TEST_METHOD(MATRIX)
		{
			const int buff = 512;
			char* start_text = new char[buff];
			start_text = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			String only_peaks;
			only_peaks = string_peaks(start_text);
			int matrix_dimension = dimension(only_peaks);
			//matrix creation
			int** matrix = new int* [matrix_dimension];
			for (int i = 0; i < matrix_dimension; i++) {
				matrix[i] = new int[matrix_dimension];
			}
			matrix = initial_matrix(start_text, only_peaks);
			Assert::IsTrue(only_peaks[0] == 'S');
			Assert::IsTrue(only_peaks[2] == 'O');
			Assert::IsTrue(only_peaks[4] == 'P');
			Assert::IsTrue(only_peaks[6] == 'Q');
			Assert::IsTrue(only_peaks[8] == 'R');
			Assert::IsTrue(only_peaks[10] == 'T');

			Assert::IsTrue(dimension(only_peaks) == 6);

			Assert::IsTrue(matrix[0][0] == 0);
			Assert::IsTrue(matrix[1][1] == 0);
			Assert::IsTrue(matrix[0][1] == 3);
			Assert::IsTrue(matrix[0][2] == 3);
			Assert::IsTrue(matrix[1][2] == 2);
			Assert::IsTrue(matrix[2][4] == 2);
			Assert::IsTrue(matrix[3][4] == 4);
			Assert::IsTrue(matrix[4][5] == 3);
		}

		TEST_METHOD(MINIMUM_ELEMENT) {
			int* array = new int[6];
			array[0] = 8;
			array[1] = 4;
			array[2] = 7;
			array[3] = 3;
			array[4] = 1;
			array[5] = 10;
			Assert::IsTrue(min_number(array) == 1);
		}

		TEST_METHOD(FORD_FULKERSON_ALGORITHM)
		{
			const int buff = 512;
			char* start_text = new char[buff];
			start_text = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			String only_peaks;
			only_peaks = string_peaks(start_text);
			int matrix_dimension = dimension(only_peaks);
			//matrix creation
			int** matrix = new int* [matrix_dimension];
			for (int i = 0; i < matrix_dimension; i++) {
				matrix[i] = new int[matrix_dimension];
			}
			matrix = initial_matrix(start_text, only_peaks);
			Assert::IsTrue(only_peaks[0] == 'S');
			Assert::IsTrue(only_peaks[2] == 'O');
			Assert::IsTrue(only_peaks[4] == 'P');
			Assert::IsTrue(only_peaks[6] == 'Q');
			Assert::IsTrue(only_peaks[8] == 'R');
			Assert::IsTrue(only_peaks[10] == 'T');

			Assert::IsTrue(dimension(only_peaks) == 6);

			Assert::IsTrue(matrix[0][0] == 0);
			Assert::IsTrue(matrix[1][1] == 0);
			Assert::IsTrue(matrix[0][1] == 3);
			Assert::IsTrue(matrix[0][2] == 3);
			Assert::IsTrue(matrix[1][2] == 2);
			Assert::IsTrue(matrix[2][4] == 2);
			Assert::IsTrue(matrix[3][4] == 4);
			Assert::IsTrue(matrix[4][5] == 3);

			Assert::IsTrue(Ford_Fulkerson_Algorithm(matrix, only_peaks) == 5);
		}

	};
}
