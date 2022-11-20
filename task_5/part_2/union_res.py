#!/bin/python
import os

import pandas as pd

INPUT_NAME = 'results'
OUTPUT_NAME = 'evolution.txt'


if __name__ == '__main__':
    files_lst = [itm for itm in os.listdir(INPUT_NAME) if '.csv' in itm]
    df_lst = []

    for name in files_lst:
        filename = os.path.join(INPUT_NAME, name)
        df = pd.read_csv(filename, sep=';', dtype=str)
        df_lst.append(df)

    df = pd.concat(df_lst, axis=0)
    df['rank '] = df['rank'].astype(int)
    df['step'] = df['step'].astype(int)
    df = (df
        .sort_values(['step', 'rank'])
        .groupby('step')['state']
        .agg(list)
        .apply(lambda x: ''.join(x) + '\n')
        .sort_index()
    )
    with open(OUTPUT_NAME, 'w') as f:
        f.writelines(df.values)
