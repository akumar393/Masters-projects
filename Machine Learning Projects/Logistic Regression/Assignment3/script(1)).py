import numpy as np
from scipy.io import loadmat
from scipy.optimize import minimize
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix
import time 


def preprocess():
    """ 
     Input:
     Although this function doesn't have any input, you are required to load
     the MNIST data set from file 'mnist_all.mat'.

     Output:
     train_data: matrix of training set. Each row of train_data contains 
       feature vector of a image
     train_label: vector of label corresponding to each image in the training
       set
     validation_data: matrix of training set. Each row of validation_data 
       contains feature vector of a image
     validation_label: vector of label corresponding to each image in the 
       training set
     test_data: matrix of training set. Each row of test_data contains 
       feature vector of a image
     test_label: vector of label corresponding to each image in the testing
       set
    """

    mat = loadmat('mnist_all.mat')  # loads the MAT object as a Dictionary

    n_feature = mat.get("train1").shape[1]
    n_sample = 0
    for i in range(10):
        n_sample = n_sample + mat.get("train" + str(i)).shape[0]
    n_validation = 1000
    n_train = n_sample - 10 * n_validation

    # Construct validation data
    validation_data = np.zeros((10 * n_validation, n_feature))
    for i in range(10):
        validation_data[i * n_validation:(i + 1) * n_validation, :] = mat.get("train" + str(i))[0:n_validation, :]

    # Construct validation label
    validation_label = np.ones((10 * n_validation, 1))
    for i in range(10):
        validation_label[i * n_validation:(i + 1) * n_validation, :] = i * np.ones((n_validation, 1))

    # Construct training data and label
    train_data = np.zeros((n_train, n_feature))
    train_label = np.zeros((n_train, 1))
    temp = 0
    for i in range(10):
        size_i = mat.get("train" + str(i)).shape[0]
        train_data[temp:temp + size_i - n_validation, :] = mat.get("train" + str(i))[n_validation:size_i, :]
        train_label[temp:temp + size_i - n_validation, :] = i * np.ones((size_i - n_validation, 1))
        temp = temp + size_i - n_validation

    # Construct test data and label
    n_test = 0
    for i in range(10):
        n_test = n_test + mat.get("test" + str(i)).shape[0]
    test_data = np.zeros((n_test, n_feature))
    test_label = np.zeros((n_test, 1))
    temp = 0
    for i in range(10):
        size_i = mat.get("test" + str(i)).shape[0]
        test_data[temp:temp + size_i, :] = mat.get("test" + str(i))
        test_label[temp:temp + size_i, :] = i * np.ones((size_i, 1))
        temp = temp + size_i

    # Delete features which don't provide any useful information for classifiers
    sigma = np.std(train_data, axis=0)
    index = np.array([])
    for i in range(n_feature):
        if (sigma[i] > 0.001):
            index = np.append(index, [i])
    train_data = train_data[:, index.astype(int)]
    validation_data = validation_data[:, index.astype(int)]
    test_data = test_data[:, index.astype(int)]

    # Scale data to 0 and 1
    train_data /= 255.0
    validation_data /= 255.0
    test_data /= 255.0

    return train_data, train_label, validation_data, validation_label, test_data, test_label


def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-z))


def blrObjFunction(initialWeights, *args):
    """
    blrObjFunction computes 2-class Logistic Regression error function and
    its gradient.

    Input:
        initialWeights: the weight vector (w_k) of size (D + 1) x 1 
        train_data: the data matrix of size N x D
        labeli: the label vector (y_k) of size N x 1 where each entry can be either 0 or 1 representing the label of corresponding feature vector

    Output: 
        error: the scalar value of error function of 2-class logistic regression
        error_grad: the vector of size (D+1) x 1 representing the gradient of
                    error function
    """
    train_data, labeli = args

    n_data = train_data.shape[0]
    n_features = train_data.shape[1]
    error = 0
    error_grad = np.zeros((n_features + 1, 1))

    ##################
    # YOUR CODE HERE #
    ##################
    # HINT: Do not forget to add the bias term to your input data
    
    temp = np.ones((train_data.shape[0],1))
    train_data_blr = np.hstack((temp,train_data))
    theta = sigmoid(np.transpose(initialWeights).dot(train_data_blr.T))
    theta = np.reshape(theta, (n_data,1))
    YLg_Theta = labeli * np.log(theta)
    OneY_Lg1Theta = (1-labeli) * np.log(1-theta)
    err_sum = sum(YLg_Theta + OneY_Lg1Theta) 
    error = -1 * err_sum / n_data
    theta_Y = theta - labeli
    thetaY_X = theta_Y * train_data_blr
    grad_sum = sum(thetaY_X)
    error_grad = grad_sum / n_data
    
    return error, error_grad


def blrPredict(W, data):
    """
     blrObjFunction predicts the label of data given the data and parameter W 
     of Logistic Regression
     
     Input:
         W: the matrix of weight of size (D + 1) x 10. Each column is the weight 
         vector of a Logistic Regression classifier.
         X: the data matrix of size N x D
         
     Output: 
         label: vector of size N x 1 representing the predicted label of 
         corresponding feature vector given in data matrix

    """
    label = np.zeros((data.shape[0], 1))

    ##################
    # YOUR CODE HERE #
    ##################
    # HINT: Do not forget to add the bias term to your input data
    
    temp = np.ones((data.shape[0],1))
    data = np.hstack((temp,data))
    output = np.zeros((data.shape[0], W.shape[1]))
    for i in range (0,data.shape[0]):
        temp = np.zeros((1,10))
        temp_sum = 0
        for j in range (0,W.shape[1]):
            temp_sum += np.exp(np.dot(W[:,j].T,data[i,:].T))
        for j in range (0,W.shape[1]):
            output[i,j] = np.exp(np.dot(W[:,j].T,data[i,:].T))/temp_sum
        label[i] = np.argmax(output[i,:])
    return label

def mlrObjFunction(params, *args):
    """
    mlrObjFunction computes multi-class Logistic Regression error function and
    its gradient.

    Input:
        initialWeights: the weight vector of size (D + 1) x 1
        train_data: the data matrix of size N x D
        labeli: the label vector of size N x 1 where each entry can be either 0 or 1
                representing the label of corresponding feature vector

    Output:
        error: the scalar value of error function of multi-class logistic regression
        error_grad: the vector of size (D+1) x 10 representing the gradient of
                    error function
    """
    train_data, labeli = args
    n_data = train_data.shape[0]
    n_feature = train_data.shape[1]
    error = 0
    error_grad = np.zeros((n_feature + 1, n_class))
    initialWeights_b = params.reshape(n_feature + 1, n_class)

    ##################
    # YOUR CODE HERE #
    ##################
    # HINT: Do not forget to add the bias term to your input data
    
    temp = np.ones((train_data.shape[0],1))
    X = np.hstack((temp,train_data))
    numerat = np.exp(np.dot(X,initialWeights_b))
    denom = np.sum(numerat, axis = 1)
    denom = np.reshape(denom, (n_data,1))
    div = np.divide(numerat,denom)
    prod = np.multiply(labeli,np.log(div))
    error = -1 * np.sum(prod)/n_data
    diff = div - labeli
    temp_grad = np.dot(X.T,diff)/n_data
    error_grad = temp_grad.flatten()
    return error, error_grad


def mlrPredict(W, data):
    """
     mlrObjFunction predicts the label of data given the data and parameter W
     of Logistic Regression

     Input:
         W: the matrix of weight of size (D + 1) x 10. Each column is the weight
         vector of a Logistic Regression classifier.
         X: the data matrix of size N x D

     Output:
         label: vector of size N x 1 representing the predicted label of
         corresponding feature vector given in data matrix

    """
    label = np.zeros((data.shape[0], 1))

    ##################
    # YOUR CODE HERE #
    ##################
    # HINT: Do not forget to add the bias term to your input data
    temp = np.ones((data.shape[0],1))
    data = np.hstack((temp,data))
    output = np.zeros((data.shape[0], W.shape[1]))
    for i in range (0,data.shape[0]):
        temp = np.zeros((1,10))
        temp_sum = 0
        for j in range (0,W.shape[1]):
            temp_sum += np.exp(np.dot(W[:,j].T,data[i,:].T))
        for j in range (0,W.shape[1]):
            output[i,j] = np.exp(np.dot(W[:,j].T,data[i,:].T))/temp_sum
        label[i] = np.argmax(output[i,:])

    return label


"""
Script for Logistic Regression
"""
train_data, train_label, validation_data, validation_label, test_data, test_label = preprocess()

# number of classes
n_class = 10

# number of training samples
n_train = train_data.shape[0]

# number of features
n_feature = train_data.shape[1]

Y = np.zeros((n_train, n_class))
for i in range(n_class):
    Y[:, i] = (train_label == i).astype(int).ravel()

print("Script for Extra Credit Part")
# FOR EXTRA CREDIT ONLY
W_b = np.zeros((n_feature + 1, n_class))
initialWeights_b = np.zeros((n_feature + 1, n_class))
opts_b = {'maxiter': 100}
start = int(round(time.time() * 1000))
args_b = (train_data, Y)
nn_params = minimize(mlrObjFunction, initialWeights_b, jac=True, args=args_b, method='CG', options=opts_b)
W_b = nn_params.x.reshape((n_feature + 1, n_class))

# Find the accuracy on Training Dataset
predicted_label_b = mlrPredict(W_b, train_data)
print(confusion_matrix(train_label, predicted_label_b, labels=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]))
print('\n Training set Accuracy:' + str(100 * np.mean((predicted_label_b == train_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("mlrObjFunction Training Time ",end-start)

# Find the accuracy on Validation Dataset
start = int(round(time.time() * 1000))
predicted_label_b = mlrPredict(W_b, validation_data)
print(confusion_matrix(validation_label, predicted_label_b, labels=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]))

print('\n Validation set Accuracy:' + str(100 * np.mean((predicted_label_b == validation_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("mlrObjFunction Validation Time ",end-start)

# Find the accuracy on Testing Dataset
start = int(round(time.time() * 1000))
predicted_label_b = mlrPredict(W_b, test_data)
print('\n Testing set Accuracy:' + str(100 * np.mean((predicted_label_b == test_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print(confusion_matrix(test_label, predicted_label_b, labels=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]))
print("mlrObjFunction Testing Time ",end-start)

print("extra credit ends")
# Logistic Regression with Gradient Descent
start = int(round(time.time() * 1000))
W = np.zeros((n_feature + 1, n_class))
initialWeights = np.zeros((n_feature + 1, 1))
opts = {'maxiter': 100}
for i in range(n_class):
    labeli = Y[:, i].reshape(n_train, 1)
    args = (train_data, labeli)
    nn_params = minimize(blrObjFunction, initialWeights, jac=True, args=args, method='CG', options=opts)
    W[:, i] = nn_params.x.reshape((n_feature + 1,))

# Find the accuracy on Training Dataset
predicted_label = blrPredict(W, train_data)
print(confusion_matrix(train_label, predicted_label, labels=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]))
print('\n Training set Accuracy:' + str(100 * np.mean((predicted_label == train_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("Logistic Regression with Gradient Descent Time ",end-start)

# Find the accuracy on Validation Dataset
predicted_label = blrPredict(W, validation_data)
print('\n Validation set Accuracy:' + str(100 * np.mean((predicted_label == validation_label).astype(float))) + '%')
print(confusion_matrix(validation_label, predicted_label, labels=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]))

# Find the accuracy on Testing Dataset
predicted_label = blrPredict(W, test_data)
print('\n Testing set Accuracy:' + str(100 * np.mean((predicted_label == test_label).astype(float))) + '%')
print(confusion_matrix(test_label, predicted_label, labels=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]))


"""
Script for Extra Credit Part
"""

"""
Script for Support Vector Machine
"""

print('\n\n--------------SVM-------------------\n\n')
##################
# YOUR CODE HERE #
##################
#tup_perm = random.sample(range(0, 49999), 30000)
train_label = train_label.ravel()
validation_label = validation_label.ravel()
test_label = test_label.ravel()

print("Linear Kernel")

start = int(round(time.time() * 1000))
clf = SVC(kernel = 'linear')
clf.fit(train_data, train_label) 
linear_predict_train = clf.predict(train_data)
print('\n SVM Linear Kernel Training set Accuracy:' + str(100 * np.mean((linear_predict_train == train_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM Linear Kernel Training Time ",end-start)

start = int(round(time.time() * 1000))
linear_predict_val = clf.predict(validation_data)
print('\n SVM Linear Kernel Validation set Accuracy:' + str(100 * np.mean((linear_predict_val == validation_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM Linear Kernel Validation Time ",end-start)

start = int(round(time.time() * 1000))
linear_predict_test = clf.predict(test_data)
print('\n SVM Linear Kernel Test set Accuracy:' + str(100 * np.mean((linear_predict_test == test_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM Linear Kernel Test Time ",end-start)
print("\n-------------------------------------------------------\n")

print("RBF Kernel gamma = default")
start = int(round(time.time() * 1000))
clf = SVC(kernel = 'rbf')
clf.fit(train_data, train_label) 
rbf_g1_predict_train = clf.predict(train_data)
print('\n SVM rbf Kernel gamma = default Training set Accuracy:' + str(100 * np.mean((rbf_g1_predict_train == train_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM rbf Kernel gamma = default Training Time ",end-start)

start = int(round(time.time() * 1000))
rbf_g1_predict_val = clf.predict(validation_data)
print('\n SVM rbf Kernel gamma = default Validation set Accuracy:' + str(100 * np.mean((rbf_g1_predict_val == validation_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM rbf Kernel gamma = default Validation Time ",end-start)

start = int(round(time.time() * 1000))
rbf_g1_predict_test = clf.predict(test_data)
print('\n SVM rbf Kernel gamma = default Test set Accuracy:' + str(100 * np.mean((rbf_g1_predict_test == test_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM rbf Kernel gamma = default Test Time ",end-start)
print("\n-------------------------------------------------------\n")

print("RBF with varying C values")
start = int(round(time.time() * 1000))
clf = SVC(kernel = 'rbf', C=1)
clf.fit(train_data, train_label) 
rbf_predict_train = clf.predict(train_data)
print('\n SVM RBF C = 1 Training set Accuracy:' + str(100 * np.mean((rbf_predict_train == train_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM RBF C = 1 Training Time ",end-start)

start = int(round(time.time() * 1000))
rbf_predict_val = clf.predict(validation_data)
print('\n SVM RBF C = 1 Validation set Accuracy:' + str(100 * np.mean((rbf_predict_val == validation_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM RBF C = 1 Validation Time ",end-start)

start = int(round(time.time() * 1000))
rbf_predict_test = clf.predict(test_data)
print('\n RBF C = 1 Test set Accuracy:' + str(100 * np.mean((rbf_predict_test == test_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM RBF C = 1 Test Time ",end-start)

for c in range (10,110,10):
    start = int(round(time.time() * 1000))
    clf = SVC(kernel = 'rbf', C=c)
    clf.fit(train_data, train_label) 
    rbf_predict_train = clf.predict(train_data)
    print('\n RBF C = ' + str(c) + ' Training set Accuracy:' + str(100 * np.mean((rbf_predict_train == train_label).astype(float))) + '%')
    end = int(round(time.time() * 1000))
    print("SVM RBF C = " + str(c) + " Training Time ",end-start)
    
    start = int(round(time.time() * 1000))
    rbf_predict_val = clf.predict(validation_data)
    print('\n RBF C = ' + str(c) + ' Validation set Accuracy:' + str(100 * np.mean((rbf_predict_val == validation_label).astype(float))) + '%')
    end = int(round(time.time() * 1000))
    print("SVM RBF C = " + str(c) + " Validation Time ",end-start)
    
    start = int(round(time.time() * 1000))
    rbf_predict_test = clf.predict(test_data)
    print('\n RBF C = ' + str(c) + ' Test set Accuracy:' + str(100 * np.mean((rbf_predict_test == test_label).astype(float))) + '%')
    end = int(round(time.time() * 1000))
    print("SVM RBF C = " + str(c) + " Validation Time ",end-start)

print("\n-------------------------------------------------------\n")

print("RBF Kernel gamma = 1")
start = int(round(time.time() * 1000))
clf = SVC(kernel = 'rbf', gamma = 1)
clf.fit(train_data, train_label) 
rbf_g1_predict_train = clf.predict(train_data)
print('\n SVM rbf Kernel gamma = 1 Training set Accuracy:' + str(100 * np.mean((rbf_g1_predict_train == train_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM rbf Kernel gamma = 1 Training Time ",end-start)

start = int(round(time.time() * 1000))
rbf_g1_predict_val = clf.predict(validation_data)
print('\n SVM rbf Kernel gamma = 1 Validation set Accuracy:' + str(100 * np.mean((rbf_g1_predict_val == validation_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM rbf Kernel gamma = 1 Validation Time ",end-start)

start = int(round(time.time() * 1000))
rbf_g1_predict_test = clf.predict(test_data)
print('\n SVM rbf Kernel gamma = 1 Test set Accuracy:' + str(100 * np.mean((rbf_g1_predict_test == test_label).astype(float))) + '%')
end = int(round(time.time() * 1000))
print("SVM rbf Kernel gamma = 1 Test Time ",end-start)
print("\n-------------------------------------------------------\n")