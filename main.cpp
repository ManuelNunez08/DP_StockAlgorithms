#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> task1(vector<vector<int>>& A) {
    int m = A.size();
    int n = A[0].size();
    int max_profit = INT_MIN;  // Set to negative infinity to always return a transaction, even if the profit is negative
    vector<int> best_transaction(3);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int profit = A[i][k] - A[i][j];
                if (profit > max_profit) {
                    max_profit = profit;
                    best_transaction[0] = i;
                    best_transaction[1] = j;
                    best_transaction[2] = k;
                }
            }
        }
    }
    return best_transaction;
}
vector<int> task2(vector<vector<int>>& A) {
    int m = A.size();
    int n = A[0].size();
    int maxProfit = INT_MIN;
    int stockIndex = 0;
    int buyDay = 0;
    int sellDay = 0;
    vector<int> best_transaction(3);

    for (int i = 0; i < m; i++) { // Iterating through each stock
        // Keeping track of the minimum of each stock
        int minPrice = A[i][0];
        int minDay = 0;

        for (int j = 1; j < n; j++) { // Iterating through each day of each stock
            int profit = A[i][j] - minPrice;
            if (profit > maxProfit) { // If the profit is greater than the max profit, this is the new transaction
                maxProfit = profit;
                stockIndex = i;
                buyDay = minDay;
                sellDay = j;
            }
            if (A[i][j] < minPrice) { // Checking for a new buy day
                minPrice = A[i][j];
                minDay = j;
            }
        }
    }
    best_transaction[0] = stockIndex;
    best_transaction[1] = buyDay;
    best_transaction[2] = sellDay;
    return best_transaction;
}


int findMin( vector<int>& A, vector<int>& B, int i) {
    if (i == 0){
        B[0] = A[0];
        return A[0];
    }
    else {
        if (B[i] == -1){
            B[i] = min(A[i], findMin(A, B, i - 1));
        }
        return B[i];
    }


}

int findMax( vector<int>& A, vector<int>& B, int i, int &x, int &y) {
    if (i == 0){
        return INT_MIN;
    }
    else {
        return max((A[i] - findMin(A, B, i - 1)), findMax(A, B, i - 1, x, y));
    }
}

vector<int> task3A(vector<vector<int> >& A) {
     /*
     * starting from the right, for every company find
     *     OPT(b, s) = max{ (A[i][j]- min(A[i][j] for 0<j<A[0].size()), (OPT(b, s-1) ))
     */
    int m = A.size();
    int stockIndex = 0;
    int buyDay = 0;
    int sellDay = 0;
    vector<int> best_transaction(3);
    int maxProfit = INT_MIN;

    //temporary buy and sell days
    int x  = 0;
    int y  = 0;
    for (int i = 0; i < m; i++){
        vector<int> Empty (A[0].size(),-1);
        int profit = findMax(A[i], Empty, A[0].size() - 1, &x, &y);

        if (profit > maxProfit){
            best_transaction[0] = i;
            maxProfit = profit;
        }
    }

    return best_transaction;
}



vector<int> task3B(vector<vector<int> >& A) {
    //PREPROCESSING
    /*Create a secondary 2 dimensional array where each entry stores the max value to the right of it. The array can be
     * built in O(n^2) time by starting on the last index of each subarray and considering for each element either the
     * element to its right or the element that its right element found the largest to the right. */
    int m = A.size();
    int n = A[0].size();

    vector<vector<int> > B(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = n-1; j >= 0 ; j--) {
            if(j == n - 1){
                B[i][j] = -1;
            }
            else if ( A[i][j+1] > B[i][j+1] ) {
                B[i][j] = A[i][j + 1];
            }
            else {
                B[i][j] = B[i][j + 1];
            }
        }
    }


    // IMPLEMENTATION
    int stockIndex = 0;
    int buyDay = 0;
    int sellDay = 0;
    int maxProfit = INT_MIN;
    vector<int> best_transaction(3);

    for (int i = 0; i < m; i++) { // Iterating through each stock
        // Keeping track of the minimum and maximum price of each stock
        int soldAt = -1;

        for (int j = 0; j < n; j++) {
            //identify date sold at
            if (A[i][j] == soldAt){
                sellDay = j;
            }
            // consider buying in every day except the last
            if (j < n-1) {
                // Iterating through each day of each stock
                int profit = B[i][j] - A[i][j];
                if (profit > maxProfit) {
                    maxProfit = profit;
                    stockIndex = i;
                    buyDay = j;
                    soldAt = B[i][j];
                    //sell day has to be found by comparing all entries to the
                }
            }
        }
    }

    best_transaction[0] = stockIndex;
    best_transaction[1] = buyDay;
    best_transaction[2] = sellDay;

    return best_transaction;

}





int main() {

    vector<vector<int>> A(5, vector<int>(5));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < A.size(); j++) {
            for (int k = 0; k < A[0].size(); k++) {
                A[j][k] = rand() % 10;
                cout << A[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;

        vector<int> task1Result = task1(A);

        cout << "Task 1 Result: " << task1Result[0] << " " << task1Result[1] << " " << task1Result[2] << endl;

        vector<int> task2Result = task2(A);

        cout << "Task 2 Result: " << task2Result[0] << " " << task2Result[1] << " " << task2Result[2] << endl;

        vector<int> task3aResult = task3A(A);

        cout << "Task 3b Result: ";
        for (i = 0; i < task3aResult.size(); i ++){
            cout << task3aResult[i] << " ";
        }

        vector<int> task3bResult = task3B(A);

        cout << endl;

        cout << "Task 3b Result: " << task3bResult[0] << " " << task3bResult[1] << " " << task3bResult[2] << endl;
        cout << endl;




    }


    int x[3][3] = {{1,2,3}, {3,5,9}, {2,3,4}};

    /* we are essentially finding the greatest percentage change in our initial investment of an arbitrary amount A.
     For the three days and three companies presented above if we start with am amount A invested in company 1,
     by day 2 we have an amount 3A. If we then sell and buy company 2, by day three we have an amount 3A* 4/5 = 12A/5.

     to calculate the transactions that maximize profit we have to consider at every day if we should buy stock
     (assuming we don't have any stock ), whether to sell our current stock (if we have any), and whether to buy stock
     (assuming we just sold our stock or don't have stock)


     Observations:
     1. We are not interested in the magnitude of a stock price, we are interested in its change over the days in question.

     2. A set of stock prices for a given company, such as {2,4,1,6}, can be represented through an array specifying changes in
        the stock price; {1,2,0.25, 6}, since day 2 has a stock price worth twice as much as day 1, day 3 has a stock price
        worth a fourth as much as day 2, etc. We call this array a derivative array.

    3. With one company, one set of stock prices (as listed above), and no limits on transactions. We can maximize profit by buying
        on all days n where day n + 1 has a value in the derivative array greater than 1 and selling on all day's where the
        derivative array has a value smaller than 1. We are indifferent on day's where the stock price equals 1.

    2. With a set of companies, a set of corresponding stock prices, and no limits on transactions, we can also create a
     derivative array. For the 2d-array shown above we have {{1,1,1}, {3,2.5,3}, {2/3,0.6,4/9}}. We can then maximize profit
     by buying stock for a company m on day n if they have the greatest n+1 derivative array value assuming a value greater than 1 exists.
     If no value greater than 1 exists we would buy nothing on day n.


     */




    return 0;
}
