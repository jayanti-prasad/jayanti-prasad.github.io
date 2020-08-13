<!-- Original:  Jayanti Prasad  (prasad.jayanti@gmail.com) -->
<!-- Web Site:  http://www.ncra.tifr.res.in/~jayanti/ -->
<!-- Begin
function addChar(input, character) {
    if(input.value == null || input.value == "0")
	input.value = character
	else
	    input.value += character
		}
function cos(form) {
    form.display.value =  Math.cos(form.display.value).toPrecision(8);}
function sin(form) {
    form.display.value = Math.sin(form.display.value).toPrecision(8);}
function tan(form) {
    form.display.value = Math.tan(form.display.value).toPrecision(8);}
function acos(form) {
   form.display.value = Math.acos(form.display.value).toPrecision(8);}
function asin(form) {
   form.display.value = Math.asin(form.display.value).toPrecision(8);}
function atan(form) {
   form.display.value = Math.atan(form.display.value).toPrecision(8);}
function ran(form) {
   form.display.value = Math.random().toPrecision(8);}
function sqrt(form) {
    form.display.value = Math.sqrt(form.display.value).toPrecision(8);}
function sq(form) {
    form.display.value = Math.pow(form.display.value,2).toPrecision(8);}
function inver(form) {
    form.display.value = Math.pow(form.display.value,-1).toPrecision(8);}
function round(form) {
   form.display.value = Math.round(form.display.value,-1).toPrecision(8);}
function percent(form) {
   form.display.value = 0.01 * form.display.value.toPrecision(3);}
function abs(form) {
   form.display.value = Math.abs(form.display.value.toPrecision(8));}
 function ln(form) {
    form.display.value = Math.log(form.display.value).toPrecision(8);}
function exp(form) {
    form.display.value = Math.exp(form.display.value).toPrecision(8);}
function sqrt(form) {
    form.display.value = Math.sqrt(form.display.value).toPrecision(8);}
function deleteChar(input) {
    input.value = input.value.substring(0, input.value.length - 1)
}
function changeSign(input) {
    if(input.value.substring(0, 1) == "-")
	input.value = input.value.substring(1, input.value.length)
	else
	    input.value = "-" + input.value
		}
function compute(form)  {
  var str=form.display.value;
  var x;  
  n = str.length; 
  for (var i = 0; i < str.length; i++) { 
      var ch = str.substring(i, i+1)
         if (ch == "^") {
	   x = str.substring(0, i);
           y = str.substring(i+1, n);
           form.display.value=Math.pow(x,y); 
	 }
   } 
   
   form.display.value = eval(form.display.value).toPrecision(8)
}

function fact(form){
       var n = form.display.value;
       var i;
       var y =1;
       for(i=1; i <= n; i++){
          y = y * i; 
       }
       form.display.value = y; 
}

   
    function square(form)  {
    form.display.value = eval(form.display.value) *
	eval(form.display.value)}
function checkNum(str)  {
    for (var i = 0; i < str.length; i++) {
	var ch = str.substring(i, i+1)
	    if (ch < "0" || ch > "9") {
		if (ch != "/" && ch != "*" && ch != "+" && ch !=
		    "-" && ch != "." &&  ch != "E" && ch != "e" && ch!="^" && ch !="!"
		    && ch != "(" && ch!= ")") {
		    alert("invalid entry!")
		    return false
		}
	   }
    }
    return true
}
//  End -->

