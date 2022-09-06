"""
Exemplo de aplicação do algoritmo de KNN (K-nearest neighbors)
Abrir arquivo no Coogle Colab.

Example of application of the KNN algorithm
Open file at Google Colab.
"""

# -*- coding: utf-8 -*-
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
#from google.colab import drive
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import classification_report, confusion_matrix
import io
from google.colab import files

# define column names
names = [
  'sepal_length',
  'sepal_width',
  'petal_length',
  'petal_width',
  'class',
]

#upload file
uploaded = files.upload()

df = pd.read_csv(io.BytesIO(uploaded['iris.data.txt']), header=None, names=names)
df.head(20)

sns.pairplot(df)

# create design matrix X and target vector y
X = np.array(df.iloc[:, 0:4])  # end index is exclusive
y = np.array(df['class'])    # another way of indexing a pandas df

# split into train and test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)

# instantiate learning model (k = 3)
knn = KNeighborsClassifier(n_neighbors=3)

# fitting the model
knn.fit(X_train, y_train)

# predict the response
y_pred = knn.predict(X_test)

# evaluate accuracy
print("accuracy: {}".format(accuracy_score(y_test, y_pred)))

# Creates a confusion matrix
cm = confusion_matrix(y_test, y_pred)
# Transform to df for easier plotting
cm_df = pd.DataFrame(cm,
                     index = ['setosa','versicolor','virginica'], 
                     columns = ['setosa','versicolor','virginica'])

sns.heatmap(cm_df, annot=True)
plt.title('Accuracy:{0:.3f}'.format(accuracy_score(y_test, y_pred)))
plt.ylabel('Actual label')
plt.xlabel('Predicted label')
plt.show()

from sklearn.metrics import classification_report, confusion_matrix
print('Confusion matrix:')
print(confusion_matrix(y_test, y_pred))
print('\nClassification report:')
print(classification_report(y_test, y_pred))
