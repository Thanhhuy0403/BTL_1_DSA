#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
// =============== Struct Node =============== //
template<typename T>
Node<T>::Node(T value, Node<T>* prev, Node<T>* next){
    this->value = value;
    this->prev = prev;
    this->next = next;
}

template<typename T>
Node<T>::Node(){
    this->value = 0;
    this->prev = NULL;
    this->next = NULL;
}

// =============== Class List =============== //


// =============== Class pList =============== //
template<typename T>
pList<T>::pList(){
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}

template<typename T>
pList<T>::~pList(){
    while(this->head != NULL){
        Node<T>* tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}

template<typename T>
void pList<T>::push_back(T value){
    if(this->size == 0){
        this->head = this->tail = new Node<T>(value, NULL, NULL);
    }else{
        Node<T>* newNode = new Node<T>(value);
        newNode->prev = this->tail;
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->size++;
}

template<typename T>
void pList<T>::push_front(T value){
    if(this->size == 0){
        this->head = this->tail = new Node<T>(value, NULL, NULL);
    }else{
        Node<T>* newNode = new Node<T>(value);
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
    }
    this->size++;
}

template<typename T>
void pList<T>::insert(int index, T value){
    if(index < 0 || index > this->size){
        return;
    }else{
        if(index == this->size){
            this->push_back(value);
        }else if(index == 0){
            this->push_front(value);
        }else{
            Node<T>* tmp  = this->head;
            for(int i = 0; i < index - 1; i++){
                tmp = tmp->next;
            }
            Node<T>* newNode = new Node<T>(value);
            newNode->prev = tmp;
            newNode->next = tmp->next;
            tmp->next->prev = newNode;
            tmp->next = newNode;
            this->size++;
        }
    }
}

template<typename T>
void pList<T>::remove(int index){
    if(index < 0 || index >= this->size){
        return;
    }else{
        if(this->size == 1){
            Node<T>* tmp = this->head;
            this->head = this->tail = NULL;
            delete tmp;
            this->size = 0;
        }else if(index == 0){
            Node<T>* tmp = this->head;
            this->head = this->head->next;
            this->head->prev = NULL;
            delete tmp;
            this->size--;
        }else if(index == this->size - 1){
            Node<T>* tmp = this->tail;
            this->tail->prev->next = NULL;
            this->tail = this->tail->prev;
            delete tmp;
            this->size--;
        }else{
            Node<T>* tmp;
            if(index < this->size/2){
                tmp = this->head;
                for(int i = 0; i < index - 1; i++){
                    tmp = tmp->next;
                }
                Node<T>* tmp2 = tmp->next;
                tmp->next = tmp2->next;
                tmp2->next->prev = tmp;
                delete tmp2;
                this->size--;
            }else{
                tmp = this->tail;
                for(int i = this->size-1; i > index - 1; i--){
                    tmp = tmp->prev;
                }
                Node<T>* tmp2 = tmp->next;
                tmp->prev = tmp2->prev;
                tmp2->prev->next = tmp;
                delete tmp2;
                this->size--;
            }
        }
    }
}

template<typename T>
T& pList<T>::get(int index) const {
    if (index < 0 || index >= this->size) {
        throw std::out_of_range("get(): Out of range");
    }else {
        Node<T>* tmp;
        if (index < this->size / 2){
            tmp = this->head;
            for (int i = 0; i < index; i++) {
                tmp = tmp->next;
            }
        }else{
            tmp = this->tail;
            for (int i = this->size - 1; i > index; i--){
                tmp = tmp->prev;
            }
        }
        return tmp->value;
    }
}

template<typename T>
void pList<T>::set(int index, T value) {
    if (index < 0 || index >= this->size) {
        throw std::out_of_range("set(): Out of range");
    } else {
        Node<T>* tmp;
        if(index < this->size / 2){
            tmp = this->head;
            for (int i = 0; i < index; i++){
                tmp = tmp->next;
            }
        }else{
            tmp = this->tail;
            for (int i = this->size - 1; i > index; i--){
                tmp = tmp->prev;
            }
        }
        tmp->value = value;
    }
}

template<typename T>
int pList<T>::length() const{
    return this->size;
}

template<typename T>
void pList<T>::clear(){
    while(this->head != NULL){
        Node<T>* tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }
    this->tail = NULL;
    this->size = 0;
}

template<typename T>
void pList<T>::print() const {
    Node<T>* tmp = this->head;
    while(tmp != NULL){
        cout << tmp->value;
        if(tmp->next != NULL){
            cout << " ";
        }
        tmp = tmp->next;
    }
}

template<typename T>
void pList<T>::reverse(){
    if(this->size <= 1){
        return;
    }else{
        Node<T>* current = this->head;
        Node<T>* nextNode = NULL;
        while(current != NULL){
            nextNode = current->next;
            current->next = current->prev;
            current->prev = nextNode;
            current = nextNode;
        }
        Node<T>* tmp = this->head;
        this->head = this->tail;
        this->tail = tmp;
    }
}

template<typename T>
int pList<T>::indexOf(T name){
    Node<T>* tmp = this->head;
    for(int i = 0; i < this->size; i++){
        if(tmp->value == name){
            return i;
        }
        tmp = tmp->next;
    }
    return -1;
}

// =============== Class Dataset =============== //
Dataset::Dataset(){
    this->data = new pList<pList<int>*>();
    this->nameLables = new pList<string>();
}

Dataset::~Dataset(){
    if(this->data){
        delete data;
    }
    if(this->nameLables){
        delete this->nameLables;
    }
}

Dataset::Dataset(const Dataset& other){
    this->data = new pList<pList<int>*>(*(other.data));
    this->nameLables = new pList<string>(*(other.nameLables));
}

Dataset& Dataset::operator=(const Dataset& other){
    if(this != &other){
        if(this->nameLables != NULL){
            delete this->nameLables;
        }
        this->nameLables = new pList<string>();
        for(int i = 0; i < other.getNameLables()->length(); i++){
            this->nameLables->push_back(other.getNameLables()->get(i));
        }
        if(this->data != NULL){
            delete this->data;
        }
        this->data = new pList<pList<int>*>();
        int n = other.getData()->length();
        int m = other.getData()->get(0)->length();
        for(int i = 0; i < n; i++){
            pList<int>* tmp = new pList<int>();
            for(int j = 0; j < m; j++){
                tmp->push_back(other.getData()->get(i)->get(j));
            }
            this->data->push_back(tmp);
        }
    }
    return *this;
}

bool Dataset::loadFromCSV(const char* fileName){
    fstream input_file(fileName, ios::in);
    if(!input_file.is_open()){
        cout << "Unable to open CSV file" << endl;
        return false;
    }else{
        this->data->clear();
        this->nameLables->clear();
        string line;
        getline(input_file, line);
        stringstream ss(line);
        string token;
        while(getline(ss, token, ',')){
            nameLables->push_back(token);
        }
        while(getline(input_file, line)){
            stringstream ss(line);
            pList<int>* tmp = new pList<int>();
            int value;
            while(ss >> value){
                tmp->push_back(value);
                if(ss.peek() == ','){
                    ss.ignore();
                }
            }
            this->data->push_back(tmp);
        }
        input_file.close();
        return true;
    }
}

void Dataset::printHead(int nRows, int nCols) const{
    if(nRows <= 0 || nCols <= 0) return;
    if(nRows > this->data->length()){
        nRows = this->data->length();
    }
    if(nCols > this->data->get(0)->length()){
        nCols = this->data->get(0)->length();
    }
    for(int i = 0; i < nCols; i++){
        cout << this->nameLables->get(i);
        if(i != nCols-1){
            cout << " ";
        }
    }
    cout << endl;
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            cout << this->data->get(i)->get(j);
            if(j != nCols-1){
                cout << " ";
            }
        }
        if(i != nRows-1){
            cout << endl;
        }
    }
}

void Dataset::printTail(int nRows, int nCols) const{
    if(nRows < 0 || nCols < 0) return;
    if(nRows > this->data->length()){
        nRows = this->data->length();
    }
    if(nCols > this->data->get(0)->length()){
        nCols = this->data->get(0)->length();
    }
    int n = this->data->length();
    int m = this->data->get(0)->length();
    for(int i = m-nCols; i <= m-1; i++){
        cout << this->nameLables->get(i);
        if(i != m-1){
            cout << " ";
        }
    }
    cout << endl;
    for(int i = n-nRows; i <= n-1; i++){
        for(int j = m-nCols; j <= m-1; j++){
            cout << this->data->get(i)->get(j);
            if(j != m-1){
                cout << " ";
            }
        }
        if(i != n-1){
            cout << endl;
        }
    }
}

void Dataset::getShape(int& nRows, int& nCols) const{
    nRows = this->data->length();
    nCols = this->data->get(0)->length();
}

void Dataset::columns() const{
    int n = this->nameLables->length();
    for(int i = 0; i < n; i++){
        cout << this->nameLables->get(i);
        if(i != n-1){
            cout << " ";
        }
    }
    cout << endl;
}

bool Dataset::drop(int axis, int index, string columnName){
    if(axis != 0 || axis != 1){
        return false;
    }
    else{
        if(axis == 0){
            if(index < 0 || index >= this->data->length()){
                return false;
            }else{
                this->data->remove(index);
                return true;
            }
        }else{
            int Colums_index = this->nameLables->indexOf(columnName);
            if(Colums_index == -1){
                return false;
            }else{
                this->nameLables->remove(Colums_index);
                int n = this->data->length();
                for(int i = 0; i < n; i++){
                    this->data->get(i)->remove(Colums_index);
                }
                return true;
            }
        }
    }
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const{
    Dataset res;
    if(endRow == -1){
        endRow = this->data->length()-1;
    }
    if(endCol == -1){
        endCol = this->nameLables->length()-1;
    }

    for(int i = startCol; i <= endCol; i++){
        res.nameLables->push_back(this->nameLables->get(i));
    }

    for(int i = startRow; i <= endRow; i++){
        pList<int>* tmp = new pList<int>();
        for(int j = startCol; j <= endCol; j++){
            tmp->push_back(this->data->get(i)->get(j));
        }
        res.data->push_back(tmp);
    }
    return res;
}

pList<pList<int>*>* Dataset::getData() const{
    return this->data;
}

pList<string>* Dataset::getNameLables() const{
    return this->nameLables;
}

int Dataset::getLenghtData() const{
    return this->data->length();
}

int Dataset::getLenghtNameLables() const{
    return this->nameLables->length();
}

// =============== Class kNN =============== //
kNN::kNN(int k){
    this->k = k;
}

void kNN::fit(const Dataset& X_train, const Dataset& y_train){
    this->X_train = X_train;
    this->Y_train = y_train;
}

double kNN::euclidean_distance(pList<int>* p1, pList<int>* p2) const{
    if(p1->length() != p2->length()){
        throw std::invalid_argument("Don't match");
    }
    double sum = 0.0;
    for(int i = 0; i < p1->length(); i++){
        double tem = p1->get(i) - p2->get(i);
        sum += tem*tem;
    }
    return (double)sqrt(sum);
}

int kNN::index_k_nearest_neighbors(pList<double>* distances, int k) const{
    pList<double>* tmp = new pList<double>();
    pList<int>* index = new pList<int>();
    for(int i = 0 ; i < distances->length(); i++){
        tmp->push_back(distances->get(i));
        index->push_back(i);
    }

    // Sorting
    // for(int i = 0; i <= k; i++){
    //     int min_index = i;
    //     double min_dist = tmp->get(i);
    //     for(int j = i+1; j < tmp->length(); j++){
    //         if(tmp->get(j) < min_dist){
    //             min_index = j;
    //             min_dist = tmp->get(j);
    //         }
    //     }
    //     if(min_index != i){
    //         std::swap(tmp->get(i), tmp->get(min_index));
    //         std::swap(index->get(i), index->get(min_index));
    //     }
    // }

    int n = tmp->length();
    for(int i = 0; i < k; i++){
        for(int j = n - 1; j > i; j--){
            if(tmp->get(j) < tmp->get(j-1)){
                swap(tmp->get(j), tmp->get(j-1));
                swap(index->get(j), index->get(j-1));
            }
        }
    }

    int res_value = this->Y_train.getData()->get(index->get(0))->get(0);
    int res_cnt = 1;

    for(int i = 0; i < k; i++){
        int current_val = this->Y_train.getData()->get(index->get(i))->get(0);
        int cnt = 1;
        for(int j = i+1; j < k; j++){
            if(this->Y_train.getData()->get(index->get(j))->get(0) == current_val){
                cnt++;
            }
        }
        if(cnt > res_cnt){
            res_cnt = cnt;
            res_value = current_val;
        }
    }

    // int res_weight = index->get(0);
    // for(int i = 0; i < k; i++){
    //     int current_weight = 0;
    //     int current_value = this->Y_train.getData()->get(index->get(i))->get(0);
    //     int current_cnt = 0;
    //     for(int j = 0; j < k; j++){
    //         if(this->Y_train.getData()->get(index->get(j))->get(0) == current_value){
    //             current_cnt++;
    //             current_weight += index->get(j);
    //         }
    //     }
    //     if(current_cnt > res_cnt){
    //         res_cnt = current_cnt;
    //         res_value = current_value;
    //         res_weight = current_weight;
    //     }else if(current_cnt == res_cnt){
    //         if(res_weight < current_weight){
    //             res_cnt = current_cnt;
    //             res_value = current_value;
    //             res_weight = current_weight;
    //         }
    //     }
    // }
    delete tmp;
    delete index;
    return res_value;
}

Dataset kNN::predict(const Dataset& X_test){
    pList<pList<int>*>* data = X_test.getData();
    Dataset res;
    res.getNameLables()->push_back("label");
    int n_X_test = data->length();
    for(int i = 0; i < n_X_test; i++){
        pList<double>* distances = new pList<double>();
        int n_lenght = this->X_train.getLenghtData();
        for(int j = 0; j < n_lenght; j++){
            distances->push_back(euclidean_distance(data->get(i), this->X_train.getData()->get(j)));
        }
        int lable_y_train = index_k_nearest_neighbors(distances, this->k);
        pList<int>* tem = new pList<int>();
        tem->push_back(lable_y_train);
        res.getData()->push_back(tem);
        delete distances;
    }
    return res;
}

double kNN::score(const Dataset& y_test, const Dataset& y_pred){
    int count = 0;
    int n = y_test.getData()->length();
    for(int i = 0; i < n; i++){
        if(y_test.getData()->get(i)->get(0) == y_pred.getData()->get(i)->get(0)){
            count++;
        }
    }
    return double(count)/double(n);
}

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test){
    int sum = X.getLenghtData();
    if(test_size > 0.5){
        test_size = 1 - test_size;
    }
    int n_X_train = (1-test_size)*sum;
    X_train = X.extract(0, n_X_train-1, 0, -1);
    y_train = y.extract(0, n_X_train-1, 0, 0);
    X_test = X.extract(n_X_train, -1, 0, -1);
    y_test = y.extract(n_X_train, -1, 0, 0);
}