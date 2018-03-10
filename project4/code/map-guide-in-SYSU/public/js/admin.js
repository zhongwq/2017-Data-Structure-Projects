/**
 * Created by zhongwq on 2017/12/16.
 */
(function() {
  var nodes, links, placeName, size, myCharts, option, links_resource, type;

  $(document).ready(function () {
    type = "all";
    makeMap(type);

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

    $("#addPlace").click(function() {
      $("#addPlaceError").empty();
      $("#add_place_value").val("");
      $("#add_introduce").val("");
      $("#add_x").val("");
      $("#add_y").val("");
      $("#addPlaceModal").modal('show');
      $("#addPlaceForm").unbind().submit(function() {
        $.post('/api/place/add', $("#addPlaceForm").serialize(), function(res) {
          if (res && res.err) {
            $("#addPlaceError").append("<div class='alert alert-danger' role='alert'>"+res.err+"</div>");
            return;
          }
          makeMap(type);
          $("#addPlaceModal").modal('hide');
        });
        return false;
      });
    });

    $('#addLink').click(function() {
      $("#addLinkError").empty();
      $("#add_source").empty();
      $("#add_target").empty();
      for (var k = 0; k < nodes.length; k++) {
        $("<option value='" + nodes[k].name + "'>" + nodes[k].value + "</option>").appendTo("#add_source");
        $("<option value='" + nodes[k].name + "'>" + nodes[k].value + "</option>").appendTo("#add_target");
      }
      $("#add_value").val("");
      $('#addLinkModal').modal('show');
      $('#submitLink').unbind().click(function() {
        var data = {
          source: nodes[getIndexByValue($("#add_source option:selected").text())].name,
          target: nodes[getIndexByValue($("#add_target option:selected").text())].name,
          type: $("#add_type").val(),
          value: $("#add_value").val()
        };
        $.post('/api/link/add', data, function(res) {
          if (res && res.err) {
            $("#addLinkError").append("<div class='alert alert-danger' role='alert'>"+res.err+"</div>");
            return;
          }
          makeMap(type);
          $('#addLinkModal').modal('hide');
        });
        return false;
      });
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

      buildPlaceTable();

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

      buildLinkTable();

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
      myCharts.on("dblclick", changeInfo);

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

      function changeInfo(params) {
        clearTimeout(timer);
        for (var i = 0; i < nodes.length; i++)
          if (nodes[i].name === params.name) {
            buildEditInfoModal(i);
            break;
          }
        if (params.dataType === "node")
          $("#changeModal").modal('show');
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
        buildPlaceTable();
      });
    });
    $('#addComment').unbind().submit(function () {
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
        buildPlaceTable();
      });
      return false;
    });
  }

  function buildEditInfoModal(i) {
    $("#changePlaceError").empty();
    $('#changeModal #value').val(nodes[i].value);
    $('#changeModal #introduce').val(nodes[i].introduce);
    $('#changeModal #x').val(nodes[i].x);
    $('#changeModal #y').val(nodes[i].y);
    $('#changeInfo').unbind().submit(function () {
      $.post('/api/place/reset/' + nodes[i]._id, $("#changeInfo").serialize(), function (res) {
        if (res && res.err) {
          $("#changePlaceError").append("<div class='alert alert-danger' role='alert'>"+res.err+"</div>");
          return;
        }
        nodes[i] = res;
        $('#changeModal #value').val(nodes[i].value);
        $('#changeModal #introduce').val(nodes[i].introduce);
        $('#changeModal #x').val(nodes[i].x);
        $('#changeModal #y').val(nodes[i].y);
        makeMap(type);
        $("#changeModal").modal('hide')
      });
      return false;
    });
  }

  function buildLinkEditModal(i) {
    $("#changeLinkError").empty();
    $("#source").empty();
    $("#target").empty();
    for (var k = 0; k < nodes.length; k++) {
      $("<option value='" + nodes[k].name + "'>" + nodes[k].value + "</option>").appendTo("#source");
      $("<option value='" + nodes[k].name + "'>" + nodes[k].value + "</option>").appendTo("#target");
    }
    $('#linkEditModal #source').val(links_resource[i].source);
    $('#linkEditModal #target').val(links_resource[i].target);
    $('#linkEditModal #link_value').val(links_resource[i].value);
    $('#linkEditModal #type').val(links_resource[i].type ? links_resource[i].type : 0);
    $('#changeLinkInfo').unbind().submit(function () {
      var data = {
        source: nodes[getIndexByValue($("#source option:selected").text())].name,
        target: nodes[getIndexByValue($("#target option:selected").text())].name,
        type: $("#type").val(),
        value: $("#link_value").val()
      };
      $.post('/api/link/reset/' + links_resource[i]._id, data, function (res) {
        if (res && res.err) {
          $("#changeLinkError").append("<div class='alert alert-danger' role='alert'>"+res.err+"</div>");
          return;
        }
        makeMap(type);
        $("#linkEditModal").modal('hide');
      });
      return false;
    });
  }

  function buildPlaceTable() {
    $('.place-list tbody').empty();
    var size = nodes.length;
    for (var i = 0; i < size; i++) {
      var newTr = "<tr>\
          <td>" + nodes[i].value + "</td>\
          <td>" + nodes[i].point + "</td>\
          <td>" + nodes[i].meta.favourite + "</td>\
          <td>" + nodes[i].comments.length + "</td>\
          <td class='manage'><a class='look btn btn-sm btn-success'>查看</a><a class='edit btn btn-sm btn-info'>编辑</a><a class='delete btn btn-sm btn-danger'>删除</a></td>\
          </tr>";
      $('.place-list tbody').append(newTr);
    }
    var trs = $(".place-list tbody tr");
    for (var i = 0; i < size; i++) {
      (function () {
        var tmp = i;
        $(trs[tmp]).find('.look').click(function () {
          buildInfoModal(tmp);
          $("#infoModal").modal('show');
        });
        $(trs[tmp]).find('.edit').click(function () {
          buildEditInfoModal(tmp);
          $("#changeModal").modal('show');
        });
        $(trs[tmp]).find('.delete').click(function () {
          $.get('/api/place/delete/'+nodes[tmp]._id, function(res) {
            makeMap(type);
          });
        });
      })();
    }
  }

  function buildLinkTable() {
    $('.link-list tbody').empty();
    var size = links.length;
    for (var i = 0; i < size; i++) {
      var newTr = "<tr>\
            <td>" + links_resource[i].source + "</td>\
            <td>" + links_resource[i].target + "</td>\
            <td>" + ((links_resource[i].type)?"车行道":"人行道") + "</td>\
            <td class='manage'><a class='edit btn btn-sm btn-info'>编辑</a><a class='delete btn btn-sm btn-danger'>删除</a></td>\
            </tr>";
      $('.link-list tbody').append(newTr);
    }
    var trs = $(".link-list tbody tr");
    for (var i = 0; i < size; i++) {
      (function () {
        var tmp = i;
        $(trs[tmp]).find('.edit').click(function () {
          buildLinkEditModal(tmp);
          $("#linkEditModal").modal('show');
        });
        $(trs[tmp]).find('.delete').click(function () {
          $.get('/api/link/delete/'+links_resource[tmp]._id, function(res) {
            makeMap(type);
          });
        });
      })();
    }
  }
})();
