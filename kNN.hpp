#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template<typename T>
struct Node{
    T value;
    Node* next;
    Node* prev;
    Node(T value, Node* prev = NULL, Node* next = NULL);
    Node();
};


template<typename T>
class List {
private:
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

template<typename T>
class pList : public List<T>{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    public:
        pList();
        ~pList() override;
        void push_back(T value) override;
        void push_front(T value) override;
        void insert(int index, T value) override;
        void remove(int index) override;
        T& get(int index) const override;
        void set(int index, T value);
        int length() const override ;
        void clear() override;
        void print() const override;
        void reverse() override;
        int indexOf(T name);
};

class Dataset {
private:
    pList<pList<int>*>* data;
    pList<string>* nameLables;
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    pList<pList<int>*>* getData () const;
    pList<string>* getNameLables() const;
    int getLenghtData() const;
    int getLenghtNameLables() const;
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    //You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);

    // self-defined attribute
    double euclidean_distance(pList<int>* p1, pList<int>* p2) const;
    int index_k_nearest_neighbors(pList<double>* distances, int k) const;
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed