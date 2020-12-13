Page({
  catch:function(){
    wx.request({
      url: 'http://api.heclouds.com/devices/642850877/datapoints',
      method: 'POST',
      header: {
        'api-key': 'TuqsxXg9j6ZxPUzg4kBiuD67cgI='
      },
      data: {
        'datastreams': [{
          'id': 'qqqqq',
          'datapoints': [{
            'value': "1"
          }]
        }]
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.log(err)
      }
    })
  },

  release:function(){
    wx.request({
      url: 'http://api.heclouds.com/devices/642850877/datapoints',
      method: 'POST',
      header: {
        'api-key': 'TuqsxXg9j6ZxPUzg4kBiuD67cgI='
      },
      data: {
        'datastreams': [{
          'id': 'qqqqq',
          'datapoints': [{
            'value': "0"
          }]
        }]
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.log(err)
      }
    })
  },

  forward:function(){
    wx.request({
      url: 'http://api.heclouds.com/devices/642850877/datapoints',
      method: 'POST',
      header: {
        'api-key': 'TuqsxXg9j6ZxPUzg4kBiuD67cgI='
      },
      data: {
        'datastreams': [{
          'id': 'qqqqq',
          'datapoints': [{
            'value': "2"
          }]
        }]
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.log(err)
      }
    })
  },

  backward:function(){
    wx.request({
      url: 'http://api.heclouds.com/devices/642850877/datapoints',
      method: 'POST',
      header: {
        'api-key': 'TuqsxXg9j6ZxPUzg4kBiuD67cgI='
      },
      data: {
        'datastreams': [{
          'id': 'qqqqq',
          'datapoints': [{
            'value': "3"
          }]
        }]
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.log(err)
      }
    })
  },

  left:function(){
    wx.request({
      url: 'http://api.heclouds.com/devices/642850877/datapoints',
      method: 'POST',
      header: {
        'api-key': 'TuqsxXg9j6ZxPUzg4kBiuD67cgI='
      },
      data: {
        'datastreams': [{
          'id': 'qqqqq',
          'datapoints': [{
            'value': "4"
          }]
        }]
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.log(err)
      }
    })
  },

  right:function(){
    wx.request({
      url: 'http://api.heclouds.com/devices/642850877/datapoints',
      method: 'POST',
      header: {
        'api-key': 'TuqsxXg9j6ZxPUzg4kBiuD67cgI='
      },
      data: {
        'datastreams': [{
          'id': 'qqqqq',
          'datapoints': [{
            'value': "5"
          }]
        }]
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.log(err)
      }
    })
  },

  Forward:function(){
    wx.request({
      url: 'http://api.heclouds.com/devices/642850877/datapoints',
      method: 'POST',
      header: {
        'api-key': 'TuqsxXg9j6ZxPUzg4kBiuD67cgI='
      },
      data: {
        'datastreams': [{
          'id': 'qqqqq',
          'datapoints': [{
            'value': "6"
          }]
        }]
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.log(err)
      }
    })
  }
 
})
