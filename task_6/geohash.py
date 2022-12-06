from math import floor
from collections import defaultdict
from typing import Tuple

import numpy as np
import pandas as pd


def encode(lat: float, lon: float, precision: int = 18, bits_per_char: int = 2) -> str:
    """
    Calculate geohash for given coords

    Params
    ------
    lat: float
        Latitude
    lon: float
        Longitude
    precision: int
        Precision rate (geohash cell size)
    bits_per_char: int
        Encoding bits count

    Returns
    -------
    code: str
        Geohash code
    """
    bits = precision * bits_per_char
    level = bits >> 1
    dim = 1 << level

    lat_y = (lat + 90) / 180.0 * dim
    lon_x = (lon + 180) / 360.0 * dim
    x, y = min(dim - 1, int(floor(lon_x))), min(dim - 1, int(floor(lat_y)))
    code = 0
    lvl = dim >> 1

    while lvl > 0:
        rx = int((x & lvl) > 0)
        ry = int((y & lvl) > 0)
        code += lvl * lvl * ((3 * rx) ^ ry)

        if ry == 0:
            if rx == 1:
                x = lvl - 1 - x
                y = lvl - 1 - y

        lvl >>= 1

    BASE4 = '0123'
    code_bit_length = code.bit_length()
    code_len = (code_bit_length + 1) // 2
    res = ['0'] * code_len

    for i in range(code_len - 1, -1, -1):
        res[i] = BASE4[code & 0b11]
        code >>= 2

    code = ''.join(res).rjust(precision, '0')

    return code


def chunk_encode(inp: Tuple[int, np.array]):
    i, chunk = inp
    res = defaultdict(list)

    for lat, lon in chunk:
        code = encode(lat, lon)
        res['lat'].append(lat)
        res['lon'].append(lon)
        res['code'].append(code)

    res = pd.DataFrame(res, dtype=str)
    res.to_csv(f"part_{i}.csv.gz", index=False, compression='gzip')
