
function keyPressed (ev) {
  if (!ev)
    ev = window.event;
  if (ev.which) {
    code = ev.which;
  } else if (ev.keyCode) {
    code = ev.keyCode;
  }
  var name;
  if (code == 37) {
    var el = document.getElementById("ABack");
    if (el != null) {
      location.href = el.href;
    }
  } else if (code == 39) {
    var el = document.getElementById("ANext");
    if (el != null) {
      location.href = el.href;
    }
  }
}
document.onkeydown = keyPressed;
