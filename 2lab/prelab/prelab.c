#include <stdio.h>

// morse is a function that accepts an integer of value 0 to 10, and returns a
// the lowest five bits carry the encoding.
// 1 is long (dah), 0 is short (dit)

unsigned int morse(int n){
  unsigned int lut[10] = {31,15,7,3,1,0,16,24,28,30};
  if((n >= 0) || (n < 10)){
    return lut[n];
  }
  else return -1;
}

void bin(unsigned n){
  unsigned i;
  for (i = 1 << 30; i > 0; i /= 2){
    if(i <= 16) (n & i)? printf("1"): printf("0");
  }
}

int main(){
  unsigned i;
  for(i = 0; i < 10; i++){
    printf("%d->",i);
    bin(morse(i));
    printf("\n");
  }
  return 0;
}
