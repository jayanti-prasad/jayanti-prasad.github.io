<!-- Original:  Jayanti Prasad  (prasad.jayanti@gmail.com) -->
<!-- Web Site:  http://www.ncra.tifr.res.in/~jayanti/ -->
<!-- Begin
function DmDelay() {
	var nu1 = document.dmdelay.low.value;
	var nu2 = document.dmdelay.high.value;
	var dm = document.dmdelay.dm.value;
	var coeff, f,x1,x2;
	coeff = 4148.80778;
	x1= Math.pow(parseFloat(nu1),-2.0);
	x2= Math.pow(parseFloat(nu2),-2.0)
	f = dm *(x1-x2) * coeff*1000.0;
	f = f.toPrecision(7); 
	document.dmdelay.total.value = +f ;
}
