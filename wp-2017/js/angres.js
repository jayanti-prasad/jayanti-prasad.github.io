<!-- Original:  Jayanti Prasad  (prasad.jayanti@gmail.com) -->
<!-- Web Site:  http://www.ncra.tifr.res.in/~jayanti/ -->
<!-- Begin
function AngRes() {
	var l, d;
	d = document.angres.baseline.value;
	if(document.angres.wave.options[0].selected == true) {
		l  = document.angres.lambda.value;
			}else {
		l  = 300.0/document.angres.lambda.value;
		}

	theta = (l/d) *(180.0*7.0/22.0) * 3600.00;
        theta = theta.toPrecision(7); 
	document.angres.total.value = "" + theta;
}
//  End -->
