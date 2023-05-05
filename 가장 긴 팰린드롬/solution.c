#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* s) {
    const unsigned int len= (unsigned int) strlen(s);
    
    int answer= 1;
    
    // Loop handles even lengths.
    for(int i= 0; i<=len-2; i++) {
        int num= 0;
        
        do
        {
            num+= 2;
        } while(0<=i-num/2+1 && i+num/2<len && s[i-num/2+1]==s[i+num/2]);
        
        if(answer<num-2) {
            answer= num-2;
        }
    }
    
    // Loop handles odd lengths.
    for(int i= 1; i<len-1; i++) {
        int dist= 1;
        
        while(0<=i-dist && i+dist<len && s[i-dist]==s[i+dist])
        {
            dist++;
        }
        
        dist--;
        
        if(answer<1+dist*2) {
            answer= 1+dist*2;
        }
    }
    
    return answer;
}
