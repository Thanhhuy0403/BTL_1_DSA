#include "kNN.hpp"

void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    feature.printHead(1, 10000);
    cout << endl;
    cout << feature.drop(1, 0, "1x2") << endl;
    feature.printHead(1, 10000);

    // train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    // X_train.getShape(nRows, nCols);
    // cout << "X_train shape: " << nRows << "x" << nCols << endl;
    // X_test.getShape(nRows, nCols);
    // cout << "X_test shape: " << nRows << "x" << nCols << endl;
    // y_train.getShape(nRows, nCols);
    // cout << "y_train shape: " << nRows << "x" << nCols << endl;
    // y_test.getShape(nRows, nCols);
    // cout << "y_test shape: " << nRows << "x" << nCols << endl;
}

int main() {
    freopen("output.txt","w", stdout);
    tc1();
    return 0;
}