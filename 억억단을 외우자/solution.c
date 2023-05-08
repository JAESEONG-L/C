#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define E_MAX 5000000
#define PRIME_MAX 331   // The number of prime numbers l.e. sqrt(E_MAX).

// starts_len은 배열 starts의 길이입니다.
int* solution(int e, int starts[], size_t starts_len) {
    static int answers[E_MAX];
    static int dp[E_MAX]= {1, 2, 2, };  // One appears once, two appears twice, and three appears twice in the matrix.
    int powerNums[12][23]= {{0, }, {0, }, {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304}, {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, }, {0, }, {1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125, }, {0, }, {1, 7, 49, 343, 2401, 16807, 117649, 823543, }, {0, }, {0, }, {0, }, {1, 11, 121, 1331, 14641, 161051, 1771561, }};
    int primes[PRIME_MAX+1];
    int primeCount= 0;
    
    for(int num= 2; num<=sqrt(e); num++) {
        int sqrtNum= (int) sqrt(num);
        int d= 2;
        
        while(d<=sqrtNum && num%d!=0)
        {
            d++;
        }
        
        if(d==sqrtNum+1) {
            primes[primeCount++]= num;
        }
    }
    
    primes[primeCount++]= 1;
    
    int pnCounts[12]= {0, 0, 22, 14, 0, 9, 0, 7, 0, 0, 0, 6};   // Look up for powerNums[][].
    
    // Calculates dp[].
    for(int num= 4; num<=e; num++) {
        int i= 0;
        
        while(num%primes[i])
        {
            i++;
        }
        
        if(i==primeCount-1) {
            dp[num-1]= 2;
            
            continue;
        }
        
        int primeFactor= primes[i];
        
        if(primeFactor<=11) {
            int left= 1, right= pnCounts[primeFactor];
            int exponent;
            
            do
            {
                int mid= (left+right)/2;
                
                if(num%powerNums[primeFactor][mid]==0) {
                    exponent= mid;
                    
                    left= mid+1;
                } else {
                    right= mid-1;
                }
            } while(left<=right);
            
            dp[num-1]= dp[(num/powerNums[primeFactor][exponent])-1]*(exponent+1);
        } else {
            int exponent= 1;
            int temp= num/primeFactor;
            
            while(temp%primeFactor==0)
            {
                exponent++;
                
                temp/= primeFactor;
            }
            
            dp[num-1]= dp[(num/(int) pow(primeFactor, exponent))-1]*(exponent+1);
        }
    }
    
    int max= -1;
    
    for(int num= e; num>=1; num--) {
        if(dp[num-1]<max) {
            answers[num-1]= answers[num];
        } else if(dp[num-1]==max) {
            answers[num-1]= num;
        } else {
            answers[num-1]= num;
            
            max= dp[num-1];
        }
    }
    
    int * answer= (int*) malloc(starts_len*sizeof(int));
    
    for(int i= 0; i<starts_len; i++) {
        answer[i]= answers[starts[i]-1];
    }
    
    return answer;
}
