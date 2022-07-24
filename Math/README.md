# Reduced row-echelon form

```c
#include <bits/stdc++.h>
using namespace std;

int makeItOne ( vector<vector<double>> &mat , int row ) {

		double x = 1 , col;
	    for ( int cell = 0; cell < mat[row].size(); cell++ ) {
			if ( mat[row][cell] != 0 && mat[row][cell] != 1) {
				x = mat[row][cell] ;
				col = cell;
                break;
			}
			else if ( mat[row][cell] == 1) {
                col = cell;
                break;
			}
	    }

    for ( int cell = col; cell < mat[row].size() && x != 1; cell++ )
			mat[row][cell] /= x;

    return col;
}
void makeItZero ( vector<vector<double>>&mat , int row , int col ) {
        double x;
    for ( int i = row; i < mat.size(); i++ ) {

            if ( mat[i][col] != 0 ) {
					x =  mat[i][col];

            for ( int cell = col; cell < mat[row].size(); cell++ )
                mat[i][cell] +=  -1 * x * mat[row-1][cell];
        }
    }
}
void setCells ( vector<vector<double>> &mat , int rows , int cols  ) {

    for ( int row = 0; row < rows; row++ ) {
        for ( int cell = 0; cell < cols; cell++ ) {
            int element;
            cin >> element;
            mat[row].push_back(element);
        }

        // Put the row which it's first cell is one in the first row i
        if (mat[row][0] == 1 && mat[0][0] != 1)
            swap ( mat[row] , mat[0] );

    }
}
void display( vector<vector<double>> mat ) {
      for(auto row : mat) {
        for(auto cell : row) {
            cout << cell << ' ';
        }
        cout << '\n';
    }

}
int main() {

    cin.tie(0);
    cin.sync_with_stdio(0);

    int rows, cols;
    cin >> rows >> cols;

    vector <vector<double>> mat(rows);
    setCells (mat , rows , cols);


        // Reduce to row-echelon form
   for ( int row = 0; row < rows-1; row++ ) {
            int col = makeItOne(mat , row);
            makeItZero(mat , row+1 , col);
   }
        // For the last row
             int col = makeItOne(mat , mat.size()-1);

        // Print the matrix
    display(mat);

}


```
