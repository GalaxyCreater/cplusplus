# -*- coding: utf-8 -*-
import copy


# 吃水不忘挖井人，先贴上思路来源（Java)http://blog.csdn.net/DERRANTCM/article/details/51433148
# 解题思路：使用三个变量，分别表示待进站火车、待出站火车、出站火车。
# 每次作业（只操作一辆车）有两种情况发生，一种是进站作业，一种是出站作业
# 将作业结果当作参数递归下去，递归结束标志是待进站火车和待出站火车都没有了


def handle(pre_station, in_station, after_station):
    if not pre_station and not in_station:  # 没有待进站的，也没有待出站的车，一种情况产生了
        result.append(" ".join(after_station))
    else:
        if in_station:  # 出站作业，先检查站内是否有车
            temp_pre = copy.copy(pre_station)
            temp_in = copy.copy(in_station)
            temp_after = copy.copy(after_station)
            temp_after.append(temp_in.pop())
            handle(temp_pre, temp_in, temp_after)  # 进行下一步作业
        if pre_station:  # 进站作业，先检查是否还有待进站车辆
            temp_pre = copy.copy(pre_station)
            temp_in = copy.copy(in_station)
            temp_after = copy.copy(after_station)
            temp_in.append(temp_pre.pop(0))
            handle(temp_pre, temp_in, temp_after)  # 进行下一步作业


count = int(raw_input())  # 火车数量，没有用到，但是是题目输入格式要求，故保留
row_2 = raw_input()
result = []  # 记录最终数据
pre_station = [x for x in row_2.split(" ")]  # 待进站的车辆
in_station = []  # 待出站车辆
after_station = []  # 出站后的车辆
handle(pre_station, in_station, after_station)
result.sort()  # 要字典序输出，排个序咯
for rs in result:
    print rs
