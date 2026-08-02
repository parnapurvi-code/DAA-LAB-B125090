/*Fair vs Biased coin: Using simulation in C, show that the probability of getting a HEAD by tossing a
 fair coin is about 0.5. Extend your simulation to compare fair vs biased coin-tossing experiments. 
 [Interesting Read] Check this article on arXiv titled “Random Coin Tossing with unknown bias” for more insight.*/

 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>


 int main(){
    int n,i;
    int fairHeads=0,biasedHeads=0;
    printf("Enter number of tosses");
    scanf("%d",&n);

    srand(time(NULL));//sets the starting point for some random no. generator and gives the time in sec

    //fair coin
    for(int i=0;i<n;i++){
        if(rand()%2==0){
            fairHeads++;
        }
    }

    //Biased coin(80% Heads)

    for(int i=0;i<n;i++){
        int r=rand()%10;
        if(r<8)biasedHeads++;
    }

    printf("Fair coin heads=%d\n",fairHeads);
    printf("probability=%0.2f",(float)fairHeads/n);

    printf("Biased Coin heads=%d\n",biasedHeads);
    printf("probability=%0.2f",(float)biasedHeads/n);
    return 0;
 }