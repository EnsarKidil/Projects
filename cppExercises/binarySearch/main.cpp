#include <iostream>
using namespace std;

class Search {
public:
   static int linear(int a[],int b) {
      for(int i=0; i<10; i++) {
         // cout << i << endl;
         if (a[i]==b){
            return i+1;
         }
      }
      return NULL;
   }
   static int binary(int a[],int b,int c,int d) {
      int mid=(d+c)/2;

      if(a[mid]>b) {
         return binary(a,b,c,(mid-1));
      }

      if(a[mid]<b) {
         return binary(a,b,mid+1,d);
      }

      return mid;

   }
};


int main() {
   int A[10]={1,2,3,4,5,6,7,8,9};
   int f = 2;
   return 0;
}
