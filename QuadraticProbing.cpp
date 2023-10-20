#include "QuadraticProbing.h"

QuadraticProbing::QuadraticProbing() {

    // init empty vals

    Account ac;
    ac.id = "NULLID";
    ac.balance = -1;

    for (int i=0; i<200003; i++) {
        bankStorage1d.push_back(ac);
    }
}

QuadraticProbing::~QuadraticProbing() {

    bankStorage1d.clear();

}

void QuadraticProbing::createAccount(std::string id, int count) {

    int hashid = hash(id);
    long seek;

    for (int i=0; i<200003; i++) {
        seek = hashid + i*i; // probe quadratically
        seek = seek % 200003;

        if (bankStorage1d[seek].id.compare("NULLID") == 0) {
            bankStorage1d[seek].id = id;
            bankStorage1d[seek].balance = count;
            return;
        }

    }

}

std::vector<int> QuadraticProbing::getTopK(int k) {
    std::vector<int> topk = {};

    for (int i=0; i<200003; i++) {
        
        if (bankStorage1d[i].balance > -1) {

            topk.push_back(bankStorage1d[i].balance);

            for (int i1 = 0; i1 < topk.size() - 1; i1++) {
                for (int j1 = 0; j1 < topk.size() - i1 - 1; j1++) {
                    if (topk[j1] > topk[j1 + 1]) {
                        std::swap(topk[j1], topk[j1 + 1]);
                    }
                }
            }

            while (topk.size() > k) {
                topk.erase(topk.begin());
            }

        }

    }
    
    // reverse topk

    for (int i = 0, j = k-1; i<j; i++, j--) {
        std::swap(topk[i], topk[j]);
    }

    return topk;  
}

int QuadraticProbing::getBalance(std::string id) {

    int hashid = hash(id);
    long seek;

    for (int i=0; i<200003; i++) {
        seek = hashid + i*i; // probe quadratically
        seek = seek % 200003;

        if (bankStorage1d[seek].id.compare("NULLID") == 0) {
            return -1;
        }

        if (bankStorage1d[seek].id.compare(id) == 0) {
            return bankStorage1d[seek].balance;
        }

    }

    return -1;

}

void QuadraticProbing::addTransaction(std::string id, int count) {

    int hashid = hash(id);
    long seek;

    for (int i=0; i<200003; i++) {
        seek = hashid + i*i; // probe quadratically
        seek = seek % 200003;

        if (bankStorage1d[seek].id.compare("NULLID") == 0) {
            bankStorage1d[seek].id = id;

            if (count > -1) {
                bankStorage1d[seek].balance = count;
            }
            else {
                bankStorage1d[seek].balance = 0;
            }   

            return;
        }

        if (bankStorage1d[seek].id.compare(id) == 0) {

            if (bankStorage1d[seek].balance > -1) {
                if (bankStorage1d[seek].balance + count > -1) {
                    bankStorage1d[seek].balance = bankStorage1d[seek].balance + count;
                }
                else {
                    bankStorage1d[seek].balance = 0;
                }
                
            }

            else {
                if (count > -1) {
                    bankStorage1d[seek].balance = count;
                }
                else {
                    bankStorage1d[seek].balance = 0;
                }
            
            }

            return;
        }

    }
}

bool QuadraticProbing::doesExist(std::string id) {

    int hashid = hash(id);
    long seek;

    for (int i=0; i<200003; i++) {
        seek = hashid + i*i; // probe quadratically
        seek = seek % 200003;

        if (bankStorage1d[seek].id.compare("NULLID") == 0) {
            return false;
        }

        if (bankStorage1d[seek].id.compare(id) == 0) {
            if (bankStorage1d[seek].balance > -1) {
                return true;
            }
            else {
                return false;
            } 
        }

    }

    return false;

}

bool QuadraticProbing::deleteAccount(std::string id) {

    int hashid = hash(id);
    long seek;

    for (int i=0; i<200003; i++) {
        seek = hashid + i*i; // probe quadratically
        seek = seek % 200003;

        if (bankStorage1d[seek].id.compare("NULLID") == 0) {
            return false;
        }

        if (bankStorage1d[seek].id.compare(id) == 0) {
            if (bankStorage1d[seek].balance > -1) {
                bankStorage1d[seek].balance = -1;
                return true;
            }
            else {
                return false;
            } 
        }

    }

    return false;

}

int QuadraticProbing::databaseSize() {
    int sum = 0;

    for (int i=0; i<200003; i++) {
        if (bankStorage1d[i].balance > -1) {
            sum += 1;
        }
    }

    return sum;
}

int QuadraticProbing::hash(std::string id) {

    // take ascii val after '0' and store as base-(122-48+1)=BASE75 number

    int sum = 0;

    for (int i=0; i<id.size(); i++) {
        
        sum = sum*75 + int(id[i]) - int('0');

        sum = sum % 200003;

    }

    return sum;

}