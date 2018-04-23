'''
Comparing single layer MLP with deep MLP (using TensorFlow)
'''
import pickle
import numpy as np
from scipy.optimize import minimize
from scipy.io import loadmat
from math import sqrt
from numpy import array
from numpy import argmax
from keras.utils import to_categorical
import time

# Do not change this
def initializeWeights(n_in,n_out):
    """
    # initializeWeights return the random weights for Neural Network given the
    # number of node in the input layer and output layer

    # Input:
    # n_in: number of nodes of the input layer
    # n_out: number of nodes of the output layer
                            
    # Output: 
    # W: matrix of random initial weights with size (n_out x (n_in + 1))"""
    epsilon = sqrt(6) / sqrt(n_in + n_out + 1);
    W = (np.random.rand(n_out, n_in + 1)*2* epsilon) - epsilon;
    return W



# Replace this with your sigmoid implementation
def sigmoid(z):
    return  1.0 / (1.0 + np.exp(-z))


# Replace this with your nnObjFunction implementation
def nnObjFunction(params, *args):
    
    n_input, n_hidden, n_class, training_data, training_label, lambdaval = args

    w1 = params[0:n_hidden * (n_input + 1)].reshape( (n_hidden, (n_input + 1)))
    w2 = params[(n_hidden * (n_input + 1)):].reshape((n_class, (n_hidden + 1)))
    obj_val = 0

    N, D = training_data.shape
    M = w1.shape[0]
    K = w2.shape[0]

    # forward pass
    temp = np.ones((training_data.shape[0],1))
    X = np.hstack((training_data, temp))
    print("X.shape",X.shape)
    traindata_dot_w1 = np.dot(X, w1.T)
    Z = sigmoid(traindata_dot_w1)
    print("Z.shape",Z.shape)
    temp = np.ones((Z.shape[0],1))
    Z = np.hstack((Z, temp))
    print("Z.shape",Z.shape)
    out_Hid_dot_w2 = np.dot(Z,w2.T)
    O = sigmoid(out_Hid_dot_w2)
    print("O.shape",O.shape)
   
    # compute objective function
    Y = np.zeros([N,K])
    #Y[np.arange(len(training_label)),training_label.astype(int)] = 1
    Y = to_categorical(training_label)
    obj_val = -(1/N)*np.sum(Y*np.log(O) + (1-Y)*np.log(1-O)) + (0.5*lambdaval/N)*(np.sum(pow(w1,2)) + np.sum(pow(w2,2)))

    print("obj_val",obj_val)
    print("------------------------------------------------")
    #Backpropagation
    deltaL = O - to_categorical(training_label)
    grad_w2 = (1.0/N)*(np.dot(deltaL.T, Z)+lambdaval*w2)
    print("np.linalg.norm(grad_w2)",np.linalg.norm(grad_w2))
    print("------------------------------------------------")
    
    #print(deltaL)
    print("####################")
    grad_w1 = (1.0/N)*(np.dot(np.transpose((Z*(1-Z))*np.dot(deltaL,w2)),X))
    grad_w1 = np.delete(grad_w1,-1,0)
    grad_w1 += (1.0/N)*lambdaval*w1
    print("grad_w1.shape",grad_w1.shape)
    print("np.linalg.norm(grad_w1)",np.linalg.norm(grad_w1))
    # Unroll gradients
    obj_grad = np.concatenate((grad_w1.flatten(), grad_w2.flatten()),0)
    return (obj_val,obj_grad)
    
# Replace this with your nnPredict implementation
def nnPredict(w1,w2,data):
    
    temp = np.ones((data.shape[0],1))
    data = np.hstack((data, temp))
    print("data.shape",data.shape)
    print("w1.shape",w1.shape)
    print("w2.shape",w2.shape)
    datadotw1 = np.dot(data,w1.T)
    print("datadotw1.shape",datadotw1.shape)
    outHidden = sigmoid(datadotw1)
    print("outHidden.shape",outHidden.shape)
    
    temp = np.ones((outHidden.shape[0],1))
    outHidden = np.hstack((outHidden, temp))
    
    outHiddenDotw2 = np.dot(outHidden,w2.T)
    print("outHiddenDotw2.shape",outHiddenDotw2.shape)
    finalOut = sigmoid(outHiddenDotw2)
    print("finalOut.shape",finalOut.shape)
    
    labels = np.argmax(finalOut, axis = 1)
    print(labels.shape)
    
    # Your code here

    return labels

# Do not change this
def preprocess():
    pickle_obj = pickle.load(file=open('face_all.pickle', 'rb'))
    features = pickle_obj['Features']
    labels = pickle_obj['Labels']
    train_x = features[0:21100] / 255
    valid_x = features[21100:23765] / 255
    test_x = features[23765:] / 255

    labels = labels[0]
    train_y = labels[0:21100]
    valid_y = labels[21100:23765]
    test_y = labels[23765:]
    
    # Feature selection
    # Your code here.
    indices = []
    for t in range(0,train_x.shape[1]):
        if(np.var(train_x[:,t]) > 0.0000001):
            indices.append(t)
    final_train_data = train_x[:,indices]
    print("final_train_data.shape",final_train_data.shape)
    train_x = final_train_data
    valid_x = valid_x[:,indices]
    test_x = test_x[:,indices]

    print('preprocess done')

    return train_x, train_y, valid_x, valid_y, test_x, test_y

"""**************Neural Network Script Starts here********************************"""
train_data, train_label, validation_data, validation_label, test_data, test_label = preprocess()
#  Train Neural Network
# set the number of nodes in input unit (not including bias unit)
n_input = train_data.shape[1]
# set the number of nodes in hidden unit (not including bias unit)
n_hidden = 100
# set the number of nodes in output unit
n_class = 2

# initialize the weights into some random matrices
initial_w1 = initializeWeights(n_input, n_hidden);
initial_w2 = initializeWeights(n_hidden, n_class);
# unroll 2 weight matrices into single column vector
initialWeights = np.concatenate((initial_w1.flatten(), initial_w2.flatten()),0)
# set the regularization hyper-parameter
lambdaval = 4;
args = (n_input, n_hidden, n_class, train_data, train_label, lambdaval)

#Train Neural Network using fmin_cg or minimize from scipy,optimize module. Check documentation for a working example
opts = {'maxiter' :50}    # Preferred value.

start = int(round(time.time() * 1000))
print("Starting time",start)

nn_params = minimize(nnObjFunction, initialWeights, jac=True, args=args,method='CG', options=opts)

print("\n")
end = int(round(time.time() * 1000))
print("Ending time",end )
print("Difference",end-start)     


params = nn_params.get('x')
#Reshape nnParams from 1D vector into w1 and w2 matrices
w1 = params[0:n_hidden * (n_input + 1)].reshape( (n_hidden, (n_input + 1)))
w2 = params[(n_hidden * (n_input + 1)):].reshape((n_class, (n_hidden + 1)))

#Test the computed parameters
predicted_label = nnPredict(w1,w2,train_data)
#find the accuracy on Training Dataset
print ('\n Training set Accuracy:' + str(100*np.mean((predicted_label == train_label).astype(float))) + '%')
predicted_label = nnPredict(w1,w2,validation_data)
#find the accuracy on Validation Dataset
print('\n Validation set Accuracy:' + str(100 * np.mean((predicted_label == validation_label).astype(float))) + '%')
predicted_label = nnPredict(w1,w2,test_data)
#find the accuracy on Validation Dataset
print('\n Test set Accuracy:' + str(100 * np.mean((predicted_label == test_label).astype(float))) + '%')
