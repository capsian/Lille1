# Preprocessor

lemma:
	python3 src/text_preprocessor.py -v -in ./dataset/train_master.csv -op l

stemm:
	python3 src/text_preprocessor.py -v -in ./dataset/train_master.csv -op s

# With train_master_lemmatized

rdg_l:
	python3 src/models.py -v -in ./dataset/train_master_lemmatized.csv -m rdg

sgd_l:
	python3 src/models.py -v -in ./dataset/train_master_lemmatized.csv -m sgd

lr_l:
	python3 src/models.py -v -in ./dataset/train_master_lemmatized.csv -m lr

lasso_l:
	python3 src/models.py -v -in ./dataset/train_master_lemmatized.csv -m lasso

gnb_l:
	python3 src/models.py -v -in ./dataset/train_master_lemmatized.csv -m gnb

rf_l:
	python3 src/models.py -v -in ./dataset/train_master_lemmatized.csv -m rf


# With train_master_stemm

rdg_s:
	python3 src/models.py -v -in ./dataset/train_master_stemm.csv -m rdg

sgd_s:
	python3 src/models.py -v -in ./dataset/train_master_stemm.csv -m sgd

lr_s:
	python3 src/models.py -v -in ./dataset/train_master_stemm.csv -m lr

lasso_s:
	python3 src/models.py -v -in ./dataset/train_master_stemm.csv -m lasso

gnb_s:
	python3 src/models.py -v -in ./dataset/train_master_stemm.csv -m gnb

rf_s:
	python3 src/models.py -v -in ./dataset/train_master_stemm.csv -m rf


# save model

sv_rdg_l:
	python3 src/models.py -v -in ./dataset/train_master_lemmatized.csv -m rdg -sm models/rdg_clf_lemma

# Load models

lm_rdg_l:
	python3 src/models.py -v -in ./dataset/train_master_lemmatized.csv -lm models/rdg_clf_lemma

# Server

server:
	python3 src/server.py

# Tests

test_server:
	./scripts/test_server.sh


tmp:
	python3 src/models.py -v -in ./dataset/server/train_master_stemm.csv -m rdg