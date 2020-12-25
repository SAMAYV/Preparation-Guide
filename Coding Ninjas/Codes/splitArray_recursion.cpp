/*Given an integer array A of size N, check if the input array can be splitted in two parts such that -

- Sum of both parts is equal
- All elements in the input, which are divisible by 5 should be in same group.
- All elements in the input, which are divisible by 3 (but not divisible by 5) should be in other group.
- Elements which are neither divisible by 5 nor by 3, can be put in any group.

Groups can be made with any set of elements, i.e. elements need not to be continuous. And you need to consider each and every element of input array in some group.
Return true, if array can be split according to the above rules, else return false.*/

bool check(int* input,int size,int lsum,int rsum,int index){
    if(index==size)
        return lsum==rsum;
    if(input[index]%3==0 && input[index]%5!=0)
        lsum += input[index];
    else if(input[index]%5==0)
        rsum += input[index];
    else {
        bool b1 = check(input,size,lsum+input[index],rsum,index+1);
        bool b2 = check(input,size,lsum,rsum+input[index],index+1);
        return b1 || b2;
    }
    return check(input,size,lsum,rsum,index+1);
        
}
bool splitArray(int *input, int size) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    return check(input,size,0,0,0);
}
