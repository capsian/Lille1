import matplotlib.pyplot as plt
from tagger import get_word_freq_df

df_word_freq = get_word_freq_df('./data/lexique.json')
df_word_freq["len"] = df_word_freq["word"].map(lambda x: len(x))

fig = plt.figure()
df_word_freq["len"].hist(bins=7)
fig.savefig('lexique_len.png')