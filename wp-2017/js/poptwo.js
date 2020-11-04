var newwindow;
function poptastic(url) {
    var newwindow;	 
    newwindow=window.open(url,'name','menubar=no,height=300,width=1000,location=buggy,toolbar=no');
    if (window.focus) {newwindow.focus()}
} 
