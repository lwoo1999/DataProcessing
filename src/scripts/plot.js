import Highcharts from "highcharts"
import HighchartsMore from 'highcharts/highcharts-more'
HighchartsMore(Highcharts)

export const boxplot = (id, datas) => {
  Highcharts.chart(id, {
    chart: {
        type: 'boxplot'
    },
    title: {
        text: '箱线图'
    },
    legend: {
        enabled: false
    },
    yAxis: {
        title: {
            text: ''
        }
    },
    plotOptions: {
        boxplot: {
            fillColor: '#F0F0E0',
            lineWidth: 2,
            medianColor: '#0C5DA5',
            medianWidth: 3,
            stemColor: '#A63400',
            stemDashStyle: 'dot',
            stemWidth: 1,
            whiskerColor: '#3D9200',
            whiskerLength: '20%',
            whiskerWidth: 3
        }
    },
    series: [{
        name: '',
        data: [
            datas
        ]
    }]
  })
}
