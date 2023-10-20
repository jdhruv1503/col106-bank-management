// -----------------------


#include<iostream>
using namespace std;

void print_bankstor(LinearProbing * mychain) {

    for (int i=0; i<200003; i++) {
        
        if (mychain->bankStorage1d[i].balance > -1) {
            cout << "hash " << i << ": " << mychain->bankStorage2d[i][0].id << "  " << mychain->bankStorage2d[i][0].balance << endl;
        }

    }

}

int main() {

    LinearProbing * mychain = new LinearProbing();

    mychain->createAccount("CDAD7786825_7990768648",648);
    mychain->createAccount("DCDA7547234_9919615552",552);
    mychain->createAccount("AACB1850545_7974534788",788);
    cout << mychain->databaseSize() << endl;

    mychain->createAccount("CDBD5250777_1124276711",711);
    mychain->createAccount("ABCB8377155_0656808575",575);
    cout << mychain->getTopK(1)[0] << endl;
    mychain->createAccount("CDDC3792028_3313680038",38);
    mychain->createAccount("CBBA9574444_7470182321",321);
    mychain->createAccount("DBCC4334636_8057544188",188);
    cout << mychain->getTopK(3)[0] << mychain->getTopK(3)[1] << mychain->getTopK(3)[2] << endl;

    mychain->createAccount("BABD5741078_5109455304",304);
    mychain->createAccount("BCBA7529510_0817878868",868);
    cout << mychain->databaseSize() << endl;
    cout << mychain->getTopK(1)[0] << endl;
    mychain->addTransaction("BCBA7529510_0817878868", -860);
    cout << mychain->getBalance("BCBA7529510_0817878868") << endl;
    cout << mychain->getTopK(1)[0] << endl;
    mychain->addTransaction("DCDA7547234_9919615552", 592);
    cout << mychain->getTopK(5)[0] << mychain->getTopK(5)[1] << mychain->getTopK(5)[2] << mychain->getTopK(5)[3] << mychain->getTopK(5)[4] << endl;
    mychain->deleteAccount("DCDA7547234_9919615552");
    cout << mychain->getTopK(4)[0] << mychain->getTopK(4)[1] << mychain->getTopK(4)[2] << mychain->getTopK(4)[3]<< endl;
    cout << mychain->databaseSize() << endl;
}