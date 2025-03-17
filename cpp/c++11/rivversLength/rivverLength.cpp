#include <vector>
using namespace std;

int length(vector<vector<int>>& matrix, int i, int j){
    matrix[i][j] = 0;  
    int size = 1; 
     int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto& dir : directions) {
        int new_i = i + dir[0];
        int new_j = j + dir[1];
        if (new_i >= 0 && new_i < int(matrix.size()) && new_j >= 0 && new_j < int(matrix[0].size()) && matrix[new_i][new_j] == 1) {
            size += length(matrix, new_i, new_j);
        }
    }
    return size;
}
    
   

vector<int> riverSizes(vector<vector<int>> matrix) {
    vector<int> result;
    vector<vector<int>>& matrixRef = matrix;
  for(int i = 0 ; i < int(matrix.size()); i++){
    for(int j = 0 ; j < int(matrixRef[0].size()); j++){
      if(matrixRef[i][j] == 1){
        result.push_back(length(matrixRef, i, j));
      }
    }
  }
  return result;
}

