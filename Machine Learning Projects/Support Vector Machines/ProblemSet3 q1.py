
# coding: utf-8

# In[ ]:


from mnist import MNIST
import matplotlib.pyplot as plt

import numpy as np
from sklearn.datasets import fetch_mldata
from sklearn import datasets, svm, metrics
from sklearn import cross_validation

mndata = MNIST('C:\\Users\\abina\\Pictures\\ML\\')
mndata.gz = True

images, labels = mndata.load_training()
#print(images[3])
plt.imshow(np.reshape(images[0],((28,28))))

images=np.array(images)
labels=np.array(labels)
print(images.shape)
print(labels.shape)



# In[ ]:


classifier = svm.SVC(gamma=3.1, C=3, kernel='linear') #C parameter sets the trade-off between the margin and the training error
classifier.fit(images,labels)
print(cross_validation.cross_val_score(classifier, images, labels, cv=5))


# In[ ]:


test_images,test_labels=mndata.load_testing()
#X_test, y_test = np.float32(mnist.X_test[60000:]) / 255., np.float32(mnist.y_test[60000:])
expected = test_labels
predicted = classifier.predict(test_images)

print("Classification report for classifier %s:\n%s\n"
      % (classifier, metrics.classification_report(expected, predicted)))
print("Confusion matrix:\n%s" % metrics.confusion_matrix(expected, predicted))

