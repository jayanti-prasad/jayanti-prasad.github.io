var newwindow;
function poptastic(url) {
    var newwindow;	 
    newwindow=window.open(url,'name','menubar=no,height=500,width=500,location=buggy,toolbar=no');
    if (window.focus) {newwindow.focus()}
} 
