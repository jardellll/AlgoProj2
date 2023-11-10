#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

double getProb (int w, int h, int s, double* states, int encodedState){

    int encodedState2 = encodedState;
    int decodedState = 0;
    //int power = 0;

    int power = 0;
    int predStates[w];
    int index = -1;
    int mul = 1;
    int curState = encodedState;


    while (encodedState > 0) {
        int digit = encodedState % 10;
        decodedState += digit * pow(h+1, power);
        // encodedState /= 10;
        // ++power;

        mul *= 10;
        //int digit = encodedState2 % 10;
        index++;
        predStates[index] = curState + mul;


        encodedState /= 10;
        ++power;
    }
    if (states[decodedState] != -1.0){
        return states[decodedState];
    }
    else{
        bool winner = true;
        if (decodedState > 0){
            
        }
        while (decodedState > 0) {
            int digit = decodedState % 10;
            if (digit == h){
                printf("in the losing state\n");
                states[decodedState] = 0;
                return 0; //losing state
            }
            if (digit < s){
                winner = false;
            }
        }
        if (decodedState == 0){
            winner = false;
        }
        if (winner == true){
            printf("in the winning state\n");
            states[decodedState] = 1;
            return 1;  // all the cols are equal to or  greater than the s value, so this is a winner
        }
        else{
            
            // int power = 0;
            // int predStates[w];
            // int index = -1;
            // int mul = 1;
            // int curState = encodedState2;
            // while (encodedState2 > 0) {
            //     index++;
            //     predStates[index] = curState + mul;
            //     mul *= 10;
            //     int digit = encodedState2 % 10;
            //     //decodedState += digit * pow(h+1, power);
            //     encodedState2 /= 10;
            //     ++power;
            // }
            double predProbs = 0.0;
            for (int i = 0; i < w; i++){
                predProbs += getProb(w,h,s, states, predStates[i]);
            }

            printf("this is one to calculate");
            states[decodedState] = predProbs / w ;
            return predProbs / w ;
            

        }
    }
}

int main(int argc, char *argv[]){

    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    int s = atoi(argv[3]);

    printf("this is the width: %d\n", w);
    printf("this is the height: %d\n", h);
    printf("this is the num lines to win: %d\n", s);

    int mul = 1;
    int maxBaseHplus1Num = 0;
    for (int i =0; i < w; i++){
        printf("the num is %d, the mul is %d\n", maxBaseHplus1Num, mul);
        maxBaseHplus1Num += h * mul;
        mul *= 10;
    }
    
    printf("the max base %d number is %d\n", h , maxBaseHplus1Num);

    int arraySize = 0;
    int power = 0;
    while (maxBaseHplus1Num > 0) {
        int digit = maxBaseHplus1Num % 10;
        arraySize += digit * pow(h+1, power);
        maxBaseHplus1Num /= 10;
        ++power;
    }

    printf("the size the array needs to be is %d", arraySize);

    //double states [arraySize] = {-1.0};
    double* states = new double[arraySize];
    fill(states, states + arraySize, -1.0);

    double prob = getProb(w,h,s, states, 0);
    printf(" this is the prob:%f", prob);

    for (int i =0; i < arraySize; i++){
        printf("at i:%d = %f\n", i, states[i]);
    }
    

    printf("jello world\n");

    return 0;
}