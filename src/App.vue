<template>
<b-container>
  <b-row><b-col><h1>不确定度计算</h1></b-col></b-row>
  <b-form-row>
    <b-col lg=2 cols=6><label for="n">输入数据个数：</label></b-col>
    <b-col lg=2 cols=6>
      <b-form-input id="n" type="number" min=3 max=10 step=1 :value="n" @input="handleNChange"></b-form-input>
    </b-col>
  </b-form-row>
  <br>
  <b-form-row>
    <b-col lg=3 cols=6 v-for="(data, key) of datas" :key="key">
      <b-form-input :value="data" @change="value => handleDataChange(value, key)"></b-form-input>
    </b-col>
  </b-form-row>
  <br>
  <b-form-row>
    <b-col lg=1 cols=3><label for="p">置信概率：</label></b-col>
    <b-col lg=2 cols=3>
      <b-form-select id="p" v-model="p" class="mb-3">
        <option value="0.68">0.68</option>
        <option value="0.90">0.90</option>
        <option value="0.95" selected>0.95</option>
        <option value="0.99">0.99</option>
      </b-form-select>
    </b-col>
    <b-col lg=1 cols=3><label for="u1">最大允差：</label></b-col>
    <b-col lg=2 cols=3><b-form-input id="u1" @change="handleUb1Change" value=0></b-form-input></b-col>
    <b-col lg=1 cols=3><label for="u2">估读误差：</label></b-col>
    <b-col lg=2 cols=3><b-form-input id="u2" @change="handleUb2Change" value=0></b-form-input></b-col>
    <b-col lg=1 cols=3><label for="d">分布：</label></b-col>
    <b-col lg=2 cols=3><b-form-select id="d" v-model="distribution" class="mb-3">
      <option value="正态分布">正态分布</option>
      <option value="均匀分布">均匀分布</option>
      <option value="三角分布">三角分布</option>
    </b-form-select></b-col>
  </b-form-row>
  <hr>
  <b-row>
    <b-col lg=4 cols=12><p>A 类不确定度：{{u_a}}</p></b-col>
    <b-col lg=4 cols=12><p>B 类不确定度：{{u_b}}</p></b-col>
    <b-col lg=4 cols=12><p>合成不确定度：{{u}}</p></b-col>
  </b-row>
  <b-row>
    <b-col><p class="lead">{{mean}}±{{u}}</p></b-col>
  </b-row>
  <div id="boxplot"></div>
</b-container>
</template>

<script>
import {t_p, C, k_p} from "./scripts/data.js"
import {mean, distance, variance, standardDeviation} from "./scripts/utils.js"
import {boxplot} from "./scripts/plot.js"

export default {
  data () {
    return {
      n: 3,
      datas: [0, 0, 0],
      p: "0.95",
      ub1: 0,
      ub2: 0,
      distribution: "正态分布"
    }
  },
  computed: {
    u_a () {
      return Math.sqrt(variance(this.datas) / this.n) * t_p[this.p][this.n]
    },
    u_b () {
      return k_p[this.distribution][this.p] * distance(this.ub1, this.ub2) * C[this.distribution]
    },
    mean () {
      return mean(this.datas)
    },
    u () {
      return distance(this.u_a, this.u_b)
    }
  },
  methods: {
    handleNChange (value) {
      this.n = Math.floor(value)
      while (this.datas.length < this.n) {
        this.datas.push(0)
      }
      while (this.datas.length > this.n) {
        this.datas.pop()
      }
    },
    handleDataChange (value, key) {
      let newData = parseFloat(value) || 0
      this.datas.splice(key, 1, newData)
      if (this.datas.length >= 5) {
        boxplot("boxplot", [...this.datas].sort((x, y) => x > y))
      }
    },
    handleUb1Change (value) {
      let val = parseFloat(value) || 0
      this.ub1 = val
    },
    handleUb2Change (value) {
      let val = parseFloat(value) || 0
      this.ub2 = val
    }
  }
}
</script>

<style>
h1 {
  padding: 1rem;
  padding-left: 0;
}
</style>
