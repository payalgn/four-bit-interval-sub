#include <stdio.h>
#include <stdlib.h>


int sanity(int low, int high)
{
// checking low and high within 0 to 15 and low >= high

        int ret = 0;

        if(low<0 || high<0)
                ret = -1;
        if(low>15 || high>15)
                ret = -1;
        if(low>=high)
                ret = -1;
        return ret;
}


main(int argc, char *argv[])
{
    int low1,high1,low2,high2;
    int inter_low, inter_high;
    int low_out, high_out;
    int i;

    low1 = atoi(argv[1]);
    high1 = atoi(argv[2]);
    low2 = atoi(argv[3]);
    high2 = atoi(argv[4]);

    if(sanity(low1,high1)<0){
        printf("Check arguments for first tuple\n");
        exit(1);
    }
    if(sanity(low2,high2)<0){
        printf("Check arguments for second tuple\n");
        exit(1);
    }
    // Checking for wrap arounds ... if low>high then it has wrapped around from -ve
    if(low1>high1)
        low1 = low1-16;
    if(low2>high2)
        low2 = low2-16;
    // Interval subtraction (low1,high1) - (low2,high2) = (low1-high2, high1-low2)
    low_out = low1-high2;
    high_out = high1-low2;
    // wrapping around for overflow
    if(low_out < 0)
        inter_low = low_out+16;
    else
        inter_low = low_out;
    if(high_out < 0)
        inter_high = high_out+16;
    else
        inter_high = high_out;

    if(inter_low == inter_high){
        low_out = 0;
        high_out = 15;
    }

    printf("output interval domain = { %d,%d } --> ",inter_low, inter_high);
    printf("{");
    for(i = low_out;i<=high_out;i++){
        if(i<0)
          printf("%d,",i+16);
        else
          printf("%d,",i);
    }
    printf("}\n");
  }

/* Sample input and output
$ ./int_sub 1 15 0 2
output interval domain = { 15,15 } --> {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,}
$ ./int_sub 3 8 1 7
output interval domain = { 12,7 } --> {12,13,14,15,0,1,2,3,4,5,6,7,}
$ ./int_sub 6 12 9 0
Check arguments for second tuple
$ ./int_sub 6 12 1 3
output interval domain = { 3,11 } --> {3,4,5,6,7,8,9,10,11,}
*/
