/**
 * Created by zhongwq on 2017/12/18.
 */
(function() {
  var posts;
  $(document).ready(function () {
    getData();
    $(".post-favourite").click(function(event) {
      var target = $(event.currentTarget).attr('post_id');
      for (var i = 0; i < posts.length; i++) {
        if (posts[i]._id == target) {
          $.get('/api/post/favourite/'+target, function(post) {
            posts[i] = post;
            $(event.currentTarget).find(".favourite").text(post.meta.favourites);
          });
          break;
        }
      }
    });

    $(".post-comments").click(function(event) {
      var target = $(event.currentTarget).attr('post_id');
      for (var i = 0; i < posts.length; i++) {
        if (posts[i]._id == target) {
          buildInfoModal(i);
          $('#infoModal').modal('show');
          break;
        }
      }
    });
  });

  function getData() {
    $.get('/api/post/all', function (res) {
      if (res.err) {
        console.log(res.err);
        return;
      }
      posts = res.posts;
      console.log("Get posts data successfully!");
    });
  };

  function buildInfoModal(i) {
    $('#infoModal .comments').empty();
    if (posts[i].comments.length == 0)
      $("#infoModal .comments").append("<p class='msg alert alert-info'>还没有评论哦！快点去留下你的心声吧！</p>");
    for (var j = 0; j < posts[i].comments.length; j++) {
      var msg = "<div class='place-comment'>\
                                  <h4 class='comment-email'>Email: " + posts[i].comments[j].email + "</h4>\
                                  <p class='comment-content'>" + posts[i].comments[j].content + " </p></div><hr/>";
      $('#infoModal .comments').append(msg);
    }
    $('#addComment').unbind().submit(function () {
      $.post('/api/post/comment/' + posts[i]._id, $("#addComment").serialize(), function (res) {
        posts[i] = res.post;
        var msg = "<div class='place-comment'>\
                                  <h4 class='comment-email'>Email: " + res.newComment.email + "</h4>\
                                  <p class='comment-content'>" + res.newComment.content + " </p></div><hr/>";
        if (posts[i].comments.length == 1)
          $('#infoModal .comments').empty();
        $('#infoModal .comments').append(msg);
        $('#addComment input').val("");
        $('#addComment textarea').val("");
      });
      return false;
    });
  }


})();
