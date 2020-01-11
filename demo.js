function myFun() {
    var l = document.getElementById('original')
    var r = document.getElementById('translation')
    var lscrollTopMax = l.scrollHeight - l.clientHeight
    var rscrollTopMax = r.scrollHeight - r.clientHeight
    var scale = rscrollTopMax / lscrollTopMax
    r.scrollTop = l.scrollTop * scale
};