#include<iostream>
#include<string>
#include<vector>
#include<limits.h>
#include <utility>

/*Definitions for easy typing*/
typedef std::string ss;
typedef std::vector<int> v;
typedef std::vector<v> vv;
typedef std::vector<std::pair<int,int>> vp;
typedef std::vector<vp> vvp;
typedef std::vector<char> vc;
/*Needleman-Wunsch function, returns the optimal score*/
int ndlw(ss X, ss Y, int i, int j, vv &M, vvp &P);
/*Function that prints the optimal sequence.*/
void printndlw(ss X, ss Y, int i, int j, vvp P, vc &R1, vc &R2);

int main(void){
    ss S1; //Sequence X
    ss S2; //Sequence Y
    std::cout<<"Ingrese la cadena 1"<<'\n';
    std::cin>>S1;
    getchar(); // Buffer thing
    std::cout<<"Ingrese la cadena 2"<<'\n';
    std::cin>>S2;

    size_t size1 = S1.size(); //Size of X
    size_t size2 = S2.size(); //Size of Y
    vc R1; //Vector of chars that contains the optimal X sequence
    vc R2; //Vector of chars that contains the optimal Y sequence
    vv mat(size1+1);//Matrix that contains the scores
    /*Initialize the Matrix with minus inf*/
    for(int i = 0; i < size1+1; ++i){
        for(int j = 0; j < size2+1; ++j){
            mat[i].push_back(INT_MIN);
        }
    }
    vvp b(size1+1); //Matrix that contains the optimal path
    /*Initialize the Matrix with minus one values*/
    for(int i = 0; i < size1+1; ++i){
        for(int j = 0; j < size2+1;++j){
            b[i].push_back({-1,-1});
        }
    }std::cout<<'\n'<<'\n';
    /*Call to the main function that returns the optimal score*/
    std::cout<<"Score: " << ndlw(S1,S2,size1,size2,mat,b) << std::endl;
    /*Print the optimal X and Y sequences*/
    printndlw(S1,S2,size1,size2,b,R1,R2);
    for(int i = 0; i < R2.size(); ++i){
        std::cout<<R2[i];
    }std::cout<<'\n';

    for(int i = 0; i < R1.size(); ++i){
        std::cout<<R1[i];
    }std::cout<<'\n';
    return 0;
}

int ndlw(ss X, ss Y, int i, int j, vv &M, vvp &P){
    //This is the memoization step
    if(M[i][j] > INT_MIN)
        return M[i][j];
    //Base case
    if(i == 0 && j == 0)
        return M[i][j] = 0;
    //Base case 2 empty strings
    if(i == 0 || j == 0){
        if(i > 0)
            return M[i][j] = ndlw(X,Y,i-1,j,M,P) - 2;
        if(j > 0)
            return M[i][j] = ndlw(X,Y,i,j-1,M,P) - 2;
    }
    //What happens if we got a match between chars
    if(X[i-1] == Y[j-1]){
        //We choose the maximum between the upper, left and diagonal cells.
        //Those cases represent match, missmatch and a gap in X or Y.
        int val = std::max(ndlw(X,Y,i-1,j,M,P) - 2, ndlw(X,Y,i,j-1,M,P) - 2);
        int valf = std::max(val, ndlw(X,Y,i-1,j-1,M,P) + 1);
        //After we got the optimal score for this chars we trace back to get the pos
        if(valf == M[i-1][j-1] + 1){
            P[i][j] = {i-1,j-1};
        }if(valf == M[i-1][j] - 2){
            P[i][j] = {i-1,j};
        }if(valf == M[i][j-1] - 2){
            P[i][j] = {i,j-1};
        }
        //We return the optimal score for this case
        return M[i][j] = valf;
    }
    //Same as above but with a missmatch instead of a match
    int val = std::max(ndlw(X,Y,i-1,j,M,P) - 2, ndlw(X,Y,i,j-1,M,P) - 2);
    int valf = std::max(val, ndlw(X,Y,i-1,j-1,M,P) - 1);
    if(valf == M[i-1][j-1] - 1){
        P[i][j] = {i-1,j-1};
    }if(valf == M[i-1][j] - 2){
        P[i][j] = {i-1,j};
    }if(valf == M[i][j-1] - 2){
        P[i][j] = {i,j-1};
    }
    return M[i][j] = valf; 
}

void printndlw(ss X, ss Y, int i, int j, vvp P, vc &R1, vc &R2){
    //Pair things for easy typing
    std::pair<int,int> diag = {i-1,j-1};
    std::pair<int,int> left = {i,j-1};
    std::pair<int,int> up = {i-1,j};
    //Base case
    if(i < 0 || j < 0){
        return;
    }
    //Base case two, the beginning of times
    if(i == 0 && j == 0){
        R1.push_back(X[i]);
        R2.push_back(Y[j]);
        return; 
    //If the optimal is a match/missmatch
    }else if(P[i][j] == diag){
        printndlw(X,Y,i-1,j-1,P,R1,R2);
        if(i-1 != 0 && j-1 != 0){
            R1.push_back(X[i-1]);
            R2.push_back(Y[j-1]);
        }
    //A gap for X
    }else if(P[i][j] == left){
        printndlw(X,Y,i,j-1,P,R1,R2);
        R1.push_back('-');
        R2.push_back(Y[j-1]);
    //A gap for Y
    }else if(P[i][j] == up){
        printndlw(X,Y,i-1,j,P,R1,R2);
        R1.push_back(X[i-1]);
        R2.push_back('-');
    }
}
