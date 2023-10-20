#include "Chaining.h"

Chaining::Chaining() {

    for (int i=0; i<200003; i++) {
        bankStorage2d.push_back({});
    }

}

Chaining::~Chaining() {

    bankStorage2d.clear();

}

void Chaining::createAccount(std::string id, int count) {

    Account ac;
    ac.id = id;
    ac.balance = count;

    bankStorage2d[hash(id)].push_back(ac);

}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> topk = {};
    
    for (int i=0; i<200003; i++) {

        for (int j=0; j<bankStorage2d[i].size(); j++) {

            if (bankStorage2d[i][j].balance > -1) {
                topk.push_back(bankStorage2d[i][j].balance);

                // bubble sort topk

                for (int i1 = 0; i1 < topk.size() - 1; i1++) {
                    for (int j1 = 0; j1 < topk.size() - i1 - 1; j1++) {
                        if (topk[j1] > topk[j1 + 1]) {
                            std::swap(topk[j1], topk[j1 + 1]);
                        }

                    }

                }


            }

            
            // trim topk

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

int Chaining::getBalance(std::string id) {

    int hashid = hash(id);
    
    for(int i=0; i<bankStorage2d[hashid].size(); i++) {
        if (bankStorage2d[hashid][i].id.compare(id) == 0) {
            return bankStorage2d[hashid][i].balance;
        }
    }

    return -1;
}

void Chaining::addTransaction(std::string id, int count) {

    int hashid = hash(id);
    bool flag = false;


    for(int i=0; i<bankStorage2d[hashid].size(); i++) {
        if (bankStorage2d[hashid][i].id.compare(id) == 0) {

            if(bankStorage2d[hashid][i].balance == -1) {

                if (count < 0) {
                    bankStorage2d[hashid][i].balance = 0;
                }
                else {
                    bankStorage2d[hashid][i].balance = count;
                }
                
            }
            
            else {

                if ((bankStorage2d[hashid][i].balance + count) < 0) {
                    bankStorage2d[hashid][i].balance = 0;
                }
                else {
                    bankStorage2d[hashid][i].balance += count;
                }

            }

            flag = true;
            
        }
    }

    if (!flag) {
        Account ac;
        ac.id = id;

        if (count < 0) {
            ac.balance = 0;
        }
        else {
            ac.balance = count;
        }

        bankStorage2d[hashid].push_back(ac);
    }
    

}

bool Chaining::doesExist(std::string id) {

    int hashid = hash(id);
    
    for(int i=0; i<bankStorage2d[hashid].size(); i++) {
        if (bankStorage2d[hashid][i].id.compare(id) == 0 && bankStorage2d[hashid][i].balance > -1) {
            return true;
        }
    }

    return false;

}

bool Chaining::deleteAccount(std::string id) {

    int hashid = hash(id);
    
    for(int i=0; i<bankStorage2d[hashid].size(); i++) {
        if (bankStorage2d[hashid][i].id.compare(id) == 0 && bankStorage2d[hashid][i].balance > -1) {

            bankStorage2d[hashid][i].balance = -1;
            return true;

        }
    }

    return false;

}

int Chaining::databaseSize() {

    int sum = 0;
    
    for (int i=0; i<200003; i++) {

        for(int j=0; j<bankStorage2d[i].size(); j++) {
        if (bankStorage2d[i][j].balance > -1) {
            sum += 1;
        }
    }

    }

    return sum;

}

int Chaining::hash(std::string id) {

    // take ascii val after '0' and store as base-(122-48+1)=BASE75 number

    int sum = 0;

    for (int i=0; i<id.size(); i++) {
        
        sum = sum*75 + int(id[i]) - int('0');

        sum = sum % 200003;

    }

    return sum;

}