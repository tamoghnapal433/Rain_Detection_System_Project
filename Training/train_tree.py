import pandas as pd
from sklearn.tree import DecisionTreeClassifier , export_text
#we are reading a dataset downloaded from open-metreo
df=pd.read_csv("dataset.csv",skiprows=3)
df.columns = ['time','humidity','rain_mm','pressure']
df['delta_pressure'] = df['pressure'].diff()
df['rain_label'] = (df['rain_mm'] > 0.0).astype(int)
df_clean = df.dropna().copy()
X = df_clean[['delta_pressure', 'humidity']]
y = df_clean['rain_label']
clf = DecisionTreeClassifier(criterion='gini', max_depth=2, random_state=0)
clf.fit(X, y)
print("\n EXTRACTED DECISION TREE RULES :\n")
print(export_text(clf, feature_names=['delta_pressure', 'humidity']))
