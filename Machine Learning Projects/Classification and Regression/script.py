import numpy as np
from scipy.optimize import minimize
from scipy.io import loadmat
from numpy.linalg import det, inv
from math import sqrt, pi
import scipy.io
import matplotlib.pyplot as plt
import pickle
import sys

def ldaLearn(X,y):
    # Inputs
    # X - a N x d matrix with each row corresponding to a training example
    # y - a N x 1 column vector indicating the labels for each tr'aining example
    # Outputs
    # means - A d x k matrix containing learnt means for each of the k classes
    #given x vector at row i,mean from all k classes, so each row is a x vector-k columns
    # covmat - A single d x d learnt covariance matrix 
    
    # IMPLEMENT THIS METHOD 
    D=X.shape[1] 
    k=[1,2,3,4,5]
    #y=[1,2,4,5,3,,4,2,1]'''
    lenk=len(k)
    s=(D,lenk)
    means=np.zeros(s)
    t=(D,D)
    covmat=np.zeros(t)
    list_0=[]
    list_1=[]
    special_list0=[]
    special_list1=[]
    count=0
    for i in range(len(k)):  #1,2,3,4,5
        for j in range(len(y)):
            if(y[j]==k[i]):
                count=count+1
                list_0.append(X[j][0])
                list_1.append(X[j][1])
                if(y[j]==1):
                    special_list0.append(X[j][0])
                if(y[j]==2):
                    special_list1.append(X[j][1])
        means[0][i]=np.mean(list_0)
        means[1][i]=np.mean(list_1)
        list_0=[]
        list_1=[]
    for i in range(D):
        for j in range(D):
            if(i==0 and j==0):
                covmat[i][j]=np.var(np.matrix(special_list0))
            if(i==1 and j==1):
                covmat[i][j]=np.var(np.matrix(special_list1))

    return means,covmat

def qdaLearn(X,y):
    # Inputs
    # X - a N x d matrix with each row corresponding to a training example
    # y - a N x 1 column vector indicating the labels for each training example
    #
    # Outputs
    # means - A d x k matrix containing learnt means for each of the k classes
    # covmats - A list of k d x d learnt covariance matrices for each of the k classes
    
    d = X.shape[1]
    k = 5
    means = np.empty([d,k])
    data = list()
    for i in range(0,k):
        data.append(X[np.where(y == i+1)[0]])
    for i in range(0,d):
            for j in range(0,k): 
                means[i,j] = np.mean(data[j][:,i])
    covMatList = list()
    for j in range(0,k):
        temp = 0
        temp = np.matrix(data[j] - means[:,j])
        covMatList.append(temp.T * temp / data[j].shape[0])

    return means, covMatList        
        
        
  

def ldaTest(means,covmat,Xtest,ytest):
    # Inputs
    # means, covmat - parameters of the LDA model
    # Xtest - a N x d matrix with each row corresponding to a test example
    # ytest - a N x 1 column vector indicating the labels for each test example
    # Outputs
    # acc - A scalar accuracy value
    # ypred - N x 1 column vector indicating the predicted labels

    # IMPLEMENT THIS METHOD
    k = 5
    d = Xtest.shape[1]
    count = 0
    ypred=np.empty([ytest.shape[0],1])
   
    for j in range(0,ytest.shape[0]):
        x = np.matrix(Xtest[j]).T
        pmle = list()
    # Xtest - a N x d matrix with each row correspond
        for i in range(0,k):
            mean = np.matrix(means[:,i]).T
            temp = (((x-mean).T) * (inv(covmat))) * (x-mean)
            temp = np.exp(-0.5*temp)
            temp = temp / (sqrt(2 * pi))**d 
            temp = temp / sqrt(det(covmat))
            pmle.append(temp)
        if((pmle.index(max(pmle)) - ytest[j] +1) == 0):
            count = count + 1
        ypred[j]=pmle.index(max(pmle))+1
        
    return count, ypred

def qdaTest(means,covmats,Xtest,ytest):
    # Inputs
    # means, covmats - parameters of the QDA model
    # Xtest - a N x d matrix with each row corresponding to a test example
    # ytest - a N x 1 column vector indicating the labels for each test example
    # Outputs
    # acc - A scalar accuracy value
    # ypred - N x 1 column vector indicating the predicted labels

    # IMPLEMENT THIS METHOD
    k = 5
    d = Xtest.shape[1]
    count = 0
    ypred=np.empty([ytest.shape[0],1])
    for j in range(0,ytest.shape[0]):
        x = np.matrix(Xtest[j]).T
        pmle = list()
    # Xtest - a N x d matrix with each row correspond
        for i in range(0,k):
            mean = np.matrix(means[:,i]).T
            temp = (((x-mean).T) * (inv(covmats[i]))) * (x-mean)
            temp = np.exp(-0.5*temp)
            temp = temp / (sqrt(2 * pi))**d 
            temp = temp / sqrt(det(covmats[i]))
            pmle.append(temp)
        
        if((pmle.index(max(pmle)) - ytest[j] +1) == 0):
            count = count + 1
        ypred[j]=pmle.index(max(pmle))+1
        
    return count,ypred


def learnOLERegression(X,y):
    # Inputs:                                                         
    # X = N x d 
    # y = N x 1                                                               
    # Output: 
    # w = d x 1 
    X = np.matrix(X)
    w = inv(X.T * X) * X.T * y
    return w

def learnRidgeRegression(X,y,lambd):
    # Inputs:
    # X = N x d                                                               
    # y = N x 1 
    # lambd = ridge parameter (scalar)
    # Output:                                                                  
    # w = d x 1                                                                

    # IMPLEMENT THIS METHOD  
   X = np.matrix(X)
   y = np.matrix(y)
   w = inv(lambd * np.identity(X.shape[1]) + X.T * X) * X.T * y
  
   return w

def testOLERegression(w,Xtest,ytest):
    # Inputs:
    # w = d x 1
    # Xtest = N x d
    # ytest = X x 1
    # Output:
    # mse
    
    # IMPLEMENT THIS METHOD
    Xtest = np.matrix(Xtest)
    ytest = np.matrix(ytest)
    temp = (ytest - Xtest * w)
    mse = temp.T * temp / Xtest.shape[0]
    # IMPLEMENT THIS METHOD
    
    return mse

def regressionObjVal(w, X, y, lambd):

    # compute squared error (scalar) and gradient of squared error with respect
    # to w (vector) for the given data X and y and the regularization parameter
    # lambda     
  
    w = np.matrix(w)
    temp = y - X * w.T
    error = 0.5 * (temp).T * temp  + 0.5 * lambd * w *w.T
    # IMPLEMENT THIS METHOD     
    error_grad = 2 * (X.T * (X * w.T - y) + lambd * w.T)
    error_grad = np.array(error_grad)
    error_grad = np.squeeze(error_grad)
    return error, error_grad

def mapNonLinear(x,p):
    # Inputs:                                                                  
    # x - a single column vector (N x 1)                                       
    # p - integer (>= 0)                                                       
    # Outputs:                                                                 
    # Xp - (N x (p+1)) 
	
    # IMPLEMENT THIS METHOD
    #x=np.array(x)
    #x=np.squeeze(x)
    Xp = np.empty([x.shape[0],p+1])
    for j in range(0,x.shape[0]):
        for i in range(0,p+1):
            Xp[j,i] = (x[j]**i)
    return Xp

# Main script

# Problem 1
# load the sample data                                                                 
if sys.version_info.major == 2:
    X,y,Xtest,ytest = pickle.load(open('sample.pickle','rb'))
    print(y)
else:
    X,y,Xtest,ytest = pickle.load(open('sample.pickle','rb'),encoding = 'latin1')

# LDA
means,covmat = ldaLearn(X,y)
ldaacc,ldares = ldaTest(means,covmat,Xtest,ytest)
print('LDA Accuracy = '+str(ldaacc))
# QDA
means,covmats = qdaLearn(X,y)
qdaacc,qdares = qdaTest(means,covmats,Xtest,ytest)
print('QDA Accuracy = '+str(qdaacc))

# plotting boundaries

x1 = np.linspace(-5,20,100)
x2 = np.linspace(-5,20,100)
xx1,xx2 = np.meshgrid(x1,x2)
xx = np.zeros((x1.shape[0]*x2.shape[0],2))
xx[:,0] = xx1.ravel()
xx[:,1] = xx2.ravel()
ytest=ytest.ravel()
fig = plt.figure(figsize=[12,6])
plt.subplot(1, 2, 1)

zacc,zldares = ldaTest(means,covmat,xx,np.zeros((xx.shape[0],1)))

zldares=np.squeeze(zldares)

plt.contourf(x1,x2,zldares.reshape((x1.shape[0],x2.shape[0])),alpha=0.3)
plt.scatter(Xtest[:,0],Xtest[:,1],c=ytest)
plt.title('LDA')

plt.subplot(1, 2, 2)

zacc2,zqdares = qdaTest(means,covmats,xx,np.zeros((xx.shape[0],1)))
zqdares=np.squeeze(zqdares)
plt.contourf(x1,x2,zqdares.reshape((x1.shape[0],x2.shape[0])),alpha=0.3)
plt.scatter(Xtest[:,0],Xtest[:,1],c=ytest)
plt.title('QDA')

plt.show() 


# Problem 2
if sys.version_info.major == 2:
    X,y,Xtest,ytest = pickle.load(open('diabetes.pickle','rb'))
else:
    X,y,Xtest,ytest = pickle.load(open('diabetes.pickle','rb'),encoding = 'latin1')

# add intercept
X_i = np.concatenate((np.ones((X.shape[0],1)), X), axis=1)
Xtest_i = np.concatenate((np.ones((Xtest.shape[0],1)), Xtest), axis=1)

w = learnOLERegression(X,y)
mle = testOLERegression(w,Xtest,ytest)

w_i = learnOLERegression(X_i,y)
mle_i = testOLERegression(w_i,Xtest_i,ytest)

print('MSE without intercept '+str(mle))
print('MSE with intercept '+str(mle_i))

# Problem 3
k = 101
min1=float('inf')
min2=float('inf')
minlambd=float('inf')
lambdas = np.linspace(0, 1, num=k)
i = 0
norm=0
mses3_train = np.zeros((k,1))
mses3 = np.zeros((k,1))
for lambd in lambdas:
    w_l = learnRidgeRegression(X_i,y,lambd)
    mses3_train[i] = testOLERegression(w_l,X_i,y)
    if(min1>mses3_train[i]):
        min1=mses3_train[i]
        minlambd=lambd
        
    mses3[i] = testOLERegression(w_l,Xtest_i,ytest)
    if(min2>mses3[i]):
        min2=mses3[i]
        minlambd=lambd

    i = i + 1

    

   
fig = plt.figure(figsize=[12,6])
plt.subplot(1, 2, 1)
plt.plot(lambdas,mses3_train)
plt.title('MSE for Train Data')
plt.subplot(1, 2, 2)
plt.plot(lambdas,mses3)
plt.title('MSE for Test Data')

plt.show()

# Problem 4
k = 101
lambdas = np.linspace(0, 1, num=k)
i = 0
mses4_train = np.zeros((k,1))
mses4 = np.zeros((k,1))
opts = {'maxiter' : 20}    # Preferred value.                                                
w_init = np.ones((X_i.shape[1],1))
for lambd in lambdas:
    args = (X_i, y, lambd)
    w_l = minimize(regressionObjVal, w_init, jac=True, args=args,method='CG', options=opts)
    w_l = np.transpose(np.array(w_l.x))
    w_l = np.reshape(w_l,[len(w_l),1])
    mses4_train[i] = testOLERegression(w_l,X_i,y)
    mses4[i] = testOLERegression(w_l,Xtest_i,ytest)
    i = i + 1
fig = plt.figure(figsize=[12,6])
plt.subplot(1, 2, 1)
plt.plot(lambdas,mses4_train)
plt.plot(lambdas,mses3_train)
plt.title('MSE for Train Data')
plt.legend(['Using scipy.minimize','Direct minimization'])

plt.subplot(1, 2, 2)
plt.plot(lambdas,mses4)
plt.plot(lambdas,mses3)
plt.title('MSE for Test Data')
plt.legend(['Using scipy.minimize','Direct minimization'])
plt.show()


#Problem 5
pmax = 7
lambda_opt = 0.07 # REPLACE THIS WITH lambda_opt estimated from Problem 3
mses5_train = np.zeros((pmax,2))
mses5 = np.zeros((pmax,2))
for p in range(pmax):
    Xd = mapNonLinear(X[:,2],p)
    Xdtest = mapNonLinear(Xtest[:,2],p)
    w_d1 = learnRidgeRegression(Xd,y,0)
    mses5_train[p,0] = testOLERegression(w_d1,Xd,y)
    mses5[p,0] = testOLERegression(w_d1,Xdtest,ytest)
    w_d2 = learnRidgeRegression(Xd,y,lambda_opt)
    mses5_train[p,1] = testOLERegression(w_d2,Xd,y)
    mses5[p,1] = testOLERegression(w_d2,Xdtest,ytest)

fig = plt.figure(figsize=[12,6])
plt.subplot(1, 2, 1)
plt.plot(range(pmax),mses5_train)
plt.title('MSE for Train Data')
plt.legend(('No Regularization','Regularization'))
plt.subplot(1, 2, 2)
plt.plot(range(pmax),mses5)
plt.title('MSE for Test Data')
plt.legend(('No Regularization','Regularization'))
plt.show()