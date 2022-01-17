#!/usr/local/bin/python3

import numpy as np
import pandas as pd

import tweet_classifier_bayes
import tweet_classifier_keyword
import tweet_classifier_knn


def scores(y_pred, y_expected):
    matrix = np.zeros(9).reshape(3, 3)
    for i in range(len(y_expected)):
        matrix[0][0] += 1 if (y_expected[i] == 0 and y_pred[i] == 0) else 0  # 1 TP_0
        matrix[0][1] += 1 if (y_expected[i] == 0 and y_pred[i] == 2) else 0  # 2
        matrix[0][2] += 1 if (y_expected[i] == 0 and y_pred[i] == 4) else 0  # 3

        matrix[1][0] += 1 if (y_expected[i] == 2 and y_pred[i] == 0) else 0  # 4
        matrix[1][1] += 1 if (y_expected[i] == 2 and y_pred[i] == 2) else 0  # 5 TP_2
        matrix[1][2] += 1 if (y_expected[i] == 2 and y_pred[i] == 4) else 0  # 6

        matrix[2][0] += 1 if (y_expected[i] == 4 and y_pred[i] == 0) else 0  # 7
        matrix[2][1] += 1 if (y_expected[i] == 4 and y_pred[i] == 2) else 0  # 8
        matrix[2][2] += 1 if (y_expected[i] == 4 and y_pred[i] == 4) else 0  # 9 TP_4

    score = np.arange(12).reshape(3, 4)

    # neg
    score[0][0] = matrix[0][0]  # 0 TP
    score[0][1] = matrix[0][1] + matrix[0][2]  # 0 FP : 2 + 3
    score[0][2] = matrix[1][1] + matrix[1][2] + matrix[2][1] + matrix[2][2]  # 0 TN : 5 + 6 + 8 + 9
    score[0][3] = matrix[1][0] + matrix[2][0]  # 0 FN: 4 + 7

    # neut
    score[1][0] = matrix[1][1]  # 2 TP
    score[1][1] = matrix[1][0] + matrix[1][2]  # 2 FP : 4 + 6
    score[1][2] = matrix[0][0] + matrix[0][2] + matrix[2][0] + matrix[2][2]  # 2 TN : 1 + 3 + 7 + 9
    score[1][3] = matrix[0][1] + matrix[2][1]  # 2 FN : 2 + 5

    # pos
    score[2][0] = matrix[2][2]  # 4 TP
    score[2][1] = matrix[2][0] + matrix[2][2]  # 4 FP : 7 + 8
    score[2][2] = matrix[0][0] + matrix[0][1] + matrix[1][0] + matrix[1][1]  # 4 TN : 1 + 2 + 4 + 5
    score[2][3] = matrix[0][2] + matrix[1][2]  # 4 FN : 3 + 6

    # TP + TN / TP+FP+TN+FN
    accuracy = score[0][0] + score[1][0] + score[2][0] + score[0][2] + score[1][2] + score[2][2]
    accuracy /= (score[0][0] + score[1][0] + score[2][0] + score[0][2] + score[1][2] + score[2][2] + score[2][1] +
                 score[1][1] + score[0][1] + score[0][3] + score[1][3] + score[2][3])

    # TP / (TP+FP)
    precision = score[2][0] + score[1][0] + score[0][0]
    precision /= (score[2][0] + score[1][0] + score[0][0] + score[2][1] + score[1][1] + score[0][0])

    # TP / (TP+FN)
    recall = score[2][0] + score[1][0] + score[0][0]
    recall /= (score[2][0] + score[1][0] + score[0][0] + score[2][3] + score[1][3] + score[0][3])

    f1_score = 2 * (precision * recall) / (precision + recall)

    return accuracy, precision, recall, f1_score


def cross_val(x, y, k, clf, verbose=False):
    indices = list(range(len(x)))
    np.random.shuffle(indices)
    i_all = np.array_split(indices, k)
    accuracy_res = []
    f1_res = []
    for i in range(len(i_all)):
        i_train = i_all.copy()
        i_valid = i_train.pop(i)
        i_train = np.concatenate(i_train)
        clf.fit(x[i_train], y[i_train])
        accuracy, precision, recall, f1_score = scores(clf.predict(x[i_valid]), y[i_valid])
        if verbose:
            print("cross_val:%d: %s: accuracy:%s, precision:%s, recall:%s, f1_score:%s" % (i, clf.name, accuracy, precision, recall, f1_score))
        accuracy_res.append(accuracy)
        f1_res.append(f1_score)
    if verbose:
        print("cross_val: " + clf.name + ", final accuracy_score: " + str(np.average(accuracy_res)) + ", final f1_score: " + str(np.average(f1_res)))
    return np.average(accuracy_res)


def main():
    print("Reading .....")
    df_in = pd.read_csv("data/training/training.1600000.processed.noemoticon.clean.csv")

    print("CounterClassifier .....")
    f1_score = cross_val(df_in["MSG"].values, df_in["SCORE"].values, 10,
                         tweet_classifier_keyword.KeywordClassifier("ANG"), True)
    print("accuracy_score = " + str(f1_score))

    print("BayesFreq .....")
    f1_score = cross_val(df_in["MSG"].values, df_in["SCORE"].values, 10, tweet_classifier_bayes.BayesClassifier("ANG"),
                         True)
    print("accuracy_score = " + str(f1_score))

    print("KNNClassifier .....")
    f1_score = cross_val(df_in["MSG"].values, df_in["SCORE"].values, 10,
                         tweet_classifier_knn.KNNClassifier("ANG", 10, tweet_classifier_knn.dist_simple))
    print("accuracy_score = " + str(f1_score))
    return 0


if __name__ == "__main__":
    main()
    exit(0)
