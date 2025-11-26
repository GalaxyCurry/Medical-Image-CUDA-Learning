# include <iostream>
# include <limits>

using namespace std;




void imagThresholdSeg(int arr[][5], int rows, float threshold){


    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < 5; ++j){
            if (arr[i][j] >= threshold)
            {
                arr[i][j] = 1;
            }else{
                arr[i][j] = 0;
            }
            
        }
    }

}






int main(){
    int arr[5][5];

    for(int i = 0; i < 5; ++i){
        for(int j= 0; j < 5; ++j){
            arr[i][j] = 50;
        }
    }

    arr[1][1] = 180;
    arr[1][2] = 180;
    arr[1][3] = 180;
    arr[2][1] = 180;
    arr[2][2] = 180;
    arr[2][3] = 180;
    arr[3][1] = 180;
    arr[3][2] = 180;
    arr[3][3] = 180;

    float threshold = 60;
    imagThresholdSeg(arr, 5, threshold);
    

    cout << "输出的数组为" << endl;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << arr[i][j] << " ";  
        }
        cout << endl; 
    }


    return 0;

}