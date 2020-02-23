#include <iostream>
#include "lib.h"
using namespace std;

int main() {
    cout << "Enter the place of departure :";
    string dep  = " ";
    cin >> dep;

    cout << "Enter the place of arrival :";
    string arriv = " ";
    cin >> arriv;

    int min = MAX;
    try{
        min = findMinWay("../src", dep, arriv);
        if ((min != 0)&&(min!=MAX)){
            cout << "Minimal way from " << dep << " to " << arriv << " equal " << min ;
        } else {
            cout << "There are no ways from " << dep << " to " << arriv ;
        }
    }
    catch(bad_alloc &e){
            cout << "File doesnt exist or you have not allow.";
        }
    catch(out_of_range &e){
        cout << e.what();
    }
    return 0;
}


