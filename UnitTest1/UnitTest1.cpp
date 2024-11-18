#include "pch.h"
#include "CppUnitTest.h"
#include "../PDC_LAB12/source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestDijkstra)
        {
            const int n = 6;
            int** matrix = new int* [n];
            for (int i = 0; i < n; ++i) {
                matrix[i] = new int[n];
                for (int j = 0; j < n; ++j) {
                    matrix[i][j] = INF;
                }
                matrix[i][i] = 0;
            }

            matrix[0][1] = 3;
            matrix[0][2] = 4;
            matrix[0][3] = 2;
            matrix[1][2] = 1;
            matrix[1][3] = 3;
            matrix[2][3] = 2;
            matrix[3][4] = 1;
            matrix[3][5] = 3;
            matrix[4][5] = 6;

            std::vector<int> dist, prev;

            dijkstra(matrix, n, 0, dist, prev);

            Assert::AreEqual(0, dist[0]);
            Assert::AreEqual(3, dist[1]);
            Assert::AreEqual(4, dist[2]);
            Assert::AreEqual(2, dist[3]);
            Assert::AreEqual(3, dist[4]);
            Assert::AreEqual(5, dist[5]); 

            Assert::AreEqual(-1, prev[0]);
            Assert::AreEqual(0, prev[1]);
            Assert::AreEqual(0, prev[2]);
            Assert::AreEqual(0, prev[3]);
            Assert::AreEqual(3, prev[4]);
            Assert::AreEqual(3, prev[5]);

            for (int i = 0; i < n; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    };
}