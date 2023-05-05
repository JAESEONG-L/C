#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

long long solution(int* sequence, size_t sequence_len) {
    long long answer= 0;
    
    int pulse[2]= {1, -1};
    long long accumulSum= 0;
    
    for(int i= 0; i<sequence_len; i++) {
        accumulSum+= pulse[i%2]*sequence[i];
        
        if(answer<accumulSum) {
            answer= accumulSum;
        } else if(accumulSum<0) {
            accumulSum= 0;
        }
    }
    
    pulse[0]= -1, pulse[1]= 1;
    
    accumulSum= 0;
    
    for(int i= 0; i<sequence_len; i++) {
        accumulSum+= pulse[i%2]*sequence[i];
        
        if(answer<accumulSum) {
            answer= accumulSum;
        } else if(accumulSum<0) {
            accumulSum= 0;
        }
    }
    
    return answer;
}
