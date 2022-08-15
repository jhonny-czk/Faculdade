#https://colab.research.google.com
'''
Ciencia de Dados
Exemplo de aplicacao da biblioteca Pandas
Usar no Google Collab!
-----------------------------------------
Data Science
Pandas lib application example
Run the code in Google Collab!
'''
#Leitura das libs
import pandas as pd
import io
from google.colab import files

#Upload de arquivo p/ leitura
uploaded = files.upload()

#Lê o arquivo e exibe o resultado na tela
df = pd.read_csv(io.BytesIO(uploaded['boxoffice.csv']))
df.head(20)

df['year'].mean()

df['year'].min()

df['lifetime_gross'].sum()

#Importar biblioteca para exibir os graficos
import matplotlib.pyplot as plt
import numpy as np

#Exibir graficos na tela
plt.bar(df['year'],df['lifetime_gross'])
plt.show()
