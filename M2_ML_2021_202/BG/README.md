# BigData

# Author

- Selim Lakhdar
    - selim.lakhdar@gmail.com
    - selim.lakhdar.etu@univ-lille.fr


# Content
## Notebooks
- exploration.ipynb
  - Data loading
  - Visualization
  - CountVectorizer:
    - Word count
  - First try with
    - Basic tokenizer
    - SnowballStemmer
  - Classifiers scores with cross_val=5 on train
  - Classifiers scores with ROC_AUC
    - fit on train
    - predict on test
  - GridSearchCV
  - Review
- exploration_corrected.ipynb
  - Using spacy fr_core_news_lg as corpus
  - Improve text_preprocess:
    - Use stop words
    - Use lemmatizer
    - Remove punctuation
    - Remove digits
- test.ipynb
  - test with saved model
## src
  - text_preprocessor.py
    - script used to transform a dataset
  - models.py
    - script used to 
      - calculate roc_auc score of a classifier (can be saved)
      - load a model and evaluate it
## models
  - ~~clf_cv: represent the model a the first try (with cross val)~~ DEPRECATED
  - ~~clf_cv_corrected: represent the model of the first try with the correction (with cross val)~~ DEPRECATED
  - clf_roc_auc: represent the model state at first try
  - clf_roc_auc_corrected: represent the model state after improvement
  - clf_grid: represent the model state at first try
  - clf_grid_corrected: represent the model state after improvement   

==> Best models are **rdg_clf_corrected** or  **rdg_grid_corrected**
## lib
  - tried to test the tree tagger library

# Scores
### First try :

| clf / test score        | cross_val | roc_auc    | hyper_param |
|-------------------------|-----------|------------|-------------|
| SGDClassifier           | 0.65      | 0.63       | 0.63        |
| Ridge                   | 0.11      | **_0.7_**  | **_0.7_**   |
| LogisticRegression      | 0.65      | 0.64       | 0.64        |
| RandomForestClassifier  | **_0.66_**| 0.64       | 0.52        |

- cross_val: cross validation = 5, tested on train

### Corrected : (lemma)

| clf / test score        | cross_val | roc_auc    | hyper_param |
|-------------------------|-----------|------------|-------------|
| SGDClassifier           | 0.66      | 0.64       | 0.64        |
| Ridge                   | 0.12      | **_0.699_**| **_0.7_**   |
| LogisticRegression      | 0.66      | 0.64       | 0.64        |
| RandomForestClassifier  | **_0.67_**| 0.64       | 0.52        |

### Ngrams: (1,3)

| clf / test score        | roc_auc lemma | roc_auc stemm |
|-------------------------|---------------|---------------|
| SGDClassifier           | 0.64          |  0.64         |
| Ridge                   | **_0.71_**     |  0.71         |
| LogisticRegression      | _0.65_    |  0.65         |
| RandomForestClassifier  | 0.64          |  0.64         |

# HowTO
- Unzip:
  - models/rf_clf_roc_auc_corrected.zip
  - models/rf_clf_roc_auc.zip
```shell
# preprocess text (make stemm)
make lemma
make stemm
# classifiers : ['sgd', 'rdg', 'lr', 'lasso', 'gnb', 'rf']
make <clf>_s # processing train_master_stemm.csv
make <clf>_l # processing train_master_lemmatized.csv
# classify and save model
make sv_rdg_l 
# load a model (rdg)
make lm_rdg_l
```

# Server
- Have to split our dataset to train and test. Then we will feed the test set ! 