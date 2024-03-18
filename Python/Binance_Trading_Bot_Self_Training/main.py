import operator
from datetime import datetime
from binance.client import Client
from enum import Enum

import talib as ta
import numpy as np
import time

from binance.enums import SIDE_SELL, SIDE_BUY, FUTURE_ORDER_TYPE_MARKET


class BinanceConnection:

    def __init__(self, file):
        self.connect(file)

    """ Creates Binance client """

    def connect(self, file):
        lines = [line.rstrip('\n') for line in open(file)]
        key = lines[0]
        secret = lines[1]
        self.client = Client(key, secret)

    def order(self, side, quantity, symbol, order_type=FUTURE_ORDER_TYPE_MARKET):
        # self.client.futures_change_leverage(symbol=symbol, leverage=10)
        try:
            print("sending order")
            order = self.client.futures_create_order(symbol=symbol,
                                                     side=side,
                                                     type=order_type,
                                                     quantity=quantity,
                                                     recvWindow=10000000)

            print(order)
        except Exception as e:
            print("an exception occured - {}".format(e))
            return False

        return True


class PositionType(Enum):
    LONG = 'Long'
    SHORT = 'Short'
    NONE = 'None'






def handleEma(arr):
    price = arr[-1]

    ema8 = ta.EMA(arr, 8)
    last_ema8 = ema8[-1]

    ema14 = ta.EMA(arr, 14)
    last_ema14 = ema14[-1]

    ema50 = ta.EMA(arr, 50)
    last_ema50 = ema50[-1]

    # long = price > ema8 > ema14 > ema50 && last_slowk > 50 && before_slowk < 50 or last_slowd > 50 && bfr_slowd<50
    if price > last_ema8 > last_ema14 > last_ema50:
        return PositionType.LONG
    elif last_ema50 > last_ema14 > last_ema8 > price:
        return PositionType.SHORT
    else:
        return PositionType.NONE



def handleRsi(arr):
    rsi = ta.RSI(arr)
    stoch = ta.STOCH(rsi, rsi, rsi, fastk_period=14, slowk_period=3, slowd_period=3)
    lastrsi = rsi[-1]


    lastk = stoch[0][-1]
    lastd = stoch[1][-1]

    previousk = stoch[0][-2]
    previousd = stoch[1][-2]

    if (lastk > 50 and lastrsi > 50):
        return PositionType.LONG
    elif (lastk < 50 and lastrsi < 50):
        return PositionType.SHORT
    else:
        return PositionType.NONE







if __name__ == '__main__':
    filename = 'credentials.txt'
    connection = BinanceConnection(filename)

    TRADE_SYMBOL = 'SOLUSDT'
    TRADE_QUANTITY = 1
    interval = "3m"
    limit = 100

    now = datetime.now()
    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

    print("bot basladi: ", dt_string)

    in_position = PositionType.NONE

    PositionEntryPrice = 0
    # slprice = 0
    #tpprice = 0
    latr = 0
    satr = 0

    while True:
        # 2 saniye bekliyoruz. Sürekli sorgu göndermeye gerek yok.
        time.sleep(2)

        try:
            klines = connection.client.get_klines(symbol=TRADE_SYMBOL, interval=interval, limit=limit)
        except Exception as exp:
            print(exp.status_code, flush=True)
            print(exp.message, flush=True)

        open = [float(entry[1]) for entry in klines]
        high = [float(entry[2]) for entry in klines]
        low = [float(entry[3]) for entry in klines]
        close = [float(entry[4]) for entry in klines]

        TR = []

        for i in range(2,16):
            TR[i-2] = max((high[-i],low[-i]), (high[-i], close(-i)), (low(-i),close(-i)))

        ATR = sum(TR) / len(TR)

        close_array = np.asarray(close)

        ema = handleEma(close_array)
        rsi = handleRsi(close_array)

        if ema == rsi and in_position == PositionType.NONE:
            if ema == PositionType.LONG:
                connection.order(SIDE_BUY, TRADE_QUANTITY, TRADE_SYMBOL)
                in_position = PositionType.LONG
                latr = ATR * 2
                PositionEntryPrice = close_array[-1]




            elif ema == PositionType.SHORT:
                connection.order(SIDE_SELL, TRADE_QUANTITY, TRADE_SYMBOL)
                in_position = PositionType.SHORT
                satr = ATR * 2
                PositionEntryPrice = close_array[-1]

        #print(ATR)
        #print(PositionEntryPrice)
        #print(latr)
        #print(satr)







        #if PositionEntryPrice != 0:
        #if in_position == PositionType.LONG:
        #slprice = PositionEntryPrice - 2 * latr
        #if in_position == PositionType.SHORT:
        #slprice = PositionEntryPrice + 2 * satr
        #  else:
        #slprice = 0





        #if PositionEntryPrice != 0:
                # if in_position == PositionType.LONG:
            #  tpprice = PositionEntryPrice + 2 * latr
                # if in_position == PositionType.SHORT:
                # tpprice = PositionEntryPrice - 2 * satr
                # else:
        #   tpprice = 0







        if PositionEntryPrice != 0:
            if in_position == PositionType.LONG and close_array[-1] >= PositionEntryPrice + latr:
                connection.order(SIDE_SELL, TRADE_QUANTITY, TRADE_SYMBOL)
                in_position = PositionType.NONE
                PositionEntryPrice = 0
                latr = 0
            if in_position == PositionType.LONG and close_array[-1] <= PositionEntryPrice - latr:
                connection.order(SIDE_SELL, TRADE_QUANTITY, TRADE_SYMBOL)
                in_position = PositionType.NONE
                PositionEntryPrice = 0
                latr = 0
            if in_position == PositionType.SHORT and close_array[-1] <= PositionEntryPrice - satr:
                connection.order(SIDE_BUY, TRADE_QUANTITY, TRADE_SYMBOL)
                in_position = PositionType.NONE
                PositionEntryPrice = 0
                satr = 0
            if in_position == PositionType.SHORT and close_array[-1] >= PositionEntryPrice + satr:
                connection.order(SIDE_BUY, TRADE_QUANTITY, TRADE_SYMBOL)
                in_position = PositionType.NONE
                PositionEntryPrice = 0
                satr = 0






        ##if PositionEntryPrice != 0:
            ##change_percentage = ((close_array[-1] - PositionEntryPrice) / PositionEntryPrice) * 100
            ##if in_position == PositionType.LONG and (change_percentage >= 1 or change_percentage <= -1):
                ##print("change percentage: ", change_percentage, "%")
                ##connection.order(SIDE_SELL, TRADE_QUANTITY, TRADE_SYMBOL)
                ##in_position = PositionType.NONE
                ##PositionEntryPrice = 0
                ##elif in_position == PositionType.SHORT and (change_percentage <= -1 or change_percentage >= 1):
                ##connection.order(SIDE_BUY, TRADE_QUANTITY, TRADE_SYMBOL)
                ##print("change percentage: ", change_percentage, "%")
                ##in_position = PositionType.NONE
                ##PositionEntryPrice = 0
