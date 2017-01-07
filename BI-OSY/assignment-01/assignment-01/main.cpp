#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#if defined (__cplusplus) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#endif /* C++ 11*/

using namespace std;

struct CExchange {
    CExchange(int id, const string &from, const string &to)
    : m_ProblemID(id), m_From(from), m_To(to), m_BankIdx(0), m_Result(false),
    m_Rate(0) {}
    void AddBank(const string &bank) { m_Banks.push_back(bank); }
    const int m_ProblemID;
    const string m_From;
    const string m_To;
    vector<string> m_Banks;
    
    int m_BankIdx;
    bool m_Result;
    vector<string> m_Currency;
    double m_Rate;
};

struct CArbitrage {
    CArbitrage(int id, const string &rates)
    : m_ProblemID(id), m_Rates(rates), m_Arbitrage(false), m_Rate(0) {}
    const int m_ProblemID;
    const string m_Rates;
    
    bool m_Arbitrage;
    vector<string> m_Currency;
    double m_Rate;
};
#endif /* __PROGTEST__ */



int doubleLessThan(const double a, const double b, double eps = 1e-12) {
    if(b + eps < a) return -1;
    if(a + eps < b) return 1;
    
    return 0;
}

struct Relation {
    string from;
    string to;
    string rate;
    
    Relation(const string str[]) {
        from = str[0];
        to   = str[1];
        rate = str[2];
    }
};

class Matrix {
public:
    struct ArbResult {
        ArbResult(): rate(0) {}
        
        bool arbitrage() { return currencies.size() != 0; }
        vector<string> currencies;
        double rate;
    };
    
    struct ExcResult {
        ExcResult(): rate(0) {}
        
        bool echangable() { return currencies.size() != 0; }
        vector<string> currencies;
        double rate;
    };
    
    Matrix(const set<string> & curr, const vector<Relation> & r) {
        for(const auto & i: curr) {
            currencies.push_back(i);
            positions.insert(make_pair(i, currencies.size()-1));
        }
        
        allocMatrix((int)positions.size());
        
        for(const auto &i: r)
            insertRelation(i);
    }
    
    ~Matrix() {
        for(int i=0; i < (int)positions.size(); i++) {
            delete[] matrix_data[i];
            delete[] incidence[i];
        }
        
        
        delete[] matrix_data;
        delete[] incidence;
    }
    
    ExcResult exchange(const string & f, const string & t) {
        int from = findCurrency(f);
        int to   = findCurrency(t);
        
        if(from == -1 || to == -1) return ExcResult();
        
        int size = (int) positions.size();
        
        for (int k = 0; k < size; k++)
            for(int i = 0; i < size; i++)
                for(int j = 0; j < size; j++)
                    if(doubleLessThan(matrix_data[i][j], matrix_data[i][k] * matrix_data[k][j]) == 1) {
                        matrix_data[i][j] = matrix_data[i][k] * matrix_data[k][j];
                        incidence[i][j]   = incidence[i][k];
                    }
        
        ExcResult res;
        reconstractPath(from, to, res.currencies);
        res.rate = decreasePrecision(matrix_data[from][to]);
        
        return res;
    }
    
    ArbResult arbitrage() {
        int size = (int) positions.size();
        
        for (int k = 0; k < size; k++)
            for(int i = 0; i < size; i++)
                for(int j = 0; j < size; j++)
                    if(doubleLessThan(matrix_data[i][j], matrix_data[i][k] * matrix_data[k][j]) == 1) {
                        matrix_data[i][j] = matrix_data[i][k] * matrix_data[k][j];
                        incidence[i][j]   = incidence[i][k];
                        
                        if(i == j && doubleLessThan(1.0, matrix_data[i][j]) == 1) {
                            ArbResult res;
                            res.rate = decreasePrecision(matrix_data[i][j]);
                            reconstractPath(i, j, res.currencies);
                            return res;
                        }
                    }
        
        return ArbResult();
    }
    
private:
    double ** matrix_data;
    int    ** incidence;
    map<string, int> positions;
    vector<string> currencies;
    
    void insertRelation(const Relation & r) {
        int from = positions[r.from];
        int to = positions[r.to];
        
        matrix_data[from][to] = atof(r.rate.c_str());
        incidence[from][to]   = to+1;
    }
    
    void allocMatrix(int size) {
        matrix_data = new double*[size];
        incidence   = new int*[size];
        
        for(int i = 0; i < size; i++) {
            matrix_data[i] = new double[size] {};
            incidence[i]   = new int[size] {};
        }
    }
    
    int findCurrency(const string & c) {
        auto s = positions.find(c);
        
        if(s != positions.end()) return s->second;
        
        return -1;
    }
    
    void reconstractPath(int from, int to, vector<string> & path) {
        if(incidence[from][to] == 0) return;
        
        path.push_back(currencies.at(from));
        
        do {
            from = incidence[from][to]-1;
            path.push_back(currencies.at(from));
        }
        while(from != to);
    }
    
    double decreasePrecision(double num, int precision = 10000) {
        return floor(num * precision) / (double) precision;
    }
};

class Worker {
public:
    Worker(): arbitrage(NULL), exchange(NULL) {}
    
    Worker(CArbitrage *arb)
    : arbitrage(arb), exchange(NULL) {}
    
    Worker(CExchange *ec)
    : arbitrage(NULL), exchange(ec) {}
    
    virtual ~Worker() {}
    
    virtual void execute() = 0;
    virtual int problemId() const = 0;
    
    bool notAJob() const {
        return arbitrage == NULL && exchange == NULL;
    }
    
protected:
    CArbitrage *arbitrage;
    CExchange *exchange;
    
    Matrix * parse(const string &str) {
        string components[3];
        int  strSize = (int) str.size();
        int  componentIndex = 0;
        bool inTheMiddle = false;
        char c = 'x';
        
        set<string> currencies;
        vector<Relation> relations;
        
        for(int i = 0; i <= strSize; i++) {
            if(componentIndex == 3 || i == (int) strSize) {
                relations.push_back(Relation(components));
                
                components[0] = "";
                components[1] = "";
                components[2] = "";
                
                componentIndex = 0;
                
                if(i == (int) strSize) break;
            }
            
            c = str.at(i);
            
            if(!isalnum(c) && c != '.') {
                if(inTheMiddle)
                    componentIndex++;
                
                if(componentIndex == 1 || componentIndex == 2)
                    currencies.insert(components[componentIndex-1]);
                
                inTheMiddle = false;
                continue;
            }
            
            components[componentIndex] += c;
            inTheMiddle = true;
        }
        
        if(currencies.size() > 0) return new Matrix(currencies, relations);
        
        return NULL;
    }
};

class ArbitrageWorker : public Worker {
public:
    ArbitrageWorker(CArbitrage *arb) : Worker(arb) {}
    
    void execute() {
        if(Matrix * m = parse(this->arbitrage->m_Rates)) {
            Matrix::ArbResult res = m->arbitrage();
            
            if(res.arbitrage()) {
                arbitrage->m_Arbitrage = true;
                arbitrage->m_Currency = res.currencies;
                arbitrage->m_Rate = res.rate;
            }
            
            delete m;
            return;
        }
    }
    
    int problemId() const { return arbitrage->m_ProblemID; }
private:
};

class ExchangeWorker : public Worker {
public:
    ExchangeWorker(CExchange *ec) : Worker(ec) {}
    
    void execute() {
        Matrix::ExcResult bestRate;
        int it = 0;
        int bestIt = 0;
        
        for(const auto &i: exchange->m_Banks ) {
            if(Matrix * m = parse(i)) {
                Matrix::ExcResult res = m->exchange(exchange->m_From, exchange->m_To);
                
                if((bestRate.currencies.size() == 0) || (res.echangable() && doubleLessThan(bestRate.rate, res.rate) == 1)) {
                    bestRate = res;
                    bestIt = it;
                }
                delete m;
            }
            
            it++;
        }
        
        if(bestRate.currencies.size() == 0) return;
        
        exchange->m_Result   = true;
        exchange->m_Rate     = bestRate.rate;
        exchange->m_Currency = bestRate.currencies;
        exchange->m_BankIdx  = bestIt;
    }
    
    int problemId() const { return exchange->m_ProblemID; }
private:
};

class EmptyWorker : public Worker {
public:
    EmptyWorker() : Worker() {}
    
    void execute() {}
    int  problemId() const { return -1; }
};

class CConsultant {
public:
    CConsultant(CArbitrage *(*arbitrageFn)(void), CExchange *(*exchangeFn)(void),
                void (*completed)(int))
    : arbitrageSource(arbitrageFn), exchangeSource(exchangeFn), jobsCount(0), endOfProducers(false), callback(completed) {}
    
    static void ExchangeSeq(CExchange *req) {
        ExchangeWorker worker(req);
        worker.execute();
    }
    
    static void ArbitrageSeq(CArbitrage *req) {
        ArbitrageWorker worker(req);
        worker.execute();
    }
    
    static void * Consume(CConsultant * inst) {
        Worker * worker;
        
        while(1) {
            sem_wait(&(inst->queueFull));
            pthread_mutex_lock(&(inst->queueLock));
            worker = inst->jobsQueue.front();
            
            if(worker->notAJob() == false) {
                inst->jobsQueue.pop();
            }
            
            pthread_mutex_unlock(&(inst->queueLock));
            sem_post(&(inst->queueEmptySlots));
            
            if(worker->notAJob()) { sem_post(&(inst->queueFull)); break; }
            
            worker->execute();
            inst->callback(worker->problemId());
            
            delete worker;
        }
        return NULL;
    }
    
    static void * ProduceExc(CConsultant * inst) {
        while (CExchange * exc = inst->exchangeSource()) {
            ExchangeWorker * worker = new ExchangeWorker(exc);
            
            sem_wait(&(inst->queueEmptySlots));
            pthread_mutex_lock(&(inst->queueLock));
            
            inst->jobsQueue.push(worker);
            
            pthread_mutex_unlock(&(inst->queueLock));
            sem_post(&(inst->queueFull));
        }
        
        return CConsultant::ProducentEnd(inst);
    }
    
    static void * ProduceArb(CConsultant * inst) {
        while (CArbitrage * exc = inst->arbitrageSource()) {
            ArbitrageWorker * worker = new ArbitrageWorker(exc);
            
            sem_wait(&(inst->queueEmptySlots));
            pthread_mutex_lock(&(inst->queueLock));
            
            inst->jobsQueue.push(worker);
            
            pthread_mutex_unlock(&(inst->queueLock));
            sem_post(&(inst->queueFull));
        }
        
        return CConsultant::ProducentEnd(inst);
    }
    
    static void * ProducentEnd(CConsultant * inst) {
        bool insertDummy = false;
        
        pthread_mutex_lock(&(inst->endLock));
        insertDummy = inst->endOfProducers;
        inst->endOfProducers = true;
        pthread_mutex_unlock(&(inst->endLock));
        
        if(insertDummy) {
            sem_wait(&(inst->queueEmptySlots));
            pthread_mutex_lock(&(inst->queueLock));
            
            inst->jobsQueue.push(new EmptyWorker());
            
            pthread_mutex_unlock(&(inst->queueLock));
            sem_post(&(inst->queueFull));
        }
        
        return NULL;
    }
    
    void Execute(int workers) {
        endOfProducers = false;
        createThreads(workers);
        
        for (int i = 0; i < workers + 2; i++)
            pthread_join(threads[i], NULL );
        
        while (!jobsQueue.empty()) {
            Worker * worker = jobsQueue.front();
            jobsQueue.pop();
            delete worker;
        }
        
        destroyThreads();
    }
    
private:
    CArbitrage *(*arbitrageSource)(void);
    CExchange  *(*exchangeSource)(void);
    pthread_t  *threads;
    pthread_mutex_t queueLock;
    pthread_mutex_t endLock;
    
    queue<Worker *> jobsQueue;
    int  jobsCount;
    bool endOfProducers;
    
    void (*callback)(int);
    
    sem_t queueFull;
    sem_t queueEmptySlots;
    
    void createThreads(int consuments) {
        pthread_attr_t attr;
        
        threads = new pthread_t[consuments + 2];
        
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_mutex_init(&queueLock, NULL);
        pthread_mutex_init(&endLock, NULL);
        
        sem_init(&queueEmptySlots, 0, 2 * consuments);
        sem_init(&queueFull, 0, 0);
        
        // Producents
        pthread_create(&threads[0], &attr, (void*(*)(void*)) CConsultant::ProduceExc, (void*)(this));
        pthread_create(&threads[1], &attr, (void*(*)(void*)) CConsultant::ProduceArb, (void*)(this));
        
        // Consuments
        for(int i = 2; i < consuments + 2; i++)
            pthread_create(&threads[i], &attr, (void*(*)(void*)) CConsultant::Consume, (void*)(this));
        
        pthread_attr_destroy(&attr);
    }
    
    void destroyThreads() {
        pthread_mutex_destroy(&queueLock);
        pthread_mutex_destroy(&endLock);
        sem_destroy(&queueEmptySlots);
        sem_destroy(&queueFull);
        
        delete[] threads;
    }
};


#ifndef __PROGTEST__

//vector<CExchange *> e;
//vector<CArbitrage *> a;

CArbitrage * arbsrc() {
    static int i = 0;
    vector<CArbitrage *> a;
    
    if(i == 0) {
        a.push_back(new CArbitrage(4, "  CZK -> USD: 0.0398 , USD -> EUR : 0.9259 , EUR -> GBP :  "
                      "0.7728 , GBP -> CZK : 35.0582 "));
        
        a.push_back(new CArbitrage(
                   5, "CZK->USD:0.0398,USD->EUR:0.9259,EUR->GBP:0.7728,GBP->CZK:35.1263"));
        
        a.push_back(new CArbitrage(6, "USD -> CZK: 25.0000, EUR -> CZK: 27.0000, CZK -> USD: "
                      "0.0400, CZK -> EUR: 0.0370, EUR -> RUB: 83.0000, RUB -> "
                      "USD: 0.0130, CZK -> RUB: 2.9990"));
        
        a.push_back(new CArbitrage(7, "USD -> CZK: 25.0000, EUR -> CZK: 27.0000, CZK -> USD: "
                      "0.0400, CZK -> EUR: 0.0370, EUR -> RUB: 83.0000, RUB -> "
                      "USD: 0.0130, CZK -> RUB: 2.9990, CZK -> PLN: 0.1736, PLN "
                      "-> HUF: 71.4216, HUF -> RUB: 0.2565"));
        
        
        a.push_back(new CArbitrage(8, "CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> CZK: "
                      "27.0472, PLN -> HUF: 71.4216, HUF -> RUB: 0.2565, RUB -> "
                      "PLN: 0.0545"));
        
        a.push_back(new CArbitrage(9, "CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> CZK: "
                      "27.0472, PLN -> HUF: 71.4216, HUF -> RUB: 0.2565, RUB -> "
                      "PLN: 0.0565"));
    }
    
    if(i == (int) a.size()) {
        return NULL;
    }
    
    return a.at(i++);
}

CExchange * excsrc() {
    static int i = 0;
    vector<CExchange *> e;
    
    if(i == 0) {
        CExchange * e0 = new CExchange(0, "CZK", "CZK");
        e0->AddBank("CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> GBP: 0.7728, CZK "
                   "-> GBP: 0.0280");
        
        CExchange * e1 = new CExchange(1, "CZK", "CAD");
        e1->AddBank("CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> GBP: 0.7728, CAD "
                   "-> GBP: 0.7494");
        
        CExchange * e2 = new CExchange(2, "CZK", "CAD");
        e2->AddBank("CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> GBP: 0.7728, USD "
                   "-> CZK: 0.0400");
        
        CExchange * e3 = new CExchange(3, "CZK", "GBP");
        e3->AddBank("CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> GBP: 0.7728, CZK "
                   "-> GBP: 0.0280");
        e3->AddBank("CZK -> USD: 0.0500, USD -> EUR: 0.8352, EUR -> GBP: 0.7728, EUR "
                   "-> HUF: 308.6779, HUF -> GBP: 0.0027");
        
        e.push_back(e0);
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
    }
    
    if(i == (int) e.size()) {
        return NULL;
    }
    return e.at(i++);
}

void cmplt(int c) {
    cout << "Completed: " << c << endl;
}


void testsV();
void testsP();

int main(void) {
    testsV();
    testsP();
    return 0;
}

void testsP() {
    CExchange e0(0, "CZK", "GBP");
    CConsultant::ExchangeSeq(&e0);
    assert(e0.m_Result == false);
    
    CExchange e1(0, "CZK", "GBP");
    e1.AddBank("");
    CConsultant::ExchangeSeq(&e1);
    assert(e1.m_Result == false);
    
    CExchange e2(0, "", "");
    e2.AddBank("");
    CConsultant::ExchangeSeq(&e2);
    assert(e2.m_Result == false);
    
    CConsultant c(arbsrc, excsrc, cmplt);
    c.Execute(30);
    
    //for(auto &i: a) delete i;
    //for(auto &i: e) delete i;
}

void testsVExchange() {
    CExchange e0(0, "CZK", "GBP");
    e0.AddBank("CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> GBP: 0.7728, CZK "
               "-> GBP: 0.0280");
    CConsultant::ExchangeSeq(&e0);
    assert(e0.m_Result == true);
    assert(e0.m_BankIdx == 0);
    // e.g.: m_BankIdx = 0, m_Rate = 0.0284, m_Currency = { CZK, USD, EUR, GBP }

    CExchange e1(1, "CZK", "CAD");
    e1.AddBank("CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> GBP: 0.7728, CAD "
               "-> GBP: 0.7494");
    CConsultant::ExchangeSeq(&e1);
    assert(e1.m_Result == false);
    
    CExchange e2(2, "CZK", "CAD");
    e2.AddBank("CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> GBP: 0.7728, USD "
               "-> CZK: 0.0400");
    CConsultant::ExchangeSeq(&e2);
    assert(e2.m_Result == false);
    
    CExchange e3(3, "CZK", "GBP");
    e3.AddBank("CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> GBP: 0.7728, CZK "
               "-> GBP: 0.0280");
    e3.AddBank("CZK -> USD: 0.0500, USD -> EUR: 0.8352, EUR -> GBP: 0.7728, EUR "
               "-> HUF: 308.6779, HUF -> GBP: 0.0027");
    CConsultant::ExchangeSeq(&e3);
    assert(e3.m_Result == true);
    assert(e3.m_BankIdx == 1);
}

void testsVArbitrage() {
    CArbitrage a0(4, "  CZK -> USD: 0.0398 , USD -> EUR : 0.9259 , EUR -> GBP :  "
                  "0.7728 , GBP -> CZK : 35.0582 ");
    CConsultant::ArbitrageSeq(&a0);
    assert(a0.m_Arbitrage == false);
    
    CArbitrage a1(
                  5, "CZK->USD:0.0398,USD->EUR:0.9259,EUR->GBP:0.7728,GBP->CZK:35.1263");
    CConsultant::ArbitrageSeq(&a1);
    assert(a1.m_Arbitrage == true);
    assert(doubleLessThan(a1.m_Rate, 1.0003) == 0);
    // prntV(a1.m_Currency);
    // e.g.: m_Rate = 1.0003, m_Currency = { GBP, CZK, USD, EUR, GBP }
    
    CArbitrage a2(6, "USD -> CZK: 25.0000, EUR -> CZK: 27.0000, CZK -> USD: "
                  "0.0400, CZK -> EUR: 0.0370, EUR -> RUB: 83.0000, RUB -> "
                  "USD: 0.0130, CZK -> RUB: 2.9990");
    CConsultant::ArbitrageSeq(&a2);
    assert(a2.m_Arbitrage == false);
    
    CArbitrage a3(7, "USD -> CZK: 25.0000, EUR -> CZK: 27.0000, CZK -> USD: "
                  "0.0400, CZK -> EUR: 0.0370, EUR -> RUB: 83.0000, RUB -> "
                  "USD: 0.0130, CZK -> RUB: 2.9990, CZK -> PLN: 0.1736, PLN "
                  "-> HUF: 71.4216, HUF -> RUB: 0.2565");
    CConsultant::ArbitrageSeq(&a3);
    assert(a3.m_Arbitrage == true);
    assert(doubleLessThan(a3.m_Rate, 1.0335) == 0);
    // prntV(a3.m_Currency);
    
    // e.g.: m_Rate = 1.0335, m_Currency = { HUF, RUB, USD, CZK, PLN, HUF }
    
    CArbitrage a4(8, "CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> CZK: "
                  "27.0472, PLN -> HUF: 71.4216, HUF -> RUB: 0.2565, RUB -> "
                  "PLN: 0.0545");
    CConsultant::ArbitrageSeq(&a4);
    assert(a4.m_Arbitrage == false);
    
    CArbitrage a5(9, "CZK -> USD: 0.0398, USD -> EUR: 0.9259, EUR -> CZK: "
                  "27.0472, PLN -> HUF: 71.4216, HUF -> RUB: 0.2565, RUB -> "
                  "PLN: 0.0565");
    CConsultant::ArbitrageSeq(&a5);
    assert(a5.m_Arbitrage == true);
    assert(doubleLessThan(a5.m_Rate, 1.0350) == 0);
    // rntV(a5.m_Currency);
    // e.g.: m_Rate = 1.0350, m_Currency = { RUB, PLN, HUF, RUB }
}

void testsV() {
    testsVExchange();
    testsVArbitrage();
}
#endif /* __PROGTEST__ */