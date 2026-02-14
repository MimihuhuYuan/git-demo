//利用C++实现矩阵的满秩分解
#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

using namespace std;
 
const double EPS = 1e-6;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    //目标：求矩阵A的满秩分解：A=FG
    int m,n;
    cout<<"A是一个mxn矩阵,请输入m的值:"<<endl;
    cin>>m;
    cout<<"请输入n的值:"<<endl;
    cin>>n;

    //填充矩阵
    float**a = new float *[m];
    for(int i=0;i<m;++i){
        a[i]=new float[n];
    }
    cout<<"请按照先行后列的顺序依次输入矩阵各个位置的数值:"<<endl;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            cin>>a[i][j];
        }
    }

    //拷贝矩阵A为B
    float**b = new float*[m];
    for(int i=0;i<m;++i){
        b[i]=new float[n];
        for(int j=0;j<n;++j){
            b[i][j]=a[i][j];
        }
    }


    //化行最简形
    int y=0;
    int r=0;
    int*c=new int [m];
    for(int j=0;j<n && y<m;++j){
        int k=y;
        //找最大值所在行
        for(int i=y;i<m;++i){
            if(b[i][j]*b[i][j]>b[k][j]*b[k][j]){
                k=i;
            }
        }
        if(b[k][j]==0){
            continue;
        }
        //进行第一类行变换
        if(k!=y){
            for(int q=0;q<n;++q){
                float x=b[y][q];
                b[y][q]=b[k][q];
                b[k][q]=b[y][q];
            }
            
        }
        
        //进行第三类行变换
        for(int q=j;q<n;++q){
            b[y][q]=b[y][q]/b[y][j];
        }
        for(int p=0;p<m;++p){
            if(p!=y && fabs(b[p][j])>EPS){
                for(int q=j;q<n;++q){
                    b[p][q]-=b[p][j]*b[y][q];
                }
            }
        }
        c[r++]=j;
        y++;

    }

    //输出G
    cout<<"G="<<endl;
    for(int i=0;i<r;++i){
        cout<<"| "<<left;
        for(int j=0;j<n;++j){
            cout<<setw(6)<<fixed<<setprecision(2)<<b[i][j]<<' ';
        }
        cout<<" |"<<endl;
    }   

    //输出F
    cout<<"F=";
    for(int i=0;i<m;++i){
        cout<<"| "<<left;
        for(int j=0;j<r;++j){
            cout<<setw(6)<<fixed<<setprecision(2)<<a[i][c[j]]<<' ';
        }
        cout<<" |"<<endl;
    }
    for(int i=0;i<m;++i){
        delete[] a[i];
        delete[] b[i];
    }
    delete[] a;
    delete[] b;
    delete[] c;
  
    return 0;
}