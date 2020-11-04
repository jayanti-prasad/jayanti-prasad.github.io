<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title> Acknowledgement </title>
<link rel="stylesheet" href="mb.css">
<script type="text/javascript" src="mb.js"></script>
<script type="text/javascript" src="menu_bar.js"></script>
<link   rel="stylesheet" href="jpstyle.css">
</head>

<body onload="mbSet('mb2', 'mbh');">

<div class="container">
<script type="text/javascript"> menu_bar(); </script>
<h1> <a name="top_page"> Acknowledgement  </a>   </h1>
<hr>
<br><br><br>



<?php

function validate_email($email){
    list($username,$domaintld) = split("@",$email);
    $pieces = explode(".", $domaintld);
    $domain_end = array_pop($pieces);
    $domain_end1 = array_pop($pieces);
    
    if(strlen($username) > 4 && strlen($username) < 12){
      if($domaintld =! ""){
	return(0);
      }
      return(1);
    }

  }
    
$msg      = '<p> To see your suggestions click <a href="list_comemnt.html"> here</a>';

$title    = $_POST["title"];
$name     = $_POST["name"];
$email    = $_POST["email"];
$response = $_POST["response"];
$about    = $_POST["about"];
$comments = $_POST["comments"];

$cmments_size = str_word_count($comments,0); 
$name_length  = strlen($name); 
$email_length = strlen($email);
$about_size   = str_word_count($about,0); 

if ($name_length  > 4 && $name_length  < 16){
  if(validate_email($email) ==0){
    if($about_size < 20){
      if($cmments_size > 4 && $cmments_size < 100){
	
	/* show the entry !*/ 
	echo '<p>Your entries are as follows: </p>';
	echo 'Name:     '.$title; 
	echo ' '.$name;
	echo "<p> </p>";
	echo 'Email:    '. $email; 
	echo "<p> </p>";
	echo 'About:    '. $about; 
	echo "<p> </p>";
	echo 'Comments: '. $comments; 
        echo "<p> </p>";
        echo 'Email Visible: '. $response;
  
        $ip = getenv("REMOTE_ADDR") ; 
        $root = getenv("DOCUMENT_ROOT") ; 
        $ad = getenv("SERVER_ADMIN") ; 
	/* write entries in the file */ 

	$today = date("F j, Y, g:i a"); 
	$fp = fopen('list_comemnt.html', 'a+');
	fwrite($fp,"<li>\n");
	fwrite($fp,'<p>');
	fwrite($fp,$today);
	fwrite($fp,"</p>");
	fwrite($fp,"\n");
	fwrite($fp,'<p>Name: <b>');
	fwrite($fp, $name);
	fwrite($fp,"</b></p>");
	fwrite($fp,"\n");
	if($response=="yes"){
        fwrite($fp,'<p>Email:  <i>');
	fwrite($fp,$email);
	fwrite($fp,"</i></p>");
	fwrite($fp,"\n");
        }else{
        fwrite($fp,"<!");
        fwrite($fp,$email);
        fwrite($fp,">");
        }
        fwrite($fp,"<! IP Address:");
        fwrite($fp,$ip);
        fwrite($fp,"><p>");
        fwrite($fp,$about);
	fwrite($fp,"</p>");
	fwrite($fp,"\n");
	fwrite($fp,"\n");
	fwrite($fp,'<p>');
	fwrite($fp,$comments);
	fwrite($fp,"</p>\n");
	fwrite($fp,'<hr width="90%">');
	fwrite($fp,"\n\n\n");
	fclose($fp);

      }else{
         echo '<font color="red">Comment too long/short !</font>';
      }
    }  else{
      echo '<font color="red">About too long !</font>';
    }
  }else{
    echo '<font color="red">Email Invalid ! </font>';
  }
} else{
  echo '<font color="red"> Name too long/short  ! </font>';
}

?>

<?php 

if (isset($msg)) {
   print $msg;
 }
?> 

</div>


<div class="container">
 <p>
    <a href="http://validator.w3.org/check?uri=referer"><img
        src="http://www.w3.org/Icons/valid-html401"
        alt="Valid HTML 4.01 Transitional" height="31" width="88"></a>
</p>

<p><script language="javascript" type="text/javascript">
document.write("This document was last modified on "+document.lastModified);
</script>
</p>

</div>

</body>
</html>



