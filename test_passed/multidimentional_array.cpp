// #include <stdio.h>

// int main() {
//     printf("=== Test 1: Basic 2D Array Access ===\n");
//     int matrix[2][2] = {{1, 2}, {3, 4}};
//     printf("matrix[0][0] = %d\n", matrix[0][0]);
//     printf("matrix[0][1] = %d\n", matrix[0][1]);
//     printf("matrix[1][0] = %d\n", matrix[1][0]);
//     printf("matrix[1][1] = %d\n", matrix[1][1]);
    
//     printf("\n=== Test 2: 3x3 Matrix Operations ===\n");
//     int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
//     printf("Original Matrix:\n");
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             printf("%d ", a[i][j]);
//         }
//         printf("\n");
//     }
    
//     printf("\n=== Test 3: Matrix Transpose ===\n");
//     int b[3][3];
    
//     // Transpose
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             b[j][i] = a[i][j];
//         }
//     }
    
//     printf("Transposed Matrix:\n");
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             printf("%d ", b[i][j]);
//         }
//         printf("\n");
//     }
    
//     printf("\n=== Test 4: Sum of All Elements ===\n");
//     int sum = 0;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             sum = sum + a[i][j];
//         }
//     }
//     printf("Total sum: %d\n", sum);
    
//     printf("\n=== Test 5: Row Sums ===\n");
//     for (int i = 0; i < 3; i++) {
//         int row_sum = 0;
//         for (int j = 0; j < 3; j++) {
//             row_sum = row_sum + a[i][j];
//         }
//         printf("Row %d sum: %d\n", i, row_sum);
//     }
    
//     printf("\n=== Test 6: Column Sums ===\n");
//     for (int j = 0; j < 3; j++) {
//         int col_sum = 0;
//         for (int i = 0; i < 3; i++) {
//             col_sum = col_sum + a[i][j];
//         }
//         printf("Column %d sum: %d\n", j, col_sum);
//     }
    
//     printf("\n=== Test 7: Diagonal Elements ===\n");
//     printf("Main diagonal: ");
//     for (int i = 0; i < 3; i++) {
//         printf("%d ", a[i][i]);
//     }
//     printf("\n");
    
//     printf("Anti-diagonal: ");
//     for (int i = 0; i < 3; i++) {
//         printf("%d ", a[i][2 - i]);
//     }
//     printf("\n");
    
//     printf("\n=== Test 8: Array Copy ===\n");
//     int c[3][3];
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             c[i][j] = a[i][j];
//         }
//     }
//     printf("Copied array:\n");
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             printf("%d ", c[i][j]);
//         }
//         printf("\n");
//     }
    
//     printf("\n=== Test 11: Scalar Multiplication ===\n");
//     int scalar = 2;
//     printf("Multiply by %d:\n", scalar);
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             printf("%d ", a[i][j] * scalar);
//         }
//         printf("\n");
//     }
    
//     printf("\n=== Test 10: Pattern Generation ===\n");
//     int pattern[4][4];
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             pattern[i][j] = i + j;
//         }
//     }
//     printf("Pattern (i+j):\n");
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             printf("%d ", pattern[i][j]);
//         }
//         printf("\n");
//     }
    
//     printf("\n=== Test 14: Counter Pattern ===\n");
//     int counter[3][3];
//     int count = 1;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             counter[i][j] = count;
//             count = count + 1;
//         }
//     }
//     printf("Counter matrix:\n");
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             printf("%d ", counter[i][j]);
//         }
//         printf("\n");
//     }
    
//     printf("\n=== Test 15: Boundary Elements ===\n");
//     printf("Top row: ");
//     for (int j = 0; j < 3; j++) {
//         printf("%d ", a[0][j]);
//     }
//     printf("\n");
    
//     printf("Bottom row: ");
//     for (int j = 0; j < 3; j++) {
//         printf("%d ", a[2][j]);
//     }
//     printf("\n");
    
//     printf("Left column: ");
//     for (int i = 0; i < 3; i++) {
//         printf("%d ", a[i][0]);
//     }
//     printf("\n");
    
//     printf("Right column: ");
//     for (int i = 0; i < 3; i++) {
//         printf("%d ", a[i][2]);
//     }
//     printf("\n");
    
//     printf("\n=== All 10 Tests Completed Successfully! ===\n");
    
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------------
// Testcase 1: Boundary Traversal of Matrix
// --------------------------------------------------
void testcase1() {
    cout << "\n--- Testcase 1: Boundary Traversal ---\n";

    int a[4][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };

    int rows = 4, cols = 5;

    vector<int> result;

    // top boundary
    for (int j = 0; j < cols; j++) result.push_back(a[0][j]);
    // right boundary
    for (int i = 1; i < rows; i++) result.push_back(a[i][cols - 1]);
    // bottom boundary
    for (int j = cols - 2; j >= 0; j--) result.push_back(a[rows - 1][j]);
    // left boundary
    for (int i = rows - 2; i >= 1; i--) result.push_back(a[i][0]);

    for (auto x : result) cout << x << " ";
    cout << "\n";
}

// --------------------------------------------------
// Testcase 2: Spiral Traversal
// --------------------------------------------------
void testcase2() {
    cout << "\n--- Testcase 2: Spiral Traversal ---\n";

    int a[3][5] = {
        {2, 4, 6, 8, 10},
        {12, 14, 16, 18, 20},
        {22, 24, 26, 28, 30}
    };

    int top = 0, bottom = 2, left = 0, right = 4;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) cout << a[top][j] << " ";
        top++;

        for (int i = top; i <= bottom; i++) cout << a[i][right] << " ";
        right--;

        if (top <= bottom) {
            for (int j = right; j >= left; j--) cout << a[bottom][j] << " ";
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) cout << a[i][left] << " ";
            left++;
        }
    }
    cout << "\n";
}

// --------------------------------------------------
// Testcase 3: 3D Array Layer Sum
// --------------------------------------------------
void testcase3() {
    cout << "\n--- Testcase 3: 3D Array Layer Sum ---\n";

    int a[3][2][2] = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}},
        {{9, 10}, {11, 12}}
    };

    int total = 0;
    for (int i = 0; i < 3; i++) {
        int layerSum = 0;
        for (int r = 0; r < 2; r++)
            for (int c = 0; c < 2; c++)
                layerSum += a[i][r][c];

        cout << "Layer " << i + 1 << " sum = " << layerSum << "\n";
        total += layerSum;
    }
    cout << "Total sum = " << total << "\n";
}

// --------------------------------------------------
// Testcase 4: Ragged 2D Vector
// --------------------------------------------------
void testcase4() {
    cout << "\n--- Testcase 4: Ragged 2D Vector ---\n";

    vector<vector<int>> a = {
        {1, 2, 3},
        {9},
        {2, 4, 6, 8},
        {5, 5},
        {7, 8, 9}
    };

    int mx = -1;

    for (int i = 0; i < a.size(); i++) {
        int sum = 0;
        for (int x : a[i]) sum += x;
        cout << "Row " << i + 1 << " sum = " << sum << "\n";
        mx = max(mx, sum);
    }

    cout << "Max row sum = " << mx << "\n";
}

// --------------------------------------------------
// Testcase 5: Saddle Point in Matrix
// --------------------------------------------------
void testcase5() {
    cout << "\n--- Testcase 5: Saddle Point ---\n";

    int a[4][4] = {
        {10, 20, 15, 12},
        {9, 7, 25, 14},
        {21, 18, 30, 16},
        {11, 13, 17, 19}
    };

    for (int i = 0; i < 4; i++) {
        int rowMin = a[i][0];
        int colIndex = 0;

        for (int j = 1; j < 4; j++) {
            if (a[i][j] < rowMin) {
                rowMin = a[i][j];
                colIndex = j;
            }
        }

        // Check if it's max in the column
        bool saddle = true;
        for (int k = 0; k < 4; k++) {
            if (a[k][colIndex] > rowMin) {
                saddle = false;
                break;
            }
        }

        if (saddle) {
            cout << "Saddle point = " << rowMin << "\n";
            return;
        }
    }

    cout << "No saddle point\n";
}

// --------------------------------------------------
// Testcase 6: Rotate Matrix 90 Degrees Clockwise
// --------------------------------------------------
void testcase6() {
    cout << "\n--- Testcase 6: Matrix Rotation ---\n";

    int a[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int b[3][3];

    // transpose
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            b[j][i] = a[i][j];

    // reverse rows
    for (int i = 0; i < 3; i++)
        reverse(b[i], b[i] + 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << b[i][j] << " ";
        cout << "\n";
    }
}

// --------------------------------------------------
// Testcase 7: Prefix Sum Queries
// --------------------------------------------------
void testcase7() {
    cout << "\n--- Testcase 7: Prefix Sum Queries ---\n";

    int a[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int ps[5][5] = {0};

    // Build prefix sum
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            ps[i][j] = a[i - 1][j - 1] +
                       ps[i - 1][j] +
                       ps[i][j - 1] -
                       ps[i - 1][j - 1];

    // Queries:
    vector<array<int, 4>> q = {
        {1, 1, 3, 3},
        {2, 2, 4, 4},
        {1, 2, 4, 3}
    };

    for (auto qu : q) {
        int r1 = qu[0], c1 = qu[1], r2 = qu[2], c2 = qu[3];
        int ans = ps[r2][c2] - ps[r1 - 1][c2] - ps[r2][c1 - 1] + ps[r1 - 1][c1 - 1];
        cout << ans << "\n";
    }
}

// --------------------------------------------------
// Testcase 8: Max Submatrix Sum (Kadane 2D)
// --------------------------------------------------
void testcase8() {
    cout << "\n--- Testcase 8: Max Submatrix Sum ---\n";

    int a[3][4] = {
        {-1, 2, -3, 4},
        {5, -6, 7, -8},
        {9, -10, 11, -12}
    };

    int rows = 3, cols = 4;
    int maxSum = INT_MIN;

    for (int left = 0; left < cols; left++) {
        int temp[3] = {0};

        for (int right = left; right < cols; right++) {
            for (int i = 0; i < rows; i++)
                temp[i] += a[i][right];

            // Kadane on temp[]
            int cur = 0, best = INT_MIN;
            for (int i = 0; i < rows; i++) {
                cur = max(temp[i], cur + temp[i]);
                best = max(best, cur);
            }

            maxSum = max(maxSum, best);
        }
    }

    cout << "Max submatrix sum = " << maxSum << "\n";
}

// --------------------------------------------------
int main() {
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();
    testcase7();
    testcase8();

    return 0;
}
