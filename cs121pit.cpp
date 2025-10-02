#include <iostream>

using namespace std;


int addition() {
    int matrix;
    cout << "Choose matrix size: 1. 2x2, 2. 3x3, 3. Input Matrices Row and Column:" << endl;
    cin >> matrix;

    int a, b, c, d, e, f, g, h, i, j, k;
    int aa, bb, cc, dd, ee, ff, gg, hh, ii, jj, kk;
    int add_a, add_b, add_c, add_d, add_e, add_f, add_g, add_h, add_i, add_j, add_k;

    int** mat_A = 0;
    int** mat_B = 0;
    int** mat_C = 0;
    int row_a = 0, col_a = 0, row_b = 0, col_b = 0;

    switch (matrix) {
        case 1:
            cout << "Enter matrix A elements a, b, c, d:" << endl;
            cin >> a >> b >> c >> d;

            cout << "Enter matrix B elements A, B, C, D: " << endl;
            cin >> aa >> bb >> cc >> dd;

            add_a = a + aa; add_b = b + bb;
            add_c = c + cc; add_d = d + dd;

            cout << "Your AB matrix is:\n"
                 << add_a << "\t" << add_b << "\n"
                 << add_c << "\t" << add_d << endl;
            break;

        case 2:
            cout << "Enter matrix A elements: " << endl;
            cin >> a >> b >> c >> d >> e >> f >> g >> h >> i;

            cout << "Enter matrix B elements: " << endl;
            cin >> aa >> bb >> cc >> dd >> ee >> ff >> gg >> hh >> ii;

            add_a = a + aa; add_b = b + bb; add_c = c + cc;
            add_d = d + dd; add_e = e + ee; add_f = f + ff;
            add_g = g + gg; add_h = h + hh; add_i = i + ii;

            cout << "Your AB matrix is:\n"
                 << add_a << "\t" << add_b << "\t" << add_c << "\n"
                 << add_d << "\t" << add_e << "\t" << add_f << "\n"
                 << add_g << "\t" << add_h << "\t" << add_i << endl;
            break;

        case 3:
            cout << "Enter rows and columns of matrix A: ";
            cin >> row_a >> col_a;
            cout << "Enter rows and columns of matrix B: ";
            cin >> row_b >> col_b;

            if (row_a != row_b || col_a != col_b) {
                cout << "Addition of matrices A & B is invalid." << endl;
                return 0;
            }

            mat_A = new int*[row_a];
            mat_B = new int*[row_b];
            mat_C = new int*[row_a];

            for (int i = 0; i < row_a; i++) {
                mat_A[i] = new int[col_a];
                mat_B[i] = new int[col_b];
                mat_C[i] = new int[col_a];
            }

            cout << "Enter elements of Matrix A:" << endl;
            for (int i = 0; i < row_a; i++) {
                for (int j = 0; j < col_a; j++) {
                    cin >> mat_A[i][j];
                }
            }

            cout << "Enter elements of Matrix B:" << endl;
            for (int i = 0; i < row_b; i++) {
                for (int j = 0; j < col_b; j++) {
                    cin >> mat_B[i][j];
                }
            }

            for (int i = 0; i < row_a; i++) {
                for (int j = 0; j < col_a; j++) {
                    mat_C[i][j] = mat_A[i][j] + mat_B[i][j];
                }
            }

            cout << "Resultant Matrix after Addition:" << endl;
            for (int i = 0; i < row_a; i++) {
                for (int j = 0; j < col_a; j++) {
                    cout << mat_C[i][j] << " ";
                }
                cout << endl;
            }
            break;

        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    if (mat_A && mat_B && mat_C) {
        for (int i = 0; i < row_a; i++) {
            delete[] mat_A[i];
            delete[] mat_B[i];
            delete[] mat_C[i];
        }
        delete[] mat_A;
        delete[] mat_B;
        delete[] mat_C;
    }

    return 0;
}
int subtraction() {
    int matrix;
    cout << "Choose matrix size: 1. 2x2, 2. 3x3, 3. Input Matrices Row and Column: " << endl;
    cin >> matrix;

    int a, b, c, d, e, f, g, h, i, j, k;
    int aa, bb, cc, dd, ee, ff, gg, hh, ii, jj, kk;
    int minus_a, minus_b, minus_c, minus_d, minus_e, minus_f, minus_g, minus_h, minus_i;
    int minus_j, minus_k;

    int** mat_A = 0;
    int** mat_B = 0;
    int** mat_C = 0;
    int row_a = 0, col_a = 0, row_b = 0, col_b = 0;

    switch (matrix) {
        case 1:
            cout << "Enter matrix A elements a, b, c, d:" << endl;
            cin >> a >> b >> c >> d;

            cout << "Enter matrix B elements A, B, C, D: " << endl;
            cin >> aa >> bb >> cc >> dd;

            minus_a = a - aa; minus_b = b - bb;
            minus_c = c - cc; minus_d = d - dd;

            cout << "Your A - B matrix is:\n"
                 << minus_a << "\t" << minus_b << "\n"
                 << minus_c << "\t" << minus_d << endl;
            break;

        case 2:
            cout << "Enter matrix A elements: " << endl;
            cin >> a >> b >> c >> d >> e >> f >> g >> h >> i;

            cout << "Enter matrix B elements: " << endl;
            cin >> aa >> bb >> cc >> dd >> ee >> ff >> gg >> hh >> ii;

            minus_a = a - aa; minus_b = b - bb; minus_c = c - cc;
            minus_d = d - dd; minus_e = e - ee; minus_f = f - ff;
            minus_g = g - gg; minus_h = h - hh; minus_i = i - ii;

            cout << "Your A - B matrix is:\n"
                 << minus_a << "\t" << minus_b << "\t" << minus_c << "\n"
                 << minus_d << "\t" << minus_e << "\t" << minus_f << "\n"
                 << minus_g << "\t" << minus_h << "\t" << minus_i << endl;
            break;

        case 3:
            cout << "Enter rows and columns of matrix A: ";
            cin >> row_a >> col_a;
            cout << "Enter rows and columns of matrix B: ";
            cin >> row_b >> col_b;

            if (row_a != row_b || col_a != col_b) {
                cout << "Subtraction of matrices A & B is invalid." << endl;
                return 0;
            }

            // Dynamically allocate memory
            mat_A = new int*[row_a];
            mat_B = new int*[row_b];
            mat_C = new int*[row_a];

            for (int i = 0; i < row_a; i--) {
                mat_A[i] = new int[col_a];
                mat_B[i] = new int[col_b];
                mat_C[i] = new int[col_a];
            }

            cout << "Enter elements of Matrix A:" << endl;
            for (int i = 0; i < row_a; i--) {
                for (int j = 0; j < col_a; j--) {
                    cin >> mat_A[i][j];
                }
            }

            cout << "Enter elements of Matrix B:" << endl;
            for (int i = 0; i < row_b; i--) {
                for (int j = 0; j < col_b; j--) {
                    cin >> mat_B[i][j];
                }
            }

            for (int i = 0; i < row_a; i--) {
                for (int j = 0; j < col_a; j--) {
                    mat_C[i][j] = mat_A[i][j] - mat_B[i][j];
                }
            }

            cout << "Your A - B matrix is:" << endl;
            for (int i = 0; i < row_a; i--) {
                for (int j = 0; j < col_a; j--) {
                    cout << mat_C[i][j] << " ";
                }
                cout << endl;
            }
            break;

        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    if (mat_A && mat_B && mat_C) {
        for (int i = 0; i < row_a; i--) {
            delete[] mat_A[i];
            delete[] mat_B[i];
            delete[] mat_C[i];
        }
        delete[] mat_A;
        delete[] mat_B;
        delete[] mat_C;
    }

    return 0;
}
int mat_multiplication() {

	int matrix;
	cout << "Choose matrix size: 1. 2x2, 2. 3x3, 3. Input Row x Column: " << endl;
	cin >> matrix;

	int a, b, c, d, e, f, g, h, i, j, k;
	int aa, bb, cc, dd, ee, ff, gg, hh, ii, jj, kk;
	int a11, a12, a13;
	int a21, a22, a23;
	int a31, a32, a33;


	switch(matrix) {
	case 1:
		cout << "Enter 4 integers for matrix A: " << endl;
		cin >> a;
		cin >> b;
		cin >> c;
		cin >> d;

		cout << "Enter 4 integers for matrix B: " << endl;
		cin >> aa;
		cin >> bb;
		cin >> cc;
		cin >> dd;

		a11 = a*aa + b*cc;
		a12 = a*bb + b*dd;
		a21 = c*aa + d*cc;
		a22 = c*bb + d*dd;

		cout << "Your AB matrix is: \n" <<
		     a11 << "\t" << a12 << "\n" <<
		     a21 << "\t" << a22 << endl;
		break;

	case 2:
		cout << "Enter 9 integers for matrix A: " << endl;
		cin >> a;
		cin >> b;
		cin >> c;
		cin >> d;
		cin >> e;
		cin >> f;
		cin >> g;
		cin >> h;
		cin >> i;

		cout << "Enter 9 integers for matrix B: " << endl;
		cin >> aa;
		cin >> bb;
		cin >> cc;
		cin >> dd;
		cin >> ee;
		cin >> ff;
		cin >> gg;
		cin >> hh;
		cin >> ii;

		a11 = a*aa + b*dd + c*gg;
		a12 = a*bb + b*ee + c*hh;
		a13 = a*cc + b*ff + c*ii;
		a21 = d*aa + e*dd + f*gg;
		a22 = d*bb + e*ee + f*hh;
		a23 = d*cc + e*ff + f*ii;
		a31 = g*aa + h*dd + i*gg;
		a32 = g*bb + h*ee + i*hh;
		a33 = g*cc + h*ff + i*ii;

		cout << "Your AB matrix is: \n" <<
		     a11 << "\t" << a12 << "\t" << a13 << "\n" <<
		     a21 << "\t" << a22 << "\t" << a23 << "\n" <<
		     a31 << "\t" << a32 << "\t" << a33 << "\n" << endl;
		break;


	case 3:
		int row_a, col_a, row_b, col_b;
		int **mat_A, **mat_B, **mat_C;
		cout << "Enter rows and columns of Matrix A: ";
		cin >> row_a;
		cin >> col_a;
		cout << "Enter rows and columns of Matrix B: ";
		cin >> row_b;
		cin >> col_b;

		if (col_a != row_b) {
			cout << "Multiplication of matrices A & B is invalid." << endl;
			break;
		}

		mat_A = new int*[row_a];
		mat_B = new int*[row_b];
		mat_C = new int*[row_a];

		for (int i = 0; i < row_a; i++) {
			mat_A[i] = new int[col_a];
			mat_C[i] = new int[col_b];
		}
		for (int i = 0; i < row_b; i++) {
			mat_B[i] = new int[col_b];
		}


		cout << "Enter elements of Matrix A:" << endl;
		for (int i = 0; i < row_a; i++) {
			for (int j = 0; j < col_a; j++) {
				cin >> mat_A[i][j];
			}
		}


		cout << "Enter elements of Matrix B:" << endl;
		for (int i = 0; i < row_b; i++) {
			for (int j = 0; j < col_b; j++) {
				cin >> mat_B[i][j];
			}
		}

		for (int i = 0; i < row_a; i++) {
			for (int j = 0; j < col_b; j++) {
				mat_C[i][j] = 0;
			}
		}


		for (int i = 0; i < row_a; i++) {
			for (int j = 0; j < col_b; j++) {
				for (int k = 0; k < col_a; k++) {
					mat_C[i][j] += mat_A[i][k] * mat_B[k][j];
				}
			}
		}

		cout << "Resultant Matrix after Multiplication:" << endl;
		for (int i = 0; i < row_a; i++) {
			for (int j = 0; j < col_b; j++) {
				cout << mat_C[i][j] << " ";
			}
			cout << endl;
		}

		for (int i = 0; i < row_a; i++) {
			delete[] mat_A[i];
			delete[] mat_C[i];
		}
		for (int i = 0; i < row_b; i++) {
			delete[] mat_B[i];
		}
		delete[] mat_A;
		delete[] mat_B;
		delete[] mat_C;

		break; // Prevent fall-through

	default:
		cout << "Invalid choice!" << endl;
	}
	return 0;
}
int scalar_multiplication() {
	int matrix, scalar;
	cout << "Choose matrix size: 1. 2x2, 2. 3x3, 3. Input Row x Column: " << endl;
	cin >> matrix;
	cout << "Enter scalar integer: " << endl;
	cin >> scalar;

	int a, b, c, d, e, f, g, h, i, j, k;
	int a11, a12, a13;
	int a21, a22, a23;
	int a31, a32, a33;

	switch(matrix) {
	case 1:
		cout << "Enter 4 integers for 2x2 matrix: " << endl;
		cin >> a;
		cin >> b;
		cin >> c;
		cin >> d;

		a11 = scalar * a;
		a12 = scalar * b;
		a21 = scalar * 3;
		a22 = scalar *3;
		cout << "Your " << scalar << "A matrix is:\n"
		     << a11 << "\t" << a12 << "\n"
		     << a21 << "\t" << a22 << endl;
		break;

	case 2:
		cout << "Enter 9 integers for 3x3 matrix: " << endl;
		cin >> a;
		cin >> b;
		cin >> c;
		cin >> d;
		cin >> e;
		cin >> f;
		cin >> g;
		cin >> h;
		cin >> i;

		a11 = scalar * a;
		a12 = scalar * b;
		a13 = scalar * c;
		a21 = scalar * d;
		a22 = scalar * e;
		a23 = scalar * f;
		a31 = scalar * g;
		a32 = scalar * h;
		a33 = scalar * i;

		cout << "Your " << scalar << "A matrix is:\n"
		     << a11 << "\t" << a12 << "\t" << a13 << "\n"
		     << a21 << "\t" << a22 << "\t"<< a23 << "\n"
		     << a31 << "\t" << a32 << "\t"<< a33 << "\n" << endl;
		break;

	case 3:
		int row_a, col_a;
		cout << "Enter rows and columns of Matrix A: ";
		cin >> row_a >> col_a;

		int mat_A[row_a][col_a];

		cout << "Enter elements of Matrix A:\n";
		for (int i = 0; i < row_a; i++) {
			for (int j = 0; j < col_a; j++) {
				cin >> mat_A[i][j];
			}
		}

		for (int i = 0; i < row_a; i++) {
			for (int j = 0; j < col_a; j++) {
				mat_A[i][j] *= scalar;
			}
		}

		cout << "Your " << scalar << "A matrix is:\n";
		for (int i = 0; i < row_a; i++) {
			for (int j = 0; j < col_a; j++) {
				cout << mat_A[i][j] << "  ";
			}
			cout << endl;
		}

		return 0;
	}
	return 0;
}


int main() {
    cout << "Welcome to the Matrix Calculator!" << endl;
    int operation, loop, multi_choice;
    
    do {
        cout << "How can we help you today?" << endl;
        cout << "1. Addition." << " " << "2. Subtraction." << " " << "3. Multiplication. " << endl;
        
        
        cin >> operation;
    
        if (operation == 1) {
            addition();  }
        else if (operation == 2) {
            subtraction();  }
        else if (operation == 3) {
            cout << "Press 1 for Matrix Multiplication, 2 for Scalar Multiplication.";
            cin >> multi_choice;
            switch(multi_choice) {
                case 1:
                mat_multiplication();
                break;
                case 2:
                scalar_multiplication();
                break;
                default:
                cout << "Invalid choice!";
                break; }
                }
            
        cout << "Do you want to do another operation? Press 1 if Yes, 0 if no." << endl;
        cin >> loop;
        
    } while (loop == 1);
     
    cout << "Thank you. Exiting program.." << endl;
    return 0;
}
    
