#include<iostream>
#include<string>
#include<vector>
#include<limits.h>
#include <utility>

typedef std::string ss;
typedef std::vector<int> v;
typedef std::vector<v> vv;
typedef std::vector<std::pair<int,int>> vp;
typedef std::vector<vp> vvp;
typedef std::vector<char> vc;

int ndlw(ss X, ss Y, int i, int j, vv &M, vvp &P);
void printndlw(ss X, ss Y, int i, int j, vvp P, vc &R1, vc &R2);

int main(void){
    ss S1;
    ss S2;
    std::cout<<"Ingrese la cadena 1"<<'\n';
    std::cin>>S1;
    getchar();
    std::cout<<"Ingrese la cadena 2"<<'\n';
    std::cin>>S2;

    size_t size1 = S1.size();
    size_t size2 = S2.size();
    vc R1;
    vc R2;
    vv mat(size1+1);
    for(int i = 0; i < size1+1; ++i){
        for(int j = 0; j < size2+1; ++j){
            mat[i].push_back(INT_MIN);
        }
    }
    vvp b(size1+1);
    for(int i = 0; i < size1+1; ++i){
        for(int j = 0; j < size2+1;++j){
            b[i].push_back({-1,-1});
        }
    }std::cout<<'\n'<<'\n';
    std::cout<<"Score: " << ndlw(S1,S2,size1,size2,mat,b) << std::endl;
   /* std::cout << "Contenidos" << std::endl;
   for(int i = 0; i < size1+1; ++i){
        for(int j = 0; j < size2+1; ++j){
            std::cout << mat[i][j] <<" ";
        }
        std::cout<<std::endl;
    }*/
   /*for(int i = 0; i < size1+1; ++i){
        for(int j = 0; j < size2+1; ++j){
            std::cout << b[i][j].first <<","<<b[i][j].second<<" ";
        }
        std::cout<<std::endl;
    }*/
    printndlw(S1,S2,size1,size2,b,R1,R2);
    //std::cout<<R1.size()<<'\n';
    for(int i = 0; i < R2.size(); ++i){
        std::cout<<R2[i];
    }std::cout<<'\n';
    //std::cout<<R2.size()<<'\n';
    for(int i = 0; i < R1.size(); ++i){
        std::cout<<R1[i];
    }std::cout<<'\n';
    return 0;
}

int ndlw(ss X, ss Y, int i, int j, vv &M, vvp &P){
    //std::cout << i << ", " << j << std::endl;
    if(M[i][j] > INT_MIN)
        return M[i][j];
    if(i == 0 && j == 0)
        return M[i][j] = 0;
    if(i == 0 || j == 0){
        if(i > 0)
            return M[i][j] = ndlw(X,Y,i-1,j,M,P) - 2;
        if(j > 0)
            return M[i][j] = ndlw(X,Y,i,j-1,M,P) - 2;
    }
    if(X[i-1] == Y[j-1]){
        int val = std::max(ndlw(X,Y,i-1,j,M,P) - 2, ndlw(X,Y,i,j-1,M,P) - 2);
        int valf = std::max(val, ndlw(X,Y,i-1,j-1,M,P) + 1);
        if(valf == M[i-1][j-1] + 1){
            P[i][j] = {i-1,j-1};
        }if(valf == M[i-1][j] - 2){
            P[i][j] = {i-1,j};
        }if(valf == M[i][j-1] - 2){
            P[i][j] = {i,j-1};
        }
        return M[i][j] = valf;
    }
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
   // std::cout << i << " " << j << '\n';
    std::pair<int,int> diag = {i-1,j-1};
    std::pair<int,int> left = {i,j-1};
    std::pair<int,int> up = {i-1,j};
    if(i < 0 || j < 0){
        return;
    }
    if(i == 0 && j == 0){
       // std::cout << X[i] << "," << Y[j] << '\n';
        R1.push_back(X[i]);
        R2.push_back(Y[j]);
        return; 
    }else if(P[i][j] == diag){
       // std::cout<<i-1<< "," <<j-1<<'\n';
        printndlw(X,Y,i-1,j-1,P,R1,R2);
       // std::cout<<X[i-1]<< "," <<Y[j-1]<<'\n';
        if(i-1 != 0 && j-1 != 0){
            R1.push_back(X[i-1]);
            R2.push_back(Y[j-1]);
        }
    }else if(P[i][j] == left){
       // std::cout<<i<< "," <<j-1<<'\n';
        printndlw(X,Y,i,j-1,P,R1,R2);
       // std::cout<<'-'<< "," <<Y[j-1]<<'\n';
        R1.push_back('-');
        R2.push_back(Y[j-1]);
    }else if(P[i][j] == up){
       // std::cout<<i-1<< "," <<j<<'\n';
        printndlw(X,Y,i-1,j,P,R1,R2);
       // std::cout<<X[i-1]<< "," <<'-'<<'\n';
        R1.push_back(X[i-1]);
        R2.push_back('-');
    }
}
