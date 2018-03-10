/**
 * Created by zhongwq on 2017/12/19.
 */
var validator = {
  username: {
    valid: false,
    errMsg: "用户名首位为字母,中间为下划线、数字或字母,长度为6-18",
    isValid: function (username) {
      this.valid = /^[a-zA-Z][a-zA-Z0-9_]{5,17}$/.test(username);
      return this.valid;
    }
  },
  password: {
    valid: false,
    errMsg: "密码长度必须大于等于6位",
    isValid: function (password) {
      this.valid = $('#password').val().length >= 6;
      return this.valid;
    }
  },
  ensure_password: {
    valid: false,
    errMsg: "两次输入的密码不一致",
    isValid: function (password) {
      this.valid = (password == $('#password').val());
      return this.valid;
    }
  },
  sid: {
    valid: false,
    errMsg: "学号为8位非零开头数字串",
    isValid: function(sid) {
      this.valid = /^[1-9]\d{7}$/.test(sid);
      return this.valid;
    }
  },
  phone: {
    valid: false,
    errMsg: "电话为11位非零开头数字串",
    isValid: function(phone) {
      this.valid = /^[1-9]\d{10}$/.test(phone);
      return this.valid;
    }
  },
  email: {
    valid: false,
    errMsg: "请输入合法邮箱",
    isValid: function(email) {
      this.valid = /^[a-zA-Z0-9_-]+@([a-zA-Z0-9_-]+\.)[a-zA-Z0-9_-]+/.test(email);
      return this.valid;
      //因为讲义上的邮箱规则不可以有数字，所以我自己写了一个邮箱规则
    }
  }
};

function showErr(msg) {
  var err = "<div class=\"error\"><div class=\"msg\">"+msg+"</div><div class=\"close\">X</div></div>";
  $(".errors").append(err);
}

function clearAllMsg() {
  $(".errors").empty();
}

$(document).ready(function() {
  $("input:not(.button)").blur(function() {
    if (!validator[this.id].isValid($(this).val())) {
      console.log(validator, validator[this.id].errMsg);
      showErr(validator[this.id].errMsg);
    }
  });

  $("#submit").click(function() {
    clearAllMsg();
    $("input:not(.button)").blur();
    for (var key in validator) {
      if (!$("#"+key).length > 0)
        continue;//判断该field是否存在
      if (!validator[key].valid)
        return false;
    }
    return true;
  });

  $("#reset").click(function() {
    clearAllMsg();
  });

  $(document).on("click", ".close", function() {
    $(this).parent().remove();
  });
});
