var getJSON = function(url, callback) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, true);
    xhr.responseType = 'json';
    xhr.onload = function() {
      var status = xhr.status;
      if (status === 200) {
        callback(null, xhr.response);
      } else {
        callback(status, xhr.response);
      }
    };
    xhr.send();
};

function getHello(){
  getJSON(url_api+"/api/hello",
  function(err, data) {
    if (err !== null) {
      alert('Something went wrong: ' + err);
    } else {
      document.getElementById("content").innerHTML += data.content;
    }
  });
}

function getEnvironnement(){
  getJSON(url_api+"/api/environment",
  function(err, data) {
    if (err !== null) {
      alert('Something went wrong: ' + err);
    } else {
      document.getElementById("env").innerHTML += data.env;
    }
  });
}
getHello();
getEnvironnement();
