<!-- Original:  Jayanti Prasad  (prasad.jayanti@gmail.com) -->
<!-- Web Site:  http://www.ncra.tifr.res.in/~jayanti/ -->
<!-- Begin
function eConvert(){ 	   
   var c = 3.0 * Math.pow(10.0,8.0);  	 
     var e = 1.6 * Math.pow(10.0,-19.0);
     var h = 6.626068 * Math.pow(10.0,-34.0);
     var k = 1.3806503 * Math.pow(10.0,-23.0);
     var y, z; 
     var  x  = document.getElementById("input").value;
       if(document.getElementById("first").options[0].selected == true) {
         y =  x;
     } if(document.getElementById("first").options[1].selected == true) {
         y  = k * x;
     } if(document.getElementById("first").options[2].selected == true) {
         y  = e * x;
     } if(document.getElementById("first").options[3].selected == true) {
         y  =  h * x;
     } if(document.getElementById("first").options[4].selected == true) {
         y  = x * Math.pow(c,2) ;
     } if(document.getElementById("second").options[0].selected == true) {
         z =  y;
     } if(document.getElementById("second").options[1].selected == true) {
         z  = y/k;
     } if(document.getElementById("second").options[2].selected == true) {
         z  = y/e ;
     } if(document.getElementById("second").options[3].selected == true) {
         z  =  y/h;
     } if(document.getElementById("second").options[4].selected == true) {
        z  = y * Math.pow(c,-2) ;
     } 
     E = z.toPrecision(8); 
     document.getElementById("output").value=E; 
  }
//  End -->

