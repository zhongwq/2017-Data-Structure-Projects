(function() {
  var nodes, links, placeName, size, myCharts, option, links_resource, type;

  $(document).ready(function () {
    type = "all";
    makeMap(type);
    if ( typeof CKEDITOR !== 'undefined') {
      CKEDITOR.replace( 'js-post-content' );
    }

    $('#all').click(function () {
      type = "all";
      makeMap(type);
    });

    $('#car').click(function () {
      type = "car";
      makeMap(type);
    });

    $('#footWay').click(function () {
      type = "footWay";
      makeMap(type);
    });
  });

  function getIndex(name) {
    for (var i = 0; i < size; i++) {
      if (placeName[i] == name)
        return i;
    }
    return -1;
  }

  function getIndexByValue(name) {
    for (var i = 0; i < size; i++) {
      if (nodes[i].value == name)
        return i;
    }
    return -1;
  }

  function makeMap(type) {
    $.get('/api/allData/' + type).done(function (response) {
      nodes = response.places;
      links_resource = response.links;
      links = [];
      placeName = [];
      size = nodes.length;
      myCharts = echarts.init($("#main").get(0));

      var data = new Array();//建立距离数组

      for (var i = 0; i < size; i++) {
        data[i] = new Array();
        placeName[i] = nodes[i].name;
      }

      for (var i = 0; i < size; i++)
        for (var j = 0; j < size; j++)
          data[i][j] = 1000000;

      for (var i = 0; i < links_resource.length; i++) {
        var source = getIndex(links_resource[i].source);
        var target = getIndex(links_resource[i].target);
        var value = links_resource[i].value;
        links[i] = {
          source: source,
          target: target,
          value: value
        };
        data[source][target] = value;
        data[target][source] = value;
      }

      for (var i = 0; i < size; i++) {
        $("<option value='" + nodes.value + "'>" + nodes[i].value + "</option>").appendTo("#from");
        $("<option value='" + nodes.value + "'>" + nodes[i].value + "</option>").appendTo("#to");
      }

      option = {
        title: {
          text: 'Simple Map of Sysu',
          top: 'bottom',
          left: 'center'
        },
        tooltip: {
          show: false,
          formatter: '{a}:{b}:{c}:{d}'
        },
        animationEasingUpdate: 'quinticInOut',
        series: [{
          name: 'Map of Sysu',
          type: 'graph',
          layout: 'none',
          focusNodeAdjacency: true,
          edgeLabel: {
            normal: {
              show: true,
            }
          },
          lineStyle: {
            normal: {
              color: "black",
              width: 2
            }
          },
          label: {
            normal: {
              show: true,
              position: 'right',
              formatter: '{c}',
              textStyle: {
                color: 'black'
              }
            }
          },
          data: nodes,
          links: links
        }]
      };
      myCharts.setOption(option);

      var timer;//添加timer使得单击双击事件可以绑定在一个元素上使用
      myCharts.on("click", clickNode);

      function clickNode(params) {
        clearTimeout(timer);
        timer = setTimeout(function () {
          showInfo(params)
        }, 150);
      }

      function showInfo(params) {
        for (var i = 0; i < nodes.length; i++)
          if (nodes[i].name === params.name) {
            buildInfoModal(i);
            break;
          }
        if (params.dataType === "node")
          $("#infoModal").modal('show');
      }

      $("#button").on("click", searchWay);
      function searchWay() {
        //获取两点的序号
        var source = $("#from option:selected").text();
        var target = $("#to option:selected").text();
        if ((source == "") || (target == ""))
          return;
        var sourceIndex = getIndexByValue(source), targetIndex = getIndexByValue(target);

        //dijstra算法

        var v = 0, w = 0;
        var found = [], distance = [], temp = [];
        for (var i = 0; i <= size; i++) {
          found[i] = false;
          distance[i] = data[sourceIndex][i];
          temp[i] = sourceIndex;
        }
        found[sourceIndex] = true;
        distance[sourceIndex] = 0;
        temp[sourceIndex] = sourceIndex;
        for (var i = 0; i < size; i++) {
          var min = 1000000;
          for (w = 0; w < size; w++) {
            if (!found[w])
              if (distance[w] < min) {
                v = w;
                min = distance[w];
              }
          }
          found[v] = true;
          for (w = 0; w < size; w++) {
            if (!found[w])
              if (min + data[v][w] < distance[w]) {
                distance[w] = min + data[v][w];
                temp[w] = v;
              }
          }
        }
        if (distance[targetIndex] == 1000000) {
          $("#show").html("<h4 id='path_result'>找不到合适的线路!</h4>");
          return;
        }
        v = targetIndex;
        var path = [], pathString = "";
        while (temp[v] != v) {
          path.unshift(v);
          v = temp[v];
        }
        path.unshift(v);
        for (var i = 0; i < path.length; i++) {
          if (i != path.length - 1)
            pathString += placeName[path[i]] + "->";
          else
            pathString += placeName[path[i]];
        }

        $("#show").html("<h4 id='path_result'>Path: " + pathString + "</h4>\
                         <h4 id='path_length'>Length: "+ distance[targetIndex] +"米</h4>\
                        <button id='share' class='btn btn-success'>分享你的路线</button>");

        $("#share").click(function () {
          buildShareModal();
          $("#shareLinkModal").modal("show");
        });

        for (var j = 0; j < links.length; j++) {
          for (var i = 0; i < path.length - 1; i++) {
            if ((links[j].source == path[i] && links[j].target == path[i + 1]) || (links[j].target == path[i] && links[j].source == path[i + 1])) {
              links[j].lineStyle = {
                normal: {
                  color: "red",
                  width: 3
                },
              };
              break;
            } else {
              links[j].lineStyle = {
                normal: {
                  color: "black",
                },
              };
            }
          }
        }
        myCharts.setOption(option);
      }
    });
  }

  function buildInfoModal(i) {
    $('#infoModal .name span').text(nodes[i].value);
    $('#infoModal .introduce span').text(nodes[i].introduce);
    $('#infoModal .favourite').text(nodes[i].meta.favourite);
    $('#infoModal .point').text(nodes[i].point);
    $('#infoModal .comments').empty();
    if (nodes[i].comments.length == 0)
      $("#infoModal .comments").append("<p class='msg alert alert-info'>还没有评论哦！快点去留下你的心声吧！</p>");
    for (var j = 0; j < nodes[i].comments.length; j++) {
      var msg = "<div class='place-comment'>\
                                  <h4 class='comment-email'>Email: " + nodes[i].comments[j].email + "</h4>\
                                  <p class='comment-content'>" + nodes[i].comments[j].content + " </p></div><hr/>";
      $('#infoModal .comments').append(msg);
    }
    $('#favourite').unbind().click(function () {
      $.get('/api/place/favourite/' + nodes[i]._id, function (data) {
        $('#infoModal .favourite').text(data.meta.favourite);
        nodes[i] = data;
      });
    });
    $('#addComment').unbind().submit(function () {
      console.log("ds");
      $.post('/api/place/comment/' + nodes[i]._id, $("#addComment").serialize(), function (res) {
        nodes[i] = res.place;
        $('#infoModal .point').text(nodes[i].point);
        var msg = "<div class='place-comment'>\
                                  <h4 class='comment-email'>Email: " + res.newComment.email + "</h4>\
                                  <p class='comment-content'>" + res.newComment.content + " </p></div><hr/>";
        if (nodes[i].comments.length == 1)
          $('#infoModal .comments').empty();
        $('#infoModal .comments').append(msg);
        $('#addComment input').val("");
        $('#addComment textarea').val("");
      });
      return false;
    });
  }

  function buildShareModal() {
    $("#path").text($("#path_result").text());
    $('#shareLinkForm').unbind().submit(function () {
      var shareData =  {
        path: $('#path').text(),
        email: $('#post_email').val(),
        title: $('#post_title').val(),
        content: $('#js-post-content').val()
      };
      console.log(shareData);
      $.post('/api/post/add', shareData, function (res) {
        console.log(res);
        $('#shareLinkModal').modal('hide');
      });
      return false;
    });
  }
})();


