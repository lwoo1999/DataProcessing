import {statistic} from "numbers"
import {t_p, C, k_p} from "./data"

const pow = Math.pow

const sqrt = Math.sqrt

export const mean = statistic.mean

export const distance = (x, y) => sqrt(pow(x, 2) + pow(y, 2))

// 样本方差
export const variance = (arr) => Math.pow(statistic.standardDev(arr), 2) * arr.length / (arr.length - 1)

// 标准差
export const standardDeviation = statistic.standardDev
