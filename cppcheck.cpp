#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

void abssort(float* x, unsigned n) {
    std::sort(x, x + n,
        // Lambda expression begins
        [](float a, float b) {
            return (std::abs(a) < std::abs(b));
        } // end of lambda expression
    );
}

int main(){
	cout << __cplusplus << endl;
}